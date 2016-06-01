/*
	SST_CPU_POSIX.c
	Author: Patrick Baggett <ptb1@762studios.com>
	Created: 12/23/2011

	Purpose: 

	libsst-os CPU querying functions for POSIX systems

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

/*
	The POSIX doesn't actually provide much in the terms of CPU
	querying. Other source files provide specific operating systems
	implementations (e.g: Linux, Solaris, ...)
*/


#include "POSIXPrivate.h"
#include <SST/SST_CPU.h>
#include <SST/SST_Assert.h>

/******************************************************************************/

int SST_OS_GetNumberCPUChips()
{
	/* 0 -> no information available */
	return 0;
}

/******************************************************************************/

int SST_OS_GetNumberPhysicalCPUs(void)
{
	/* 0 -> no information available */
	return 0;
}

/******************************************************************************/

int SST_OS_GetNumberLogicalCPUs(void)
{
	return (int)sysconf(_SC_NPROCESSORS_ONLN);
}

/******************************************************************************/

int SST_OS_MapPhysicalToLogicalCPU(int physCpuId, int* logCpuIds)
{
	(void)physCpuId;
	(void)logCpuIds;
	/* 0 -> API not available */
	return 0;
}

/******************************************************************************/

int SST_OS_GetCPUAffinity(unsigned char* cpuMaskReturn, unsigned int cpuMaskSize)
{
	SST_OS_DebugAssert(cpuMaskReturn != NULL, "CPU mask may not be NULL");

	(void)cpuMaskReturn;
	(void)cpuMaskSize;
	return 0; /* NYI */
}

/******************************************************************************/

int SST_OS_SetCPUAffinity(const unsigned char* cpuMask, unsigned int cpuMaskSize)
{
	SST_OS_DebugAssert(cpuMask != NULL, "CPU mask may not be NULL");

	(void)cpuMask;
	(void)cpuMaskSize;
	return 0; /* NYI */
}

/******************************************************************************/

void SST_OS_SetPreferredCPU(int logCpuId)
{
	(void)logCpuId;
	
	/* Hint ignored */
	return;
}
