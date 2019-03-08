/////////////////////////////////////////////////////////////
// Render Host Windows                                     //
/////////////////////////////////////////////////////////////
// (c) 1989-2009 MAXON Computer GmbH, all rights reserved  //
/////////////////////////////////////////////////////////////
// this basic code demonstrates how to use the TCP/IP      //
// render connection to CINEMA 4D                          //
/////////////////////////////////////////////////////////////

#include <tchar.h>
#include <windows.h>
#include <vfw.h>
#include "resource.h"
#include "c4d_network.h"
#include "c4d_renderconnection.h"

#define MAX_LOADSTRING 100

// Global Variables
HINSTANCE hInst;													// current instance
TCHAR gSzTitle[MAX_LOADSTRING];						// The title bar text
TCHAR gSzWindowClass[MAX_LOADSTRING];			// the main window class name
WCHAR gFilename[512], gFilenameExecutable[512];
CRITICAL_SECTION semaphore;

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
MSG msg;
void CallCommand(melange::Int32 type, const melange::Filename &filename);
void FreeRenderhost();

// this is a simple bitmap class used to display raw RGB image data
class WinBitmap
{
	friend void WinImageUpdate(void *userdata, melange::Int32 xpos, melange::Int32 ypos, melange::Int32 xcnt, melange::ColorResolution bpp, melange::UChar *rgba_data);
	friend void ClearBitmap();
	friend long GetBitmapWidth();

private:
	HDC dc;
	void *hd, *ohd, *Bits;
	long xres, yres;
	BITMAPINFO bih;

public:
	WinBitmap()
	{
		dc = nullptr;
		hd = nullptr;
		ohd = nullptr;
		Bits = nullptr;
	}
	~WinBitmap()
	{
		Free();
	}

	// free the content of the bitmap
	void Free()
	{
		EnterCriticalSection(&semaphore);

		if (hd)
		{
			SelectObject((HDC)dc, ohd);
			DeleteObject(hd);
		}
		if (dc)
			DeleteDC(dc);

		dc = nullptr;
		hd = ohd = nullptr;

		xres = yres = 0;

		LeaveCriticalSection(&semaphore);
	}

	// initialize the bitmap with a given x/y resolution
	bool Init(long x_resolution, long y_resolution)
	{
		EnterCriticalSection(&semaphore);

		Free();
		xres = x_resolution;
		yres = y_resolution;

		memset(&bih, 0, sizeof(bih));
		bih.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bih.bmiHeader.biWidth = x_resolution;
		bih.bmiHeader.biHeight = y_resolution;
		bih.bmiHeader.biPlanes = 1;
		bih.bmiHeader.biBitCount = 24;
		bih.bmiHeader.biCompression = BI_RGB;
		bih.bmiHeader.biSizeImage = y_resolution*x_resolution*3;
		bih.bmiHeader.biXPelsPerMeter = 999;
		bih.bmiHeader.biYPelsPerMeter = 999;
		bih.bmiHeader.biClrUsed = 0;
		bih.bmiHeader.biClrImportant = 0;

		if (!dc)
			dc = CreateCompatibleDC(nullptr);

		hd = CreateDIBSection((HDC)dc, &bih, DIB_PAL_COLORS, (void**) &Bits, nullptr, 0);
		if (hd)
		{
			ohd = SelectObject((HDC)dc, hd);
			DeleteObject(ohd);
		}

		memset(Bits, 0, bih.bmiHeader.biSizeImage);

		LeaveCriticalSection(&semaphore);

		return true;
	}

