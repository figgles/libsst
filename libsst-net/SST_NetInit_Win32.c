/*
	SST_NetInit_Win32.c
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 8/7/2012

	Purpose: 

	libsst-net initialization functions for Win32

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#include "PlatformPrivate.h"

/*************************************************************************/

int SST_Net_Init(void)
{
    WSADATA wsainfo;

	return (WSAStartup(MAKEWORD(2,2), &wsainfo) == 0);
}

/*************************************************************************/

void SST_Net_Shutdown(void)
{
    WSACleanup();
}
