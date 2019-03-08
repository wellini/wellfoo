#ifndef MSHADOW_CATCHER_H__
#define MSHADOW_CATCHER_H__

enum
{
	SHADOWCATCHER_MATERIALPROPERTIES									= 1000,
	
	SHADOWCATCHER_REFLECTION_COLOR										= 2000,
	
	SHADOWCATCHER_SHADOWS_GROUP												= 3000,	// Group
	SHADOWCATCHER_SHADOWS															= 3001,
	SHADOWCATCHER_SHADOW_COLOR												= 3002,
	SHADOWCATCHER_SHADOW_STRENGTH											= 3003,
	SHADOWCATCHER_SHADOW_LIGHTING											= 3004,
	
	SHADOWCATCHER_REFLECTIONS_GROUP										= 4000,	// Group
	SHADOWCATCHER_REFLECTIONS													= 4001,
	SHADOWCATCHER_REFLECTIONS_STRENGTH								= 4002,
	SHADOWCATCHER_REFLECTIONS_MASK										= 4003,
};

#endif // MSHADOW_CATCHER_H__
