/*
	SST_Sockets_Win32.c
	Author: Chris Ertel <crertel@762studios.com>
	Created: 07/15/2012

	Purpose: 

	libsst-net BSD sockets wrapper, Win32 implementation.

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#include <SST/SST_Sockets.h>
#include <SST/SST_NetTypes.h>
#include <SST/SST_NetResult.h>
#include "Win32Private.h"

#include <stdlib.h>

typedef struct SST_NetPollDescriptorSet_Win32
{
    size_t Count;
    WSAPOLLFD* Descriptors;
} SST_NetPollDescriptorSet_Win32;


typedef struct SST_NetAddrInfo_Win32
{
	SST_NetAddrInfoFlags flags;
	SST_NetAddressFamily family;
	SST_NetSocketType socketType;
	SST_NetProtocol protocol;
	char* canonicalName;
	SOCKADDR_STORAGE addr;
	struct SST_NetAddrInfo_Win32* next;
} SST_NetAddrInfo_Win32;
SST_NetResult SST_Net_CreateSocketSet( SST_NetSocketSet* _out )
{
    fd_set* ret;

    ret = (fd_set*) calloc( 1, sizeof(fd_set) );
    if (ret == NULL)
    {
        return SSTNETRESULT_NOSPACE;
    }
    else
    {
        *_out = (SST_NetSocketSet) ret;
        return SSTNETRESULT_SUCCESS;
    }
}

void SST_Net_DestroySocketSet( SST_NetSocketSet _set )
{
    free( (void*) _set );
}

void SST_Net_ClearSocketFromSocketSet( SST_NetSocketSet _set, SST_Socket _sock)
{
    FD_CLR( ( *(SOCKET*)_sock), (fd_set*) _set );
}   

void SST_Net_AddSocketToSocketSet( SST_NetSocketSet _set, SST_Socket _sock)
{
    FD_SET( ( *(SOCKET*)_sock), (fd_set*) _set );
}

int SST_Net_IsSocketInSocketSet( SST_NetSocketSet _set, SST_Socket _sock)
{
    return FD_ISSET( ( *(SOCKET*)_sock), (fd_set*) _set );
}

void SST_Net_ZeroSocketSet( SST_NetSocketSet _set)
{
    FD_ZERO( (fd_set*) _set );
}

static SST_NetResult decodeerror_select(int _errcode)
{
	switch( _errcode )
	{
        case WSANOTINITIALISED: return SSTNETRESULT_NETNOTINIT; break;
        case WSAEFAULT: return SSTNETRESULT_BADPOINTER; break;	
        case WSAENETDOWN: return SSTNETRESULT_NETDOWN; break;
        case WSAEINVAL: return SSTNETRESULT_INVALIDARGS; break;
        case WSAEINTR: return SSTNETRESULT_INTERRUPTED; break;
        case WSAEINPROGRESS: return SSTNETRESULT_INPROGRESS; break;
        case WSAENOTSOCK: return SSTNETRESULT_NOTASOCKET; break;

        default: return SSTNETRESULT_UNKNOWN; break;
	}
}

SST_NetResult SST_Net_Select( size_t _numSockets, SST_NetSocketSet _readSockets, SST_NetSocketSet _writeSockets, SST_NetSocketSet _errorSockets, SST_NetTimeval* _timeout, size_t* _numEvented)
{
    int numEvented;
    struct timeval timeVal; /* really, Winsock? You couldn't typedef this? */

    if (_timeout != NULL)
    {
        timeVal.tv_sec = _timeout->seconds;
        timeVal.tv_usec = _timeout->microseconds;
    }
    else
    {
        timeVal.tv_sec = 0;
        timeVal.tv_usec = 0;
    }

    numEvented = select((int) _numSockets,
                        (fd_set*) _readSockets,
                        (fd_set*) _writeSockets,
                        (fd_set*) _errorSockets,
                        (_timeout != NULL)? &timeVal : NULL );

    if (numEvented == SOCKET_ERROR)
    {
        return decodeerror_select(WSAGetLastError());
    }
    else
    {
        *_numEvented = numEvented;
        return SSTNETRESULT_SUCCESS;
    }
}

