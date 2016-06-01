/*
	SST_ThreadBarrier.c
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 12/20/2011

	Purpose: 

	libsst-concurrency thread barrier functions

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#include <SST/SST_Concurrency.h> /* SST_WAIT_INFINITE */
#include <SST/SST_ThreadBarrier.h> /* Functions being implemented */
#include <SST/SST_Atomic.h> /* Needed for atomic operations */
#include <stdlib.h>

#define WAKEUP_UNSIGNALED (-1)
#define WAKEUP_CANCELED 0
#define WAKEUP_SUCCESS 1

typedef struct SST_ThreadBarrierImpl
{
	SST_Event event;
	uint32_t count;
	volatile int wakeup_reason;
	uint32_t threshold;
} SST_ThreadBarrierImpl;

/*************************************************************************/

SST_ThreadBarrier SST_Concurrency_CreateThreadBarrier(uint32_t threshold)
{
	SST_ThreadBarrierImpl* barrier;
	
	/* Allocate barrier */
	barrier = (SST_ThreadBarrierImpl*)malloc(sizeof(SST_ThreadBarrierImpl));
	if(barrier == NULL)
		return NULL;
	
	barrier->event = SST_Concurrency_CreateEvent();
	if(barrier->event == NULL) /* Out of memory */
	{
		free(barrier);
		return NULL;
	}
	
	barrier->count = 0;
	barrier->wakeup_reason = WAKEUP_UNSIGNALED; /* == error condition */
	barrier->threshold = threshold;
	
	/* Ensure all memory operations are visible by the time this returns */
	SST_Concurrency_MemoryBarrier();

	return (SST_ThreadBarrier)barrier;
}

/*************************************************************************/

int SST_Concurrency_WaitThreadBarrier(SST_ThreadBarrier _barrier)
{
	SST_ThreadBarrierImpl* barrier = (SST_ThreadBarrierImpl*)_barrier;
	uint32_t newValue;
	const int reason = barrier->wakeup_reason;
	int retval;

	/* Already canceled? */
	if(reason == WAKEUP_CANCELED)
		return 0;
		
	/* Already successful? */
	if(reason == WAKEUP_SUCCESS)
		return (int)barrier->threshold;
	
	/* At this point, we believe the barrier has not yet been canceled/finished. Due to
	multithreading, it could have been though. */
	
	/* Increment barrier count, see if we've exceeded the threshold */
	newValue = (uint32_t)SST_Atomic_AddReturn((volatile int*)&barrier->count, 1);
	if(newValue == barrier->threshold)
	{
		/* Yes -- but is it already cancelled/finished? */
		const int state = SST_Atomic_CAS(&barrier->wakeup_reason, WAKEUP_UNSIGNALED, WAKEUP_SUCCESS);
		
		/*
			'state' can only be WAKEUP_SUCCESS or WAKEUP_CANCELED at this point. Don't
			(redundantly) signal the event if it was cancelled.
		*/
		
		if(state == WAKEUP_SUCCESS)
			SST_Concurrency_SignalEvent(barrier->event);

		retval = SST_BARRIER_SINGLE;
	}
	else /* either newValue < threshold newValue > threshold or */
	{
		/* No not yet. Wait. */
		SST_Concurrency_WaitEvent(barrier->event, SST_WAIT_INFINITE);
		retval = 1;
	}
	
	/* Threads could have been woken up due to a cancel or due to the count being exceeded. */
	if(barrier->wakeup_reason == WAKEUP_UNSIGNALED) /* error? */
		return -1;
	if(barrier->wakeup_reason == WAKEUP_CANCELED) /* cancelled */
		return 0;

	return retval; 
}

/*************************************************************************/

void SST_Concurrency_ResetThreadBarrier(SST_ThreadBarrier _barrier, uint32_t newThreshold)
{
	SST_ThreadBarrierImpl* barrier = (SST_ThreadBarrierImpl*)_barrier;
	barrier->count = 0;
	barrier->threshold = newThreshold;
	barrier->wakeup_reason = WAKEUP_UNSIGNALED; /* == error condition */

	SST_Concurrency_ResetEvent(barrier->event);
}

/*************************************************************************/

void SST_Concurrency_CancelThreadBarrier(SST_ThreadBarrier _barrier)
{
	SST_ThreadBarrierImpl* barrier = (SST_ThreadBarrierImpl*)_barrier;
	barrier->wakeup_reason = WAKEUP_CANCELED; /* == barrier cancelled */
	SST_Concurrency_SignalEvent(barrier->event);
	
	/* NOTE: SignalEvent() provides a memory barrier so that barrier->wakeup_reason is globally
	visible before the event is signalled. */	
}

/*************************************************************************/

void SST_Concurrency_DestroyThreadBarrier(SST_ThreadBarrier _barrier)
{
	SST_ThreadBarrierImpl* barrier = (SST_ThreadBarrierImpl*)_barrier;
	SST_Concurrency_DestroyEvent(barrier->event);
	free(barrier);
}

