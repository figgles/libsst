/*
	SST_Event_POSIX.c
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 12/20/2011
	
	Purpose: 

	libsst-concurrency event functions for POSIX platforms

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/
#include <SST/SST_Event.h> /* Functions being implemented */
#include <SST/SST_Concurrency.h> /* SST_WAIT_INFINITE constant */
#include <pthread.h> /* POSIX concurrency */
#include <time.h> /* clock_gettime() */
#include <stdlib.h> /* malloc()/free() */
#include "timespecadd.h" /* inline function to add timespec*/

#ifdef __APPLE__
#include <sys/time.h>
#endif
/******************************************************************************/

typedef struct UnixEvent
{
	pthread_mutex_t lock;
	pthread_cond_t cond;
	volatile int signaled;
} UnixEvent;

/******************************************************************************/

SST_Event SST_Concurrency_CreateEvent(void)
{
	UnixEvent* ev = (UnixEvent*)malloc(sizeof(UnixEvent));
	
	pthread_mutex_init(&ev->lock, NULL);
	pthread_cond_init(&ev->cond, NULL);
	ev->signaled = 0;

	return (SST_Event)ev;
}

/******************************************************************************/

void SST_Concurrency_DestroyEvent(SST_Event _event)
{
	UnixEvent* ev = (UnixEvent*)_event;
	
	pthread_mutex_destroy(&ev->lock);
	pthread_cond_destroy(&ev->cond);
	free(ev);
}

/******************************************************************************/

void SST_Concurrency_SignalEvent(SST_Event _event)
{
	UnixEvent* ev = (UnixEvent*)_event;
	
	pthread_mutex_lock(&ev->lock);
	
	ev->signaled = 1;
	
	pthread_cond_broadcast(&ev->cond);
	pthread_mutex_unlock(&ev->lock);
}

/******************************************************************************/

void SST_Concurrency_ResetEvent(SST_Event _event)
{
	UnixEvent* ev = (UnixEvent*)_event;

	/* TODO: Optimization opportunity here: These locks aren't needed except to serialize set/reset calls. However,
	if we can leave the behavior 'undefined' for concurrent set/reset, then all that is needed is a set + membar. */
	pthread_mutex_lock(&ev->lock);
	ev->signaled = 0;
	pthread_mutex_unlock(&ev->lock);
}

/******************************************************************************/

int SST_Concurrency_WaitEvent(SST_Event _event, uint32_t _ticks)
{
	int result = 0;
	UnixEvent* ev = (UnixEvent*)_event;
	
	pthread_mutex_lock(&ev->lock);

	/* Infinite wait */
	if(_ticks == SST_WAIT_INFINITE)
	{
		while(ev->signaled == 0)
			pthread_cond_wait(&ev->cond, &ev->lock);
			
		result = 1;
	}
	else /* Maximum wait measured in milliseconds */
	{
		struct timespec ts, tswait;
		int retval = 0;
	
#ifdef __APPLE__
		/* Less precise, but getting nanosecond precision out of mach was proving exceedingly painful.*/
		struct timeval tv;
		struct timezone tz;
		tz.tz_minuteswest = 0; tz.tz_dsttime = 0;
	 	gettimeofday(&tv, &tz);
		ts.tv_sec = tv.tv_sec;
		ts.tv_nsec = tv.tv_usec * 1000;	
#else
		clock_gettime(CLOCK_REALTIME, &ts);
#endif
		tswait.tv_sec = (_ticks / 1000); 	/* add whole seconds */
		tswait.tv_nsec = (_ticks % 1000) * 1000 * 1000; /* add remaining milliseconds (converted to nanosecs by factor of 10^6) */

		_sst_add_timespec(&ts, &tswait);
		
		/* timedwait() returns 0 on success, and non-zero on failure. Spurious wakeups return 0 (success)
		 while timeouts don't. A spurious wakeup won't have ev->signaled though, so it will go back to waiting */
		while(retval == 0 && ev->signaled == 0)
			retval = pthread_cond_timedwait(&ev->cond, &ev->lock, &ts);
		
		/* If this returned success, then the condition is met AND the timeout did not expire -> success */
		result = (retval == 0);
	}
	
	pthread_mutex_unlock(&ev->lock);
	return result;
}
