/////////////////////////////////////////////////////////////
// MELANGE SDK                                             //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef C4D_ROOTVIDEOPOSTDATA_H__
#define C4D_ROOTVIDEOPOSTDATA_H__

#include "c4d_rootlist2d.h"

namespace melange
{
#pragma pack (push, 8)

//----------------------------------------------------------------------------------------
/// @markPrivate
//----------------------------------------------------------------------------------------
class RootVideoPost : public RootList2D
{
	INSTANCEOF(RootVideoPost, RootList2D)

private:
	virtual Bool CopyToX(PrivateChunk* dst, COPYFLAGS flags, AliasTrans* trans);

public:
	virtual Bool HandleSubChunk(HyperFile* hf, Int32 id, Int32 level);
	virtual Bool Write(HyperFile* hf);
};

#pragma pack (pop)
}

#endif	// C4D_ROOTVIDEOPOSTDATA_H__
