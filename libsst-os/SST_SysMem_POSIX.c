/*
	SST_SysMem_POSIX.c
	Author: Patrick Baggett <ptb1@762studios.com>
	Created: 12/23/2011

	Purpose: 

	libsst-os system memory allocation functions for POSIX platforms

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#include "POSIXPrivate.h"
#include <SST/SST_SysMem.h>
#include <SST/SST_Assert.h>

#ifdef __APPLE__
#include<sys/sysctl.h>
#endif

static uint32_t cached_pagesize;

void __libsst_init_pagesize()
{
	uint32_t pgsz = (uint32_t)-1;

	#ifdef _SC_PAGESIZE
	pgsz = (uint32_t)sysconf(_SC_PAGESIZE);
	#elif defined(_SC_PAGE_SIZE)
	if(pgsz == (uint32_t)-1)
		pgsz = (uint32_t)sysconf(_SC_PAGE_SIZE);
	#endif

	cached_pagesize = pgsz;
}

/******************************************************************************/

uint64_t SST_OS_GetMemorySize()
{
#ifdef __APPLE__
	int param[2] = { CTL_HW, HW_MEMSIZE };
	uint64_t mem;
	size_t size = sizeof(mem);
	sysctl(param, 2, &mem, &size, NULL, 0);
	return mem;
#else
	uint32_t pagesize = SST_OS_GetPageSize();
	uint32_t pages;

	pages = sysconf(_SC_PHYS_PAGES);
	if(pages == (uint32_t)-1)
		return 0;

	return (uint64_t)pages*(uint64_t)pagesize;
#endif
}

/******************************************************************************/

uint32_t SST_OS_GetPageSize()
{
	return cached_pagesize;
}

/******************************************************************************/

void* SST_OS_AllocPages(size_t allocBytes)
{
	void* addr;
	#if defined(MAP_ANON) && !defined(MAP_ANONYMOUS)
	int flags = MAP_SHARED | MAP_ANON;
	#else
	int flags = MAP_SHARED | MAP_ANONYMOUS;
	#endif

	SST_OS_DebugAssert(allocBytes > 0, "Allocating 0 bytes is not allowed");
	
	#ifdef MAP_UNINITIALIZED /* Linux only,  2.6.33+, don't zero pages */
	flags |= MAP_UNINITIALIZED;
	#endif

	addr = mmap(NULL, allocBytes, PROT_READ | PROT_WRITE, flags, -1, 0);

	if(addr == MAP_FAILED)
		return NULL;

	return addr;
}

/******************************************************************************/

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
	return (munmap(pageBase, nrBytes) == 0);
}

/******************************************************************************/

int SST_OS_ProtectPages(void* pageBase, size_t nrBytes, int protectFlags)
{
	uintptr_t addr;
	uint32_t pageSize;
	int newFlags = 0;

	SST_OS_DebugAssert(pageBase != NULL, "Base address may not be NULL");
	SST_OS_DebugAssert(nrBytes > 0, "The number of bytes to free may not be zero");
	SST_OS_DebugAssert((protectFlags & (~(SST_PROTECT_READ|SST_PROTECT_WRITE|SST_PROTECT_EXEC))) == 0, "Protect flags contain invalid bits");

	addr = (uintptr_t)pageBase;
	pageSize = SST_OS_GetPageSize();

	/* Check if address is aligned to page boundary */
	if(addr & (pageSize-1))
		return -1;

	if(protectFlags & SST_PROTECT_READ)
		newFlags |= PROT_READ;
	if(protectFlags & SST_PROTECT_WRITE)
		newFlags |= PROT_WRITE;
	if(protectFlags & SST_PROTECT_EXEC)
		newFlags |= PROT_EXEC;

	return (mprotect(pageBase, nrBytes, newFlags) == 0);
}

