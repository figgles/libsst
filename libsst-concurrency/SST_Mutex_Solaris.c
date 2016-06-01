/*
	SST_Mutex_Solaris.c
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 4/11/2012
	
	Purpose: 

	libsst-concurrency mutex functions using native Solaris mutexes

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.
	
*/

#include <SST/SST_Mutex.h>
#include <synch.h>
#include <stdlib.h>

/******************************************************************************/

SST_Mutex SST_Concurrency_CreateMutex(void)
{
	mutex_t* mutex = (mutex_t*)malloc(sizeof(mutex_t));

	mutex_init(mutex, USYNC_THREAD, NULL);
	return (SST_Mutex)mutex;
}

/******************************************************************************/

void SST_Concurrency_DestroyMutex(SST_Mutex _mutex)
{
	mutex_t* mutex = (mutex_t*)_mutex;

	mutex_destroy(mutex);
	free(mutex);
}

/******************************************************************************/

void SST_Concurrency_LockMutex(SST_Mutex _mutex)
{
	mutex_t* mutex = (mutex_t*)_mutex;
	mutex_lock(mutex);
}

/******************************************************************************/

int SST_Concurrency_TryLockMutex(SST_Mutex _mutex)
{
	mutex_t* mutex = (mutex_t*)_mutex;
	return (mutex_trylock(mutex) == 0);
}

/******************************************************************************/

void SST_Concurrency_UnlockMutex(SST_Mutex _mutex)
{
	mutex_t* mutex = (mutex_t*)_mutex;
	mutex_unlock(mutex);
}


