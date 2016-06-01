/*
	SST_CPU_Win32.c
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 12/23/2011

	Purpose: 

	libsst-os CPU querying functions for Win32 systems (Windows 7 or later)

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#include "Win32Private.h"
#include <malloc.h> /* _alloca() */

#include <SST/SST_CPU.h>
#include <SST/SST_Assert.h>

/*
	SUPPORT FOR > 64 CPUS
	----------------------
	This code does its best to be compatible with large numbers of logical CPUs. Processor groups are
	a bit weird, see MSDN (http://msdn.microsoft.com/en-us/library/windows/desktop/dd405503(v=vs.85).aspx)
*/

/*************************************************************************/

static const uint8_t popbits[16] = { 0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4 };

/*************************************************************************/

/* popcount of an 8-bit value */
static uint8_t popcount8(uint8_t v)
{
	return popbits[v & 0x0Fu] + popbits[v>>4];
}

/*************************************************************************/

/* popcount on the Win32 KAFFINITY value (64-bit value) */
static int popcount(KAFFINITY mask)
{
	int count = 0, i;

	for(i=0; i<sizeof(KAFFINITY); i++)
	{
		/* No more bits set? */
		if(!mask)
			break;

		count += popcount8(mask & 0xFF);

		mask >>= 8;
	}

	return count;
}

/*************************************************************************/

int SST_OS_GetNumberCPUChips()
{
	DWORD length = 0;
	SYSTEM_LOGICAL_PROCESSOR_INFORMATION* relat;
	DWORD nr;
	int nrChips = 0;

	/* Query data structure size */
	GetLogicalProcessorInformation(NULL, &length);
	if(GetLastError() != ERROR_INSUFFICIENT_BUFFER)
		return -1;

	/* Really get the info this time */
	relat = (SYSTEM_LOGICAL_PROCESSOR_INFORMATION*)_alloca((size_t)length);
	if(GetLogicalProcessorInformation(relat, &length) == FALSE)
		return -2;

	/* Scan list */
	nr = length / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION);
	while(nr > 0)
	{
		if(relat->Relationship == RelationProcessorPackage)
			nrChips++;
	
		relat++;
		nr--;
	}

	return nrChips;
}

/*************************************************************************/

int SST_OS_GetNumberPhysicalCPUs(void)
{
	DWORD length = 0;
	char* ptr, *end;
	int nrCores = 0;

	/* Query data structure size */
	GetLogicalProcessorInformationEx(RelationProcessorCore, NULL, &length);
	if(GetLastError() != ERROR_INSUFFICIENT_BUFFER)
		return -1;

	/* Really get the info this time */
	ptr = (char*)_alloca((size_t)length);
	end = ptr + length;
	if(GetLogicalProcessorInformationEx(
		RelationProcessorCore,
		(SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX*)ptr,
		&length) == FALSE)
		return -2;

	while(ptr < end)
	{
		SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX* info = (SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX*)ptr;
		nrCores++;
	
		ptr += (size_t)info->Size;
	}

	return nrCores;
}

/*************************************************************************/

int SST_OS_GetNumberLogicalCPUs(void)
{
	DWORD length = 0;
	char* ptr, *end;
	int nrThreads = 0;

	/* Query data structure size */
	GetLogicalProcessorInformationEx(RelationProcessorPackage, NULL, &length);
	if(GetLastError() != ERROR_INSUFFICIENT_BUFFER)
		return -1;

	/* Really get the info this time */
	ptr = (char*)_alloca((size_t)length);
	end = ptr + length;
	if(GetLogicalProcessorInformationEx(
		RelationProcessorPackage,
		(SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX*)ptr,
		&length) == FALSE)
		return -2;

	while(ptr < end)
	{
		WORD i;
		SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX* info = (SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX*)ptr;

		for(i=0; i<info->Processor.GroupCount; i++)
			nrThreads += popcount(info->Processor.GroupMask[i].Mask);

	
		ptr += info->Size;
	}

	return nrThreads;
}

/*************************************************************************/

int SST_OS_MapPhysicalToLogicalCPU(int physCpuId, int* logCpuIds)
{
	DWORD length = 0;
	char* ptr, *end;
	WORD i;
	int j;
	SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX* info;

	SST_OS_DebugAssert(logCpuIds != NULL, "The return array for logical CPUs may not be NULL");

	/* Query data structure size */
	GetLogicalProcessorInformationEx(RelationProcessorCore, NULL, &length);
	if(GetLastError() != ERROR_INSUFFICIENT_BUFFER)
		return -2;

	/* Really get the info this time */
	ptr = (char*)_alloca((size_t)length);
	end = ptr + length;
	if(GetLogicalProcessorInformationEx(
		RelationProcessorCore,
		(SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX*)ptr,
		&length) == FALSE)
		return -3;

	info = (SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX*)ptr;
	#ifdef _DEBUG
	{
		/* Figure out how many elements in this array */
		int nr = (int)(length / info->Size);

		/* Bounds checking */
		SST_OS_DebugAssert(!(physCpuId >= nr), "Array too small to contain logical CPUs. Use SST_OS_GetNumberLogicalCPUs() to determine correct size");
	}
	#endif

	/* This union is large, so we can't just do info[index], we have to do
	'base_address + size * index'. Ugly, but necessary. */
	info = (SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX*)(ptr + (size_t)(info->Size*physCpuId));

	j = 0; /* j = number of logical CPUs mapped */
	for(i=0; i<info->Processor.GroupCount; i++)
	{
		/* Figure out base logical CPU ID for processor group. Usually 64 CPUs / group. */
		int groupbase = (int)(info->Processor.GroupMask[i].Group * 8 * sizeof(KAFFINITY));
		size_t k;
		KAFFINITY mask = info->Processor.GroupMask[i].Mask;

		/*
			Algorithm: Each GROUP_AFFINITY structure has a mask. Scan through it and
			if bit 'k' is set, then add 'k+groupbase' to the array.
		*/

		/* Scan through bits and add logical CPUs */
		for(k=0; k<(8 * sizeof(KAFFINITY)); k++)
		{
			/* No more bits set */
			if(!mask)
				break;
			
			/* Is this bit set? */
			if(mask & 1)
			{
				/* Add the logical CPU to the array */
				logCpuIds[j] = (int)k + groupbase;
				j++;
			}

			/* Next bit... */
			mask >>= 1;
		}	
	}
	
	/* Return the number of logical CPUs written to logCpuIds[] */
	return j;
}

