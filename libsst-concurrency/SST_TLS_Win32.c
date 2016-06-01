/*
	SST_TLS_Win32.c
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 12/20/2011

	Purpose: 

	libsst-concurrency thread local storage functions for Win32 platforms (Windows 7 or later)

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#include <SST/SST_TLS.h>

#define _WIN32_WINNT 0x0601 /* Windows 7 or later */
#include <windows.h>

/*************************************************************************/

SST_TLS SST_Concurrency_CreateTLS(void)
{
	DWORD slot = TlsAlloc();

	return (SST_TLS)slot;
}

/*************************************************************************/

void SST_Concurrency_DestroyTLS(SST_TLS tls)
{
	DWORD slot = (DWORD)tls;

	TlsFree(slot);
}

/*************************************************************************/

void* SST_Concurrency_GetTLSValue(SST_TLS tls)
{
	DWORD slot = (DWORD)tls;

	return TlsGetValue(slot);
}

/*************************************************************************/

void SST_Concurrency_SetTLSValue(SST_TLS tls, void* value)
{
	DWORD slot = (DWORD)tls;
	
	TlsSetValue(slot, value);
}
