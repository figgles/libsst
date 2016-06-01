/*
	SST_Mutex_Win32.c
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 12/20/2011

	Purpose: 

	libsst-concurrency mutex functions for Win32 platforms (Windows 7 or later)

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#include <SST/SST_Mutex.h>

#define _WIN32_WINNT 0x0601 /* Windows 7 or later */
#include <windows.h>

#define SST_DEFAULT_SPINCOUNT 5500

/*************************************************************************/

SST_Mutex SST_Concurrency_CreateMutex(void)
{
	CRITICAL_SECTION* cs = HeapAlloc(GetProcessHeap(), 0, sizeof(CRITICAL_SECTION));

	/* No memory? */
	if(!cs)
		return NULL;

	InitializeCriticalSectionAndSpinCount(cs, SST_DEFAULT_SPINCOUNT);

	return (SST_Mutex)cs;
}

/*************************************************************************/

void SST_Concurrency_DestroyMutex(SST_Mutex _mutex)
{
	CRITICAL_SECTION* cs = (CRITICAL_SECTION*)_mutex;

	DeleteCriticalSection(cs);
	HeapFree(GetProcessHeap(), 0, cs);
}

/*************************************************************************/

void SST_Concurrency_LockMutex(SST_Mutex _mutex)
{
	CRITICAL_SECTION* cs = (CRITICAL_SECTION*)_mutex;

	EnterCriticalSection(cs);
}

/*************************************************************************/

int SST_Concurrency_TryLockMutex(SST_Mutex _mutex)
{
	CRITICAL_SECTION* cs = (CRITICAL_SECTION*)_mutex;

	return (int)TryEnterCriticalSection(cs);
}

/*************************************************************************/

void SST_Concurrency_UnlockMutex(SST_Mutex _mutex)
{
	CRITICAL_SECTION* cs = (CRITICAL_SECTION*)_mutex;
	LeaveCriticalSection(cs);
}

