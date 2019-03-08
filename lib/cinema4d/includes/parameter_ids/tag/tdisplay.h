#ifndef TDISPLAY_H__
#define TDISPLAY_H__

enum
{
	DISPLAYTAG_SDISPLAYMODE					= 1000, // LONG
		DISPLAYTAG_SDISPLAY_GOURAUD					= 0,
		DISPLAYTAG_SDISPLAY_GOURAUD_WIRE		= 1,
		DISPLAYTAG_SDISPLAY_QUICK						= 2,
		DISPLAYTAG_SDISPLAY_QUICK_WIRE			= 3,
		DISPLAYTAG_SDISPLAY_FLAT_WIRE				= 4,
		DISPLAYTAG_SDISPLAY_HIDDENLINE			= 5,
		DISPLAYTAG_SDISPLAY_NOSHADING				= 6,
		DISPLAYTAG_SDISPLAY_FLAT						= 7,

	DISPLAYTAG_BACKFACECULLING			= 1001, // BOOL
	DISPLAYTAG_TEXTURES							= 1002, // BOOL
	DISPLAYTAG_REFLECTIONS					= 1038031, // BOOL
	DISPLAYTAG_TESSELLATION					= 1038032, // BOOL
	DISPLAYTAG_LEVELOFDETAIL				= 1004, // REAL
	DISPLAYTAG_VISIBILITY						= 1006, // REAL

	DISPLAYTAG_AFFECT_DISPLAYMODE			= 1007, // BOOL
	DISPLAYTAG_AFFECT_BACKFACECULLING = 1008, // BOOL
	DISPLAYTAG_AFFECT_TEXTURES				= 1009, // BOOL
	DISPLAYTAG_AFFECT_REFLECTIONS			= 1038033, // BOOL
	DISPLAYTAG_AFFECT_TESSELLATION		= 1038034, // BOOL
	DISPLAYTAG_AFFECT_LEVELOFDETAIL		= 1010, // BOOL
	DISPLAYTAG_AFFECT_VISIBILITY			= 1012,  // BOOL
	DISPLAYTAG_WDISPLAYMODE						= 1013, // LONG
		DISPLAYTAG_WDISPLAY_WIREFRAME				= 0,
		DISPLAYTAG_WDISPLAY_ISOPARMS				= 1,
		DISPLAYTAG_WDISPLAY_BOX							= 2,
		DISPLAYTAG_WDISPLAY_SKELETON				= 3,

	DISPLAYTAG_AFFECT_HQ_OGL					= 1014, // BOOL
	DISPLAYTAG_HQ_OGL									= 1015, // BOOL

	ONION_ONLY_RANGE    = 10000, // bool
	ONION_FROM          = 10001, // basetime
	ONION_TO            = 10002, // basetime

	ONION_FRAMES_BEFORE = 10003, // long
	ONION_FRAMES_AFTER  = 10004, // long
	ONION_FRAMES_STEP   = 10005, // long

	ONION_KEYS_BEFORE   = 10006, // long
	ONION_KEYS_AFTER    = 10007, // long

	ONION_CUSTOM        = 10009, // string

	ONION_SCALE         = 10010, // real
	ONION_PSIZE         = 10011, // long

	ONION_COL_FRAMES_BEFORE = 20000, // vector
	ONION_COL_FRAMES_AFTER  = 20001, // vector
	ONION_COL_KEYS_BEFORE   = 20002, // vector
	ONION_COL_KEYS_AFTER    = 20003, // vector
	ONION_COL_CUSTOM        = 20004, // vector

	ONION_MODE              = 30000, // long
		ONION_MODE_OBJECT   = 1,
		ONION_MODE_POINT    = 2,
		ONION_MODE_AXIS     = 3,
		ONION_MODE_TRAIL    = 4,
		ONION_MODE_MTRAIL   = 5,
		ONION_MODE_VELOCITY = 6,
		ONION_MODE_BONES    = 7,

	ONION_CACHE         = 30002, // bool
	ONION_CALCULATE     = 30003, // button
	ONION_DELCACHE      = 30004, // button
	ONION_CACHE_INFO1   = 30005, // button

	ONION_USE           = 30006, // bool
	ONION_USE_KEYS      = 30007, // bool
	ONION_USE_CUSTOM    = 30008, // bool

	ONION_DISPLAYMODE   = 30009, // long
		ONION_DISPLAY_GOURAUD				= 0,
		ONION_DISPLAY_GOURAUD_WIRE	= 7,
		ONION_DISPLAY_QUICK					= 1,
		ONION_DISPLAY_QUICK_WIRE		= 9,
		ONION_DISPLAY_FLAT_WIRE			= 11,
		ONION_DISPLAY_HIDDENLINE		= 14,
		ONION_DISPLAY_NOSHADING			= 2,
		ONION_DISPLAY_FLAT					= 1100,
	ONION_XRAY          = 30010, // bool

	ID_ONION_GROUP      = 40000,


	DISPLAYTAG_
};

#endif // TDISPLAY_H__

