/*
	SST_NetSocket.c
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 8/7/2012

	Purpose: 

	Socket functions

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/
#include <SST/SST_NetSocket.h>
#include "PlatformPrivate.h"

/*************************************************************************/

SST_NetResult SST_Net_Socket( SST_NetAddressFamily _addressFamily, SST_NetSocketType _socketType,  SST_NetProtocol _protocol, SST_Socket* _createdSocket)
{
	NativeSocketType sock;
	int af;
	int socktype;
	int proto;
	
	/* Configure socket options */
	switch (_addressFamily)
	{
		case SSTNETADDRFAM_IPV4: af = AF_INET; break;
		case SSTNETADDRFAM_IPV6: af = AF_INET6; break;
		default: return SSTNETRESULT_ADDRFAMNOTSUPPORTED; break;
	}

	switch (_socketType)
	{
		case SSTNETSOCKTYPE_STREAM: socktype = SOCK_STREAM; break;
		case SSTNETSOCKTYPE_DATAGRAM: socktype = SOCK_DGRAM; break;
		default: return SSTNETRESULT_SOCKETNOTSUPPORTED; break;
	}
	
	switch (_protocol)
	{
		case SSTNETPROTOCOL_TCP: proto = IPPROTO_TCP; break;
		case SSTNETPROTOCOL_UDP: proto = IPPROTO_UDP; break;
		default: return SSTNETRESULT_PROTOCOLNOTSUPPORTED; break;
	}
	
	/* Create socket */
	sock = socket(af, socktype, proto);
	if(sock == SST_NATIVE_INVALIDSOCKET)
		return NativeDecodeError();

	*_createdSocket = (SST_Socket)sock;
	return SSTNETRESULT_SUCCESS;
}

/*************************************************************************/

SST_NetResult SST_Net_Bind(SST_Socket sock, const SST_NetAddress* addr)
{
	NativeSocketLen socklen;
	NativeSocketType s = (NativeSocketType)sock;

	socklen = sockLenForNetAddr(addr);

	if(bind(s, (struct sockaddr*) addr, socklen) == 0)
		return SSTNETRESULT_SUCCESS;

	return NativeDecodeError();
}

/*************************************************************************/

SST_NetResult SST_Net_Listen( SST_Socket sock, int backlog)
{
	NativeSocketType s = (NativeSocketType)sock;

	if(listen(s, backlog) == 0)
		return SSTNETRESULT_SUCCESS;

	return NativeDecodeError();
}

/*************************************************************************/

SST_NetResult SST_Net_Connect( SST_Socket sock, const SST_NetAddress* addr)
{
	int socklen;
	NativeSocketType s = (NativeSocketType)sock;

	socklen = sockLenForNetAddr(addr);

	if(connect(s, (struct sockaddr*)addr, socklen) == 0)
		return SSTNETRESULT_SUCCESS;

	return NativeDecodeError();
}

/*************************************************************************/

SST_NetResult SST_Net_Accept(SST_Socket sock, SST_NetAddress* addr, SST_Socket* newSockReturn)
{
	NativeSocketType s = (NativeSocketType)sock;
	NativeSocketType newSock;

	NativeSocketLen addrlen = (int) sizeof(SST_NetAddress);

	newSock = accept(s, (struct sockaddr*)addr, &addrlen);
	if(newSock != SST_NATIVE_INVALIDSOCKET)
	{
		*newSockReturn = newSock;
		return SSTNETRESULT_SUCCESS;
	}

	return NativeDecodeError();
}

/*************************************************************************/

SST_NetResult SST_Net_Send(SST_Socket sock, const void* data, size_t length, uint32_t sendFlags, size_t* bytesSentReturn)
{
	NativeSocketType s = (NativeSocketType)sock;
	int bytesSent;
	int flags = 0;
	int sendAmount;

	flags |= (sendFlags & SSTNET_DONTROUTE ? MSG_DONTROUTE : 0);
	flags |= (sendFlags & SSTNET_OOB ? MSG_OOB : 0);

	/* Ensure send() with huge values doesn't result in negative numbers when typecasted to an int */
	if(length > INT_MAX)
		sendAmount = INT_MAX;
	else
		sendAmount = (int)length;

	bytesSent = send(s, data, sendAmount,flags);
	if(bytesSent != SST_NATIVE_NETERROR)
	{
		*bytesSentReturn = (size_t)bytesSent;
		return SSTNETRESULT_SUCCESS;
	}

	return NativeDecodeError();
}

/*************************************************************************/

SST_NetResult SST_Net_Recv(SST_Socket sock, void* data, size_t length, uint32_t recvFlags, size_t* bytesRecvReturn)
{
	NativeSocketType s = (NativeSocketType)sock;
	int bytesReceived;
	int flags = 0;
	int recvSize;

	flags |= (recvFlags & SSTNET_PEEK)? MSG_PEEK : 0;
	flags |= (recvFlags & SSTNET_OOB)? MSG_OOB : 0;
	flags |= (recvFlags & SSTNET_WAITALL)? MSG_WAITALL : 0;

	/* Ensure recv() with huge values doesn't result in negative numbers when typecasted to an int */
	if(length > INT_MAX)
		recvSize = INT_MAX;
	else
		recvSize = (int)length;

	bytesReceived = recv(s, data, recvSize, flags);
	if(bytesReceived != SST_NATIVE_NETERROR)
	{
		*bytesRecvReturn = (size_t)bytesReceived;
		return SSTNETRESULT_SUCCESS;
	}

	return NativeDecodeError();
}