	// draw the bitmap centered into a window; paint borders gray
	void Draw(HWND win)
	{
		EnterCriticalSection(&semaphore);

		HDC wdc = GetDC(win);

		RECT rc;
		GetClientRect(win, &rc);

		melange::Int32 ox = (rc.right-xres)/2;
		melange::Int32 oy = (rc.bottom-yres)/2;

		if (Bits && xres)
			BitBlt(wdc, ox, oy, xres, yres, dc, 0, 0, SRCCOPY);

		HBRUSH brush = CreateSolidBrush(RGB(127, 127, 127));

		// right area
		rc.left = ox+xres;
		FillRect(wdc, &rc, brush);

		// left area
		rc.left = 0;
		rc.right = ox;
		FillRect(wdc, &rc, brush);

		// bottom area
		rc.left = ox;
		rc.right = ox+xres;
		rc.top = oy+yres;
		FillRect(wdc, &rc, brush);

		// top area
		rc.top = 0;
		rc.bottom = oy;
		FillRect(wdc, &rc, brush);

		DeleteObject(brush);

		ReleaseDC(win, wdc);

		LeaveCriticalSection(&semaphore);
	}
};

// simple Windows file chooser
static bool FileSelect(LPWSTR filename, melange::Int32 title)
{
#define MAXFILENAME 512

	bool	ret;
	long  i;

	OPENFILENAMEW localdata, *pofn = &localdata;

	TCHAR szFileName[MAXFILENAME];
	TCHAR szFileTitle[MAXFILENAME];
	TCHAR szInitialDir[MAXFILENAME];
	TCHAR szTitle[MAXFILENAME];

	memset(szFileName, 0, MAXFILENAME);
	memset(szFileTitle, 0, MAXFILENAME);
	memset(&localdata, 0, sizeof(localdata));
	memset(szInitialDir, 0, MAXFILENAME);
	wcscpy(szTitle,title?(L"Select a melange file..."):(L"Select CINEMA 4D executable..."));

	//////////////////////////////////////////////////////////////////////////

	pofn->lStructSize = sizeof(localdata);

	pofn->hwndOwner	= msg.hwnd;

	pofn->lpstrFile = (LPWSTR)szFileName;
	pofn->nMaxFile	= MAXFILENAME;
	pofn->lpstrFileTitle = (LPWSTR)szFileTitle;
	pofn->nMaxFileTitle = MAXFILENAME;
	pofn->Flags = OFN_EXPLORER|OFN_ENABLESIZING;

	wcscpy(szInitialDir, filename);

	ret = false;

	pofn->lpstrTitle = (LPCWSTR)szTitle;
	pofn->Flags |= OFN_HIDEREADONLY | OFN_FILEMUSTEXIST;

	for (i = 0; i < 2; i++)
	{
		if (GetOpenFileNameW(pofn))
		{
			pofn->lpstrFile[255] = 0;
			wcscpy(filename, pofn->lpstrFile);
			ret = true;
			i = 99;
		}
		else
		{
			melange::Int32 err = CommDlgExtendedError();
			if (err == FNERR_INVALIDFILENAME)
			{
				szFileName[0] = 0;
				szInitialDir[0] = 0;
			}
			else
				i = 99;
		}
	}

	return ret;
}

void ShowMessage(melange::Int32 id)
{
	if (id == 0)
		MessageBoxW(nullptr,L"Could not establish communication with render server. Make sure it is running!",L"Render Connection",MB_APPLMODAL | MB_SETFOREGROUND);
	else if (id == 2)
		MessageBoxW(nullptr,L"Could not start render server!",L"Render Connection",MB_APPLMODAL | MB_SETFOREGROUND);
}

// the global bitmap for this example
WinBitmap *global_bmp = nullptr;

// clear the bitmap
void ClearBitmap()
{
	if (!global_bmp || !global_bmp->Bits)
		return;

	memset(global_bmp->Bits, 0, global_bmp->xres*global_bmp->yres*3);
}

static long ConvFtoL(float f)
{
	f *= 256.0;
	if (f < 0.0)
		return 0;
	else if (f > 255.0)
		return 255;

	return (long)f;
}