static SST_NetResult decodeerror_poll(int _errcode)
{
	switch( _errcode )
	{
		case WSAENETDOWN: return SSTNETRESULT_NETDOWN; break;
		case WSAEFAULT: return SSTNETRESULT_BADPOINTER; break;	
		case WSAEINVAL: return SSTNETRESULT_INVALIDARGS; break;
		case WSAENOBUFS: return SSTNETRESULT_NOSPACE; break;

		default: return SSTNETRESULT_UNKNOWN; break;
	}
}

SST_NetResult SST_Net_CreatePollDescriptorSet(size_t _numDescriptors, SST_NetPollDescriptorSet* _out)
{
	WSAPOLLFD* fds;
	SST_NetPollDescriptorSet_Win32* ret;

	fds = (WSAPOLLFD*) calloc(_numDescriptors, sizeof(WSAPOLLFD));
	if (fds == NULL)
		return SSTNETRESULT_NOSPACE;

	ret = (SST_NetPollDescriptorSet_Win32*) malloc( sizeof(SST_NetPollDescriptorSet_Win32) );
	if (ret == NULL)
	{
		free(fds);
		return SSTNETRESULT_NOSPACE;
	}

	ret->Count = _numDescriptors;
	ret->Descriptors = fds;
	*_out = ret;

	return SSTNETRESULT_SUCCESS;
}

void SST_Net_DestroyPollDescriptorSet(SST_NetPollDescriptorSet _toDestroy)
{
	SST_NetPollDescriptorSet_Win32* desc = (SST_NetPollDescriptorSet_Win32*) _toDestroy;

	free(desc->Descriptors);
	desc->Descriptors = NULL;
	desc->Count = 0;
}

void SST_Net_SetPollDescriptorSocket(SST_NetPollDescriptorSet _descriptors, size_t _which, SST_Socket _socket)
{
	SST_NetPollDescriptorSet_Win32* desc = (SST_NetPollDescriptorSet_Win32*) _descriptors;
	desc->Descriptors[_which].fd = *((SOCKET*) _socket);
}

SST_Socket SST_Net_GetPollDescriptorSocket(SST_NetPollDescriptorSet _descriptors, size_t _which )
{
	SST_Socket ret;
	SST_NetPollDescriptorSet_Win32* desc = (SST_NetPollDescriptorSet_Win32*) _descriptors;
	
	if (convertWinSocketToSSTSocket(&(desc->Descriptors[_which].fd), &ret) != SSTNETRESULT_SUCCESS)
	{
		return SSTNET_INVALIDSOCKET;
	}
	else
	{
		return ret;
	}
}

static short convertSSTPollFlagsToWinPollFlags(SST_NetPollFlag _flags)
{
	short ret = 0;

	ret |= (_flags & SSTNETPOLLFLAG_POLLPRI)? POLLPRI : 0;
	ret |= (_flags & SSTNETPOLLFLAG_POLLRDBAND)? POLLRDBAND : 0;
	ret |= (_flags & SSTNETPOLLFLAG_POLLRDNORM)? POLLRDNORM : 0;
	ret |= (_flags & SSTNETPOLLFLAG_POLLWRNORM)? POLLWRNORM : 0;
	ret |= (_flags & SSTNETPOLLFLAG_POLLERR)? POLLERR : 0;
	ret |= (_flags & SSTNETPOLLFLAG_POLLHUP)? POLLHUP : 0;
	ret |= (_flags & SSTNETPOLLFLAG_POLLNVAL)? POLLNVAL : 0;

	return ret;
}

