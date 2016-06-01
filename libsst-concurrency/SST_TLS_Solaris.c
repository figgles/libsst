/*
	SST_TLS_POSIX.c
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 4/11/2012

	Purpose: 

	libsst-concurrency thread local storage functions using native Solaris TLS

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#include <SST/SST_TLS.h>
#include <thread.h>

/******************************************************************************/

SST_TLS SST_Concurrency_CreateTLS(void)
{
	thread_key_t key;

	if(thr_keycreate(&key, NULL) != 0)
		return NULL;
	
	return (SST_TLS)key;
}

/******************************************************************************/

void SST_Concurrency_DestroyTLS(SST_TLS tls)
{
	/* As noted in Solaris's source code, there is no function to destroy keys.
	 This is done for performance. Even the good old pthread_key_destroy()
	 interface does nothing on Solaris. Well. Hmm. */
	(void)tls;
}

/******************************************************************************/

void* SST_Concurrency_GetTLSValue(SST_TLS tls)
{
	thread_key_t key = (thread_key_t)tls;
	void* value = NULL;
	
	thr_getspecific(key, &value);
	
	return value;
}

/******************************************************************************/

void SST_Concurrency_SetTLSValue(SST_TLS tls, void* value)
{
	thread_key_t key = (thread_key_t)tls;

	thr_setspecific(key, value);
}


