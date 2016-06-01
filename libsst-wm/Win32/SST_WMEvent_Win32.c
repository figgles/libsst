/*
	SST_WMEvent_Win32.c
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 6/5/2012

	Purpose: 

	Window event functions

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#include <SST/SST_WMEvent.h>
#include "Win32Private.h"
#include "../APIPrivate.h"
static void copyAndRemoveUserEvent(SST_DisplayTarget_Win32* displayTarget, SST_WMEvent* eventReturn);

/*************************************************************************/

static int Win32_GetEvent(SST_DisplayTarget target, SST_WMEvent* eventReturn)
{
	MSG msg;
	SST_DisplayTarget_Win32* displayTarget = (SST_DisplayTarget_Win32*)target;
	SST_Window_Win32* win;
	int found = 0;

	/* First, get Win32 messages and dispatch to winproc. We
	do this immediately, otherwise the OS thinks we've hung. */
	while(PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessageA(&msg);	
	}

	/* Check for user events */
	if(RemoveFromEQ(&displayTarget->userEventQueue, eventReturn))
		return 1;

	/* Now check each window's event queue */
	win = displayTarget->firstWindow;
	while(win)
	{
		if(RemoveFromEQ(&win->eventQueue, eventReturn))
		{
			found = 1;
			break;
		}

		win = win->next;
	}

	return found;
}

/*************************************************************************/

/* Platform-specific code dealing with user event queue */

static void Win32_lockUserEventQueue(SST_DisplayTarget target)
{
	SST_DisplayTarget_Win32* displayTarget = (SST_DisplayTarget_Win32*)target;
	EnterCriticalSection(&displayTarget->userEventLock);
}

static void Win32_unlockUserEventQueue(SST_DisplayTarget target)
{
	SST_DisplayTarget_Win32* displayTarget = (SST_DisplayTarget_Win32*)target;
	LeaveCriticalSection(&displayTarget->userEventLock);
}

static EventQueue* Win32_getUserEventQueue(SST_DisplayTarget target)
{

	SST_DisplayTarget_Win32* displayTarget = (SST_DisplayTarget_Win32*)target;
	return &displayTarget->userEventQueue; 
}

const struct SST_WM_EventFuncs Win32_EventFuncs = {
	Win32_GetEvent,
	Win32_getUserEventQueue,
	Win32_lockUserEventQueue,
	Win32_unlockUserEventQueue
};
