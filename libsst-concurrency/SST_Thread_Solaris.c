/*
	SST_Thread_Solaris.c
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 4/11/2012
	
	Purpose: 

	libsst-concurrency thread functions using Solaris native threads

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/
#include <thread.h> /* Solaris native threads */
#include <unistd.h> /* usleep() */
#include <errno.h> /* system error codes */
#include <time.h> /* nanosleep() */
#include <sys/syscall.h>

#include <pstdint.h>
#include <SST/SST_Thread.h>

/******************************************************************************/

SST_Thread SST_Concurrency_CreateThread(int(*_func)(void*), void *_arg)
{
	thread_t thr;
	
	#ifdef _DEBUG
	if(_func == (int(*)(void*))NULL)
		return NULL;
	#endif
		
	/* Create the thread */
	if(thr_create(NULL, 0, (void*(*)(void*))_func, _arg, THR_BOUND, &thr) != 0)
		return NULL;
	
	return (SST_Thread)thr;
}

/******************************************************************************/

void SST_Concurrency_DestroyThread(SST_Thread _thr)
{
	/* Detach the thread. This uses the direct system call
	since there is no thr_detach() function. This has
	been tested to work on Solaris 10. */ 
	syscall(SYS_lwp_detach, (thread_t)_thr);
}

/******************************************************************************/

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

/******************************************************************************/

uint32_t SST_Concurrency_GetThreadId()
{
	return (uint32_t)thr_self();
}

/******************************************************************************/

uint64_t SST_Concurrency_GetTicks(void)
{
	struct timespec tv;

	clock_gettime(CLOCK_MONOTONIC, &tv);

	return ((uint64_t)tv.tv_sec * 1000) + ((uint64_t)tv.tv_nsec / 1000000);	
}

/******************************************************************************/

int SST_Concurrency_WaitThread(SST_Thread _thr, int* _retval)
{
	thread_t thr = (thread_t)_thr;
	thread_t departed = 0;
	void* thrRetval;
	int join_retval;
	
	/* Join, capturing the return value */
	if(_retval)
	{
		uintptr_t masked;
		join_retval = thr_join(thr, &departed, &thrRetval);
		
		
		masked = (uintptr_t)thrRetval;
		*_retval = (int)masked;
	}
	else
		join_retval = thr_join(thr, &departed, NULL);


	return (join_retval == 0 && thr == departed);
}

/******************************************************************************/

void SST_Concurrency_YieldThread(void)
{
	thr_yield();
}

