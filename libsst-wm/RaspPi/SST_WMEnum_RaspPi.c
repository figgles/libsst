/*
	SST_WMEnum_RaspPi.c
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 5/31/2013

	Purpose: 

	Raspberry Pi native (no display server) port for Linux
	
	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#include <SST/SST_WM.h>

#include <bcm_host.h>	/* R-Pi header */

#include <string.h> /* strlen() etc. */
#include <stdlib.h> 

/******************************************************************************/

SST_GraphicsEnumerator SST_WM_CreateGraphicsEnumerator(void)
{
	/* Call this just in case. Multiple calls do not affect anything */
	bcm_host_init();

	return (void*)(uintptr_t)(0x40000000);	/* No, it is meaningless */
}

/******************************************************************************/

size_t SST_WM_GetEnumAdapterCount(SST_GraphicsEnumerator enumerator)
{
	(void)enumerator;

	/* R-Pi only has the one on-chip device */
	return 1;
}

/******************************************************************************/

void SST_WM_GetEnumAdapterName(SST_GraphicsEnumerator enumerator, size_t adapterId, char* nameReturn, size_t* bufferSize)
{
	size_t len;
	const char* name = "VideoCore IV (R) GPU"; 

	(void)enumerator;
	(void)adapterId;

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

/******************************************************************************/

size_t SST_WM_GetEnumScreenCount(SST_GraphicsEnumerator enumerator, size_t adapterId)
{
	(void)enumerator;
	(void)adapterId;
	return 1;
}

/******************************************************************************/

void SST_WM_GetEnumVideoModes(SST_GraphicsEnumerator enumerator, size_t adapterId, size_t screenId, SST_VideoMode* modesReturn, size_t* modeCountReturn)
{
	(void)enumerator;

	/* Only one adapter/screen supported */
	if(adapterId != 0 || screenId != 0)
		return;
	
	if(modesReturn == NULL)
		*modeCountReturn = 1;
	else
	{
		/* TODO: there might be a way to do this, but it
		is very manual. Just return current resolution. */
		uint32_t w, h;

		graphics_get_display_size(0, &w, &h);
	
		modesReturn[0].bpp = 16; /* TODO: not always 16 */
		modesReturn[0].width = w;
		modesReturn[0].height = h;
		modesReturn[0].refreshRate = 0;
	}

}

/******************************************************************************/

void SST_WM_GetEnumCurrentVideoMode(SST_GraphicsEnumerator enumerator, size_t adapterId, size_t screenId, SST_VideoMode* mode)
{
	uint32_t w, h;
	(void)enumerator;

	if(adapterId != 0 || screenId != 0)
		return;

	/* TODO: does this reflect changes made with fbset? */
	graphics_get_display_size(0, &w, &h);

	mode->bpp = 16;
	mode->width = w;
	mode->height = h;
	mode->refreshRate = 0;
}

/******************************************************************************/

void SST_WM_DestroyGraphicsEnumerator(SST_GraphicsEnumerator enumerator)
{
	(void)enumerator;
}
