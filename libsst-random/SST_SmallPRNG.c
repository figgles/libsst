/*
	SST_SmallPRNG.c
	Author: Chris Ertel <crertel@762studios.com>
	Created: 2/26/2012

	Purpose: 

	Implementation of SmallPRNG

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.
*/

#include "RandomFuncTbl.h"

#define BIT_ROTATE(x,k) (((x)<<(k))|((x)>>(32-(k))))

/*************************************************************************/

typedef struct SST_SmallPRNG_Private
{
	uint32_t a;
	uint32_t b;
	uint32_t c;
	uint32_t d;
} SST_SmallPRNG_Private;

static int sprng_random(SST_SmallPRNG_Private* x)
{
	uint32_t e = x->a - BIT_ROTATE(x->b, 27);
	x->a = x->b ^ BIT_ROTATE(x->c, 17);
	x->b = x->c + x->d;
	x->c = x->d + e;
	x->d = e + x->a;
	return (int)x->d;
}

/*************************************************************************/

static void SmallPRNG_InitFromSeed(void* priv, uint32_t seed)
{
	SST_SmallPRNG_Private* sprng = (SST_SmallPRNG_Private*)priv;
	int i;
	sprng->a = 0xf1ea5eed;
	sprng->b = sprng->c = sprng->d = seed;
	
	for(i=0; i<20; ++i)
		(void)sprng_random(sprng);
}

/*************************************************************************/

static void SmallPRNG_GetFloatArray(void* priv, float* _out, size_t _numElements, float _min, float _max)
{
	SST_SmallPRNG_Private* sprng_data = (SST_SmallPRNG_Private*)priv;
	size_t i;
	const float diff = _max - _min;

	for (i = 0; i < _numElements; i++)
		_out[i] = _min + randIntToFloat(boundInt(sprng_random(sprng_data), 0, SST_RAND_FLOATBITS_MAX)) * diff;
}

/*************************************************************************/

static int SmallPRNG_GetInt(void* priv)
{
	SST_SmallPRNG_Private* sprng_data = (SST_SmallPRNG_Private*)priv;

	return sprng_random(sprng_data);
}

/*************************************************************************/

static void SmallPRNG_GetIntArray(void* priv, int* _out, size_t _numElements, int _min, int _max)
{
	SST_SmallPRNG_Private* sprng_data = (SST_SmallPRNG_Private*)priv;
	size_t i;

	for (i = 0; i < _numElements; i++)
	{
		_out[i] = boundInt(sprng_random(sprng_data), _min, _max); /* TODO: This does redundant operations. Compilers may not be able to optimize. */
	}
}

/*************************************************************************/

/* Function table for SmallPRNG random number generator */
const SST_PRNG_FuncTable _SST_SmallPRNGFuncTable = 
{
	SmallPRNG_InitFromSeed,
	SmallPRNG_GetFloatArray,
	SmallPRNG_GetInt,
	SmallPRNG_GetIntArray,
	sizeof(SST_SmallPRNG_Private)
};
