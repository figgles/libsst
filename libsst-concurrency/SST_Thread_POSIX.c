/*
	SST_Thread_POSIX.c
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 12/20/2011
	
	Purpose: 

	libsst-concurrency thread functions for POSIX platforms

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/
#include <pthread.h> /* POSIX threads API */
#include <unistd.h> /* usleep() */
#include <stdlib.h> /* malloc()/free() */
#include <sched.h> /* sched_yield() */
#include <errno.h> /* system error codes */
#include <time.h> /* nanosleep() */

#include <pstdint.h>
#include <SST/SST_Thread.h>

/* Less-than-POSIX madness. Used for getting the thread ID, which POSIX decided to leave out... /rage */
#if defined(__linux__) && !defined(__ANDROID__)
	#include <sys/syscall.h>
#endif

#ifdef __FreeBSD__
	#include <sys/thr.h>
#endif

#ifdef __APPLE__
	#include <sys/time.h>
	#include <mach/mach_init.h>
#endif

SST_Thread SST_Concurrency_CreateThread(int(*_func)(void*), void *_arg)
{
	pthread_t* thr;
	
	#ifdef _DEBUG
	if(_func == (int(*)(void*))NULL)
		return NULL;
	#endif
	
	thr =(pthread_t*)malloc(sizeof(pthread_t));
	
	/* Create the thread */
	if(pthread_create(thr, NULL, (void*(*)(void*))_func, _arg) != 0)
	{
		free(thr);
		return NULL;
	}
	
	return (SST_Thread)thr;
}

void SST_Concurrency_DestroyThread(SST_Thread _thr)
{
	pthread_t* thr = (pthread_t*)_thr;
	
	pthread_detach(*thr);
	
	free(thr);
}

void SST_Concurrency_SleepThread(uint32_t _ms)
{
	struct timespec req, rem;
	long msecs  = _ms % 1000; /* milliseconds that are less than 1 sec (0-999) */
	rem.tv_sec = _ms / 1000; /* msec -> sec by mult 1e-3 */
	rem.tv_nsec = msecs * (1000 * 1000); /* msec -> nsec by mult 1e6 */


	/* Sleep, continuing if woken up by EINTR (POSIX signal) */
	do
	{
		/* On EINTR, 'rem' contains the remaining time that has not yet
		been slept. */
		req = rem;
		if(nanosleep(&req, &rem) == 0) /* 0 == success */
			break;
	} while(errno == EINTR);

}

uint32_t SST_Concurrency_GetThreadId()
{
#if defined(__APPLE__)
	return (uint32_t)mach_thread_self();
#elif defined(__FreeBSD__)
	long lwpid;
	
	thr_self(&lwpid);
	return (uint32_t)lwpid;
#elif defined(__ANDROID__)
	return (uint32_t)pthread_self(); /* Android uses integer as pthread_t */
#elif defined(__linux__)
	return (uint32_t)syscall(SYS_gettid); /* kinda hacky but works */
#else
	#error Need Thread ID implementation for your OS
#endif

}

uint64_t SST_Concurrency_GetTicks(void)
{
#if defined(__APPLE__)
	struct timeval tv;
	struct timezone tz; tz.tz_minuteswest = 0; tz.tz_dsttime = 0;
	gettimeofday(&tv, &tz);

	return ((uint64_t) tv.tv_sec * 1000) + ((uint64_t)tv.tv_usec / 1000); 

#else

	struct timespec tv;

	clock_gettime(CLOCK_REALTIME, &tv);

	return ((uint64_t)tv.tv_sec * 1000) + ((uint64_t)tv.tv_nsec / 1000000);	
#endif
}

int SST_Concurrency_WaitThread(SST_Thread _thr, int* _retval)
{
	pthread_t* thr = (pthread_t*)_thr;
	void* thrRetval;
	int join_retval;
	
	/* Join, capturing the return value */
	if(_retval)
	{
		uintptr_t masked;
		join_retval = pthread_join(*thr, &thrRetval);
		
		
		masked = (uintptr_t)thrRetval;
		*_retval = (int)masked;
	}
	else
		join_retval = pthread_join(*thr, NULL);


	return (join_retval == 0);
}

void SST_Concurrency_YieldThread(void)
{
	sched_yield();
}

