/////////////////////////////////////////////////////////////
// MELANGE SDK                                             //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef REFLECTIONGUI_H__
#define REFLECTIONGUI_H__

#include "private_reflectionlayers.h"
#include "c4d_system.h"

namespace melange
{
#pragma pack (push, 8)

class XReflectionLayer;
class XReflectionLayers;
class iXRLayersDataType;

#define RESOURCE_SYMBOL_XR_LAYERS	"REFLECTION_LAYERS"

#define DESC_LAYERS_TRANSPARENCY 1000
#define CUSTOMDATA_XR_LAYERS		 1031184
#define CUSTOMGUI_XR_LAYERS			 1031185

class XRBaseData
{
};

/// @markInternal
class iXRLayersDataType : public iCustomDataType<XRBaseData>
{
public:
	XReflectionLayers	m_ReflectionLayers;
	Bool							m_bTabManager;
	Bool							m_bUpdated;
	Bool							m_bLoaded;
	Int32							m_nLastID;

	iXRLayersDataType();
	virtual ~iXRLayersDataType();

	Int32	GetNextID() { return ++m_nLastID; }
};

#pragma pack (pop)
}

#endif	// REFLECTIONGUI_H__