/*************************************************************************/

int SST_OS_GetCPUAffinity(unsigned char* cpuMaskReturn, unsigned int cpuMaskSize)
{
	WORD maxGroup;
	GROUP_AFFINITY aff;
	SST_OS_DebugAssert(cpuMaskReturn != NULL, "CPU mask may not be NULL");
	SST_OS_DebugAssert(cpuMaskSize > 0, "CPU mask may not be zero");

	/* Calculate the maximum number of groups that can be stored using the space provided */
	maxGroup = (WORD)(cpuMaskSize / sizeof(KAFFINITY));
	if(cpuMaskSize % sizeof(KAFFINITY))
		maxGroup += 1;

	if(maxGroup == 0)
		return -1;

	memset(cpuMaskReturn, 0, cpuMaskSize);

	GetThreadGroupAffinity(GetCurrentThread(), &aff);

	/* Ensure the real processor group doesn't exceed provided space */
	if(aff.Group < maxGroup)
	{
		uint32_t byteOffset = aff.Group * sizeof(KAFFINITY);	/* i.e. where to begin in cpuMaskReturn[] */
		uint32_t bytesLeft = cpuMaskSize - byteOffset;		/* i.e. how many bytes are left */
		uint32_t i;
		KAFFINITY mask = aff.Mask;
		unsigned char* maskReturn = cpuMaskReturn + byteOffset;

		for(i=0; i<bytesLeft; i++)
		{
			if(!mask)
				break;

			maskReturn[i] = (uint8_t)(mask & 0xFF);

			mask >>= 8;
		}
	}

	return 1;
}

/*************************************************************************/

int SST_OS_SetCPUAffinity(const unsigned char* cpuMask, unsigned int cpuMaskSize)
{
	uint8_t groupPopCount[4096/(sizeof(KAFFINITY) * 8)];
	KAFFINITY groupMask[4096/(sizeof(KAFFINITY) * 8)];
	uint8_t lowest = UINT8_MAX;
	uint8_t lowestGroup = 0;
	unsigned int i;
	GROUP_AFFINITY aff;


	SST_OS_DebugAssert(cpuMask != NULL, "CPU mask may not be NULL");


	/* Windows only allows a thread to be a member of a single processor group, which makes sense
	when you consider that migrating threads across NUMA nodes is a bad idea. Here, we select the
	processor group that has the fewest bits set (except for 0...) */
	if(cpuMaskSize > 4096)	/* Disallow arbitrarily large masks. 4096 processors is fine, really */
		cpuMaskSize = 4096;

	memset(groupPopCount, 0, sizeof(groupPopCount));
	memset(groupMask, 0, sizeof(groupMask));

	/* Operate on each byte */
	for(i=0; i<cpuMaskSize; i++)
	{
		uint8_t groupIndex = (uint8_t)(i / sizeof(KAFFINITY));	/* i is in bytes, sizeof() is in bytes */
		uint8_t groupByte =  (uint8_t)(i % 8);

		/* Sum all popcount8() of the bytes that make up a processor group's mask */
		groupPopCount[groupIndex] += popcount8(cpuMask[i]);

		/* OR the 8-bit mask into KAFFINITY values (essentially merge them) */
		groupMask[groupIndex] |= (KAFFINITY)cpuMask[i] <<  (KAFFINITY)(groupByte * 8);

		/* Record the smallest group that is not 0 */
		if(groupPopCount[groupIndex] > 0 && groupPopCount[groupIndex] < lowest)
			lowest = groupIndex;
	}


	aff.Group = (WORD)((uint16_t)lowestGroup);
	aff.Mask = groupMask[lowestGroup];

	SetThreadGroupAffinity(GetCurrentThread(), &aff, NULL);

	return 1;
}

/*************************************************************************/

void SST_OS_SetPreferredCPU(int logCpuId)
{
	PROCESSOR_NUMBER ideal;

	SST_OS_DebugAssert(logCpuId < SST_OS_GetNumberLogicalCPUs(), "Logical CPU ID is out of range");

	ideal.Group = (WORD)logCpuId / (WORD)(sizeof(KAFFINITY)*8);
	ideal.Number = (WORD)logCpuId % (WORD)(sizeof(KAFFINITY)*8);
	ideal.Reserved = 0;

	SetThreadIdealProcessorEx(GetCurrentThread(), &ideal, NULL);
}