void SST_Net_SetPollDescriptorFlag(SST_NetPollDescriptorSet _descriptors, size_t _which, SST_NetPollFlag _flags)
{
	SST_NetPollDescriptorSet_Win32* desc = (SST_NetPollDescriptorSet_Win32*) _descriptors;
	desc->Descriptors[_which].events = convertSSTPollFlagsToWinPollFlags(_flags);
}

static short convertWinPollFlagsToSSTPollFlags(short _flags)
{
	SST_NetPollFlag ret = 0;

	ret |= (_flags & POLLPRI)? SSTNETPOLLFLAG_POLLPRI : 0;
	ret |= (_flags & POLLRDBAND )? SSTNETPOLLFLAG_POLLRDBAND : 0;
	ret |= (_flags & POLLRDNORM )? SSTNETPOLLFLAG_POLLRDNORM : 0;
	ret |= (_flags & POLLWRNORM )? SSTNETPOLLFLAG_POLLWRNORM : 0;
	ret |= (_flags & POLLERR )? SSTNETPOLLFLAG_POLLERR : 0;
	ret |= (_flags & POLLHUP )? SSTNETPOLLFLAG_POLLHUP : 0;
	ret |= (_flags & POLLNVAL )? SSTNETPOLLFLAG_POLLNVAL : 0;

	return ret;
}

SST_NetPollFlag SST_Net_GetPollDescriptorFlags(SST_NetPollDescriptorSet _descriptors, size_t _which)
{
	SST_NetPollDescriptorSet_Win32* desc = (SST_NetPollDescriptorSet_Win32*) _descriptors;
	return convertWinPollFlagsToSSTPollFlags(desc->Descriptors[_which].events);
}

void SST_Net_ClearPollDescriptorFlags(SST_NetPollDescriptorSet _descriptors, size_t _which)
{
	SST_NetPollDescriptorSet_Win32* desc = (SST_NetPollDescriptorSet_Win32*) _descriptors;
	desc->Descriptors[_which].events = 0;
}

SST_NetPollFlag SST_Net_GetPollDescriptorEvents(SST_NetPollDescriptorSet _descriptors, size_t _which)
{
	SST_NetPollDescriptorSet_Win32* desc = (SST_NetPollDescriptorSet_Win32*) _descriptors;
	return convertWinPollFlagsToSSTPollFlags(desc->Descriptors[_which].revents);
}

SST_NetResult SST_Net_Poll( SST_NetPollDescriptorSet _toPoll, int _timeout, size_t* _numEvented)
{
	int polled = 0;
	SST_NetPollDescriptorSet_Win32* set = (SST_NetPollDescriptorSet_Win32*) _toPoll;

	polled = WSAPoll( (WSAPOLLFD*)set->Descriptors,
                      (ULONG) set->Count,
                      _timeout);

	if (polled == SOCKET_ERROR)
	{
		return decodeerror_poll(WSAGetLastError());
	}
	else
	{
		*_numEvented = polled;
		return SSTNETRESULT_SUCCESS;
	}
}

static SST_NetResult decodeerror_getsockopt(int _errcode)
{
	switch( _errcode )
	{
		case WSANOTINITIALISED: return SSTNETRESULT_NETNOTINIT; break;
		case WSAENETDOWN: return SSTNETRESULT_NETDOWN; break;
		case WSAEFAULT: return SSTNETRESULT_BADPOINTER; break;	
		case WSAEINPROGRESS: return SSTNETRESULT_INPROGRESS; break;
		case WSAEINVAL: return SSTNETRESULT_INVALIDARGS; break;
		case WSAENOPROTOOPT: return SSTNETRESULT_PROTOCOLOPNOTSUPPORED; break;
		case WSAENOTSOCK: return SSTNETRESULT_NOTASOCKET; break;	

		default: return SSTNETRESULT_UNKNOWN; break;
	}
}

