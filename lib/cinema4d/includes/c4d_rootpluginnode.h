/////////////////////////////////////////////////////////////
// MELANGE SDK                                             //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef C4D_ROOTPLUGINNODE_H__
#define C4D_ROOTPLUGINNODE_H__

#include "c4d_rootlist2d.h"

namespace melange
{
#pragma pack (push, 8)

//----------------------------------------------------------------------------------------
/// @markPrivate
//----------------------------------------------------------------------------------------
class RootPluginNode : public RootList2D
{
	INSTANCEOF(RootPluginNode, RootList2D)

private:
	virtual Bool CopyToX(PrivateChunk* dst, COPYFLAGS flags, AliasTrans* trn);

public:
	virtual Bool HandleSubChunk(HyperFile* hf, Int32 id, Int32 level);
	virtual Bool Write(HyperFile* hf);
};

#pragma pack (pop)
}

#endif	// C4D_ROOTPLUGINNODE_H__
