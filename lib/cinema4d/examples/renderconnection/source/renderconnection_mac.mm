/////////////////////////////////////////////////////////////
// Render Connection Macintosh                             //
/////////////////////////////////////////////////////////////
// (c) 1989-2009 MAXON Computer GmbH, all rights reserved  //
/////////////////////////////////////////////////////////////
// this basic code demonstrates how to use the TCP/IP      //
// render connection to CINEMA 4D                          //
/////////////////////////////////////////////////////////////

#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>
#import <Carbon/Carbon.h>
#import	"MenuHandler.h"

#import "renderconnection_mac.h"
#include "c4d_baselink.h"
#include "c4d_network.h"
#include "c4d_renderconnection.h"
#include "macbitmap.h"

using namespace melange;

void FreeRenderhost();
static void ShowMessage(const String &s);
void ClearBitmap();
void WinImageUpdate(void *userdata, melange::Int32 xpos, melange::Int32 ypos, melange::Int32 xcnt, melange::ColorResolution bpp, UChar *rgb_data);
void RedrawWindow();
void ShowMessage(Int32 id);
Bool FileSelect(Filename &name, Int32 val_title);
void SetTitle(NSSavePanel *panel, const String &title);
void ChangeTitle(const String &title);

// global variables for this example
MacBitmap *global_bmp=NULL;
NSView *global_view=NULL;

int main(int argc, const char *argv[])
{
	bool res=FALSE;

	// ignore SIGPIPE
	signal(SIGPIPE,SIG_IGN);

	// initialize display bitmap with resolution 640x480
	global_bmp = new MacBitmap;
	if (!global_bmp || !global_bmp->Init(640,480))
		return FALSE;

	// init MainThreadPtr and Timer!!
	melange::GeInitThreads();

	// initialize melange network code
	melange::GeIpInitNetwork();

	res=NSApplicationMain(argc, argv);

	// free threads that are still running
	FreeRenderhost();

	// free global bitmap
	delete(global_bmp);

	// free melange network & Thread code
	melange::GeIpCloseNetwork();

	melange::GeEndThreads();

	return res;
}

void ClearBitmap()
{
	if ( global_bmp )
		global_bmp->Clear();
}

// update the image with RGB data
void WinImageUpdate( void *userdata, melange::Int32 xpos, melange::Int32 ypos, melange::Int32 xcnt, melange::ColorResolution bpp, UChar *rgb_data )
{
	if ( global_bmp )
		global_bmp->Update( userdata, xpos, ypos, xcnt, bpp, rgb_data );
}

void RedrawWindow()
{
	if (!global_view)
		return;
	[global_view setNeedsDisplay:YES];
}

void ChangeTitle(const String &title)
{
	if ( global_view )
	{
		CFStringRef	cf_title;

		cf_title = StringToCF( title );
		if ( cf_title )
		{
			[[global_view window] setTitle:(NSString *) cf_title];
			CFRelease( cf_title );
		}
	}
}


// Get the directory and name part from a Filename
static void	GetDirectoryAndName( const Filename &fn, NSString **directory, NSString **name )
{
	*directory = NULL;
	*name = NULL;

	if ( fn.Content())
	{
		CFStringRef	full_path;
		BOOL	is_directory;

		full_path = StringToCF( fn.GetString());

		if ( [[NSFileManager defaultManager] fileExistsAtPath:(NSString *) full_path isDirectory:&is_directory] && is_directory )
		{
			*directory = (NSString *) full_path;									// only use the directory and leave the name part empty
			full_path = NULL;
		}
		else																										// Filename is not an existing directory
		{
			*directory = (NSString *) StringToCF( fn.GetDirectory().GetString());	// get the directory part (which most likely exists)
			*name = (NSString *) StringToCF( fn.GetFileString());	// get the file name part (which may not exist)
		}

		if ( full_path )
			CFRelease( full_path );
	}
}

// Set an open/save panel's title
void SetTitle( NSSavePanel *panel, const String &title )
{
	CFStringRef	cf_title;
	cf_title = StringToCF( title );
	if ( cf_title )
	{
		[panel setTitle:(NSString *) cf_title];
		CFRelease( cf_title );
	}
}