static int convertSSTSockOptToWinSockOpt( SST_NetSocketOption _in, int* _out)
{
	int ret = 0;
	switch(_in)
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

		default: return -1; break;
	}

	*_out = ret;
	return 0;
}

static int convertSSTSockLevelToWinSockLevel( SST_NetProtocolLevel _in, int* _out)
{
	int ret = 0;
	switch(_in)
	{
	case SSTNETPROTOLEVEL_SOCKET: ret = SO_DEBUG; break;
	default: return -1; break;
	}

	*_out = ret;
	return 0;
}

SST_NetResult SST_Net_GetSockOpt( SST_Socket _socket, SST_NetProtocolLevel _level, SST_NetSocketOption _option, void* _optionStorage, size_t* _optionStorageSize)
{
	int winsockopt;
	int winsocklevel;
	int errcode;
    int optlen;
	
	if (convertSSTSockLevelToWinSockLevel(_level, &winsocklevel) != 0)
		return SSTNETRESULT_BADPROTOCOLLEVEL;

	if (convertSSTSockOptToWinSockOpt(_option, &winsockopt) != 0)
		return SSTNETRESULT_BADSOCKETOP;
	
    optlen = (int) _optionStorageSize;
	errcode = getsockopt( *((SOCKET*)_socket),
                          winsocklevel,
                          winsockopt,
                          (char*) _optionStorage,
                          &optlen);
	if (errcode == SOCKET_ERROR)
	{
		return decodeerror_getsockopt(WSAGetLastError());
	}
	else
	{
        *_optionStorageSize = (size_t) optlen;
		return SSTNETRESULT_SUCCESS;
	}
}

static SST_NetResult decodeerror_setsockopt(int _errcode)
{
	switch( _errcode )
	{
		case WSANOTINITIALISED: return SSTNETRESULT_NETNOTINIT; break;
		case WSAENETDOWN: return SSTNETRESULT_NETDOWN; break;
		case WSAEFAULT: return SSTNETRESULT_BADPOINTER; break;	
		case WSAEINPROGRESS: return SSTNETRESULT_INPROGRESS; break;
		case WSAEINVAL: return SSTNETRESULT_INVALIDARGS; break;
		case WSAENETRESET: return SSTNETRESULT_NETRESET; break;
		case WSAENOPROTOOPT: return SSTNETRESULT_PROTOCOLOPNOTSUPPORED; break;
		case WSAENOTCONN: return SSTNETRESULT_NOTCONNECTED; break;
		case WSAENOTSOCK: return SSTNETRESULT_NOTASOCKET; break;	

		default: return SSTNETRESULT_UNKNOWN; break;
	}
}
SST_NetResult SST_Net_SetSockOpt( SST_Socket _socket, SST_NetProtocolLevel _level, SST_NetSocketOption _option, const void* _optionData, size_t* _optionDataSize)
{
	int winsockopt;
	int winsocklevel;
	int errcode;
    int optlen;

	if (convertSSTSockLevelToWinSockLevel(_level, &winsocklevel) != 0)
		return SSTNETRESULT_BADPROTOCOLLEVEL;

	if (convertSSTSockOptToWinSockOpt(_option, &winsockopt) != 0)
		return SSTNETRESULT_BADSOCKETOP;
	
    optlen = (int) *_optionDataSize;
	errcode = getsockopt( *((SOCKET*)_socket),
                          winsocklevel,
                          winsockopt,
                          (char*) _optionData,
                          &optlen);
	if (errcode == SOCKET_ERROR)
	{
		return decodeerror_setsockopt(WSAGetLastError());
	}
	else
	{
        *_optionDataSize = (size_t) optlen;
		return SSTNETRESULT_SUCCESS;
	}
}

static SST_NetResult decodeerror_pton(int _errcode)
{
	switch( _errcode )
	{
		case WSAEAFNOSUPPORT:	return SSTNETRESULT_ADDRFAMNOTSUPPORTED; break;
		case WSAEFAULT:			return SSTNETRESULT_BADPOINTER; break;

		default: return SSTNETRESULT_UNKNOWN; break;
	}
}

