/*
	SST_Once.c
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 12/20/2011

	Purpose: 

	libsst-concurrency "once" functions. This requires libsst-atomic.

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#include <SST/SST_Once.h>
#include <SST/SST_Atomic.h>
#include <SST/SST_Concurrency.h>
#include <SST/SST_MemBarrier.h>

#define SST_ONCE_INPROGRESS_BIT	0x80000000 /* Highest bit */
#define SST_ONCE_DONE_BIT		0x00000001 /* Lowest bit */

#define SST_ONCE_DONE 0xd1d d0
#ifdef _DEBUG
#include <stdlib.h>
#endif

static void wait_done(volatile int* vonce)
{
	/* Spin carefully */
	while((*vonce & SST_ONCE_DONE_BIT) == 0)
	{
		SST_Concurrency_YieldThread();
		SST_Concurrency_Spin();
	}
}

void SST_Concurrency_ExecOnce(SST_Once* once, SST_OnceFunc once_func, void* arg)
{
	int state;
	volatile int* vonce = (volatile int*)once;
	
	/* Take a snapshot of the current state */
	state = *vonce;
	

	/* Already done? */
	if((state & SST_ONCE_DONE_BIT) != 0)
		return;
		
	/* In progress? */
	if((state & SST_ONCE_INPROGRESS_BIT) != 0)
	{
		wait_done(vonce);
		return;
	}
		
	/* Not done, not yet started -> attempt to set SST_ONCE_INPROGRESS bit.  */
	if(SST_Atomic_CAS(vonce, SST_ONCE_INIT, SST_ONCE_INIT | SST_ONCE_INPROGRESS_BIT) == SST_ONCE_INIT)
	{
		/* Success: call user's once function */
		once_func(arg);
			
		/* Done, so set that we are done */
		SST_Atomic_Or(vonce, SST_ONCE_DONE_BIT);
	}
	else /* Already started or done, so just chill */
		wait_done(vonce);

}

/*************************************************************************/

void SST_Concurrency_InitOnceHandle(SST_Once* once)
{
	*once = SST_ONCE_INIT;
	
	/* This is the only tricky part -- a memory barrier. An atomic
	operation could be used, but honestly, that's overkill for just
	ensuring an atomic write. */
	SST_Concurrency_MemoryBarrier();
}


