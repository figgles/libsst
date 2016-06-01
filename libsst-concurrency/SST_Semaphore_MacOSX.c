/*
	SST_Semaphore_MacOSX.c
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 11/27/2012

	Purpose: 

	libsst-concurrency semaphore functions for MacOS X platform

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

/*
	MacOS X doesn't implement named POSIX semaphores, nor does it have
	a timed wait, making it utterly useless for any practical purposes.
	This implementation uses pthread condition variables/mutexes to implement
	a semaphore. It may end up replacing the POSIX semaphores implementation
	on other platforms if their implementation is crap, too.
*/

#include <SST/SST_Concurrency.h>
#include <pthread.h> /* POSIX threads stuff */
#include <sys/time.h> /* gettimeofday() */
#include <stdlib.h> /* malloc()/free() */
#include <errno.h> /* ETIMEDOUT */
#include "timespecadd.h"

/* Semaphore implementation */
typedef struct SST_Semaphore_MacOSX
{
	pthread_mutex_t mutex;
	pthread_cond_t cond;
	volatile uint32_t semaCount;	/* Semaphore's value */
	volatile uint32_t waiters;		/* Number of waiters */
} SST_Semaphore_MacOSX;


/******************************************************************************/

SST_Semaphore SST_Concurrency_CreateSemaphore(uint32_t _initialCount)
{
	SST_Semaphore_MacOSX* sema = malloc(sizeof(SST_Semaphore_MacOSX));
	
	if(sema != NULL)
	{
		pthread_mutex_init(&sema->mutex, NULL);
		pthread_cond_init(&sema->cond, NULL);
		sema->semaCount = _initialCount;
		sema->waiters = 0;
	}
	
	return (SST_Semaphore)sema;
}

/******************************************************************************/

void SST_Concurrency_DestroySemaphore(SST_Semaphore _sema)
{
	SST_Semaphore_MacOSX* sema = (SST_Semaphore_MacOSX*)_sema;
	
	pthread_mutex_destroy(&sema->mutex);
	pthread_cond_destroy(&sema->cond);
	free(sema);
}

/******************************************************************************/

void SST_Concurrency_PostSemaphore(SST_Semaphore _sema, uint32_t _count)
{
	SST_Semaphore_MacOSX* sema = (SST_Semaphore_MacOSX*)_sema;

	pthread_mutex_lock(&sema->mutex);

	if(sema->waiters > 0)
	{
		if(_count <= 1) /* Typically wake one */
			pthread_cond_signal(&sema->cond);
		else /* But if > 1, use broadcast */
			pthread_cond_broadcast(&sema->cond);
	}
	
	/* Post the count to the semaphore */
	sema->semaCount += _count;
	
	
	/* After this unlock, threads are scheduled again */
	pthread_mutex_unlock(&sema->mutex);
}

/******************************************************************************/

int SST_Concurrency_WaitSemaphore(SST_Semaphore _sema, uint32_t _ticks)
{
	int result = 0;
	SST_Semaphore_MacOSX* sema = (SST_Semaphore_MacOSX*)_sema;

	/* Infinite wait */
	if(_ticks == SST_WAIT_INFINITE)
	{
		pthread_mutex_lock(&sema->mutex);
		sema->waiters++;

		while(sema->semaCount == 0)
		{
			pthread_cond_wait(&sema->cond, &sema->mutex);
		}
		
		/* Drop count by 1 (we still hold lock) */
		sema->semaCount--;
		sema->waiters--;
		result = 1;
	}
	else /* Maximum wait measured in milliseconds */
	{
		struct timespec ts, tswait;
		struct timeval tv;
		int timeout = 0;
		
		/* Get absolute time in the future */
	 	gettimeofday(&tv, NULL);
		ts.tv_sec = tv.tv_sec;
		ts.tv_nsec = tv.tv_usec * 1000;
		tswait.tv_sec = (_ticks / 1000);  
		tswait.tv_nsec = (_ticks % 1000) * 1000 * 1000;

		_sst_add_timespec(&ts, &tswait);

		/* We do the locking now just in case locking takes a significant
		amount of time */
		pthread_mutex_lock(&sema->mutex);

		/* Wait for the condition to be signaled or a timeout */
		while(sema->semaCount == 0)
		{
			/* This is one the few POSIX functions that doesn't use errno */	
			int err = pthread_cond_timedwait(&sema->cond, &sema->mutex, &ts);
			
			if(err == ETIMEDOUT)
			{
				timeout = 1;
				break;
			}
		}
		
		/* Only decrease count if we didn't time out on the wait */
		if(!timeout)
		{
			sema->semaCount--;
			sema->waiters--;
			result = 1;
		}
		
	}

	pthread_mutex_unlock(&sema->mutex);
	return result;
}
