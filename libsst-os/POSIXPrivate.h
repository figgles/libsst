/*
	POSIXPrivate.h
	Author: Patrick Baggett <ptb1@762studios.com>
	Created: 12/23/2011

	Purpose: 

	Private data structures for POSIX implementation of libsst-os. Not to be distributed
	as part of public SDK headers.

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#pragma once

#ifndef _POSIXPRIVATE_H
#define _POSIXPRIVATE_H

/* We *really* want 64-bit support */
#define _LARGEFILE64_SOURCE
#define _FILE_OFFSET_BITS 64
#include <pstdint.h>

#include <stdlib.h> /* size_t, malloc(), free()*/
#include <unistd.h>
#include <sys/mman.h> /* mmap(), mprotect(), munmap(), etc. */

/******************************************************************************/
typedef struct SST_File_POSIX
{
	int fd;
	int isAsync; /* Is this file in async mode */

#ifdef _DEBUG
	int nrMmaps; /* Number of outstanding memory maps */
#endif
} SST_File_POSIX;

typedef struct SST_MemoryMap_POSIX
{
	uint64_t offset;	/* Offset parameter as given to SST_OS_MmapCreate() */
	size_t len;			/* Length parameter as given to SST_OS_MmapCreate() */
	void* base;			/* Returned base address from SST_OS_MmapCreate() */

#ifdef _DEBUG
	SST_File_POSIX* owner; /* File that created this memory map */
#endif
} SST_MemoryMap_POSIX;

#endif
