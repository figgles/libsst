/*
	PlatformPrivate.h
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 8/7/2012

	Purpose: 

	Crossplatform include that defers to platform-specific headers. Not to be
	distributed as part of public SDK headers.

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#pragma once

#ifndef _SST_PLATFORMPRIVATE_H
#define _SST_PLATFORMPRIVATE_H

#include <pstdint.h>
#include <limits.h>
#include <SST/SST_Build.h>
#ifdef _WIN32
	#include "Win32Private.h"
#else
	#include "POSIXPrivate.h"
#endif

#include <SST/SST_NetResult.h>
#include <SST/SST_NetTypes.h>

SST_NetResult NativeDecodeError(void);

/*************************************************************************/

static INLINE NativeSocketLen sockLenForNetAddr(const SST_NetAddress* addr)
{
	NativeSocketLen socklen = 0;
	const struct sockaddr* saddr = (const struct sockaddr*)addr;

	switch(saddr->sa_family)
	{
		case AF_INET: socklen = sizeof(struct sockaddr_in); break;
		case AF_INET6: socklen = sizeof(struct sockaddr_in6); break;
	}

	return socklen;
}

/*************************************************************************/

static INLINE int convertSockOpt(SST_NetSocketOption option)
{
	int ret;

	switch(option)
	{
		case SSTNETSOCKOPT_DEBUG: ret = SO_DEBUG; break;
		case SSTNETSOCKOPT_ACCEPTCONN: ret = SO_ACCEPTCONN; break;
		case SSTNETSOCKOPT_BROADCAST: ret = SO_BROADCAST; break;
		case SSTNETSOCKOPT_REUSEADDR: ret = SO_REUSEADDR; break;
		case SSTNETSOCKOPT_KEEPALIVE: ret = SO_KEEPALIVE; break;
		case SSTNETSOCKOPT_LINGER: ret = SO_LINGER; break;
		case SSTNETSOCKOPT_OOBINLINE: ret = SO_OOBINLINE; break;
		case SSTNETSOCKOPT_SENDBUFFERSIZE: ret = SO_SNDBUF; break;
		case SSTNETSOCKOPT_RECVBUFFERSIZE: ret = SO_RCVBUF; break;
		case SSTNETSOCKOPT_ERRORSTATUS: ret = SO_ERROR; break;
		case SSTNETSOCKOPT_SOCKETTYPE: ret = SO_TYPE; break;
		case SSTNETSOCKOPT_DONTROUTE: ret = SO_DONTROUTE; break;
		default: ret = -1; break;
	}

	return ret;
}

/*************************************************************************/

static INLINE int convertSockLevel(SST_NetProtocolLevel level)
{
	int ret;

	switch(level)
	{
		case SSTNETPROTOLEVEL_SOCKET: ret = SO_DEBUG; break;
		default: ret = -1; break;
	}

	return ret;
}

#endif

