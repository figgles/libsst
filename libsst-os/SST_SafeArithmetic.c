/*
	SST_SafeArithmetic.c
	Author: Chris Ertel <crertel@762studios.com>
	Created: 1/16/2012

	Purpose: 

	Functions to help perform integer arithmetic while catching overflow conditions.

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#include <SST/SST_SafeArithmetic.h>
#include <limits.h>

int SST_OS_SafeAddI8(int8_t _a, int8_t _b, int8_t* _out)
{
	int8_t ret = _a + _b;

	/* if they are opposite signs, they cannot overflow */
	if ( (_a >= 0 && _b <= 0) ||
		 (_b >= 0 && _a <= 0) )
	{ 
		*_out = ret;
		return 1;
	}

	/* if they are the same sign, check for overflow */
	if (_a < 0 || _b < 0)
	{
		if (ret > _a && ret > _b)
			return 0;
	}
	else
	{
		if (ret < _a && ret < _b)
			return 0;
	}
	

	*_out = ret;
	return 1;
}

int SST_OS_SafeAddI8ToSizeT(int8_t _a, size_t _size, size_t* _out)
{
	size_t ret = _size + _a;

	if (_a >= 0)
	{
		if (ret < _size)
			return 0;
	}
	else
	{
		if (ret > _size)
			return 0;
	}

	*_out = ret;
	return 1;
}

int SST_OS_SafeAddU8(uint8_t _a, uint8_t _b, uint8_t* _out)
{
	uint8_t ret = _a + _b;

	if (ret < _a || ret < _b)
		return 0;

	*_out = ret;
	return 1;
}

int SST_OS_SafeMultiplyU8(uint8_t _a, uint8_t _b, uint8_t* _out)
{
	uint16_t a = _a;
	uint16_t b = _b;
	uint16_t ret = a*b;
	
	if (ret > 0xff)
		return 0;

	*_out = (uint8_t) ret;
	return 1;
}

int SST_OS_SafeAddU8ToSizeT(uint8_t _a, size_t _size, size_t* _out)
{
	size_t ret = _a + _size;

	if (ret < _size)
		return 0;

	*_out = ret;
	return 1;
}

int SST_OS_SafeAddI16(int16_t _a, int16_t _b, int16_t* _out)
{
	int16_t ret = _a + _b;

	/* if they are opposite signs, they cannot overflow */
	if ( (_a >= 0 && _b <= 0) ||
		(_b >= 0 && _a <= 0) )
	{
		*_out = ret;
		return 1;
	}

	/* if they are the same sign, check for overflow */
	if (_a < 0 || _b < 0)
	{
		if (ret > _a && ret > _b)
			return 0;
	}
	else
	{
		if (ret < _a && ret < _b)
			return 0;
	}


	*_out = ret;
	return 1;
}

int SST_OS_SafeAddI16ToSizeT(int16_t _a, size_t _size, size_t* _out)
{
	size_t ret = _size + _a;

	if (_a >= 0)
	{
		if (ret < _size)
			return 0;
	}
	else
	{
		if (ret > _size)
			return 0;
	}

	*_out = ret;
	return 1;
}

int SST_OS_SafeAddU16(uint16_t _a, uint16_t _b, uint16_t* _out)
{
	uint16_t ret = _a + _b;

	if (ret < _a || ret < _b)
		return 0;

	*_out = ret;
	return 1;
}

int SST_OS_SafeMultiplyU16(uint16_t _a, uint16_t _b, uint16_t* _out)
{
	uint32_t a = _a;
	uint32_t b = _b;
	uint32_t ret = a*b;

	if (ret > 0xffff)
		return 0;

	*_out = (uint16_t) ret;
	return 1;
}

int SST_OS_SafeAddU16ToSizeT(uint16_t _a, size_t _size, size_t* _out)
{
	size_t ret = _a + _size;

	if (ret < _size)
		return 0;

	*_out = ret;
	return 1;
}

int SST_OS_SafeAddI32(int32_t _a, int32_t _b, int32_t* _out)
{
	int32_t ret = _a + _b;

	/* if they are opposite signs, they cannot overflow */
	if ( (_a >= 0 && _b <= 0) ||
		(_b >= 0 && _a <= 0) )
	{
		*_out = ret;
		return 1;
	}

	/* if they are the same sign, check for overflow */
	if (_a < 0 || _b < 0)
	{
		if (ret > _a && ret > _b)
			return 0;
	}
	else
	{
		if (ret < _a && ret < _b)
			return 0;
	}

	*_out = ret;
	return 1;
}