Bool FileSelect(Filename &name, Int32 val_title)
{
	String title;
	if (val_title==1)
		title=String("Select a melange file...");
	else
		title=String("Select CINEMA 4D executable...");

	NSOpenPanel	*panel;
	NSInteger		button = NSModalResponseCancel;

	panel = [NSOpenPanel openPanel];													// create an open panel
	if ( panel )
	{
		NSString		*directory;
		NSString		*file_name;

		[panel setCanChooseFiles:YES];
		[panel setCanChooseDirectories:NO];
		[panel setAllowsMultipleSelection:NO];

		SetTitle( panel, title );																// set the title (if any)
		GetDirectoryAndName( name, &directory, &file_name );		// get directory and name from Filename
    button = [panel runModal]; //:(NSString *)directory file:(NSString *)file_name types:NULL];
		[file_name release];
		[directory release];
	}

	if (button == NSModalResponseOK)
	{
		name = CFToString((CFStringRef)[[[panel URLs] objectAtIndex:0] path]);
		return TRUE;
	}
	return FALSE;
}

void ShowMessage(Int32 id)
{
	if (id==0)
		ShowMessage("Could not establish communication with render server. Make sure it is running!");
	else if (id==2)
		ShowMessage("Could not start render server!");
}

static void ShowMessage(const String &s)
{
	NSAutoreleasePool	*pool;

	pool = [[NSAutoreleasePool alloc] init];									// create autorelease pool to make sure we don't leak memory if we are being called on a non-main thread
	if ( pool )
	{
		NSAlert *alert;
		CFStringRef explanation, progname;
		CFStringRef	defaultText;
		NSInteger	button;

		defaultText = StringToCF( String( "OK" ));						// if we have the wrong or no resources IDS_OK might be empty
		explanation = StringToCF( s );
		progname = StringToCF( String("RenderConnection") );

		alert = [[NSAlert alloc] init];
		if ( alert )
		{
			[alert setAlertStyle:NSWarningAlertStyle];

			if ( defaultText )
				[alert addButtonWithTitle:(NSString *)defaultText];

			[alert setMessageText:(NSString *)progname];
			[alert setInformativeText:(NSString *)explanation];

			button = [alert runModal];
			[alert release];
		}

		if ( progname )
			CFRelease( progname );
		if ( explanation )
			CFRelease( explanation );
		if ( defaultText )
			CFRelease( defaultText);

		[pool release];
	}
}

// helper code for string conversion
void	CFToString( const CFStringRef in, String *out )
{
	if ( in )
	{
		UInt16 stack_buf[4096];
		UInt16	*buf;
		CFRange range;
		Int32 len;

		buf = stack_buf;
		len = (Int32) CFStringGetLength( in );

		if ( len > 4096 )																				// stack buffer too small?
		{
			buf = (UInt16 *) NewMem(UInt16, len);
			if ( buf == NULL )																		// failed?
			{
				buf = stack_buf;
				len = 4096;
			}
		}

		range.location = 0;
		range.length = (CFIndex) len;

		CFStringGetCharacters( in, range, (::UniChar *) buf );
		out->SetUcBlock( buf, len );														// copy unicode block

		if ( buf != stack_buf )
			DeleteMem( buf );
	}
}

String CFToString( CFStringRef in )
{
	String out;

	CFToString( in, &out );
	return out;
}

CFStringRef StringToCF( const String &in )
{
	const UInt16	*buf_ptr;
	Int32	length;
	UInt16	dummy=0;

	length = in.GetDataPtr( &buf_ptr );												// get string length and buffer pointer
	if (( length == 0 ) || ( buf_ptr == NULL ))								// empty string? Some safety code due to QuickTime crashes ...
	{
		buf_ptr = &dummy;																				// use a dummy pointer, CFStringCreateWithCharacters() might crash otherwise
		length = 0;																							// make sure this is null
	}
	return CFStringCreateWithCharacters( kCFAllocatorDefault, buf_ptr, length );
}

