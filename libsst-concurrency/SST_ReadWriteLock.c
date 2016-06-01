/*
	SST_ReadWriteLock.c

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.
*/
#ifndef __APPLE_CC__
#include <malloc.h>
#else
#include <stdlib.h>
#endif

#include <SST/SST_Build.h>
#include <SST/SST_Concurrency.h>

/* Leading (negative) bit is used to signal write lock */
#define SST_RWL_WRITE_BIT	(0x80000000u)

/* ReadWriteLock implementation structure */
typedef struct SST_ReadWriteLockImpl {
	volatile uint32_t state;	/* state flag in the form 0xWRRRRRRR, i.e., write flag and then number of readers */
} SST_ReadWriteLockImpl;

/*************************************************************************/

extern SST_ReadWriteLock SST_Concurrency_CreateReadWriteLock( void )
{
	SST_ReadWriteLockImpl *lock_impl = (SST_ReadWriteLockImpl*)malloc(sizeof(SST_ReadWriteLockImpl));

	/* Check for allocation failure */
	if (lock_impl == NULL)
		return NULL;

	/* Initialize the impl */
	lock_impl->state = 0;

	/* Make sure that goes out to memory */
	SST_Concurrency_MemoryBarrier();

	return lock_impl;
}

/*************************************************************************/

extern void SST_Concurrency_DestroyReadWriteLock( SST_ReadWriteLock lock )
{
	SST_ReadWriteLockImpl* lock_impl;

	if (lock == NULL)
		return;

	lock_impl = (SST_ReadWriteLockImpl*)lock;

	free(lock_impl);
}

/*************************************************************************/

extern int SST_Concurrency_LockForReading( SST_ReadWriteLock lock, uint32_t ticks )
{
	uint64_t startTicks, currentTicks;
	SST_ReadWriteLockImpl* lock_impl;

	if (lock == NULL)
		return 0;

	startTicks = (uint32_t)SST_Concurrency_GetTicks();

	lock_impl = (SST_ReadWriteLockImpl*)lock;

	/* Spin (and yield) until we are not writing */
	while (lock_impl->state & SST_RWL_WRITE_BIT)
	{
		if (ticks != SST_WAIT_INFINITE)
		{
			currentTicks = SST_Concurrency_GetTicks();

			if ((uint32_t)(currentTicks - startTicks) > ticks)
				return 0;
		}

		SST_Concurrency_YieldThread();
	}

	/* Increment the reader count by incrementing the state variable */
	SST_Atomic_Inc(&lock_impl->state);

	return 1;
}

/*************************************************************************/

extern int SST_Concurrency_LockForWriting( SST_ReadWriteLock lock, uint32_t ticks )
{
	uint64_t startTicks, currentTicks;
	SST_ReadWriteLockImpl* lock_impl;

	if (lock == NULL)
		return 0;

	startTicks = SST_Concurrency_GetTicks();

	lock_impl = (SST_ReadWriteLockImpl*)lock;

	/* If we are already locked for writing, return */
	if (lock_impl->state & SST_RWL_WRITE_BIT)
		return 0;

	/* Set the write flag */
	SST_Atomic_Or((volatile int*)&lock_impl->state, SST_RWL_WRITE_BIT);

	/* Spin (and yield) until we have no more readers */
	while (lock_impl->state & ~SST_RWL_WRITE_BIT)
	{
		if (ticks != SST_WAIT_INFINITE)
		{
			currentTicks = SST_Concurrency_GetTicks();

			if ((uint32_t)(currentTicks - startTicks) > ticks)
				return 0;
		}

		SST_Concurrency_YieldThread();
	}

	return 1;
}

/*************************************************************************/

extern void SST_Concurrency_EndReading( SST_ReadWriteLock lock )
{
	SST_ReadWriteLockImpl* lock_impl;

	if (lock == NULL)
		return;

	lock_impl = (SST_ReadWriteLockImpl*)lock;

	/* Decrement the readers counter */
	SST_Atomic_Dec(&lock_impl->state);	
}

/*************************************************************************/

extern void SST_Concurrency_EndWriting( SST_ReadWriteLock lock )
{
	SST_ReadWriteLockImpl* lock_impl;

	if (lock == NULL)
		return;

	lock_impl = (SST_ReadWriteLockImpl*)lock;

	/* Signal that we are free to read */
	SST_Atomic_And((volatile int*)&lock_impl->state, ~SST_RWL_WRITE_BIT);
}
