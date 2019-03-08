/////////////////////////////////////////////////////////////
// MELANGE SDK                                             //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef REFLECTIONMAIN_H__
#define REFLECTIONMAIN_H__

#include "b3d_file.h"
#include "c4d_misc/datastructures/basearray.h"

namespace melange
{
#pragma pack (push, 8)

#define STATIC_FLAG_DUMMY															(1 << 0)
#define STATIC_FLAG_JOINBEGIN													(1 << 1)
#define STATIC_FLAG_JOINEND														(1 << 2)
#define STATIC_FLAG_JOINENDSCALE											(1 << 3)
#define STATIC_FLAG_NOTEXT														(1 << 4)
#define STATIC_FLAG_NEWLINE														(1 << 5)
#define STATIC_FLAG_SCALEH														(1 << 6)

#define STATICTEXT_DUMMY															2400
#define STATICTEXT_JOINBEGIN													2401
#define STATICTEXT_JOINEND														2402
#define STATICTEXT_JOINENDSCALE												2403
#define STATICTEXT_NOTEXT															2405
#define STATICTEXT_BORDER															2406

class XReflectionLayer;
class iXRLayersDataType;

class BaseContainer;
class BaseShader;
class ReflectionLayer;
class Material;
class CTrack;

class MaterialReflections
{
public:
	// --- Material Data
	Material*							m_pMaterial;
	BaseContainer*				m_pData;

	// --- Render Data
	iXRLayersDataType*		m_pLayerData;

	// --- Save State
	Bool									m_bSaveStateReflection;
	Bool									m_bSaveStateSpecular;

	// --- Render Optimization
	Float									m_fGlobalReflection;
	Float									m_fGlobalSpecular;
	Bool									m_bValidDDUV;

	// --- Name
	String								m_szLayerName;

public:
	MaterialReflections();
	virtual ~MaterialReflections();

	// --- Init
	void									Init(Material *pMaterial);

 	// --- ID Functions
 	Int32									ConvertToID(Int32 nDescID);
 	Int32									ConvertToLayerID(Int32 nDescID);
 	Int32									ConvertToDataID(Int32 nDescID);
 	XReflectionLayer*			GetLayer(Int32 nLayerID);

 	// --- Copy Animation Data
 	void									ScaleAnimationTrack(CTrack *pTrack, Float fScale);
 	void									CopyAnimationData(Int32 nSourceID, Int32 nTargetID, Bool bQuick = false, Bool bScale = false, Float fScale = 1.0);

	// --- Legacy Support
 	void									RemapOldData(BaseContainer *pData, bool bOnLoad, Int32 nFileVersion);
 	void									FindPrimaryLayers(BaseContainer *pData, Int32 &nLayerReflection, Int32 &nLayerSpecular);
	void									RebuildOldData(BaseContainer *pData, bool bQuick);
	void									RebuildOldDataRestore(BaseContainer *pData);

	// --- API Access
	ReflectionLayer*			SDKAddReflectionLayer();
	ReflectionLayer*			SDKGetReflectionLayerID(Int32 nID);
	ReflectionLayer*			SDKGetReflectionLayerIndex(Int32 nIndex);
	ReflectionLayer*			SDKGetReflectionLayerTrans();
	Int32									SDKGetReflectionLayerCount();
	void									SDKRemoveReflectionLayerID(Int32 nID);
	void									SDKRemoveReflectionLayerIndex(Int32 nIndex);
	void									SDKRemoveReflectionAllLayers();
	void									SDKGetAllReflectionShaders(BaseArray<BaseShader*> &ShaderList);
	void									SDKGetReflectionPrimaryLayers(Int32 &nLayerReflection, Int32 &nLayerSpecular);

 	// ---
 	Bool									GetParameter(const DescID &id,	GeData &t_data);
 	Bool									SetDParameter(const DescID &id, const GeData &t_data);
};

#pragma pack (pop)
}

#endif	// REFLECTIONMAIN_H__
