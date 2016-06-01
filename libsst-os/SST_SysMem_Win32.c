/*
	SST_SysMem_Win32.c
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 12/23/2011

	Purpose: 

	libsst-os system memory allocation functions for Win32 platforms (Windows 7 or later)

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#include "Win32Private.h"
#include <SST/SST_SysMem.h>
#include <SST/SST_Assert.h>

static uint32_t cached_pagesize;

void __libsst_init_pagesize()
{
	SYSTEM_INFO info;
	GetNativeSystemInfo(&info);

	cached_pagesize = (uint32_t)info.dwPageSize;
}

/* Round an allocation of 'amount' bytes to be a multiple of 'pageSize' */
static size_t roundToPage(uint32_t pageSize, size_t amount)
{
	size_t rounded;

	/* ASSUMPTION: pageSize is a power of two */
	
	/*
		Algorithm: Round up allocation to the nearest page.
		
		[1] x & (pageSize-1)    = Bytes that are extra parts of a page
		[2] x & (~(pageSize-1)) = Bytes that are whole pages.

		Start with [2] bytes. If [1] is non-zero, then add page size.
	*/
	rounded = amount & (~(pageSize-1));
	if(amount & (pageSize-1))
		rounded += pageSize;

	return rounded;
}

/*************************************************************************/

uint64_t SST_OS_GetMemorySize()
{
	ULONGLONG mem = 0;

	if(GetPhysicallyInstalledSystemMemory(&mem))
		return (uint64_t)mem;

	return 0;
}

/*************************************************************************/

uint32_t SST_OS_GetPageSize()
{
	return cached_pagesize;
}

/*************************************************************************/

void* SST_OS_AllocPages(size_t allocBytes)
{
	SST_OS_DebugAssert(allocBytes > 0, "Allocating 0 bytes is not allowed");

	return VirtualAllocEx(GetCurrentProcess(), NULL, roundToPage(SST_OS_GetPageSize(), allocBytes), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
}

/*************************************************************************/

int SST_OS_FreePages(void* pageBase, size_t nrBytes)
{
	uintptr_t addr;
	uint32_t pageSize;

	SST_OS_DebugAssert(pageBase != NULL, "Base address may not be NULL");
	SST_OS_DebugAssert(nrBytes > 0, "The number of bytes to free may not be zero");

	addr = (uintptr_t)pageBase;
	pageSize = SST_OS_GetPageSize();

	/* Check if address is aligned to page boundary */
	if(addr & (pageSize-1))
		return -1;

	/* Free the pages */
	if(VirtualFreeEx(GetCurrentProcess(), pageBase, roundToPage(pageSize, nrBytes), MEM_DECOMMIT | MEM_RELEASE) != 0)
		return 1;

	return 0;
}

/*************************************************************************/

int SST_OS_ProtectPages(void* pageBase, size_t nrBytes, int protectFlags)
{
	uintptr_t addr;
	uint32_t pageSize;
	DWORD newFlags = PAGE_NOACCESS;

	SST_OS_DebugAssert(pageBase != NULL, "Base address may not be NULL");
	SST_OS_DebugAssert(nrBytes > 0, "The number of bytes to free may not be zero");


	addr = (uintptr_t)pageBase;
	pageSize = SST_OS_GetPageSize();

	/* Check if address is aligned to page boundary */
	if(addr & (pageSize-1))
		return -1;

	/* Microsoft doesn't believe in bitfields. This switch brought to you by a poor design decision */
	switch(protectFlags)
	{
		/* r/o  */
		case SST_PROTECT_READ: newFlags = PAGE_READONLY; break;

		/* r/w, w/o */
		case SST_PROTECT_READ | SST_PROTECT_WRITE:
		case SST_PROTECT_WRITE: newFlags = PAGE_READWRITE; break; /* Win32 doesn't have w/o */

		/* x/o */
		case SST_PROTECT_EXEC: newFlags = PAGE_EXECUTE; break;

		/* w/x */
		case SST_PROTECT_WRITE | SST_PROTECT_EXEC: newFlags = PAGE_EXECUTE_READWRITE; break;

		/* r/x */
		case SST_PROTECT_READ | SST_PROTECT_EXEC: newFlags = PAGE_EXECUTE_READ; break;

		/* r/w/x */
		case SST_PROTECT_READ | SST_PROTECT_WRITE | SST_PROTECT_EXEC: newFlags = PAGE_EXECUTE_READWRITE; break;
	}
	
	if(VirtualProtectEx(GetCurrentProcess(), (void*)addr, roundToPage(pageSize, nrBytes), newFlags, NULL) != 0)
		return 1;

	return 0;
}

