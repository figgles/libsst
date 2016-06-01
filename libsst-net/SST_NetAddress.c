/*
	SST_NetAddress.h
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 8/7/2012

	Purpose: 

	Address storage manipulation

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#include "PlatformPrivate.h"
#include <SST/SST_NetAddress.h>
#include <string.h>

/*************************************************************************/

SST_NetResult SST_Net_InitAddress(SST_NetAddress* addr, SST_NetAddressFamily family, unsigned short port)
{
	unsigned short nboPort; /* Port in network byte order */
	size_t addrSize;
	uint8_t* asBytes = (uint8_t*)addr;

	nboPort = htons(port);

	/* Avoid strict aliasing violations by setting up a temporary structure and memcpy()ing. */

	switch(family)
	{
		case SSTNETADDRFAM_IPV4:
		{
			struct sockaddr_in addr4;

			addr4.sin_family = AF_INET;
			addr4.sin_port = nboPort;
			addr4.sin_addr.s_addr = INADDR_ANY;
			memset(&addr4.sin_zero, 0, sizeof(addr4.sin_zero));

			addrSize = sizeof(struct sockaddr_in);
			memcpy(addr, &addr4, addrSize);
			break;
		}

		case SSTNETADDRFAM_IPV6:
		{
			struct sockaddr_in6 addr6;

			addr6.sin6_family = AF_INET;
			addr6.sin6_port = nboPort;
			addr6.sin6_flowinfo = 0;
			addr6.sin6_addr = in6addr_any;
			addr6.sin6_scope_id = 0;

			addrSize = sizeof(struct sockaddr_in6);
			memcpy(addr, &addr6, addrSize);
			break;
		}

		/* Default: return error */
		default:
			return SSTNETRESULT_ADDRFAMNOTSUPPORTED;
	}
	
	/* memset() the rest of the address storage to all-bits-zero. */
	memset(asBytes + addrSize, 0, sizeof(SST_NetAddress) - addrSize);

	return SSTNETRESULT_SUCCESS;
}

/*************************************************************************/

SST_NetAddressFamily SST_Net_GetAddressFamily(const SST_NetAddress* addr)
{
	switch(addr->ss_family)
	{
		case AF_INET: return SSTNETADDRFAM_IPV4;
		case AF_INET6: return SSTNETADDRFAM_IPV6;
		default: return SSTNETADDRFAM_UNKNOWN;
	}
}

/*************************************************************************/

unsigned short SST_Net_GetAddressPort(const SST_NetAddress* addr)
{

	switch(addr->ss_family)
	{
		case AF_INET:
		{
			const struct sockaddr_in* addr4 = (const struct sockaddr_in*)addr;

			return ntohs(addr4->sin_port);
		}

		case AF_INET6:
		{
			const struct sockaddr_in6* addr6 = (const struct sockaddr_in6*)addr;

			return ntohs(addr6->sin6_port);
		}

		default: return UINT16_MAX;
	}
}

/*************************************************************************/

int SST_Net_AddressCompare(const SST_NetAddress* addr1, const SST_NetAddress* addr2)
{

	if(addr1->ss_family != addr2->ss_family)
		return (addr1->ss_family < addr2->ss_family ? -1 : 1);

	switch(addr1->ss_family)
	{
		case AF_INET:
		{
			const struct sockaddr_in* A = (const struct sockaddr_in*)addr1;
			const struct sockaddr_in* B = (const struct sockaddr_in*)addr2;

			/* Are the addresses different? */
			if(A->sin_addr.s_addr != B->sin_addr.s_addr)
				return (A->sin_addr.s_addr < B->sin_addr.s_addr ? -1 : 1);
			
			/* Are the ports different? */
			if(A->sin_port != B->sin_port)
				return (A->sin_port < B->sin_port ? -1 : 1);

			/* Address/port are the same, so OK */
			return 0;
		}

		case AF_INET6:
		{
			const struct sockaddr_in6* A = (const struct sockaddr_in6*)addr1;
			const struct sockaddr_in6* B = (const struct sockaddr_in6*)addr2;
			int result;

			result = memcmp(&A->sin6_addr, &B->sin6_addr, sizeof(struct in6_addr));

			/* Are the addresses different? */
			if(result != 0)
				return result;
			
			/* Are the ports different? */
			if(A->sin6_port != B->sin6_port)
				return (A->sin6_port < B->sin6_port ? -1 : 1);

			/* Address/port are the same, so OK */
			return 0;
		}

	}

	/* Undefined structure -> useless result */
	return -1;
}