SST_NetResult SST_Net_PToN( SST_NetAddressFamily _family, const char* _addressText, SST_NetAddress _storage)
{
	int af = 0;
	int errcode = 0;
	void* addr = NULL;

	struct in_addr* v4addr = &( ((struct sockaddr_in*)_storage)->sin_addr );
	struct in6_addr* v6addr = &( ((struct sockaddr_in6*)_storage)->sin6_addr );

	switch (_family)
	{
		case SSTNETADDRFAM_IPV4: af = AF_INET;
								 addr = (void*) v4addr;
								 ((struct sockaddr_in*)_storage)->sin_family = AF_INET;
								 break;
		case SSTNETADDRFAM_IPV6: af = AF_INET6;
								 addr = (void*) v6addr;
								 ((struct sockaddr_in6*)_storage)->sin6_family = AF_INET6;
								 break;
		default: return SSTNETRESULT_ADDRFAMNOTSUPPORTED; break;
	}
	
	errcode = InetPton(	af,
						_addressText,
						addr );
	if (errcode == 1)
	{
		return SSTNETRESULT_SUCCESS;
	}
	else
	{
		if (errcode == 0)
		{
			return SSTNETRESULT_BADADDRESSSTRING;
		}
		else
		{
			return decodeerror_pton(WSAGetLastError());
		}
	}
}

static SST_NetResult decodeerror_ntop(int _errcode)
{
	switch( _errcode )
	{
	case WSAEAFNOSUPPORT:			return SSTNETRESULT_ADDRFAMNOTSUPPORTED; break;
	case ERROR_INVALID_PARAMETER:	return SSTNETRESULT_INVALIDARGS; break;

	default: return SSTNETRESULT_UNKNOWN; break;
	}
}

SST_NetResult SST_Net_NToP( SST_NetAddressFamily _family, SST_NetAddress _data, char* _addressTextStorage, size_t _addressTextStorageLength)
{
	char* retval = NULL;
	struct sockaddr_storage* ss = (struct sockaddr_storage*) _data;

	switch (_family)
	{
		case SSTNETADDRFAM_IPV4: retval = (char*) InetNtop(AF_INET, &(((struct sockaddr_in*)ss)->sin_addr), _addressTextStorage, _addressTextStorageLength); break;
		case SSTNETADDRFAM_IPV6: retval = (char*) InetNtop(AF_INET6, &(((struct sockaddr_in6*)ss)->sin6_addr), _addressTextStorage, _addressTextStorageLength); break;
		default: return SSTNETRESULT_ADDRFAMNOTSUPPORTED; break;
	}

	if (retval == NULL)
	{
		return decodeerror_ntop(WSAGetLastError());
	}
	else
	{
		return SSTNETRESULT_SUCCESS; 
	}
}

static SST_NetResult decodeerror_getaddrinfo( int _errcode )
{
	switch( _errcode )
	{
		case WSATRY_AGAIN:				return SSTNETRESULT_TRYAGAIN; break;
		case WSAEINVAL:					return SSTNETRESULT_INVALIDARGS; break;
		case WSANO_RECOVERY:			return SSTNETRESULT_HOSTUNREACHABLE; break;
		case WSAEAFNOSUPPORT:			return SSTNETRESULT_ADDRFAMNOTSUPPORTED; break;
		case WSA_NOT_ENOUGH_MEMORY:		return SSTNETRESULT_NOSPACE; break;
		case WSAHOST_NOT_FOUND:			return SSTNETRESULT_HOSTUNREACHABLE; break;
		case WSATYPE_NOT_FOUND:			return SSTNETRESULT_SERVICENOTSUPPORTED; break;
		case WSAESOCKTNOSUPPORT:		return SSTNETRESULT_SOCKETNOTSUPPORTED; break;

		default: return SSTNETRESULT_UNKNOWN; break;
	}
}

