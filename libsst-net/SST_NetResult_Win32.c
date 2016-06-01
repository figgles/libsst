/*
	SST_NetResult_Win32.c
	Authors: Chris Ertel <crertel@762studios.com, Patrick Baggett <ptbaggett@762studios.com>
	Created: 8/7/2012

	Purpose: 

	Winsock2 to libsst-net error codes

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/
#include <SST/SST_NetResult.h>
#include "PlatformPrivate.h"

SST_NetResult NativeDecodeError(void)
{
	SST_NetResult e;
	switch(WSAGetLastError())
	{
		case WSANOTINITIALISED: e = SSTNETRESULT_NETNOTINIT; break;
		case WSAENETDOWN: e = SSTNETRESULT_NETDOWN; break;
		case WSAEAFNOSUPPORT: e = SSTNETRESULT_ADDRFAMNOTSUPPORTED; break;
		case WSAEINPROGRESS: e = SSTNETRESULT_INPROGRESS; break;
		case WSAEMFILE: e = SSTNETRESULT_NOFILESAVAILABLE; break;
		case WSAEINVAL: e = SSTNETRESULT_INVALIDARGS; break;
		case WSAENOBUFS: return SSTNETRESULT_NOSPACE; break;
		case WSAEPROTONOSUPPORT: e = SSTNETRESULT_PROTOCOLNOTSUPPORTED; break;
		case WSAEPROTOTYPE: e = SSTNETRESULT_WRONGPROTOCOLFORSOCK; break;
		case WSAEPROVIDERFAILEDINIT: e = SSTNETRESULT_NETNOTINIT; break;
		case WSAESOCKTNOSUPPORT: e = SSTNETRESULT_SOCKETNOTSUPPORTED; break;
		case WSAEINVALIDPROVIDER: e = SSTNETRESULT_NETNOTINIT; break;
		case WSAEINVALIDPROCTABLE: e = SSTNETRESULT_NETNOTINIT; break;
	    case WSAEFAULT: return SSTNETRESULT_BADPOINTER; break;
	    case WSAENOTSOCK: return SSTNETRESULT_NOTASOCKET; break;
	    case WSAEADDRINUSE: return SSTNETRESULT_ADDRINUSE; break;
	    case WSAEISCONN: return SSTNETRESULT_ALREADYCONNECTED; break;
	    case WSAEOPNOTSUPP: return SSTNETRESULT_OPNOTSUPPORTED; break;
	    case WSAEINTR: return SSTNETRESULT_INTERRUPTED; break;	
	    case WSAEALREADY: return SSTNETRESULT_ALREADYCONNECTING; break;
	    case WSAEADDRNOTAVAIL: return SSTNETRESULT_ADDRNOTAVAILABLE; break;
	    case WSAECONNREFUSED: return SSTNETRESULT_CONNECTIONREFUSED; break;
	    case WSAENETUNREACH: return SSTNETRESULT_NETUNREACHABLE; break;
	    case WSAEHOSTUNREACH: return SSTNETRESULT_HOSTUNREACHABLE; break;
	    case WSAETIMEDOUT: return SSTNETRESULT_TIMEDOUT; break;
	    case WSAEWOULDBLOCK: return SSTNETRESULT_WOULDBLOCK; break;
	    case WSAEACCES: return SSTNETRESULT_ACCESSDENIED; break;
		case WSAECONNRESET: return SSTNETRESULT_CONNECTIONRESET; break;
		case WSAENOTCONN: return SSTNETRESULT_NOTCONNECTED; break;	
		case WSAENETRESET: return SSTNETRESULT_NETRESET; break;
		case WSAESHUTDOWN: return SSTNETRESULT_SOCKETSHUTDOWN; break;
		case WSAEMSGSIZE: return SSTNETRESULT_MESSAGESIZE; break;
		case WSAECONNABORTED: return SSTNETRESULT_CONNECTIONABORTED; break;
		case WSAEDESTADDRREQ: return SSTNETRESULT_NODESTADDRESSGIVEN; break;


		default: e = SSTNETRESULT_UNKNOWN; break;
	}

	return e;
}