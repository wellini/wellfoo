/////////////////////////////////////////////////////////////
// MELANGE SDK                                             //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef CUSTOMGUI_GRADIENT_H__
#define CUSTOMGUI_GRADIENT_H__

#include "c4d_customdatatype.h"
#include "c4d_gedata.h"

namespace melange
{
#pragma pack (push, 8)

class AliasTrans;
class HyperFile;

/// Gradient data type ID.
#define CUSTOMDATATYPE_GRADIENT	1000481

///////////////////////////////////////////////////////////////////////////////////////////////////

/// @addtogroup GRADIENT_INTERPOLATION
/// @ingroup group_enumeration
/// @{
enum
{
	GRADIENT_INTERPOLATION_CUBICKNOT	= 0,	///< Cubic knot.
	GRADIENT_INTERPOLATION_CUBICBIAS	= 1,	///< Cubic bias.
	GRADIENT_INTERPOLATION_SMOOTHKNOT	= 2,	///< Smooth knot.
	GRADIENT_INTERPOLATION_LINEARKNOT	= 3,	///< Linear knot.
	GRADIENT_INTERPOLATION_LINEAR			= 4,	///< Linear.
	GRADIENT_INTERPOLATION_NONE				= 5,	///< None.
	GRADIENT_INTERPOLATION_EXP_UP			= 6,	///< Exponential up.
	GRADIENT_INTERPOLATION_EXP_DOWN		= 7		///< Exponential down.
};
/// @}

/// @addtogroup GRADIENTMODE
/// @ingroup group_enumeration
/// @{
#define GRADIENTMODE_COLOR			0	///< Color only.
#define GRADIENTMODE_ALPHA			1	///< Alpha only.
#define GRADIENTMODE_COLORALPHA	2	///< Color and alpha.
/// @}

/// @addtogroup GRADIENT_CONTAINERIDS
/// @ingroup group_enumeration
/// @{
#define GRADIENT_INTERPOLATION 1000	///< Int32 Interpolation: @ref GRADIENT_INTERPOLATION
#define GRADIENT_KNOT					 1001	///< BaseContainer Holds the gradient knots as sub-containers: @ref GRADIENTKNOT_CONTAINERIDS
#define GRADIENT_MODE					 1002	///< Int32 Gradient mode: @ref GRADIENTMODE
#define GRADIENT_UNCLAMPED		 1003	///< Bool Unclamped.
/// @}

/// @addtogroup GRADIENTKNOT_CONTAINERIDS
/// @ingroup group_enumeration
/// @{
#define GRADIENTKNOT_COLOR			1000	///< Vector Color.
#define GRADIENTKNOT_BRIGHTNESS	1001	///< Float Brightness.
#define GRADIENTKNOT_POSITION		1002	///< Float Position.
#define GRADIENTKNOT_BIAS				1003	///< Float Bias.
#define GRADIENTKNOT_ID					1004	///< Int32 Index.
/// @}


//----------------------------------------------------------------------------------------
/// Represents a knot in a gradient.
//----------------------------------------------------------------------------------------
struct GradientKnot
{
	//----------------------------------------------------------------------------------------
	/// Default constructor.
	//----------------------------------------------------------------------------------------
	GradientKnot(void)
	{
		col = Vector(1.0);
		brightness = 1.0;
		pos		= 0.0;
		bias	= 0.5;
		index = 0;
	}

	Vector col;					///< Color.
	Float	 brightness;	///< Brightness.
	Float	 pos;					///< Position.
	Float	 bias;				///< Bias.
	Int32	 index;				///< Index.
};

///////////////////////////////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------------------------
/// Gradient data type (@ref CUSTOMDATATYPE_GRADIENT).
/// @addAllocFreeNote
//----------------------------------------------------------------------------------------
class Gradient : public CustomDataType
{
public:
	/// @name Alloc/Free
	/// @{

	//----------------------------------------------------------------------------------------
	/// @allocatesA{gradient data}
	/// @return												@allocReturn{gradient data}
	//----------------------------------------------------------------------------------------
	static Gradient* Alloc();

	//----------------------------------------------------------------------------------------
	/// @destructsAlloc{gradient data}
	/// @param[in,out] grad						@theToDestruct{gradient data}
	//----------------------------------------------------------------------------------------
	static void Free(Gradient*& grad);

	/// @}

	/// @name Knots
	/// @{

	//----------------------------------------------------------------------------------------
	/// Inverts the knots.
	/// @return												@trueIfOtherwiseFalse{knots were successfully inverted}
	//----------------------------------------------------------------------------------------
	Bool InvertKnots(void);

	//----------------------------------------------------------------------------------------
	/// Doubles the knots.
	/// @return												@trueIfOtherwiseFalse{knots were successfully doubled}
	//----------------------------------------------------------------------------------------
	Bool DoubleKnots(void);

	//----------------------------------------------------------------------------------------
	/// Flushes all knots.
	//----------------------------------------------------------------------------------------
	void FlushKnots(void);

	/// @}

	/// @name Knot
	/// @{

	//----------------------------------------------------------------------------------------
	/// Gets the number of knots.
	/// @return												The knot count.
	//----------------------------------------------------------------------------------------
	Int32 GetKnotCount(void);