static SST_NetResult convertSSTAddrHintsToWinAddrHints( const SST_NetAddrHints* _hints, struct addrinfo* _winHints )
{
	int tempflags = 0;

	/* handle address family */
	switch (_hints->addressFamily)
	{
		case SSTNETADDRFAM_IPV4: _winHints->ai_family = AF_INET; break;
		case SSTNETADDRFAM_IPV6: _winHints->ai_family = AF_INET6; break;
		default: return SSTNETRESULT_ADDRFAMNOTSUPPORTED; break;
	}

	/* handle socket type */
	switch (_hints->socketType)
	{
		case SSTNETSOCKTYPE_STREAM: _winHints->ai_socktype = SOCK_STREAM; break;
		case SSTNETSOCKTYPE_DATAGRAM: _winHints->ai_socktype = SOCK_DGRAM; break;
		default: return SSTNETRESULT_SOCKETNOTSUPPORTED; break;
	}

	/* handle protocol */
	switch (_hints->protocolType)
	{
		case SSTNETPROTOCOL_TCP: _winHints->ai_protocol = IPPROTO_TCP; break;
		case SSTNETPROTOCOL_UDP: _winHints->ai_protocol = IPPROTO_UDP; break;
		default: return SSTNETRESULT_PROTOCOLNOTSUPPORTED; break;
	}

	/* handle flags */
	tempflags |= (_hints->flags & SSTNETAINFOFLAG_PASSIVE) ? AI_PASSIVE : 0;
	tempflags |= (_hints->flags & SSTNETAINFOFLAG_CANONICALNAME) ? AI_CANONNAME : 0;
	tempflags |= (_hints->flags & SSTNETAINFOFLAG_NUMERICHOST) ? AI_NUMERICHOST : 0;
	tempflags |= (_hints->flags & SSTNETAINFOFLAG_ADDRESSCONFIG) ? AI_ADDRCONFIG : 0;
	tempflags |= (_hints->flags & SSTNETAINFOFLAG_NONAUTHORATATIVE) ? AI_NON_AUTHORITATIVE : 0;
	tempflags |= (_hints->flags & SSTNETAINFOFLAG_SECURE) ? AI_SECURE : 0;
	tempflags |= (_hints->flags & SSTNETAINFOFLAG_RETURNPREFERREDNAME) ? AI_RETURN_PREFERRED_NAMES : 0;
	tempflags |= (_hints->flags & SSTNETAINFOFLAG_FILESERVER) ? AI_FILESERVER : 0;
	_winHints->ai_flags = tempflags;

	return SSTNETRESULT_SUCCESS;
}

