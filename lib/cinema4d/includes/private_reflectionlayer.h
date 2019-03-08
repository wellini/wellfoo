/////////////////////////////////////////////////////////////
// MELANGE SDK                                             //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef REFLECTIONLAYER_H__
#define REFLECTIONLAYER_H__

#include "c4d_file.h"
#include "c4d_reflection.h"
#include "private_ge_mtools.h"

namespace melange
{
#pragma pack (push, 8)

class XReflectionLayers;
class XRClothWeavePattern;
class BaseLink;

/// @markInternal
struct XRShaderValue
{
	BaseLink*							m_pLink;
	BaseShader*						m_pShader;
	Int32									m_nDirty;
	Float									m_fValue;

	XRShaderValue();
	~XRShaderValue();

	void									Alloc(Bool &bSuccess, Float fValue);

	Bool									Read(HyperFile* pFile);
	Bool									Write(HyperFile* pFile) const;

	Bool									CopyTo(XRShaderValue* pDest, BaseDocument *pDoc, Material *pMaterial, AliasTrans* pTrans, Bool bCopyShaders) const;
	Bool									CopyFrom(const XRShaderValue* pSrc, BaseDocument *pDoc, Material *pMaterial, AliasTrans* pTrans, Bool bCopyShaders);

	Bool									IsChanged(BaseDocument *pDoc, Float fOriginalValue);
	void									CopyLink(const GeData &t_data, BaseDocument *pDoc);
	BaseShader*						GetShader(BaseDocument *pDoc) const;

	int										operator !=(const XRShaderValue& rhs) const;
};

/// @markInternal
class XReflectionLayer : public ReflectionLayer
{
public:
	XReflectionLayers*		m_pParent;
	String								m_szNameShow;

	// --- Multipass
	Int32									m_nReflectionIndex;
	Int32									m_nSpecularIndex;

	// --- Images and Preview
	Int32									m_nDirtyPreview;
	Int32									m_nDirtyModel;
	Int32									m_nDirtyAnisotropy;
	Int32									m_nDirtyPrimary;
	Int32									m_nDirtySecondary;
	Int32									m_nDirtyDistance;
	Int32									m_nDirtyCloth;

	// --- Main
	Int32									m_nDistribution;
	Int32									m_nAdditiveMode;
	Int32									m_nBlendMode;
	Bool									m_bColoredRefl;
	Bool									m_bColoredSpec;
	Bool									m_bPreviewMode;
	Bool									m_bLinearTextures;

	// ---
	XRShaderValue					m_sRoughness;
	XRShaderValue					m_sFalloff;
	XRShaderValue					m_sInner;
	XRShaderValue					m_sOrenNayar;
	XRShaderValue					m_sReflection;
	XRShaderValue					m_sSpecular;

	// --- Bump
	Int32									m_nBumpMode;
	Int32									m_nBumpSpace;
	Float									m_fBumpValueBump;
	Float									m_fBumpValueNorm;
	Bool									m_bBumpMIPMap;
	Bool									m_bBumpFlipX;
	Bool									m_bBumpFlipY;
	Bool									m_bBumpFlipZ;
	Bool									m_bBumpSwap;
	XRShaderValue					m_sBumpMap;
	XRShaderValue					m_sBumpMapCustom;

	// --- Color
	Vector								m_vColorColor;
	Float									m_fColorBrightness;
	Int32									m_nColorMixMode;
	Float									m_fColorMixStrength;
	XRShaderValue					m_sColorTexture;

	// --- Transparency
	Vector								m_vTransColor;
	Float									m_fTransAmount;
	Int32									m_nTransMixMode;
	Float									m_fTransMixStrength;
	XRShaderValue					m_sTransTexture;

	// --- Anisotropy
	Int32									m_nAnisoProjection;
	Int32									m_nAnisoPattern;
	Int32									m_nAnisoMirror;
	Int32									m_nAnisoScratchesMode;
	Int32									m_nAnisoProjectionCount;
	Float									m_fAnisoProjectionScale;
	Float									m_fAnisoProjectionAngle;
	Float									m_fAnisoProjectionOffsetU;
	Float									m_fAnisoProjectionOffsetV;
	XRShaderValue					m_sAnisoPatternCustom;
	XRShaderValue					m_sAnisoAnisotropy;
	XRShaderValue					m_sAnisoOrientation;
	// ---
	XRShaderValue					m_sAnisoPrimaryAmplitude;
	XRShaderValue					m_sAnisoPrimaryScale;
	XRShaderValue					m_sAnisoPrimaryLength;
	XRShaderValue					m_sAnisoPrimaryAttenuate;
	// ---
	XRShaderValue					m_sAnisoSecondaryAmplitude;
	XRShaderValue					m_sAnisoSecondaryScale;
	XRShaderValue					m_sAnisoSecondaryLength;
	XRShaderValue					m_sAnisoSecondaryAttenuate;

	// --- Cloth
#if 0 // no need for Melange
	XRClothWeavePattern*	m_pClothPattern;
#endif

	// ---
	Int32									m_nClothPreset;
	Int32									m_nClothPattern;
	Int32									m_nClothQuality;
	Float									m_fClothSmoothing;
	Float									m_fClothScatteringA;
	Float									m_fClothScatteringB;
	XRShaderValue					m_sClothOrientation;
	XRShaderValue					m_sClothScaleU;
	XRShaderValue					m_sClothScaleV;
	XRShaderValue					m_sClothHighlights;

