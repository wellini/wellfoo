/////////////////////////////////////////////////////////////
// MELANGE SDK                                             //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef C4D_SHADOWSTRUCT_H__
#define C4D_SHADOWSTRUCT_H__

#include "ge_math.h"

namespace melange
{
#pragma pack (push, 8)

//----------------------------------------------------------------------------------------
/// @markPrivate
//----------------------------------------------------------------------------------------
class ShadowStruct
{
public:
	ShadowStruct(void);

	Float	 absbias, relbias, density, parradius, coneangle, areawidth;
	Int32	 mapsize_x, mapsize_y, smpradius;
	Bool	 transparency, absolute, outline, cone, softcone, clipinfluence;
	Vector color;
	Int32	 mapsize;
};

#pragma pack (pop)
}

#endif	// C4D_SHADOWSTRUCT_H__
