/*
	SST_Event_Solaris.c
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 4/11/2012
	
	Purpose: 

	libsst-concurrency event functions using native Solaris primitives

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/
#include <SST/SST_Event.h> /* Functions being implemented */
#include <SST/SST_Concurrency.h> /* SST_WAIT_INFINITE constant */
#include <thread.h> /* POSIX concurrency */
#include <time.h> /* clock_gettime() */
#include <stdlib.h> /* malloc()/free() */
#include "timespecadd.h" /* inline function to add timespec*/
#include <atomic.h> /* membar_producer() */

/******************************************************************************/

typedef struct SolarisEvent
{
	mutex_t lock;
	cond_t cond;
	volatile int signaled;
} SolarisEvent;

/******************************************************************************/

SST_Event SST_Concurrency_CreateEvent(void)
{
	SolarisEvent* ev = (SolarisEvent*)malloc(sizeof(SolarisEvent));
	
	mutex_init(&ev->lock, USYNC_THREAD, NULL);
	cond_init(&ev->cond, USYNC_THREAD, NULL);
	ev->signaled = 0;

	return (SST_Event)ev;
}

/******************************************************************************/

void SST_Concurrency_DestroyEvent(SST_Event _event)
{
	SolarisEvent* ev = (SolarisEvent*)_event;
	
	mutex_destroy(&ev->lock);
	cond_destroy(&ev->cond);
	free(ev);
}

/******************************************************************************/

void SST_Concurrency_SignalEvent(SST_Event _event)
{
	SolarisEvent* ev = (SolarisEvent*)_event;
	
	mutex_lock(&ev->lock);
	
	ev->signaled = 1;
	
	cond_broadcast(&ev->cond);
	mutex_unlock(&ev->lock);
}

/******************************************************************************/

void SST_Concurrency_ResetEvent(SST_Event _event)
{
	SolarisEvent* ev = (SolarisEvent*)_event;

	
	ev->signaled = 0;
	membar_producer(); /* all stores reach global visibility before new stores */
}

/******************************************************************************/

int SST_Concurrency_WaitEvent(SST_Event _event, uint32_t _ticks)
{
	int result = 0;
	SolarisEvent* ev = (SolarisEvent*)_event;
	
	mutex_lock(&ev->lock);

	/* Infinite wait */
	if(_ticks == SST_WAIT_INFINITE)
	{
		while(ev->signaled == 0)
			cond_wait(&ev->cond, &ev->lock);
			
		result = 1;
	}
	else /* Maximum wait measured in milliseconds */
	{
		struct timespec ts, tswait;
		int retval = 0;

		clock_gettime(CLOCK_REALTIME, &ts);

		tswait.tv_sec = (_ticks / 1000); 	/* add whole seconds */
		tswait.tv_nsec = (_ticks % 1000) * 1000 * 1000; /* add remaining milliseconds (converted to nanosecs by factor of 10^6) */

		_sst_add_timespec(&ts, &tswait);
		
		/* timedwait() returns 0 on success, and non-zero on failure. Spurious wakeups return 0 (success)
		 while timeouts don't. A spurious wakeup won't have ev->signaled though, so it will go back to waiting */
		while(retval == 0 && ev->signaled == 0)
			retval = cond_timedwait(&ev->cond, &ev->lock, &ts);
		
		/* If this returned success, then the condition is met AND the timeout did not expire -> success */
		result = (retval == 0);
	}
	
	mutex_unlock(&ev->lock);
	return result;
}
