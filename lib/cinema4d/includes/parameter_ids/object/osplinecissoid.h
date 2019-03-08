#ifndef OSPLINECISSOID_H__
#define OSPLINECISSOID_H__

enum
{
	PRIM_CISSOID_TYPE					= 2020, // LONG - Type [0:Cissoid; 1:Lemniscate; 2:Strophoid]
		PRIM_CISSOID_TYPE_CISSOID			= 0,
		PRIM_CISSOID_TYPE_LEMNISCATE	= 1,
		PRIM_CISSOID_TYPE_STROPHOID		= 2,
	PRIM_CISSOID_TENSION		  = 2021,	// REAL - Value Range
	PRIM_CISSOID_WIDTH				= 2023, // REAL - Width
	PRIM_CISSOID_SUB					= 2024  // LONG - Subdivision [>=3]
};

#endif // OSPLINECISSOID_H__
