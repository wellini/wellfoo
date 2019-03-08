/////////////////////////////////////////////////////////////
// MELANGE SDK                                             //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef REFLECTIONLAYERS_H__
#define REFLECTIONLAYERS_H__

#include "c4d_system.h"
#include "private_ge_mtools.h"

namespace melange
{
#pragma pack (push, 8)

class XReflectionLayer;
class BaseDocument;
class BaseContainer;
class Material;
class BaseLink;

/// @markInternal
class XReflectionLayers : public CDynamicObjectArray<XReflectionLayer>
{
public:
	XReflectionLayer*			m_pLayer;

	XReflectionLayers();

	virtual XReflectionLayer* AllocObject() const;
	virtual XReflectionLayer* AllocObjectType(Int32 nType) const;
	virtual void					FreeObject(XReflectionLayer *&pObj) const;

	XReflectionLayer*			Add(BaseDocument *pDoc, BaseContainer *pData, Int32 nID, Bool bAppend = true);
	void									Remove(Material *pParent, BaseContainer *pData, XReflectionLayer* pLayer, bool bAddUndo);
	virtual void					Free();
	XReflectionLayer*			GetLayer(Int32 nIndex);
	const XReflectionLayer* GetLayer(Int32 nIndex) const;
	XReflectionLayer*			GetLayerTrans();

	Bool									ReadElementCreate(HyperFile* pFile, XReflectionLayer* &pLayer, Int32 nLevel);
	Bool									WriteElement(HyperFile* pFile, const XReflectionLayer* pElement) const;
	Int32									Compare(XReflectionLayers* pLayers);
	Int32									FindLayer(XReflectionLayer* pLayer);
	virtual Bool					CopyTo(CDynamicObjectArray<XReflectionLayer>* pDest, AliasTrans* pTrans, Bool bAppend = false) const;
	XReflectionLayer*			SearchLayer(Int32 nLayerID);
	Bool									CompareStructure(XReflectionLayers* pLayers, Bool bCompareNames);
};

#pragma pack (pop)
}

#endif	// REFLECTIONLAYERS_H__
