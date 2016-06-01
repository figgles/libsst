/*
	SST_Mutex_POSIX.c
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 12/20/2011
	
	Purpose: 

	libsst-concurrency mutex functions for POSIX platforms

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.
	
*/

#include <SST/SST_Mutex.h>
#include <pthread.h>
#include <stdlib.h>

/******************************************************************************/

SST_Mutex SST_Concurrency_CreateMutex(void)
{
	pthread_mutex_t* mutex = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));

	pthread_mutex_init(mutex, NULL);
	return (SST_Mutex)mutex;
}

/******************************************************************************/

void SST_Concurrency_DestroyMutex(SST_Mutex _mutex)
{
	pthread_mutex_t* mutex = (pthread_mutex_t*)_mutex;

	pthread_mutex_destroy(mutex);
	free(mutex);
}

/******************************************************************************/

void SST_Concurrency_LockMutex(SST_Mutex _mutex)
{
	pthread_mutex_t* mutex = (pthread_mutex_t*)_mutex;
	pthread_mutex_lock(mutex);
}

/******************************************************************************/

int SST_Concurrency_TryLockMutex(SST_Mutex _mutex)
{
	pthread_mutex_t* mutex = (pthread_mutex_t*)_mutex;
	return (pthread_mutex_trylock(mutex) == 0);
}

/******************************************************************************/

void SST_Concurrency_UnlockMutex(SST_Mutex _mutex)
{
	pthread_mutex_t* mutex = (pthread_mutex_t*)_mutex;
	pthread_mutex_unlock(mutex);
}