	// ---
	Float									m_fClothNoiseIntensity;
	Float									m_fClothNoiseScale;
	Float									m_fClothNoiseShapeWarp;
	Float									m_fClothNoiseShapeWeft;
	Float									m_fClothNoiseShapeScale;
	// ---
	Vector								m_vClothDiffuseWarp;
	Vector								m_vClothDiffuseWeft;
	Vector								m_vClothSpecularWarp;
	Vector								m_vClothSpecularWeft;
	// ---
	XRShaderValue					m_sClothDiffuseWarp;
	XRShaderValue					m_sClothDiffuseWeft;
	XRShaderValue					m_sClothSpecularWarp;
	XRShaderValue					m_sClothSpecularWeft;

	// --- Fresnel
	Int32									m_nFresnelMode;
	Int32									m_nFresnelPreset;
	Int32									m_nFresnelMetal;
	Bool									m_bFresnelInverted;
	Bool									m_bFresnelOpaque;
	XRShaderValue					m_sFresnelStrength;
	XRShaderValue					m_sFresnelIOR;
	XRShaderValue					m_sFresnelEta;
	XRShaderValue					m_sFresnelAbsorption;

	// --- Precomputed
	Vector								m_vFresnelIOR;
	Vector								m_vFresnelK;

	// --- Sampling
	Int32									m_nSamples;
	Bool									m_bDimEnabled;
	Float									m_fDimDistance;
	Float									m_fDimFalloff;
	Float									m_fClamp;
	Float									m_fCutoff;
	Vector								m_vDimColor;
	Vector								m_vExitColor;

	// --- Debug
	Int32									m_nDebugDUDVMode;
	Int32									m_nDebugScratchMode;
	Int32									m_nDebugClothMode;

	// ---
	XReflectionLayer();
	virtual ~XReflectionLayer();

	// ---
	static XReflectionLayer* Alloc();
	static void						Free(XReflectionLayer *&pLayer) { DeleteObj(pLayer); }

	// ---
	Bool									SetupLayer(BaseDocument *pDoc, BaseContainer *pData);

	// --- Flags
	Bool									CheckFlag(Int32 nFlag);
	void									SetFlag(Int32 nFlag);
	void									ResetFlag(Int32 nFlag);
	void									ChangeFlag(Int32 nFlag, Bool bValue);

	// ---
	void									CopyData(BaseDocument *pDoc, BaseList2D *pObjectSource, BaseList2D *pObjectTarget, Int32 nSourceID, Int32 nTargetID, Int32 nID) const;

	// ---
 	virtual String				GetLayerName(BaseDocument* pDoc, Bool bReset = false) { return name; }
 	virtual String				GetLayerNameShow(Material *pParent);
 	virtual Float					GetLayerValue(Material *pParent);
 	virtual Int32					GetLayerMode(Material *pParent);
 	virtual Bool					CopyTo(XReflectionLayers *pLayers, XReflectionLayer* pDestLayer, BaseDocument *pDoc, BaseList2D *pSource, BaseList2D *pTarget, Bool bCopyID, Bool bCopyName, Bool bUpdateName, Bool bCopyShaders) const;
 	virtual Bool					Read(HyperFile* pFile, Int32 nLevel);
 	virtual Bool					Write(HyperFile* pFile) const;
 	virtual Int32					Compare(XReflectionLayer* pLayer);
 	virtual void					GetParameter(Int32 nItem, const DescID &id, GeData &t_data, DESCFLAGS_GET &nFlags) const { }
 	virtual void					SetParameter(Int32 nItem, const DescID &id, const GeData &t_data, DESCFLAGS_SET &nFlags) { }

	// --- Remove
 	virtual void					RemoveNotifyID(BaseContainer *pData, Material *pParent, Int32 nID);
 	virtual void					RemoveNotify(BaseContainer *pData, Material *pParent, Bool bAddUndo);

 	// --- Rename
	//virtual void					RenameNotifyID(BaseContainer *pData, Material *pParent, Int32 nID);
	//virtual void					RenameNotify(BaseContainer *pData, Material *pParent, Bool bAddUndo);

 	// --- Get All Shaders
 	virtual void					GetAllShaders(BaseContainer *pData, BaseDocument* pDoc, BaseArray<BaseShader*> &ShaderList, Int32 nShaderID);
 	virtual void					GetAllShaders(BaseContainer *pData, BaseDocument* pDoc, BaseArray<BaseShader*> &ShaderList);

	// --- Fresnel Presets
	static Float					ComputeFresnelDielectric(Int32 nFresnelPreset);
	//static void						ComputeFresnelMetal(Int32 nFresnelMetal, Vector& vFresnelIOR, Vector& vFresnelK);

	// --- Cloth Patterns
	void									SetupClothPreset(BaseContainer *pData, BaseDocument *pDoc, Int32 nPreset);

	// --- Mixing Sampling
	Vector								CalculateMix(Vector vShaderColor, Vector vValue, Int32 nMixMode, Float fMixValue);
	//Vector								CalculateMix(XRShaderValue *pShaderValue, Vector vValue, Int32 nMixMode, Float fMixValue, ChannelData *pCD);

	// ---
	virtual Bool					GetParameter(Int32 nID, GeData &d) const;
	virtual Bool					SetParameter(Int32 nID, const GeData &d);

	// ---
	Bool									GetParameter_(Int32 nID, GeData &d) const { return GetParameter(nID, d); }
	Bool									SetParameter_(Int32 nID, const GeData &d) { return SetParameter(nID, d); }
	String								GetName(BaseDocument* pDoc)								{ return GetLayerName(pDoc); }
};

#pragma pack (pop)
}

// ---
#endif	// REFLECTIONLAYER_H__
