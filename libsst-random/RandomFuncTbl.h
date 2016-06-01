/*
	RandomFuncTbl.h
	Author: James Russell <jcrussell@762studios.com>, Patrick Baggett <@762studios.com>
	Created: 5/1/2012

	Purpose: 

	Private header for libsst-random function table

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.
*/

#pragma once

#ifndef _SST_RANDOMFUNCTBL_H
#define _SST_RANDOMFUNCTBL_H

#include <SST/SST_PRNG.h>
#include <SST/SST_Build.h>
#include <stdlib.h>		/* size_t */

/*
The following typedefs are used to set function pointer types.
*/
typedef void  (*SST_Random_InitFromSeedFunc)(void*, uint32_t);
typedef void  (*SST_Random_GetFloatArrayFunc)(void*, float*, size_t, float, float);
typedef int   (*SST_Random_GetIntFunc)(void*);
typedef void  (*SST_Random_GetIntArrayFunc)(void*, int*, size_t, int, int);

/*
	Struct used to contain the necessary function pointers for a given PRNG.
	See SST_PRNG.c for explanation of non-orthogonality.
*/
typedef struct SST_PRNG_FuncTable
{
	SST_Random_InitFromSeedFunc initFromSeed;
	SST_Random_GetFloatArrayFunc getFloatArray;
	SST_Random_GetIntFunc getInt;
	SST_Random_GetIntArrayFunc getIntArray;
	size_t privateSize;
} SST_PRNG_FuncTable;


#define SST_RAND_FLOATBITS_MAX (0x00FFFFFF)

/* Takes a value in the range of [0, SST_RAND_FLOATBITS_MAX] and converts to float in the range 0.0 to 1.0 */
static INLINE float randIntToFloat(uint32_t value)
{
	return (float)value / (float)SST_RAND_FLOATBITS_MAX;
}

/* Take any random integer in [INT_MIN,INT_MAX] and bound it to [min,max] */
static INLINE int boundInt(int x, int min, int max)
{
	int diff;

	x &= 0x7FFFFFFF; /* Ensure this number is positive. Modulus with negative numbers can be "surprising", e.g. 340 % 60 == 40, but -340 % 60 == 20  */
	
	/* Handle edge cases */
	if(min == max)
		return min;
	if(min > max)
	{
		int tmp = min;
		min = max;
		max = tmp;
	}
	
	diff = max - min;

	return min + (x % diff);
}



extern const SST_PRNG_FuncTable _SST_MersenneFuncTable;
extern const SST_PRNG_FuncTable _SST_CMWCFuncTable;
extern const SST_PRNG_FuncTable _SST_SmallPRNGFuncTable;

#endif

