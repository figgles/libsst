/*
	Win32Private.h
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 12/23/2011

	Purpose: 

	Private data structures for Win32 implementation of libsst-os. Not to be distributed
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
#include <windows.h>
#include <pstdint.h>

#if defined(__GNUC__) /* Missing Windows 7 API on various GCC targets, remove when is fixed. */
typedef ULONG_PTR  KAFFINITY;

typedef enum _LOGICAL_PROCESSOR_RELATIONSHIP { 
  RelationProcessorCore,
  RelationNumaNode,
  RelationCache,
  RelationProcessorPackage,
  RelationGroup,
  RelationAll               = 0xffff
} LOGICAL_PROCESSOR_RELATIONSHIP;

typedef enum _PROCESSOR_CACHE_TYPE { 
  CacheUnified,
  CacheInstruction,
  CacheData,
  CacheTrace
} PROCESSOR_CACHE_TYPE;

typedef struct _CACHE_DESCRIPTOR {
  BYTE                 Level;
  BYTE                 Associativity;
  WORD                 LineSize;
  DWORD                Size;
  PROCESSOR_CACHE_TYPE Type;
} CACHE_DESCRIPTOR, *PCACHE_DESCRIPTOR;

typedef struct _GROUP_AFFINITY {
  KAFFINITY Mask;
  WORD      Group;
  WORD      Reserved[3];
} GROUP_AFFINITY, *PGROUP_AFFINITY;

typedef struct _PROCESSOR_NUMBER {
  WORD Group;
  BYTE Number;
  BYTE Reserved;
} PROCESSOR_NUMBER, *PPROCESSOR_NUMBER;

typedef struct _PROCESSOR_GROUP_INFO {
  BYTE      MaximumProcessorCount;
  BYTE      ActiveProcessorCount;
  BYTE      Reserved[38];
  KAFFINITY ActiveProcessorMask;
} PROCESSOR_GROUP_INFO, *PPROCESSOR_GROUP_INFO;

typedef struct _PROCESSOR_RELATIONSHIP {
  BYTE           Flags;
  BYTE           Reserved[21];
  WORD           GroupCount;
  GROUP_AFFINITY GroupMask[ANYSIZE_ARRAY];
} PROCESSOR_RELATIONSHIP, *PPROCESSOR_RELATIONSHIP;

typedef struct _NUMA_NODE_RELATIONSHIP {
  DWORD          NodeNumber;
  BYTE           Reserved[20];
  GROUP_AFFINITY GroupMask;
} NUMA_NODE_RELATIONSHIP, *PNUMA_NODE_RELATIONSHIP;

typedef struct _CACHE_RELATIONSHIP {
  BYTE                 Level;
  BYTE                 Associativity;
  WORD                 LineSize;
  DWORD                CacheSize;
  PROCESSOR_CACHE_TYPE Type;
  BYTE                 Reserved[20];
  GROUP_AFFINITY       GroupMask;
} CACHE_RELATIONSHIP, *PCACHE_RELATIONSHIP;

typedef struct _GROUP_RELATIONSHIP {
  WORD                 MaximumGroupCount;
  WORD                 ActiveGroupCount;
  BYTE                 Reserved[20];
  PROCESSOR_GROUP_INFO GroupInfo[ANYSIZE_ARRAY];
} GROUP_RELATIONSHIP, *PGROUP_RELATIONSHIP;

typedef struct _SYSTEM_LOGICAL_PROCESSOR_INFORMATION {
  ULONG_PTR                      ProcessorMask;
  LOGICAL_PROCESSOR_RELATIONSHIP Relationship;
  union {
    struct {
      BYTE Flags;
    } ProcessorCore;
    struct {
      DWORD NodeNumber;
    } NumaNode;
    CACHE_DESCRIPTOR Cache;
    ULONGLONG        Reserved[2];
  };
} SYSTEM_LOGICAL_PROCESSOR_INFORMATION, *PSYSTEM_LOGICAL_PROCESSOR_INFORMATION;

typedef struct _SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX {
  LOGICAL_PROCESSOR_RELATIONSHIP Relationship;
  DWORD                          Size;
  union {
    PROCESSOR_RELATIONSHIP Processor;
    NUMA_NODE_RELATIONSHIP NumaNode;
    CACHE_RELATIONSHIP     Cache;
    GROUP_RELATIONSHIP     Group;
  };
} SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX, *PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX;

BOOL WINAPI GetLogicalProcessorInformationEx(
	LOGICAL_PROCESSOR_RELATIONSHIP RelationshipType,
	PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX Buffer,
	PDWORD ReturnedLength);

BOOL WINAPI GetLogicalProcessorInformation(PSYSTEM_LOGICAL_PROCESSOR_INFORMATION Buffer, PDWORD ReturnLength);


BOOL WINAPI SetThreadIdealProcessorEx(HANDLE hThread, PPROCESSOR_NUMBER lpIdealProcessor, PPROCESSOR_NUMBER lpPreviousIdealProcessor);

#endif

/*************************************************************************/
typedef struct SST_File_Win32
{
	HANDLE hFile; /* Handle from CreateFile() */
	HANDLE hMap; /* Handle from CreateFileMapping() */
	int isAsync; /* Is this file in async mode */
	DWORD accessFlags; /* Flags for access used in CreateFileA() */

#ifdef _DEBUG
	int nrMmaps; /* Number of outstanding memory maps */
#endif
} SST_File_Win32;

typedef struct SST_MemoryMap_Win32
{
	uint64_t offset;	/* Offset parameter as given to SST_OS_MmapCreate() */
	size_t len;			/* Length parameter as given to SST_OS_MmapCreate() */
	void* base;			/* Returned base address from SST_OS_MmapCreate() */

#ifdef _DEBUG
	SST_File_Win32* owner; /* File that created this memory map */
#endif
} SST_MemoryMap_Win32;

#endif