/*************************************************************************/

SST_NetResult SST_Net_SendTo(SST_Socket sock, const void* data, size_t length, uint32_t sendFlags, const SST_NetAddress* dest, size_t* bytesSentReturn)
{
	NativeSocketType s = (NativeSocketType)sock;
	int bytesSent;
	int flags = 0;
	int sendAmount;
	NativeSocketLen addrLen = sockLenForNetAddr(dest);

	flags |= (sendFlags & SSTNET_DONTROUTE)? MSG_DONTROUTE : 0;
	flags |= (sendFlags & SSTNET_OOB)? MSG_OOB : 0;

	/* Ensure send() with huge values doesn't result in negative numbers when typecasted to an int */
	if(length > INT_MAX)
		sendAmount = INT_MAX;
	else
		sendAmount = (int)length;


	bytesSent = sendto(s, data, sendAmount, flags, (struct sockaddr*)dest, addrLen);
	if(bytesSent != SST_NATIVE_NETERROR)
	{
		*bytesSentReturn = (size_t)bytesSent;
		return SSTNETRESULT_SUCCESS;
	}

	return NativeDecodeError();
}

/*************************************************************************/

SST_NetResult SST_Net_RecvFrom(SST_Socket sock, void* data, size_t length, uint32_t recvFlags, SST_NetAddress* senderReturn, size_t* bytesRecvReturn)
{
	NativeSocketType s = (NativeSocketType)sock;
	int bytesReceived;
	int flags = 0;
	NativeSocketLen addrsize = sizeof(SST_NetAddress);
	int recvSize;

	flags |= (recvFlags & SSTNET_DONTROUTE)? MSG_DONTROUTE : 0;
	flags |= (recvFlags & SSTNET_OOB)? MSG_OOB : 0;

	/* Ensure recv() with huge values doesn't result in negative numbers when typecasted to an int */
	if(length > INT_MAX)
		recvSize = INT_MAX;
	else
		recvSize = (int)length;

	bytesReceived = recvfrom(s, data, recvSize, flags, (struct sockaddr*)senderReturn, &addrsize);

	if(bytesReceived != SST_NATIVE_NETERROR)
	{
		*bytesRecvReturn = (size_t)bytesReceived;
		return SSTNETRESULT_SUCCESS;
	}

	return NativeDecodeError();
}

/*************************************************************************/

void SST_Net_Close(SST_Socket sock)
{
	NativeSocketType s = (NativeSocketType)sock;

	NativeCloseSocket(s);
}

/*************************************************************************/

SST_NetResult SST_Net_GetSockOpt(SST_Socket sock, SST_NetProtocolLevel level, SST_NetSocketOption option, void* optionStorage, size_t* optionStorageSize)
{
	NativeSocketType s = (NativeSocketType)sock;
	int opt;
	int lvl;
	NativeSocketLen optlen;

	lvl = convertSockLevel(level);
	if(lvl == -1)
		return SSTNETRESULT_BADPROTOCOLLEVEL;

	opt = convertSockOpt(option);
	if(opt == -1)
		return SSTNETRESULT_BADSOCKETOP;

	optlen = (NativeSocketLen)*optionStorageSize;
	if(getsockopt(s, lvl, opt, optionStorage, &optlen) == SST_NATIVE_NETERROR)
		return NativeDecodeError();

	*optionStorageSize = (size_t)optlen;
	return SSTNETRESULT_SUCCESS;
}

/*************************************************************************/

SST_NetResult SST_Net_SetSockOpt(SST_Socket sock, SST_NetProtocolLevel level, SST_NetSocketOption option, const void* optionData, size_t optionDataSize)
{
	NativeSocketType s = (NativeSocketType)sock;
	int opt;
	int lvl;
	int optlen;

	lvl = convertSockLevel(level);
	if(lvl == -1)
		return SSTNETRESULT_BADPROTOCOLLEVEL;

	opt = convertSockOpt(option);
	if(opt == -1)
		return SSTNETRESULT_BADSOCKETOP;

	optlen = (int)optionDataSize;
	if(setsockopt(s, lvl, opt, (const void*)optionData, optlen) == SST_NATIVE_NETERROR)
		return NativeDecodeError();

	return SSTNETRESULT_SUCCESS;
}

/*************************************************************************/

SST_NetResult SST_Net_SetNonblock(SST_Socket sock, int nonblock)
{
	NativeSocketType s = (NativeSocketType)sock;
	int nb = (nonblock != 0);

	if(NativeIoctl(s, FIONBIO, (void*)&nb) != SST_NATIVE_NETERROR)
		return SSTNETRESULT_SUCCESS;

	return NativeDecodeError();
}
