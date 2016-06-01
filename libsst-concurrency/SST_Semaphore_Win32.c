/*
	SST_Semaphore_Win32.c
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 12/20/2011

	Purpose: 

	libsst-concurrency semaphore functions for Win32 platforms (Windows 7 or later)

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#include <SST/SST_Concurrency.h> /* SST_WAIT_INFINITE */

#define _WIN32_WINNT 0x0601 /* Windows 7 or later */
#include <windows.h>

/*************************************************************************/

SST_Semaphore SST_Concurrency_CreateSemaphore(uint32_t _initialCount)
{
	/* Windows wants a maximum count, so 2^31-1 */
	HANDLE hSema = CreateSemaphoreA(NULL, _initialCount, (LONG)INT32_MAX, NULL);

	return (SST_Semaphore)hSema;
}

/*************************************************************************/

void SST_Concurrency_DestroySemaphore(SST_Semaphore _sema)
{
	HANDLE hSema = (HANDLE)_sema;

	CloseHandle(hSema);
}

/*************************************************************************/

void SST_Concurrency_PostSemaphore(SST_Semaphore _sema, uint32_t _count)
{
	HANDLE hSema = (HANDLE)_sema;

	ReleaseSemaphore(hSema, _count, NULL);
}

/*************************************************************************/

int SST_Concurrency_WaitSemaphore(SST_Semaphore _sema, uint32_t _ticks)
{
	HANDLE hSema = (HANDLE)_sema;
	DWORD dwTime;

	if(_ticks == SST_WAIT_INFINITE)
		dwTime = INFINITE;
	else
		dwTime = (DWORD)_ticks;

	return (WaitForSingleObject(hSema, dwTime) == WAIT_OBJECT_0);
}
