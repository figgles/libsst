/*
	SST_Mersenne.c
	Author: Chris Ertel <crertel@762studios.com>
	Created: 2/26/2012

	Purpose: 

	Implementation of Mersenne Twister

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.
*/

#include "RandomFuncTbl.h"

/*
Note: This implementation of mersenne twister was originally written by Michael Brundage and has 
been placed in the public domain.  We modified it somewhat.
*/

/* Length of our mersenne twister buffer */
#define MT_LEN 624

/* Bunch of useful macro functions and magic numbers */
#define MT_IA           397
#define MT_IB           (MT_LEN - MT_IA)
#define UPPER_MASK      0x80000000
#define LOWER_MASK      0x7FFFFFFF
#define MATRIX_A        0x9908B0DF
#define SEED_MAGIC		0x6C078965
#define TWIST(b,i,j)    ((b)[i] & UPPER_MASK) | ((b)[j] & LOWER_MASK)
#define MAGIC(s)        (((s)&1)*MATRIX_A)

/*************************************************************************/

/* Mersenne Twister Data Struct */
typedef struct SST_Mersenne_Private
{
	uint32_t mt_buffer[MT_LEN];	/* Buffer for our seed data */
	size_t mt_index;
} SST_Mersenne_Private;

/*************************************************************************/

/* get the next random value from the mersenne twister array */
static int mt_random(SST_Mersenne_Private* mt)
{
	uint32_t* b = mt->mt_buffer;
	size_t idx = mt->mt_index;

	uint32_t s;
	int i;

	if(idx == MT_LEN)
	{
		idx = 0;
		i = 0;
		for (; i < MT_IB; i++) {
			s = TWIST(b, i, i+1);
			b[i] = b[i + MT_IA] ^ (s >> 1) ^ MAGIC(s);
		}
		for (; i < MT_LEN-1; i++) {
			s = TWIST(b, i, i+1);
			b[i] = b[i - MT_IB] ^ (s >> 1) ^ MAGIC(s);
		}

		s = TWIST(b, MT_LEN-1, 0);
		b[MT_LEN-1] = b[MT_IA-1] ^ (s >> 1) ^ MAGIC(s);
	}

	mt->mt_index = idx + 1;

	return (int)b[idx];
}

/*************************************************************************/

static void Mersenne_InitFromSeed(void* priv, uint32_t seed)
{
	SST_Mersenne_Private* mt_data = (SST_Mersenne_Private*)priv;
	size_t i;

	mt_data->mt_index = 0;
	mt_data->mt_buffer[0] = seed;

	/* Initialize the generator */
	for(i = 1; i < MT_LEN; i++)
		mt_data->mt_buffer[i] = (SEED_MAGIC * (mt_data->mt_buffer[i - 1] ^ (mt_data->mt_buffer[i - 1] >> 30)) + (uint32_t)i);

}

/*************************************************************************/

static void Mersenne_GetFloatArray(void* priv, float* _out, size_t _numElements, float _min, float _max)
{
	SST_Mersenne_Private* mt_data = (SST_Mersenne_Private*)priv;
	size_t i;
	const float diff = _max - _min;
	
	/* grab a number of pseudorandom floating point numbers in the specified range */
	for (i = 0; i < _numElements; i++)
	{
		_out[i] = _min + randIntToFloat((uint32_t)boundInt(mt_random(mt_data), 0, SST_RAND_FLOATBITS_MAX)) * diff; /* x = [0,1];  value = min + x*(max - min) */
	}
}

/*************************************************************************/

static int Mersenne_GetInt(void* priv)
{
	SST_Mersenne_Private* mt_data = (SST_Mersenne_Private*)priv;
	
	return mt_random(mt_data);
}

/*************************************************************************/

static void Mersenne_GetIntArray(void* priv, int* _out, size_t _numElements, int _min, int _max)
{
	SST_Mersenne_Private* mt_data = (SST_Mersenne_Private*)priv;
	size_t i;

	/* grab an number of pseudorandom ints in the specified range */
	for (i = 0; i <_numElements; i++)
		_out[i] = boundInt(mt_random(mt_data), _min, _max);
}

/*************************************************************************/

/* Function table for mersenne random number generation. */
const SST_PRNG_FuncTable _SST_MersenneFuncTable = 
{
	Mersenne_InitFromSeed,
	Mersenne_GetFloatArray,
	Mersenne_GetInt,
	Mersenne_GetIntArray,
	sizeof(SST_Mersenne_Private)
};
