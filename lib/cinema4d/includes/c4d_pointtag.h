/////////////////////////////////////////////////////////////
// MELANGE SDK                                             //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef C4D_POINTTAG_H__
#define C4D_POINTTAG_H__

#include "c4d_basetag.h"

namespace melange
{
#pragma pack (push, 8)

//----------------------------------------------------------------------------------------
/// Point tag. Holds point data.
//----------------------------------------------------------------------------------------
class PointTag : public BaseTag
{
	INSTANCEOF(PointTag, BaseTag)

private:
	Vector* vdata;
	Int32		vcount;

public:
	/// @name Constructor/Destructor
	/// @{

	//----------------------------------------------------------------------------------------
	/// Default constructor.
	//----------------------------------------------------------------------------------------
	PointTag();

	//----------------------------------------------------------------------------------------
	/// Default destructor.
	//----------------------------------------------------------------------------------------
	virtual ~PointTag();

	/// @}

	/// @name Data
	/// @{

	//----------------------------------------------------------------------------------------
	/// Gets the number of points.
	/// @return												The number of points.
	//----------------------------------------------------------------------------------------
	Int32 GetCount(void);

	//----------------------------------------------------------------------------------------
	/// Resizes the point data array.
	/// @param[in] newcnt							The new array size.
	/// @return												@trueIfOtherwiseFalse{the point array was resized successfully}
	//----------------------------------------------------------------------------------------
	Bool Resize(Int32 newcnt);

	//----------------------------------------------------------------------------------------
	/// Gets a pointer to the writable point array.
	/// @return												The writable point array. @theOwnsPointed{tag,point array}
	//----------------------------------------------------------------------------------------
	Vector* GetPointAdr(void);

	/// @}

	/// @name Private
	/// @{

	//----------------------------------------------------------------------------------------
	/// @markPrivate
	//----------------------------------------------------------------------------------------
	virtual Bool CopyToX(PrivateChunk* dst, COPYFLAGS flags, AliasTrans* trans);

	//----------------------------------------------------------------------------------------
	/// @markPrivate
	//----------------------------------------------------------------------------------------
	virtual Bool HandleSubChunk(HyperFile* hf, Int32 id, Int32 level);

	//----------------------------------------------------------------------------------------
	/// @markPrivate
	//----------------------------------------------------------------------------------------
	virtual Bool Write(HyperFile* hf);

	//----------------------------------------------------------------------------------------
	/// @markPrivate
	//----------------------------------------------------------------------------------------
	virtual Int32 GetInfo();

	/// @}
};

#pragma pack (pop)
}

#endif	// C4D_POINTTAG_H__
