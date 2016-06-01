/*
	SST_WMEvent_Win32.c
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 6/25/2013

	Purpose: 

	Raspberry Pi "window" event functions

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#include <SST/SST_WMEvent.h>
#include "RaspPiPrivate.h"

/******************************************************************************/

int SST_WM_GetEvent(SST_DisplayTarget target, SST_WMEvent* eventReturn)
{
	SST_DisplayTarget_RaspPi* displayTarget = (SST_DisplayTarget_RaspPi*)target;

	/* Check for user events */
	if(RemoveFromEQ(&displayTarget->userEventQueue, eventReturn))
		return 1;

	if(RemoveFromEQ(&displayTarget->eventQueue, eventReturn))
		return 1;


	return 0;
}

/******************************************************************************/
/* These functions are used by SST_WMEvent_Common.c */
EventQueue* getUserEventQueue(SST_DisplayTarget target)
{

	SST_DisplayTarget_RaspPi* displayTarget = (SST_DisplayTarget_RaspPi*)target;
	return &displayTarget->userEventQueue;
}

void lockUserEventQueue(SST_DisplayTarget target)
{
	SST_DisplayTarget_RaspPi* displayTarget = (SST_DisplayTarget_RaspPi*)target;
	pthread_mutex_lock(&displayTarget->eventLock);
}

void unlockUserEventQueue(SST_DisplayTarget target)
{
	SST_DisplayTarget_RaspPi* displayTarget = (SST_DisplayTarget_RaspPi*)target;
	pthread_mutex_unlock(&displayTarget->eventLock);
}

