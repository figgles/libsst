/*
	SST_TLS_POSIX.c
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 12/20/2011

	Purpose: 

	libsst-concurrency thread local storage functions for POSIX platforms

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#include <SST/SST_TLS.h>
#include <pthread.h>
#include <stdlib.h>

/******************************************************************************/

SST_TLS SST_Concurrency_CreateTLS(void)
{
	pthread_key_t* key = (pthread_key_t*)malloc(sizeof(pthread_key_t));

	if(key == NULL)
		return NULL;

	if(pthread_key_create(key, NULL) != 0)
	{
		free(key);
		return NULL;
	}
	
	return (SST_TLS)key;
}

/******************************************************************************/

void SST_Concurrency_DestroyTLS(SST_TLS tls)
{
	pthread_key_t* key = (pthread_key_t*)tls;
	
	pthread_key_delete(*key);
	free(key);
}

/******************************************************************************/

void* SST_Concurrency_GetTLSValue(SST_TLS tls)
{
	pthread_key_t* key = (pthread_key_t*)tls;

	return pthread_getspecific(*key);
}

/******************************************************************************/

void SST_Concurrency_SetTLSValue(SST_TLS tls, void* value)
{
	pthread_key_t* key = (pthread_key_t*)tls;

	pthread_setspecific(*key, value);	
}