static SST_NetResult copySingleWinAddrInfoToSSTAddrInfo( const ADDRINFO* _winInfo, SST_NetAddrInfo_Win32* _sstInfo )
{
	SST_NetAddrInfoFlags tempflags = 0;
	int winFlags = 0;

	/* handle address family */
	switch (_winInfo->ai_family)
	{		
		case AF_INET: _sstInfo->family = SSTNETADDRFAM_IPV4; break;
		case AF_INET6: _sstInfo->family = SSTNETADDRFAM_IPV6; break;
		default: _sstInfo->family = SSTNETADDRFAM_UNKNOWN; break;
	}

	/* handle socket type */
	switch (_winInfo->ai_socktype)
	{
		case SOCK_STREAM: _sstInfo->socketType = SSTNETSOCKTYPE_STREAM; break;
		case SOCK_DGRAM: _sstInfo->socketType = SSTNETSOCKTYPE_DATAGRAM; break;
		default: _sstInfo->socketType = SSTNETSOCKTYPE_UNKNOWN; break;
	}

	/* handle protocol */
	switch (_winInfo->ai_protocol)
	{
		case IPPROTO_TCP: _sstInfo->protocol = SSTNETPROTOCOL_TCP; break;
		case IPPROTO_UDP: _sstInfo->protocol = SSTNETPROTOCOL_UDP; break;
		default: _sstInfo->protocol = SSTNETPROTOCOL_UNKNOWN; break;
	}

	/* handle flags */
	winFlags = _winInfo->ai_flags;
	tempflags |= (winFlags & AI_PASSIVE) ? SSTNETAINFOFLAG_PASSIVE : 0;
	tempflags |= (winFlags & AI_CANONNAME) ? SSTNETAINFOFLAG_CANONICALNAME : 0;
	tempflags |= (winFlags & AI_NUMERICHOST) ? SSTNETAINFOFLAG_NUMERICHOST : 0;
	tempflags |= (winFlags & AI_ADDRCONFIG) ? SSTNETAINFOFLAG_ADDRESSCONFIG : 0;
	tempflags |= (winFlags & AI_NON_AUTHORITATIVE) ? SSTNETAINFOFLAG_NONAUTHORATATIVE : 0;
	tempflags |= (winFlags & AI_SECURE) ? SSTNETAINFOFLAG_SECURE : 0;
	tempflags |= (winFlags & AI_RETURN_PREFERRED_NAMES) ? SSTNETAINFOFLAG_RETURNPREFERREDNAME : 0;
	tempflags |= (winFlags & AI_FILESERVER) ? SSTNETAINFOFLAG_FILESERVER : 0;
	_sstInfo->flags = tempflags;

	/* handle canonical name */
	_sstInfo->canonicalName = _strdup(_winInfo->ai_canonname);
	if (_sstInfo->canonicalName == NULL)
		return SSTNETRESULT_NOSPACE;

	/* handle sockaddr info */
	memcpy(	&(_sstInfo->addr),
			&(_winInfo->ai_addr),
			_winInfo->ai_addrlen);

	return SSTNETRESULT_SUCCESS;
}

static SST_NetResult convertWinAddrInfoToSSTAddrInfo( ADDRINFO* _winai, SST_NetAddrInfo_Win32** _out )
{
	SST_NetAddrInfo_Win32* root = NULL;
	SST_NetAddrInfo_Win32* prev = NULL;
	SST_NetAddrInfo_Win32* temp = NULL;
	ADDRINFO* currWinInfo = _winai;

	while (currWinInfo != NULL)
	{
		/* allocate our temp node space */
		temp = calloc( 1, sizeof(SST_NetAddrInfo_Win32)	);
		if (temp == NULL)
		{
			/* handle out of memory... */
			if (root != NULL)
			{
				SST_Net_FreeAddrInfo(root);
			}
			*_out = NULL;
			return SSTNETRESULT_NOSPACE;
		}

		/* if we haven't had a root node yet, set that */
		if (root == NULL)
		{
			root = temp;
		}

		/* if we have a previous node, attach us as the next node */
		if (prev != NULL)
		{
			prev->next = temp;
		}

		/* copy over attributes, bail if we can't */
		temp->next = NULL;
		if ( copySingleWinAddrInfoToSSTAddrInfo(currWinInfo, temp) != SSTNETRESULT_SUCCESS ) 
		{
			/* handle out of memory... */
			if (root != NULL)
			{
				SST_Net_FreeAddrInfo(root);
			}
			*_out = NULL;
			return SSTNETRESULT_NOSPACE;
		}

		/* set us to be the previous node */
		prev = temp;

		/* go to next record */
		currWinInfo = currWinInfo->ai_next;
	}

	return SSTNETRESULT_SUCCESS;
};