int SST_OS_SafeAddI32ToSizeT(int32_t _a, size_t _size, size_t* _out)
{
	size_t ret = _size + _a;

	if (_a >= 0)
	{
		if (ret < _size)
			return 0;
	}
	else
	{
		if (ret > _size)
			return 0;
	}

	*_out = ret;
	return 1;
}

int SST_OS_SafeAddU32(uint32_t _a, uint32_t _b, uint32_t* _out)
{
	uint32_t ret = _a + _b;

	if (ret < _b || ret < _a)
		return 0;

	*_out = ret;
	return 1;
}

int SST_OS_SafeMultiplyU32(uint32_t _a, uint32_t _b, uint32_t* _out)
{
	uint64_t a = _a;
	uint64_t b = _b;
	uint64_t ret = a*b;

	if (ret > 0xffffffff)
		return 0;

	*_out = (uint32_t) ret;
	return 1;
}

int SST_OS_SafeAddU32ToSizeT(uint32_t _a, size_t _size, size_t* _out)
{
	size_t ret = _a + _size;

	if (ret < _size)
		return 0;

	*_out = ret;
	return 1;
}

int SST_OS_SafeAddI64(int64_t _a, int64_t _b, int64_t* _out)
{
	int64_t ret = _a + _b;

	/* if they are opposite signs, they cannot overflow */
	if ( (_a >= 0 && _b <= 0) ||
		(_b >= 0 && _a <= 0) )
	{
		*_out = ret;
		return 1;
	}

	/* if they are the same sign, check for overflow */
	if (_a < 0 || _b < 0)
	{
		if (ret > _a && ret > _b)
			return 0;
	}
	else
	{
		if (ret < _a && ret < _b)
			return 0;
	}

	*_out = ret;
	return 1;
}

int SST_OS_SafeAddI64ToSizeT(int64_t _a, size_t _size, size_t* _out)
{

	/* Positive value being added */
	if(_a >= 0)
	{
		/*
			Some weirdness with the casting: if you cast 32-bit size_t to
			a signed int64_t, it can sign extend the value. This is bad.
			We want to zero extend to 64 bits, *then* interpret that as
			a 64-bit integer. In other words, size_t -> int64_t should
			always be a positive integer, and the upper 32-bits are zero.

			On 64-bit machines where size_t is 64 bits, then the cast
			will never do a sign extend.
		*/
		const int64_t diff64 = (int64_t)((uint64_t)(SIZE_MAX - _size));

		/* Then it shouldn't matter */
		if(_a > diff64)
			return 0;	
	}
	else /* Negative value being added. */
	{
		const int64_t size64 = (int64_t)((uint64_t)_size);

		/* Ensure that if _a was added, the results
		would be > 0, otherwise it is negative we
		would overflow */
		if(size64 + _a < 0)
		{
			return 0;
		}
	}

	*_out = (size_t)_a + _size;
	return 1;
}

int SST_OS_SafeAddU64(uint64_t _a, uint64_t _b, uint64_t* _out)
{
	uint64_t ret = _a + _b;

	if (ret < _a || ret < _b)
		return 0;

	*_out = ret;
	return 1;
}

/* SLOWSLOW This is obviously correct, but not fast. Use LUTs or something. */
static int countHighestSetBitU64(uint64_t _in)
{
	int ret = 0;
	while (_in > 0)
	{
		_in >>= 1;
		ret++;
	}
	return ret;
}

/* NOTE: For explanation, see ( http://stackoverflow.com/a/199455 ). */
int SST_OS_SafeMultiplyU64(uint64_t _a, uint64_t _b, uint64_t* _out)
{
	uint64_t ret;
	int log2a;
	int log2b;

	/* special-case for 1 -- probably not needed */
	if (_a == 1 || _b == 1)
	{
		*_out = _a*_b;
		return 1;
	}

	log2a = countHighestSetBitU64(_a);
	log2b = countHighestSetBitU64(_b);

	if (log2a + log2b > 64)
		return 0;

	ret = _a*_b;
	*_out = ret;
	return 1;
}

int SST_OS_SafeAddU64ToSizeT(uint64_t _a, size_t _size, size_t* _out)
{
	const size_t diff = SIZE_MAX - _size;
	const uint64_t diff64 = (uint64_t)diff;

	if(diff64 < _a)
		return 0;

	*_out = (size_t)_a + _size;

	return 1;
}

int SST_OS_SafeAddSizeTToSizeT( size_t _a, size_t _b, size_t* _out)
{
	size_t out = _a + _b;
	if (out < _a && out < _b)
		return 0;

	*_out = out;
	return 1;
}
