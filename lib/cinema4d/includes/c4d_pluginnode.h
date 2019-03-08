/////////////////////////////////////////////////////////////
// MELANGE SDK                                             //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef C4D_PLUGINNODE_H__
#define C4D_PLUGINNODE_H__

#include "c4d_baselist2d.h"

namespace melange
{
#pragma pack (push, 8)

//----------------------------------------------------------------------------------------
/// @markPrivate
//----------------------------------------------------------------------------------------
class PluginNode : public BaseList2D
{
	OVERRIDENINSTANCEOF(PluginNode, BaseList2D)

public:
	PluginNode(void);
	PluginNode(Int32 pId);
	virtual ~PluginNode(void);

	virtual Int32 GetType(void) const;
	virtual Int32 GetDiskType(void) const;

	virtual Bool CopyToX(PrivateChunk* dst, COPYFLAGS flags, AliasTrans* trans);
	virtual BaseList2D* GetClone(COPYFLAGS flags, AliasTrans* trans);

	NodeData* AllocData(Int32 id, Bool& known);

	virtual Bool Write(HyperFile* hf);
	virtual Bool HandleSubChunk(HyperFile* hf, Int32 id, Int32 level);
};

#pragma pack (pop)
}

#endif	// C4D_PLUGINNODE_H__
