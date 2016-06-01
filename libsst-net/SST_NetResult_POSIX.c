/*
	SST_NetResult_POSIX.c
	Authors: Patrick Baggett <ptbaggett@762studios.com>
	Created: 12/03/2012

	Purpose: 

	errno to libsst-net error codes

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#include <SST/SST_NetResult.h>
#include "PlatformPrivate.h"
#include <errno.h>

SST_NetResult NativeDecodeError(void)
{
	SST_NetResult e;
	switch(errno)
	{
		case EAFNOSUPPORT: e = SSTNETRESULT_ADDRFAMNOTSUPPORTED; break;
		case EINPROGRESS: e = SSTNETRESULT_INPROGRESS; break;
		case EMFILE: e = SSTNETRESULT_NOFILESAVAILABLE; break;
		case EINVAL: e = SSTNETRESULT_INVALIDARGS; break;
		case ENOBUFS: return SSTNETRESULT_NOSPACE; break;
		case EPROTONOSUPPORT: e = SSTNETRESULT_PROTOCOLNOTSUPPORTED; break;
		case EPROTOTYPE: e = SSTNETRESULT_WRONGPROTOCOLFORSOCK; break;
		case ESOCKTNOSUPPORT: e = SSTNETRESULT_SOCKETNOTSUPPORTED; break;
	    	case EFAULT: return SSTNETRESULT_BADPOINTER; break;
	    	case ENOTSOCK: return SSTNETRESULT_NOTASOCKET; break;
	    	case EADDRINUSE: return SSTNETRESULT_ADDRINUSE; break;
	    	case EISCONN: return SSTNETRESULT_ALREADYCONNECTED; break;
	    	case EOPNOTSUPP: return SSTNETRESULT_OPNOTSUPPORTED; break;
	    	case EINTR: return SSTNETRESULT_INTERRUPTED; break;	
	    	case EALREADY: return SSTNETRESULT_ALREADYCONNECTING; break;
	    	case EADDRNOTAVAIL: return SSTNETRESULT_ADDRNOTAVAILABLE; break;
	    	case ECONNREFUSED: return SSTNETRESULT_CONNECTIONREFUSED; break;
	    	case ENETUNREACH: return SSTNETRESULT_NETUNREACHABLE; break;
	    	case EHOSTUNREACH: return SSTNETRESULT_HOSTUNREACHABLE; break;
	    	case ETIMEDOUT: return SSTNETRESULT_TIMEDOUT; break;
	    	case EWOULDBLOCK: return SSTNETRESULT_WOULDBLOCK; break;
	    	case EACCES: return SSTNETRESULT_ACCESSDENIED; break;
		case ECONNRESET: return SSTNETRESULT_CONNECTIONRESET; break;
		case ENOTCONN: return SSTNETRESULT_NOTCONNECTED; break;	
		case ENETRESET: return SSTNETRESULT_NETRESET; break;
		case ESHUTDOWN: return SSTNETRESULT_SOCKETSHUTDOWN; break;
		case EMSGSIZE: return SSTNETRESULT_MESSAGESIZE; break;
		case ECONNABORTED: return SSTNETRESULT_CONNECTIONABORTED; break;
		case EDESTADDRREQ: return SSTNETRESULT_NODESTADDRESSGIVEN; break;


		default: e = SSTNETRESULT_UNKNOWN; break;
	}

	return e;
}
