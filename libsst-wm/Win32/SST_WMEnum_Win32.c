/*
	SST_WMEnum_Win32.c
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 1/7/2012

	Purpose: 

	Enumerates graphics adapters and screens.

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#include <SST/SST_WM.h>

#include "Win32Private.h"
#include "../APIPrivate.h"

#include <string.h> /* strlen() etc. */
#include <stdlib.h> 

/*************************************************************************/

static SST_GraphicsEnumerator Win32_CreateGraphicsEnumerator(void)
{
	DISPLAY_DEVICEA* devsFound = NULL;
	char* adapterNames;
	char* adapterGUIDs;
	size_t* screenCount;
	size_t adapterCount;
	size_t devCount = 0;
	size_t ASPairCount = 0;
	size_t i;
	SST_GraphicsEnumerator_Win32* enumerator;
	ASMapEntry* ASMap;
	HANDLE hProcessHeap;

	/* Get a list of Win32 display devices */
	devsFound = get_win32devs(&devCount);
	if(devsFound == NULL)
		return NULL;

	hProcessHeap = GetProcessHeap();

	/* Get a list of the graphics adapters' names */
	adapterNames = get_adapters(devsFound, devCount, &adapterCount, &adapterGUIDs);
	if(adapterNames == NULL)
	{
		HeapFree(hProcessHeap, 0, devsFound);
		return NULL;
	}

	/* Make a map of adapter->screen count */
	screenCount = HeapAlloc(hProcessHeap, 0, adapterCount*sizeof(size_t));
	if(screenCount == NULL)
	{
		HeapFree(hProcessHeap, 0, adapterGUIDs);
		HeapFree(hProcessHeap, 0, adapterNames);
		HeapFree(hProcessHeap, 0, devsFound);
		return NULL;
	}
	for(i=0; i<adapterCount; i++)
		screenCount[i] = 0;
	
	/* Attempt to build the adapter-screen map */
	ASMap = build_asmap(devsFound, adapterGUIDs, devCount, adapterCount, screenCount, &ASPairCount);
	if(ASMap == NULL)
	{
		HeapFree(hProcessHeap, 0, adapterGUIDs);
		HeapFree(hProcessHeap, 0, adapterNames);
		HeapFree(hProcessHeap, 0, devsFound);
		HeapFree(hProcessHeap, 0, screenCount);
		return NULL;
	}

	/* Done with GUIDs */
	HeapFree(hProcessHeap, 0, adapterGUIDs);

	/* Get the list of video modes for each adapter-screen pair */
	for(i=0; i<ASPairCount; i++)
	{
		size_t vmodeCount;
		SST_VideoMode* vmodes;
		
		vmodes = get_vmodes(ASMap[i].dev, &vmodeCount, &ASMap[i].defaultVmode);
		if(vmodes == NULL)
		{
			size_t j;
			for(j=0; j<i; j++)
				HeapFree(hProcessHeap, 0, ASMap[i].vmodes);
			HeapFree(hProcessHeap, 0, adapterNames);
			HeapFree(hProcessHeap, 0, devsFound);
			HeapFree(hProcessHeap, 0, screenCount);
			HeapFree(hProcessHeap, 0, ASMap);
			return NULL;
		}
		/* Save the screens for this */
		ASMap[i].vmodeCount = vmodeCount;
		ASMap[i].vmodes = vmodes;
	}

	/* Prepare a structure to return... */
	enumerator = HeapAlloc(hProcessHeap, 0, sizeof(SST_GraphicsEnumerator_Win32));
	if(enumerator == NULL)
	{
		/* Doh! So close :\ */
		size_t j;
		for(j=0; j<i; j++)
			HeapFree(hProcessHeap, 0, ASMap[i].vmodes);

		HeapFree(hProcessHeap, 0, adapterNames);
		HeapFree(hProcessHeap, 0, devsFound);
		HeapFree(hProcessHeap, 0, screenCount);
		HeapFree(hProcessHeap, 0, ASMap);
		return NULL;
	}

	/* Save fields */
	enumerator->adapterNames = adapterNames;
	enumerator->adapterCount = adapterCount;
	enumerator->devCount = devCount;
	enumerator->devsFound = devsFound;
	enumerator->screenCount = screenCount;
	enumerator->ASMap = ASMap;
	enumerator->ASPairCount = ASPairCount;

	return enumerator;
}

/*************************************************************************/

static size_t Win32_GetEnumAdapterCount(SST_GraphicsEnumerator enumerator)
{
	SST_GraphicsEnumerator_Win32* enumWin32 = (SST_GraphicsEnumerator_Win32*)enumerator;

	return enumWin32->adapterCount;
}

