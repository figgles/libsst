/*
	SST_Alloc.c
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 1/7/2012

	Purpose: 

	Provides portable implementations for various CRT-like memory functions

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#include <SST/SST_Alloc.h>
#include <SST/SST_Assert.h>
#include <stdio.h>
#include <pstdint.h>
#include <limits.h>

#define OVERFLOW_MESSAGE "Multiplication overflow in memory allocation"

/*************************************************************************/

void* SST_OS_AlignPtr(void* ptr, size_t boundary)
{
	if ((((uintptr_t)ptr) % boundary) == 0)
		return ptr;

	return (void*)((uintptr_t)ptr + (boundary) - ((uintptr_t)ptr % boundary));
}

/*************************************************************************/

void* SST_OS_AlignedMalloc(size_t bytes, size_t boundary)
{
	uintptr_t mask;
	uintptr_t addr;
	unsigned char delta;
	void* base;
	unsigned char* backptr;

	if(boundary == 0 || boundary > UCHAR_MAX)
		return NULL;

	mask = (uintptr_t)(boundary - 1);

	/* Check if not a power 2 */
	if(boundary & mask)
		return NULL;

	/* Allocate memory with some slack space */
	base = malloc(bytes + boundary);
	if(base == NULL)
		return NULL;

	/* Get aligned address. It'll be somewhere in the extra slackspace that we just malloc()'d */
	addr = ((uintptr_t)base + boundary - 1) & mask;

	/* Address was already aligned...but the free function expects a backtrack amount */
	if(addr == (uintptr_t)base)
		addr += boundary;

	delta = (unsigned char)((addr - (uintptr_t)base) & 0xFF);

	backptr = (unsigned char*)(addr-1);
	*backptr = delta-1;

	return (void*)addr;
}

/*************************************************************************/

void SST_OS_AlignedFree(void* ptr)
{
	unsigned char* back = ((unsigned char*)ptr) - 1;
	unsigned char delta;

	delta = *back;

	back = back - delta;

	free(back);
}

/*************************************************************************/

void* SST_OS_SafeAlignedMalloc(size_t nelem, size_t elsize, size_t boundary)
{
	if(nelem > SIZE_MAX/elsize)
	{
		SST_OS_RuntimeError(OVERFLOW_MESSAGE);

		/* If app just swallows the error, then return NULL */
		return NULL;
	}
	return SST_OS_AlignedMalloc(nelem*elsize, boundary);
}

/*************************************************************************/

void* SST_OS_SafeRealloc(void* ptr, size_t nelem, size_t elsize)
{
	if(nelem > SIZE_MAX/elsize)
	{
		SST_OS_RuntimeError(OVERFLOW_MESSAGE);

		/* If app just swallows the error, then return NULL */
		return NULL;
	}

	return realloc(ptr, nelem * elsize);
}
