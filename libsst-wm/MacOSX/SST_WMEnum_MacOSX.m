/*
	SST_WMEnum_MacOSX.m
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 11/16/2012

	Purpose: 

	Enumerates graphics adapters and screens on MacOS X

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#import <AppKit/AppKit.h>
#import <Foundation/Foundation.h>
#import <IOKit/IOKitLib.h>

#include <SST/SST_WM.h>
#include "MacOSXPrivate.h"

#include <string.h>
#include <stdlib.h>

/******************************************************************************/

SST_GraphicsEnumerator SST_WM_CreateGraphicsEnumerator(void)
{
	SST_GraphicsEnumerator_MacOSX* enumerator;
	uint32_t count = 0, i;
	CGDirectDisplayID* ids;
	
	/* Get list of active displays */
	CGGetActiveDisplayList(UINT32_MAX, NULL, &count);
	if(count == 0)
		return NULL;
	
	/* Allocate array of displays, then fetch */
	ids = malloc(sizeof(CGDirectDisplayID) * count);
	if(ids == NULL)
		return NULL;
	if(CGGetActiveDisplayList(count, ids, &count) != kCGErrorSuccess)
	{
		free(ids);
		return NULL;
	}

	/* Match GPU to display */
	for(i=0; i<count; i++)
	{
		io_service_t port = CGDisplayIOServicePort(ids[i]); /* Port is owned by CG, don't release */
		
		/* TODO: derp how does one do this using I/O Kit? */
		
		
	}

	/* Allocate enumerator object */
	enumerator = malloc(sizeof(SST_GraphicsEnumerator_MacOSX));
	if(enumerator == NULL)
		return NULL;
	
	
	
	
	return (SST_GraphicsEnumerator)enumerator;
}

/******************************************************************************/

size_t SST_WM_GetEnumAdapterCount(SST_GraphicsEnumerator enumerator)
{
	/* TODO: Implement */
	return 1;
}

/******************************************************************************/

void SST_WM_GetEnumAdapterName(SST_GraphicsEnumerator enumerator, size_t adapterId,char* nameReturn, size_t* bufferSize)
{
	/* TODO: Implement fully */
	const char* s = "Default Adapter";

	/* Query name length */
	if(nameReturn == NULL)
		*bufferSize = strlen(s) + 1;
	else
	{
		size_t copyAmount;
		
		/* Nothing to do? */
		if(*bufferSize == 0)
			return;

		/* Use min(len, (*bufferSize)-1) */
		copyAmount = strlen(s);
		if(copyAmount > (*bufferSize)-1)
			copyAmount = (*bufferSize)-1;

		memcpy(nameReturn, s, copyAmount);
		nameReturn[copyAmount] = '\0';
	}
}

/******************************************************************************/

size_t SST_WM_GetEnumScreenCount(SST_GraphicsEnumerator enumerator, size_t adapterId)
{
	/* TODO: Implement */

	return 1;
}

/******************************************************************************/

void SST_WM_GetEnumVideoModes(SST_GraphicsEnumerator enumerator, size_t adapterId, size_t screenId, SST_VideoMode* modesReturn, size_t* modeCountReturn)
{
	/* TODO: Implement */

}

/******************************************************************************/

void SST_WM_GetEnumCurrentVideoMode(SST_GraphicsEnumerator enumerator, size_t adapterId, size_t screenId, SST_VideoMode* mode)
{
	/* TODO: Implement */
}

/******************************************************************************/

void SST_WM_DestroyGraphicsEnumerator(SST_GraphicsEnumerator enumerator)
{
	/* TODO: Implement */
	SST_GraphicsEnumerator_MacOSX* enumMac = (SST_GraphicsEnumerator_MacOSX*)enumerator;

	free(enumMac);
}

/******************************************************************************/