SST_NetResult SST_Net_GetAddrInfo( const char* _node, const char* _service, const SST_NetAddrHints* _hints, SST_NetAddrInfo* _results)
{
	int errcode = 0;
	ADDRINFO hints;
	ADDRINFO* results;
	ADDRINFO* currResult;
	SST_NetAddrInfo_Win32* ret;
	SST_NetResult convret;
	size_t recordCount = 0;

	/* convert the hints */
	memset(&hints, 0, sizeof(struct addrinfo));
	convret = convertSSTAddrHintsToWinAddrHints(_hints, &hints);
	if ( convret != SSTNETRESULT_SUCCESS )
	{
		return convret;
	}

	/* do the lookup */
	errcode = getaddrinfo(_node, _service, (struct addrinfo*) _hints, &results);
	if ( errcode != 0 )
	{
		return decodeerror_getaddrinfo(errcode);
	}

	/* count the number of records */
	currResult = results;
	while (currResult != NULL)
	{
		currResult = currResult->ai_next;
		recordCount++;
	}

	/* convert results */
	*_results = NULL;
	convret = convertWinAddrInfoToSSTAddrInfo(results, &ret);
	if (convret == SSTNETRESULT_SUCCESS)
	{
		*_results = ret;
	}

	/* cleanup */
	freeaddrinfo(results);

	return convret;
}

void SST_Net_FreeAddrInfo( SST_NetAddrInfo _toFree )
{
	SST_NetAddrInfo_Win32* root = (SST_NetAddrInfo_Win32*) _toFree;
	SST_NetAddrInfo_Win32* curr;
	SST_NetAddrInfo_Win32* temp;

	
	curr = root;
	while (curr != NULL)
	{
		/* free strings */
		free(curr->canonicalName);
		curr->canonicalName = NULL;

		/* save where we are and free it */
		temp = curr;
		curr = curr->next;
		free(temp);
	}
}

static SST_NetResult decodeerror_getnameinfo( int _errcode )
{
	switch( _errcode )
	{
		case WSATRY_AGAIN:				return SSTNETRESULT_TRYAGAIN; break;
		case WSAEINVAL:					return SSTNETRESULT_INVALIDARGS; break;
		case WSANO_RECOVERY:			return SSTNETRESULT_HOSTUNREACHABLE; break;
		case WSAEAFNOSUPPORT:			return SSTNETRESULT_ADDRFAMNOTSUPPORTED; break;
		case WSA_NOT_ENOUGH_MEMORY:		return SSTNETRESULT_NOSPACE; break;
		case WSAHOST_NOT_FOUND:			return SSTNETRESULT_HOSTUNREACHABLE; break;
		case WSAEFAULT:					return SSTNETRESULT_BADPOINTER; break;

		default: return SSTNETRESULT_UNKNOWN; break;
	}
}

SST_NetResult SST_Net_GetNameInfo(SST_NetAddress _address, char* _hostName, size_t _hostNameLength, char* _serviceName, size_t _serviceNameLength, SST_NetNameInfoFlags _flags)
{
	int flags = 0;
	int errcode = 0;
	
	flags |= ( _flags &SSTNETNINFOFLAGS_NOFQDN) ? NI_NOFQDN : 0;
	flags |= ( _flags &SSTNETNINFOFLAGS_NUMBERICHOST) ? NI_NUMERICHOST : 0;
	flags |= ( _flags &SSTNETNINFOFLAGS_NAMEREQD) ? NI_NAMEREQD : 0;
	flags |= ( _flags &SSTNETNINFOFLAGS_NUMERICSERVICE) ? NI_NUMERICSERV : 0;
	flags |= ( _flags &SSTNETNINFOFLAGS_DATAGRAM) ? NI_DGRAM : 0;

	errcode = getnameinfo( (const struct sockaddr*) _address,
							sizeof(SOCKADDR_STORAGE),
							_hostName,
							(DWORD) _hostNameLength,
							_serviceName,
							(DWORD) _serviceNameLength,
							flags );

	if (errcode != 0)
	{
		return decodeerror_getnameinfo(WSAGetLastError());
	}
	else
	{
		return SSTNETRESULT_SUCCESS;
	}
}