/*
	SST_Semaphore_Solaris.c
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 4/11/2012

	Purpose: 

	libsst-concurrency semaphore functions using native Solaris semaphores

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#include <SST/SST_Concurrency.h>
#include <SST/SST_Semaphore.h>
#include <synch.h> /* native Solaris semaphores */
#include <time.h>
#include <stdlib.h> /* malloc()/free() */
#include <errno.h> /* errno */
#include "timespecadd.h" /* add struct timespec */

/******************************************************************************/

SST_Semaphore SST_Concurrency_CreateSemaphore(uint32_t _initialCount)
{

	sema_t* sema = (sema_t*)malloc(sizeof(sema_t));

	if(sema)
	{	
		if(sema_init(sema, (unsigned int)_initialCount, USYNC_THREAD, NULL) == 0)
			return (SST_Semaphore)sema;
	}

	return NULL;	
}

/******************************************************************************/

void SST_Concurrency_DestroySemaphore(SST_Semaphore _sema)
{
	sema_t* sema = (sema_t*)_sema;
	sema_destroy(sema);
	free(sema);
}

/******************************************************************************/

void SST_Concurrency_PostSemaphore(SST_Semaphore _sema, uint32_t _count)
{
	sema_t* sema = (sema_t*)_sema;
	while(_count)
	{
		/* sema_post() only allows 1 increment, so loop */
		sema_post(sema);
		_count--;
	}
}

/******************************************************************************/

int SST_Concurrency_WaitSemaphore(SST_Semaphore _sema, uint32_t _ticks)
{
	int result = 0;
	sema_t* sema = (sema_t*)_sema;
	int ok;
	
	if(_ticks == SST_WAIT_INFINITE)
	{
		/* Wait in a loop until we get a value OTHER than EINTR,
		or the function succeeds.
		Basically, EINTR means a signal interrupted this function,
		so we can retry the wait */
		do
		{
			ok = sema_wait(sema);
			if(ok == 0)
				break;

		} while(errno == EINTR);
		
		/* sema_wait() returns 0 on success, so see if successful */	
		result = (ok == 0);	
	}
	else /* Maximum wait measured in milliseconds */
	{
		struct timespec ts, tswait;
		
		/* get absolute time in the future */
		clock_gettime(CLOCK_REALTIME, &ts);
		tswait.tv_sec = (_ticks / 1000);  
		tswait.tv_nsec = (_ticks % 1000) * 1000 * 1000;

		_sst_add_timespec(&ts, &tswait);
		/* EINTR = signal interrupted the function. Loop until we get
		something other than a signal interruption */
		do
		{
			ok = sema_timedwait(sema, &ts);
			if(ok == 0)
				break;
		} while(errno == EINTR);
		
		/* Either success or timeout, trap legitimate errors (which
		are due to invalid conditions -> bug) */
		if(ok < 0 && errno != ETIMEDOUT)
		{
			result = 0;
		}
		else
		{
			/* If this returned success, then save that result
			as TRUE */
			result = (ok == 0);
		}
	}

	return result;
}


