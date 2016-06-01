/*
	Win32Private.h
	Author: Chris Ertel <crertel@762studios.com>
	Created: 07/15/2012

	Purpose: 

	Private data structures for Win32 implementation of libsst-net. Not to be distributed
	as part of public SDK headers.

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#pragma once

#ifndef _WIN32PRIVATE_H
#define _WIN32PRIVATE_H

#define _WIN32_WINNT 0x0601 /* Windows 7 or later */
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <ws2ipdef.h>

typedef SOCKET NativeSocketType;
typedef int NativeSocketLen;
#define SST_NATIVE_INVALIDSOCKET INVALID_SOCKET
#define SST_NATIVE_NETERROR SOCKET_ERROR
#define NativeCloseSocket(s) closesocket(s)
#define NativeIoctl(s, cmd, arg) ioctlsocket(s, cmd, arg)
#endif
