/*
	SST_Event_Win32.c
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 12/20/2011

	Purpose: 

	libsst-concurrency event functions for Win32 platforms (Windows 7 or later)

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

SST_Event SST_Concurrency_CreateEvent(void)
{
	HANDLE hEvent = CreateEventA(NULL, TRUE, FALSE, NULL);

	return (SST_Event)hEvent;
}

/*************************************************************************/

void SST_Concurrency_DestroyEvent(SST_Event _event)
{
	HANDLE hEvent = (HANDLE)_event;

	CloseHandle(hEvent);
}

/*************************************************************************/

void SST_Concurrency_SignalEvent(SST_Event _event)
{
	HANDLE hEvent = (HANDLE)_event;

	SetEvent(hEvent);
}

/*************************************************************************/

void SST_Concurrency_ResetEvent(SST_Event _event)
{
	HANDLE hEvent = (HANDLE)_event;

	ResetEvent(hEvent);
}

/*************************************************************************/

int SST_Concurrency_WaitEvent(SST_Event _event, uint32_t _ticks)
{
	HANDLE hEvent = (HANDLE)_event;
	DWORD dwTime;

	if(_ticks == SST_WAIT_INFINITE)
		dwTime = INFINITE;
	else
		dwTime = (DWORD)_ticks;

	return (WaitForSingleObject(hEvent, dwTime) == WAIT_OBJECT_0);
}
