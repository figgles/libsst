/*
	SST_Thread_Win32.c
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 12/20/2011

	Purpose: 

	libsst-concurrency thread functions for Win32 platforms (Windows 7 or later)

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#include <SST/SST_Thread.h>

#define _WIN32_WINNT 0x0601 /* Windows 7 or later */
#include <windows.h>
#include <process.h> /* _beginthreadex() */

struct WrapStdcallData
{
	int (*func)(void*); /* Function to call */
 	void* arg; /* Arg for said function */
};

/*************************************************************************/

/* OS really need "unsigned int" data type here, don't change! */
static unsigned int __stdcall wrapStdcall(void* arg)
{
	struct WrapStdcallData* info = (struct WrapStdcallData*)arg;
	struct WrapStdcallData thrData;
	int retval;

	/* Copy data to local variable */
	thrData.arg = info->arg;
	thrData.func = info->func;

	/* Free the allocated copy */
	HeapFree(GetProcessHeap(), 0, arg);

	/* Call user supplied function */
	retval = thrData.func(thrData.arg);

	/* This actually kills the thread */
	return (unsigned int)retval;
}

/*************************************************************************/

SST_Thread SST_Concurrency_CreateThread(SST_ThreadFunc _func, void *_arg)
{
	HANDLE hNewThread;
	struct WrapStdcallData* info;

	/* Allocate heap structure to pass between threads */
	info = HeapAlloc(GetProcessHeap(), 0, sizeof(struct WrapStdcallData));
	if(!info)
		return NULL;
	info->arg = _arg;
	info->func = _func;

	/* Create the thread, and return the handle immediately on success */
	hNewThread = (HANDLE)_beginthreadex(NULL, 0, wrapStdcall, info, 0, NULL);
	if(hNewThread != NULL)
		return (SST_Thread)hNewThread;

	/* Not successful -- don't leak memory */
	free(info);
	return (SST_Thread)NULL;
}

/*************************************************************************/

void SST_Concurrency_DestroyThread(SST_Thread _thr)
{
	HANDLE hThread = (HANDLE)_thr;

	CloseHandle(hThread);
}

/*************************************************************************/

void SST_Concurrency_SleepThread(uint32_t _ms)
{
	ULONGLONG now;
	ULONGLONG done;

	/* Get the time now, and the time in the future for when it should be done */
	now = SST_Concurrency_GetTicks();
	done = now + (ULONGLONG)_ms;

	/* Do a cursory sleep. This can sleep less than the required time, per MSDN.*/
	Sleep((DWORD)_ms);

	/* Now, if didn't sleep enough, then do small sleeps until we did. */
	while(SST_Concurrency_GetTicks() < done)
		Sleep(1);
}

/*************************************************************************/

uint32_t SST_Concurrency_GetThreadId()
{
	return (uint32_t)GetCurrentThreadId();
}

/*************************************************************************/

uint64_t SST_Concurrency_GetTicks(void)
{
#if defined(__GNUC__)
	static ULONGLONG (WINAPI* pf_GetTickCount64)(void) = NULL;
	
	if(pf_GetTickCount64 == NULL)
	{
		pf_GetTickCount64 = (ULONGLONG (WINAPI*)(void))GetProcAddress(GetModuleHandleA("kernel32.dll"), "GetTickCount64"); 
	}
	return (uint64_t)pf_GetTickCount64();
#else
	return (uint64_t)GetTickCount64();
#endif
}

/*************************************************************************/

int SST_Concurrency_WaitThread(SST_Thread _thr, int* _retval)
{
	HANDLE hThread = (HANDLE)_thr;
	DWORD exitCode;
	int waitOk = 0;

	/* Wait for the thread to exit */
	if(WaitForSingleObject(hThread, INFINITE) == WAIT_OBJECT_0)
	{
		/* Is a return value wanted? */
		if(_retval)
		{
			/* OK, try and get it */
			if(GetExitCodeThread(hThread, &exitCode))
			{
				*_retval = (int)exitCode;
				waitOk = 1;
			}
		}
		else /* No return code wanted, so we're good */
			waitOk = 1;
	}

	return waitOk;
}

/*************************************************************************/

void SST_Concurrency_YieldThread(void)
{
	/* Attempt to schedule a different thread. False -> nothing to do */
	if(SwitchToThread() == FALSE)
		Sleep(1); /* Nothing to do -> sleeeeeep */
}
