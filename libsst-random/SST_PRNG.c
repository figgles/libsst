/*
	SST_PRNG.c
	Author: Patrick Baggett <ptbaggett@762studios.h>
	Created: 5/1/2012

	Purpose: 

	PRNG interface functions that call out to implementations as necessary

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.
*/

#include "RandomFuncTbl.h"
#include <time.h> /* clock() */
#include <string.h> /* memcpy() */

/*
	PRNG instances consist of a function table and associated private data that is implementation-specific.
	In order to reduce the number of malloc() calls and points of failure, the private data is not stored as
	a pointer but actually grafted onto the instance structure. Thus, the layout in memory is:
	
	[ handle data ][ private data ]
	
	In order to know the required size of the private data, the function table has a 'size_t' member called "privateSize"
	that is used. The PRNG_GET_PRIVATE() macro is used to get the address of the private data section given the base handle.
	This is what is passed to the implementation-specific functions.
	
	The function tables mimic the API somewhat, but with a few exceptions. First, they don't do any memory allocation, so they
	can't fail. Second, they only expose the functions required to implement the API optimally. For example, GetInt() is required, but
	it returns the full range, and these functions convert it to the necessary range. GetFloat() does not exist because it can be
	done via int -> float conversions; however the GetFloatArray() /is/ because it would require dereferencing a function pointer
	(indirect jump) over and over which reduces performance compared to looping in implementation code. Same goes for GetIntArray().
	The non-orthogonality may seem odd, but it is minimal and optimal.
	
*/

/* Macro to get the start of the private data section given a PRNG handle */
#define PRNG_GET_PRIVATE(prng)	(void*)(((uintptr_t)prng) + sizeof(SST_PRNGImpl))

/*
This struct contains the data necessary for a created PRNG of any
of the implemented types.
*/
typedef struct SST_PRNGImpl {
	const SST_PRNG_FuncTable* vtbl;	/* function table for the generator */
} SST_PRNGImpl;

/*************************************************************************/

SST_PRNG SST_Random_CreatePRNG(SST_PRNG_TYPE type)
{
	uint32_t seed = (uint32_t)clock();
	return (SST_PRNG)SST_Random_CreatePRNGFromSeed(type,  seed);
}

/*************************************************************************/

SST_PRNG SST_Random_CreatePRNGFromSeed(SST_PRNG_TYPE type, uint32_t seed)
{
	SST_PRNGImpl* instance;
	const SST_PRNG_FuncTable* vtbl;
	
	switch(type)
	{
		case SST_PRNG_MERSENNE:  vtbl = &_SST_MersenneFuncTable; break;
		case SST_PRNG_CMWC:      vtbl = &_SST_CMWCFuncTable; break;
		case SST_PRNG_SMALLPRNG: vtbl = &_SST_SmallPRNGFuncTable; break;
		
		/* Unknown */
		default: return NULL;
	}
	
	/* Allocate instance + private data */
	instance = (SST_PRNGImpl*)malloc(sizeof(SST_PRNGImpl) + vtbl->privateSize);	
	if(instance == NULL)
		return NULL;
	
	/* Initialize the instance */
	instance->vtbl = vtbl;
	
	vtbl->initFromSeed(PRNG_GET_PRIVATE(instance), seed);
	
	return (SST_PRNG)instance;
}

/*************************************************************************/

SST_PRNG SST_Random_ClonePRNG(SST_PRNG instance)
{
	SST_PRNGImpl* prng = (SST_PRNGImpl*)instance;
	SST_PRNGImpl* newPrng;

	/* Allocate new prng data */
	newPrng = (SST_PRNGImpl*)malloc(sizeof(SST_PRNGImpl) + prng->vtbl->privateSize);
	if(newPrng == NULL)
		return NULL;
	
	/* Copy function table, then private data area */
	newPrng->vtbl = prng->vtbl;
	memcpy(PRNG_GET_PRIVATE(newPrng), PRNG_GET_PRIVATE(prng), prng->vtbl->privateSize);
	
	return (SST_PRNG)newPrng;
}

/*************************************************************************/

void SST_Random_DestroyPRNG(SST_PRNG instance)
{
	free(instance);
}

/*************************************************************************/

float SST_Random_GetPRNGFloat(SST_PRNG instance, float min, float max)
{
	int x;
	
	/* Get integer value in the range [0, SST_RAND_FLOATBITS_MAX] */
	x = SST_Random_GetPRNGInt(instance, 0, SST_RAND_FLOATBITS_MAX);
	
	/* Convert to float in range [0, 1.0], then scale/bias to [min,max] range */	
	return  randIntToFloat(x) * (max - min) + min; /* This works even if min >= max */
}

/*************************************************************************/

void SST_Random_GetPRNGFloatArray(SST_PRNG instance, float* out, size_t num, float min, float max)
{
	SST_PRNGImpl* prng = (SST_PRNGImpl*)instance;
	
	prng->vtbl->getFloatArray(PRNG_GET_PRIVATE(prng), out, num, min, max);
}

/*************************************************************************/

int	SST_Random_GetPRNGInt(SST_PRNG instance, int min, int max)
{
	SST_PRNGImpl* prng = (SST_PRNGImpl*)instance;

	return boundInt(prng->vtbl->getInt(PRNG_GET_PRIVATE(prng)), min, max);
}

/*************************************************************************/

void SST_Random_GetPRNGIntArray(SST_PRNG instance, int* out, size_t num, int min, int max)
{
	SST_PRNGImpl* prng = (SST_PRNGImpl*)instance;
	
	prng->vtbl->getIntArray(PRNG_GET_PRIVATE(prng), out, num, min, max);
}