// update the image with RGB data
void WinImageUpdate(void *userdata, melange::Int32 xpos, melange::Int32 ypos, melange::Int32 xcnt, melange::ColorResolution bpp, melange::UChar *rgba_data)
{
	// a few safety checks
	if (!global_bmp || !global_bmp->Bits || ypos<0 || ypos >= global_bmp->yres)
		return;

	melange::UChar *adr = (melange::UChar*)global_bmp->Bits + (global_bmp->yres-1-ypos) * global_bmp->xres * 3;

	if (xpos+xcnt > global_bmp->xres)
		xcnt = global_bmp->xres-xpos;

	melange::UChar *dst = adr+xpos*3;

	if (bpp == 4) // floating point data is streamed
	{
		float *src = (float*)rgba_data;
		while (xcnt-->0)
		{
			dst[0] = ConvFtoL(src[2]);
			dst[1] = ConvFtoL(src[1]);
			dst[2] = ConvFtoL(src[0]);
			src += 4;
			dst += 3;
		}
	}
	else
	{
		melange::UChar *src = rgba_data;
		while (xcnt-->0)
		{
			dst[0] = src[2];
			dst[1] = src[1];
			dst[2] = src[0];
			src += 4;
			dst += 3;
		}
	}
}

// start a window redraw
void RedrawWindow()
{
	WndProc(msg.hwnd, WM_PAINT, 0, 0);
}

void ChangeTitle(const melange::String &title)
{
	melange::UInt16 t[1024];
	title.GetUcBlockNull(t, 1024);
	SetWindowTextW(msg.hwnd, (LPCWSTR)t);
}

// windows main function
int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	HACCEL hAccelTable;

	// initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, gSzTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_RENDERHOSTWIN, gSzWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// initialize semaphore - needed because of threading
	InitializeCriticalSection(&semaphore);

	// initialize display bitmap with resolution 640x480
	global_bmp = new WinBitmap;
	if (!global_bmp || !global_bmp->Init(640, 480))
		return false;

	// Perform application initialization
	if (!InitInstance (hInstance, nCmdShow))
		return false;

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_RENDERHOSTWIN));

	// init MainThreadPtr and Timer!!
	melange::GeInitThreads();

	// initialize melange network code
	melange::GeIpInitNetwork();

	// Main message loop
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	// free threads that are still running
	FreeRenderhost();

	// free global bitmap
	delete(global_bmp);

	// free melange network & Thread code
	melange::GeIpCloseNetwork();

	melange::GeEndThreads();

	// free semaphore
	DeleteCriticalSection(&semaphore);

	return (int) msg.wParam;
}

// standard windows UI code is following...

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= nullptr;
	wcex.hCursor		= LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_RENDERHOSTWIN);
	wcex.lpszClassName	= gSzWindowClass;
	wcex.hIconSm		= nullptr;

	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // Store instance handle in our global variable
	hWnd = CreateWindow(gSzWindowClass, gSzTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, 700, 600, nullptr, nullptr, hInstance, nullptr);
	if (!hWnd)
		return false;

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return true;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
		case WM_COMMAND:
			wmId    = LOWORD(wParam);
			wmEvent = HIWORD(wParam);
			// Parse the menu selections:
			switch (wmId)
			{
				case ID_FILE_TEST:
					CallCommand(0, nullptr);
					break;
				case ID_FILE_IMPORT:
					if (FileSelect(gFilename, 1))
						CallCommand(5, melange::Filename((melange::UInt16*)gFilename));
					break;
				case ID_FILE_IMPORT_IES:
					if (FileSelect(gFilename, (melange::Int32)1))
						CallCommand(6, melange::Filename((melange::UInt16*)gFilename));
					break;
				case ID_FILE_SHUTDOWN:
					CallCommand(1, nullptr);
					break;
				case ID_FILE_LOAD:
					if (FileSelect(gFilename, 1))
						CallCommand(2, melange::Filename((melange::UInt16*)gFilename));
					break;
				case ID_FILE_STARTUP:
					if (FileSelect(gFilenameExecutable, 0))
						CallCommand(3, melange::Filename((melange::UInt16*)gFilenameExecutable));
					break;
				case ID_FILE_STOP:
					CallCommand(4, nullptr);
					break;
				case IDM_EXIT:
					DestroyWindow(hWnd);
					break;
				default:
					return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;

		case WM_ERASEBKGND:
			return 1;

		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			if (global_bmp)
				global_bmp->Draw(hWnd);
			EndPaint(hWnd, &ps);
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
