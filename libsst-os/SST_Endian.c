/*
	SST_Endian.c
	Author: Chris Ertel <crertel@762studios.com>
	Created: 1/16/2012

	Purpose: 

	libsst-os endian and byte reordering routines.

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#include <SST/SST_Endian.h>
#include <pstdint.h>

static SST_ByteOrder machineByteOrder;

void __libsst_init_endian()
{
	const uint16_t testSeq = 0x55FE;
	const uint8_t* c = (const uint8_t*)&testSeq;

	if(c[0] == 0x55)
		machineByteOrder = SST_BIG_ENDIAN;
	else
		machineByteOrder = SST_LITTLE_ENDIAN;
}

SST_ByteOrder SST_OS_GetHostEndianness( void )
{
	return machineByteOrder;
}

uint16_t SST_OS_ByteSwap16( uint16_t _toSwap)
{
	return (_toSwap >> 8) | (_toSwap << 8);
}

uint32_t SST_OS_ByteSwap32( uint32_t _toSwap)
{
	uint32_t a = (_toSwap & 0x000000ff);
	uint32_t b = (_toSwap & 0x0000ff00) >> 8;
	uint32_t c = (_toSwap & 0x00ff0000) >> 16;
	uint32_t d = (_toSwap & 0xff000000) >> 24;

	uint32_t ret = (a << 24) | (b << 16) | (c << 8) | (d);
	return ret;
}

uint64_t SST_OS_ByteSwap64( uint64_t _toSwap)
{
	uint64_t a = (_toSwap & 0x00000000000000ffull);
	uint64_t b = (_toSwap & 0x000000000000ff00ull) >> 8;
	uint64_t c = (_toSwap & 0x0000000000ff0000ull) >> 16;
	uint64_t d = (_toSwap & 0x00000000ff000000ull) >> 24;
	uint64_t e = (_toSwap & 0x000000ff00000000ull) >> 32;
	uint64_t f = (_toSwap & 0x0000ff0000000000ull) >> 40;
	uint64_t g = (_toSwap & 0x00ff000000000000ull) >> 48;
	uint64_t h = (_toSwap & 0xff00000000000000ull) >> 56;

	uint64_t ret = (a << 56) | (b << 48) | (c << 40) | (d << 32) | (e << 24) | (f << 16) | (g << 8) | h;
	return ret;
}