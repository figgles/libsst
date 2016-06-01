/*
	POSIXPrivate.h
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 12/3/2012

	Purpose: 

	Private data structures for POSIX implementation of libsst-net. Not to be distributed
	as part of public SDK headers.

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#pragma once

#ifndef _POSIXPRIVATE_H
#define _POSIXPRIVATE_H

/* Solaris needs this for FIONBIO */
#define BSD_COMP

#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>

#include <netinet/in.h>
#include <arpa/inet.h>

typedef int NativeSocketType;
typedef socklen_t NativeSocketLen;
#define SST_NATIVE_INVALIDSOCKET (-1) 
#define SST_NATIVE_NETERROR (-1) 
#define NativeCloseSocket(s) close(s)
#define NativeIoctl(s, cmd, arg) ioctl(s, cmd, arg)


#endif
