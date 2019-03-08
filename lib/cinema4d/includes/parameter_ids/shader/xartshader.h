#ifndef XARTSHADER_H__
#define XARTSHADER_H__

enum
{
	ARTSHADER_BUMP = 10000,
	ARTSHADER_SCALE = 10001,
	ARTSHADER_SCALE_U = 10002,
	ARTSHADER_SCALE_V = 10003,
	ARTSHADER_TEXTURE = 10004,
	ARTSHADER_ROTATE = 10005,
	ARTSHADER_SPACE = 10006,
		ARTSHADER_SPACE_WORLD = 0,
		ARTSHADER_SPACE_CAMERA = 1,
		ARTSHADER_SPACE_NORMAL = 2,
	ARTSHADER_LIGHT = 10007,
	ARTSHADER_SHADOW = 10008,
	ARTSHADER_SHADOW_TEXTURE = 10009,
	ARTSHADER_BACKFACE = 10010,
	ARTSHADER_BACKFACE_TEXTURE = 10011
};

#endif // XARTSHADER_H__
