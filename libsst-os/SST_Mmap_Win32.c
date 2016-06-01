/*
	SST_Mmap_Win32.c
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 12/23/2011

	Purpose: 

	libsst-os memory mapped file I/O functions for Win32 systems (Windows 7 or later)

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#include "Win32Private.h"
#include <SST/SST_Mmap.h>
#include <SST/SST_SysMem.h> /* SST_PROTECT_XXXXX constants */
#include <SST/SST_Assert.h>

#if !defined(FILE_MAP_EXECUTE) /* Added in Windows XP SP2 */
	#define FILE_MAP_EXECUTE 0x20
#endif

static uint32_t allocGranularity;

void __libsst_init_mmapsize()
{
	SYSTEM_INFO si;

	GetNativeSystemInfo(&si);

	allocGranularity = (uint32_t)si.dwAllocationGranularity;
}


/*************************************************************************/

uint32_t SST_OS_GetMmapGranularity(void)
{
	return allocGranularity;
}

/*************************************************************************/

SST_MemoryMap SST_OS_CreateMmap(SST_File file, uint64_t offset, size_t mapLength, int mode)
{
	SST_File_Win32* fp = (SST_File_Win32*)file;
	SST_MemoryMap_Win32* mm;
	DWORD access, offsetLow, offsetHigh;
	void* ptr;

	SST_OS_DebugAssert(file != NULL, "File handle may not be NULL");
	SST_OS_DebugAssert((mode & (~(SST_PROTECT_READ|SST_PROTECT_WRITE|SST_PROTECT_EXEC))) == 0, "The mode bits may only contain SST_PROTECT_READ/WRITE/EXEC and nothing else");
	SST_OS_DebugAssert((offset & (SST_OS_GetMmapGranularity()-1)) == 0, "Offset must be aligned to system granularity. Use SST_OS_GetMmapGranuality() to determine this");
	SST_OS_DebugAssert((offset == 0 && mapLength == 0) || mapLength > 0, "Map length must be non-zero OR offset and length must both be zero (map whole file)");

	/* No file mapping yet? */
	if(fp->hMap == NULL)
	{
		DWORD pageProt;

		/* Decide on protection flags. See SST_File_Win32.c/SST_OS_OpenFile() for the 'case' values */
		switch(fp->accessFlags)
		{
			case GENERIC_READ | GENERIC_EXECUTE: pageProt = PAGE_EXECUTE_READ; break;
			case GENERIC_READ | GENERIC_WRITE | GENERIC_EXECUTE: pageProt = PAGE_EXECUTE_READWRITE; break;
			default: return NULL;
		}

		/* Actually create the file mapping */
		fp->hMap = CreateFileMappingA(fp->hFile, NULL, pageProt, 0, 0, NULL);
		if(fp->hMap == NULL)
			return NULL;
	}
	/* Windows is weird about its flags: it allows {R, W} + {X}, so only 4 combinations of
	possible values. However, the 'W' bit implies 'R'. */
	if(mode & SST_PROTECT_READ)
		access = FILE_MAP_READ;
	if(mode & SST_PROTECT_WRITE) 
		access = FILE_MAP_WRITE; /* This is actually r/w, which is why we don't use "else if(...)" */
	if(mode & SST_PROTECT_EXEC)
		access |= FILE_MAP_EXECUTE; 
	
	offsetLow = (DWORD)(offset & 0xFFFFFFFF);
	offsetHigh = (DWORD)(offset >> 32);

	/* Windows already treats a mapLength == 0 as "map to end of file". We just ensure (at the top) that
	offset == 0 so it really means "map from beginning to end". */

	ptr = MapViewOfFileEx(fp->hMap, access, offsetHigh, offsetLow, mapLength, NULL);

	if(ptr == NULL)
		return NULL;

	/* Allocate a memory map region */
	mm = (SST_MemoryMap_Win32*)HeapAlloc(GetProcessHeap(), 0, sizeof(SST_MemoryMap_Win32));
	if(mm == NULL)
	{
		UnmapViewOfFile(ptr);
		return NULL;
	}

	if(mapLength == 0)
	{
		LARGE_INTEGER size;
		GetFileSizeEx(fp->hFile, &size);

		mapLength = (size_t)size.QuadPart;
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

/*************************************************************************/

void SST_OS_DestroyMmap(SST_MemoryMap mappedRegion)
{
	SST_MemoryMap_Win32* mm = (SST_MemoryMap_Win32*)mappedRegion;

	SST_OS_DebugAssert(mappedRegion != NULL, "Memory map handle may not be NULL");

	UnmapViewOfFile(mm->base);

	#ifdef _DEBUG
	mm->base = NULL;
	mm->owner->nrMmaps--;
	#endif

	HeapFree(GetProcessHeap(), 0, mm);
}

/*************************************************************************/

void* SST_OS_GetMmapBase(SST_MemoryMap mappedRegion)
{
	SST_MemoryMap_Win32* mm = (SST_MemoryMap_Win32*)mappedRegion;

	SST_OS_DebugAssert(mappedRegion != NULL, "Memory map handle may not be NULL");

	return mm->base;
}

/*************************************************************************/

size_t SST_OS_GetMmapSize(SST_MemoryMap mappedRegion)
{
	SST_MemoryMap_Win32* mm = (SST_MemoryMap_Win32*)mappedRegion;

	SST_OS_DebugAssert(mappedRegion != NULL, "Memory map handle may not be NULL");

	return mm->len;
}

/*************************************************************************/

uint64_t SST_OS_GetMmapOffset(SST_MemoryMap mappedRegion)
{
	SST_MemoryMap_Win32* mm = (SST_MemoryMap_Win32*)mappedRegion;

	SST_OS_DebugAssert(mappedRegion != NULL, "Memory map handle may not be NULL");

	return mm->offset;
}

/*************************************************************************/

void SST_OS_SyncMmap(SST_MemoryMap mappedRegion)
{
	SST_MemoryMap_Win32* mm = (SST_MemoryMap_Win32*)mappedRegion;

	SST_OS_DebugAssert(mappedRegion != NULL, "Memory map handle may not be NULL");

	FlushViewOfFile(mm->base, mm->len);
}

