/*
	SST_CMWC.c
	Author: Chris Ertel <crertel@762studios.com>
	Created: 2/26/2012

	Purpose: 

	Implementation of complimentary multiply with carry algorithm

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.
*/

#include "RandomFuncTbl.h"

/* Do you believe in magic? */
#define PHI 0x9e3779b9
#define CMWC_SIZE 4096

/* CMWC Data Struct */
typedef struct SST_CMWC_Private
{
	uint32_t cmwc_buffer[CMWC_SIZE];
	uint32_t cmwc_carry;
	size_t cmwc_index;
} SST_CMWC_Private;

/*************************************************************************/

static int cmwc_random(SST_CMWC_Private* cmwc)
{
	uint64_t t, a = (uint64_t)18782;
	uint32_t x, r = 0xfffffffe;
	
	cmwc->cmwc_index = (cmwc->cmwc_index + 1) % CMWC_SIZE;
	t = a * cmwc->cmwc_buffer[cmwc->cmwc_index] + cmwc->cmwc_carry;
	cmwc->cmwc_carry = (uint32_t)(t >> 32);
	x = (uint32_t)(t + cmwc->cmwc_carry);

	if (x < cmwc->cmwc_carry) 
	{
		x++;
		cmwc->cmwc_carry++;
	}

	cmwc->cmwc_buffer[cmwc->cmwc_index] = r - x;
	
	return (int)cmwc->cmwc_buffer[cmwc->cmwc_index];
}

/*************************************************************************/

static void CMWC_InitFromSeed(void* priv, uint32_t seed)
{
	SST_CMWC_Private* cmwc = (SST_CMWC_Private*)priv;
	size_t i;
	
	cmwc->cmwc_index = 4095;
	cmwc->cmwc_carry = 362436;
	cmwc->cmwc_buffer[0] = seed;
	cmwc->cmwc_buffer[1] = seed + PHI;
	cmwc->cmwc_buffer[2] = seed + PHI + PHI;

	for (i = 3; i < CMWC_SIZE; i++)
		cmwc->cmwc_buffer[i] = cmwc->cmwc_buffer[i - 3] ^ cmwc->cmwc_buffer[i - 2] ^ PHI ^ (uint32_t)i;
}

/*************************************************************************/

static void CMWC_GetFloatArray(void* priv, float* _out, size_t _numElements, float _min, float _max)
{
	SST_CMWC_Private* cmwc = (SST_CMWC_Private*)priv;
	size_t i;
	const float diff = _max - _min;
	
	/* compute and return a pseudorandom float in the range */
	for ( i = 0; i < _numElements; i++ )
	{
		_out[i] = _min + randIntToFloat((uint32_t)boundInt(cmwc_random(cmwc), 0, SST_RAND_FLOATBITS_MAX)) * diff; /* x = [0,1];  value = min + x*(max - min) */
	}
}

/*************************************************************************/

static int CMWC_GetInt(void* priv)
{
	SST_CMWC_Private* cmwc = (SST_CMWC_Private*)priv;
	
	return cmwc_random(cmwc);
}

/*************************************************************************/

static void CMWC_GetIntArray(void* priv, int* _out, size_t _numElements, int _min, int _max)
{
	SST_CMWC_Private* cmwc = (SST_CMWC_Private*)priv;
	size_t i;

	/* grab an number of pseudorandom ints in the specified range */
	for(i = 0; i < _numElements; i++)
	{
		_out[i] = boundInt(cmwc_random(cmwc), _min, _max);
	}
}

/*************************************************************************/

/* Function table for CMWC random number generation. */
const SST_PRNG_FuncTable _SST_CMWCFuncTable = 
{
	CMWC_InitFromSeed,
	CMWC_GetFloatArray,
	CMWC_GetInt,
	CMWC_GetIntArray,
	sizeof(SST_CMWC_Private)
};