/*************************************************************************/

static void Win32_GetEnumAdapterName(SST_GraphicsEnumerator enumerator, size_t adapterId, char* nameReturn, size_t* bufferSize)
{
	SST_GraphicsEnumerator_Win32* enumWin32 = (SST_GraphicsEnumerator_Win32*)enumerator;
	size_t len;
	const char* name = &enumWin32->adapterNames[adapterId * ADAPTER_NAME_STRLEN];

	len = strlen(name);

	/* Query name length */
	if(nameReturn == NULL)
	{
		*bufferSize = len+1;
	}
	else
	{
		size_t copyAmount;

		/* Nothing to do? */
		if(*bufferSize == 0)
			return;

		/* Use min(len, (*bufferSize)-1) */
		copyAmount = len;
		if(copyAmount > (*bufferSize)-1)
			copyAmount = (*bufferSize)-1;

		memcpy(nameReturn, name, copyAmount);
		nameReturn[copyAmount] = '\0';
	}

}

/*************************************************************************/

static size_t Win32_GetEnumScreenCount(SST_GraphicsEnumerator enumerator, size_t adapterId)
{
	SST_GraphicsEnumerator_Win32* enumWin32 = (SST_GraphicsEnumerator_Win32*)enumerator;
	
	return enumWin32->screenCount[adapterId];
}

/*************************************************************************/

static void Win32_GetEnumVideoModes(SST_GraphicsEnumerator enumerator, size_t adapterId, size_t screenId, SST_VideoMode* modesReturn, size_t* modeCountReturn)
{
	SST_GraphicsEnumerator_Win32* enumWin32 = (SST_GraphicsEnumerator_Win32*)enumerator;
	size_t i;
	ASMapEntry* entry = NULL;

	/* Determine which adapter-screen pair to use */
	for(i=0; i<enumWin32->ASPairCount; i++)
	{
		entry = &enumWin32->ASMap[i];
		if(entry->adapter == adapterId && entry->screen == screenId)
		{
			entry = &enumWin32->ASMap[i];
			break;
		}
	}

	/* When 'modesReturn' is null, user is getting mode count */
	if(modesReturn == NULL)
		*modeCountReturn = entry->vmodeCount;
	else /* else, copy '*modeCountReturn' number of modes */
	{
		size_t nrCopy = *modeCountReturn;
		if(nrCopy > entry->vmodeCount)
			nrCopy = entry->vmodeCount;
		
		memcpy(modesReturn, entry->vmodes, sizeof(SST_VideoMode) * nrCopy);
	}

}

/*************************************************************************/

static void Win32_GetEnumCurrentVideoMode(SST_GraphicsEnumerator enumerator, size_t adapterId, size_t screenId, SST_VideoMode* mode)
{
	SST_GraphicsEnumerator_Win32* enumWin32 = (SST_GraphicsEnumerator_Win32*)enumerator;
	size_t i;

	for(i=0; i<enumWin32->ASPairCount; i++)
	{
		if(enumWin32->ASMap[i].adapter == adapterId && enumWin32->ASMap[i].screen == screenId)
		{
			*mode = enumWin32->ASMap[i].defaultVmode;
			return;
		}
	}
}

/*************************************************************************/

static void Win32_DestroyGraphicsEnumerator(SST_GraphicsEnumerator enumerator)
{
	SST_GraphicsEnumerator_Win32* enumWin32 = (SST_GraphicsEnumerator_Win32*)enumerator;
	size_t i;
	HANDLE hProcessHeap;

	hProcessHeap = GetProcessHeap();

	HeapFree(hProcessHeap, 0, enumWin32->adapterNames);
	HeapFree(hProcessHeap, 0, enumWin32->devsFound);
	HeapFree(hProcessHeap, 0, enumWin32->screenCount);

	/* Free modes for each adapter-screen pair */
	for(i=0; i<enumWin32->ASPairCount; i++)
		HeapFree(hProcessHeap, 0, enumWin32->ASMap[i].vmodes);
	HeapFree(hProcessHeap, 0, enumWin32->ASMap);

	HeapFree(hProcessHeap, 0, enumWin32);
}

struct SST_WM_EnumFuncs Win32_EnumFuncs = {
	Win32_CreateGraphicsEnumerator,
	Win32_GetEnumAdapterCount,
	Win32_GetEnumAdapterName,
	Win32_GetEnumScreenCount,
	Win32_GetEnumVideoModes,
	Win32_GetEnumCurrentVideoMode,
	Win32_DestroyGraphicsEnumerator
};
