/*
	SST_Mmap_POSIX.c
	Author: Patrick Baggett <ptb1@762studios.com>
	Created: 12/23/2011

	Purpose: 

	libsst-os memory mapped file I/O functions for POSIX

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#include "POSIXPrivate.h"
#include <sys/stat.h>
#include <SST/SST_Mmap.h>
#include <SST/SST_SysMem.h> /* SST_PROTECT_XXXXX constants, SST_OS_GetPageSize() */
#include <SST/SST_Assert.h>

void __libsst_init_mmapsize() { /* Not used on POSIX */ }

/******************************************************************************/

uint32_t SST_OS_GetMmapGranularity(void)
{
	return SST_OS_GetPageSize();
}

/******************************************************************************/

SST_MemoryMap SST_OS_CreateMmap(SST_File file, uint64_t offset, size_t mapLength, int mode)
{
	SST_File_POSIX* fp = (SST_File_POSIX*)file;
	SST_MemoryMap_POSIX* mm;
	int access = 0;
	void* ptr;
	off_t off;

	SST_OS_DebugAssert(file != NULL, "File handle may not be NULL");
	SST_OS_DebugAssert((mode & (~(SST_PROTECT_READ|SST_PROTECT_WRITE|SST_PROTECT_EXEC))) == 0, "The mode bits may only contain SST_PROTECT_READ/WRITE/EXEC and nothing else");
	SST_OS_DebugAssert((offset & (SST_OS_GetMmapGranularity()-1)) == 0, "Offset must be aligned to system granularity. Use SST_OS_GetMmapGranuality() to determine this");
	SST_OS_DebugAssert( (offset == 0 && mapLength == 0) || mapLength > 0, "Map length must be non-zero OR offset and length must both be zero (map whole file)");

	if(mode & SST_PROTECT_READ)
		access |= PROT_READ;;
	if(mode & SST_PROTECT_WRITE) 
		access |= PROT_WRITE;
	if(mode & SST_PROTECT_EXEC)
		access |= PROT_EXEC;
	
	off = (off_t)offset;
	
	/* Map whole file */
	if(mapLength == 0)
	{
		struct stat s;
		if(fstat(fp->fd, &s) == 0)
			mapLength = (size_t)s.st_size;
		else /* fstat() failed, try lseek() */
		{
			off_t here, end;
			
			here = lseek(fp->fd, 0, SEEK_CUR);
			end = lseek(fp->fd, 0, SEEK_END);
			
			/* failed? */
			if(here == (off_t)-1 || end == (off_t)-1)
				return NULL;
			
			mapLength = (size_t)end;
			
			/* Restore file position (not that it matters much if you mmap() the whole thing) */
			lseek(fp->fd, here, SEEK_SET);
		}
		
	}
	
	ptr = mmap(NULL, mapLength, access, MAP_SHARED, fp->fd, off);
		
	if(ptr == MAP_FAILED)
		return NULL;

	/* Allocate a memory map region */
	mm = (SST_MemoryMap_POSIX*)malloc(sizeof(SST_MemoryMap_POSIX));
	if(mm == NULL)
	{
		munmap(ptr, mapLength);
		return NULL;
	}

	mm->offset = offset;
	mm->len = mapLength;
	mm->base = ptr;
	#ifdef _DEBUG
	mm->owner = fp;
	fp->nrMmaps++;
	#endif

	return (SST_MemoryMap)mm;
}

/******************************************************************************/

void SST_OS_DestroyMmap(SST_MemoryMap mappedRegion)
{
	SST_MemoryMap_POSIX* mm = (SST_MemoryMap_POSIX*)mappedRegion;

	SST_OS_DebugAssert(mappedRegion != NULL, "Memory map handle may not be NULL");

	munmap(mm->base, mm->len);

	#ifdef _DEBUG
	mm->base = NULL;
	mm->owner->nrMmaps--;
	#endif

	free(mm);
}

/******************************************************************************/

void* SST_OS_GetMmapBase(SST_MemoryMap mappedRegion)
{
	SST_MemoryMap_POSIX* mm = (SST_MemoryMap_POSIX*)mappedRegion;

	SST_OS_DebugAssert(mappedRegion != NULL, "Memory map handle may not be NULL");

	return mm->base;
}

/******************************************************************************/

size_t SST_OS_GetMmapSize(SST_MemoryMap mappedRegion)
{
	SST_MemoryMap_POSIX* mm = (SST_MemoryMap_POSIX*)mappedRegion;

	SST_OS_DebugAssert(mappedRegion != NULL, "Memory map handle may not be NULL");

	return mm->len;
}

/******************************************************************************/

uint64_t SST_OS_GetMmapOffset(SST_MemoryMap mappedRegion)
{
	SST_MemoryMap_POSIX* mm = (SST_MemoryMap_POSIX*)mappedRegion;

	SST_OS_DebugAssert(mappedRegion != NULL, "Memory map handle may not be NULL");

	return mm->offset;
}

/******************************************************************************/

void SST_OS_SyncMmap(SST_MemoryMap mappedRegion)
{
	SST_MemoryMap_POSIX* mm = (SST_MemoryMap_POSIX*)mappedRegion;

	SST_OS_DebugAssert(mappedRegion != NULL, "Memory map handle may not be NULL");

	/* Synchronize with the OS, but do so async */
	msync(mm->base, mm->len, MS_ASYNC);
}