/*************************************************************************/

int SST_Net_AddressIsLocalhost(const SST_NetAddress* addr)
{
	int retval = 0;

	switch(addr->ss_family)
	{
		case AF_INET:
		{
			struct sockaddr_in* addr4 = (struct sockaddr_in*)addr;

			uint32_t localhost = (uint32_t)inet_addr("127.0.0.1");
			uint32_t myaddr = (uint32_t)addr4->sin_addr.s_addr;

			/* Compare address to loopback */
			retval = (myaddr == localhost);
		}

		case AF_INET6:
		{
			struct sockaddr_in6* addr6 = (struct sockaddr_in6*)addr;

			/* Compare address to loopback */
			retval = (memcmp(&addr6->sin6_addr, &in6addr_loopback, sizeof(in6addr_loopback)) == 0);
		}

		default: retval = -1; /* Error code*/
	}

	return retval;
}

/*************************************************************************/

void SST_Net_AddressSetToLocalhost(SST_NetAddress* addr)
{
	switch(addr->ss_family)
	{
		case AF_INET:
		{
			struct sockaddr_in* addr4 = (struct sockaddr_in*)addr;

			addr4->sin_addr.s_addr = inet_addr("127.0.0.1");
		}

		case AF_INET6:
		{
			struct sockaddr_in6* addr6 = (struct sockaddr_in6*)addr;

			addr6->sin6_addr = in6addr_loopback;
		}
	}

}


/*************************************************************************/

SST_NetResult SST_Net_SetAddressFromAddress(SST_NetAddress* dst, const SST_NetAddress* src)
{
	switch(src->ss_family)
	{
		case AF_INET:
		{
			struct sockaddr_in* dstAddr = (struct sockaddr_in*)dst;
			const struct sockaddr_in* srcAddr = (const struct sockaddr_in*)src;

			memcpy(&dstAddr->sin_addr, &srcAddr->sin_addr, sizeof(struct in_addr));
			break;
		}

		case AF_INET6:
		{
			struct sockaddr_in6* dstAddr = (struct sockaddr_in6*)dst;
			const struct sockaddr_in6* srcAddr = (const struct sockaddr_in6*)src;

			memcpy(&dstAddr->sin6_addr, &srcAddr->sin6_addr, sizeof(struct in6_addr));
			break;
		}
		/* Default: return error */
		default:
			return SSTNETRESULT_ADDRFAMNOTSUPPORTED;
	}

	return SSTNETRESULT_SUCCESS;
}

/*************************************************************************/

SST_NetResult SST_Net_SetAddressFromString(SST_NetAddress* addr, const char* addrString)
{
	int result;
	char buf[sizeof(SST_NetAddress)];
	result = inet_pton(addr->ss_family, addrString, buf);

	if(result > 0)
	{
		switch(addr->ss_family)
		{
			case AF_INET:
			{
				struct sockaddr_in* dst = (struct sockaddr_in*)addr;

				memcpy(&dst->sin_addr, buf, sizeof(dst->sin_addr));

				break;
			}

			case AF_INET6:
			{
				struct sockaddr_in6* dst = (struct sockaddr_in6*)addr;

				memcpy(&dst->sin6_addr, buf, sizeof(dst->sin6_addr));
				break;			
			}
		}
		return SSTNETRESULT_SUCCESS;
	}
	else if(result == 0)
		return SSTNETRESULT_BADADDRESSSTRING;
	
	//Other error
	return NativeDecodeError();
}