	//----------------------------------------------------------------------------------------
	/// Inserts a knot.
	/// @param[in] knot								The knot to insert.
	/// @return												The index of the inserted knot. GetKnotCount() - @em 1
	//----------------------------------------------------------------------------------------
	Int32 InsertKnot(const GradientKnot& knot);

	//----------------------------------------------------------------------------------------
	/// Removes a knot.
	/// @param[in] index							The knot index. @em 0 <= @formatParam{index} < GetKnotCount()
	/// @return												@trueIfOtherwiseFalse{knot was successfully removed}
	//----------------------------------------------------------------------------------------
	Bool RemoveKnot(Int32 index);

	//----------------------------------------------------------------------------------------
	/// Gets the knot at @formatParam{index}.
	/// @param[in] index							The knot index. @em 0 <= @formatParam{index} < GetKnotCount()
	/// @return												The knot data.
	//----------------------------------------------------------------------------------------
	GradientKnot GetKnot(Int32 index);

	//----------------------------------------------------------------------------------------
	/// Sets the data for a knot at @formatParam{index}.
	/// @param[in] index							The knot index. @em 0 <= @formatParam{index} < GetKnotCount()
	/// @param[in] k									The knot information.
	//----------------------------------------------------------------------------------------
	void SetKnot(Int32 index, const GradientKnot& k);

	/// @}

	/// @name Render
	/// @{

	//----------------------------------------------------------------------------------------
	/// Initializes the gradient data for renderer.
	/// @return												@trueIfOtherwiseFalse{the gradient data was successfully initialized for renderer}
	//----------------------------------------------------------------------------------------
	Bool InitRender(void);

	//----------------------------------------------------------------------------------------
	/// Frees the gradient data for renderer.
	//----------------------------------------------------------------------------------------
	void FreeRender(void);

	//----------------------------------------------------------------------------------------
	/// Gets a pointer to the knot at @formatParam{index} between InitRender() and FreeRender().
	/// @param[in] index							The knot index. @em 0 <= @formatParam{index} < GetKnotCount()
	/// @return												The knot at @formatParam{index}. @theOwnsPointed{gradient,knot}
	//----------------------------------------------------------------------------------------
	GradientKnot* GetRenderKnot(Int32 index);

	//----------------------------------------------------------------------------------------
	/// Gets the number of knots for GetRenderKnot().
	/// @return												The render knot count.
	//----------------------------------------------------------------------------------------
	Int32 GetRenderKnotCount(void);

	//----------------------------------------------------------------------------------------
	/// Calculates a gradient pixel.
	/// @param[in] pos								The X position.
	/// @return												The calculated gradient pixel.
	//----------------------------------------------------------------------------------------
	Vector CalcGradientPixel(Float pos);

	/// @}

	/// @name Data
	/// @{

	//----------------------------------------------------------------------------------------
	/// Gets data from the gradient container.
	/// @param[in] id									The gradient data ID: @ref GRADIENT_CONTAINERIDS.
	/// @return												The data.
	//----------------------------------------------------------------------------------------
	GeData GetData(Int32 id) const;

	//----------------------------------------------------------------------------------------
	/// Sets data in the gradient container.
	/// @param[in] id									The gradient data ID: @ref GRADIENT_CONTAINERIDS.
	/// @param[in] data								The data.
	/// @return												@trueIfOtherwiseFalse{the gradient data was successfully set}
	//----------------------------------------------------------------------------------------
	Bool SetData(Int32 id, const GeData& data);

	/// @}

	/// @name Alpha
	/// @{

	//----------------------------------------------------------------------------------------
	/// Gets the alpha gradient.
	/// @return												Alpha gradient. @theOwnsPointed{gradient,knot}
	//----------------------------------------------------------------------------------------
	Gradient* GetAlphaGradient(void);

	//----------------------------------------------------------------------------------------
	/// Allocates an alpha gradient.
	/// @return												The allocated alpha gradient, or @formatConstant{nullptr} if the allocation failed.
	//----------------------------------------------------------------------------------------
	Gradient* AllocAlphaGradient(void);

	/// @}

	/// @name Miscellaneous
	/// @{

	//----------------------------------------------------------------------------------------
	/// Gets a checksum of the whole gradient state, including the needles, colors and interpolation type.
	/// @return												The checksum.
	//----------------------------------------------------------------------------------------
	UInt32 GetChecksum();

	/// @}

private:
	Gradient(void);
	~Gradient(void);
};

/// @markInternal
class GradientDataTypeClass
{
public:
	static Int32 GetId();

	static CustomDataType* AllocData();
	static void FreeData(CustomDataType* data);

	static Bool CopyData(const CustomDataType* src, CustomDataType* dst, AliasTrans* aliastrans);
	static Int32 Compare(const CustomDataType* d1, const CustomDataType* d2);

	static Bool WriteData(const CustomDataType* t_d, HyperFile* hf);
	static Bool ReadData(CustomDataType* t_d, HyperFile* hf, Int32 level);

	static Bool GetParameter(const CustomDataType* data, const DescID& id, GeData& t_data, Int32& flags);
	static Bool SetDParameter(CustomDataType* data, const DescID& id, const GeData& t_data, Int32& flags);
};

#pragma pack (pop)
}

#endif	// CUSTOMGUI_GRADIENT_H__
