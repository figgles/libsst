/*
	SST_WMEnum_Xlib.c
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 1/8/2013

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

#include "XlibPrivate.h"
#include "APIPrivate.h"
#include <string.h> /* strlen() etc. */
#include <stdlib.h> 

/******************************************************************************/

static SST_GraphicsEnumerator Xlib_CreateGraphicsEnumerator(void)
{
	Display* display;
	SST_GraphicsEnumerator_Xlib* enumerator;

	enumerator = (SST_GraphicsEnumerator_Xlib*)malloc(sizeof(SST_GraphicsEnumerator_Xlib));

	if(enumerator == NULL)
		return NULL;

	/* Open the display */
	display = X.OpenDisplay(NULL);
	if(display == NULL)
	{
		free(enumerator);
		return NULL;
	}

	/* Save and return */
	enumerator->bpp = (uint32_t)DefaultDepth(display, DefaultScreen(display));
	enumerator->width = (uint32_t)DisplayWidth(display, DefaultScreen(display));
	enumerator->height = (uint32_t)DisplayHeight(display, DefaultScreen(display));

	/* Done with display */
	X.CloseDisplay(display);

	return enumerator;
}

/******************************************************************************/

static size_t Xlib_GetEnumAdapterCount(SST_GraphicsEnumerator enumerator)
{
	(void)enumerator;

	/* Only support 1 adapter */
	return 1;
}

/******************************************************************************/

static void Xlib_GetEnumAdapterName(SST_GraphicsEnumerator enumerator, size_t adapterId, char* nameReturn, size_t* bufferSize)
{
	size_t len;
	const char* name = "X Display Device"; 

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

static size_t Xlib_GetEnumScreenCount(SST_GraphicsEnumerator enumerator, size_t adapterId)
{
	(void)enumerator;
	(void)adapterId;
	return 1;
}

/******************************************************************************/

static void Xlib_GetEnumVideoModes(SST_GraphicsEnumerator enumerator, size_t adapterId, size_t screenId, SST_VideoMode* modesReturn, size_t* modeCountReturn)
{
	SST_GraphicsEnumerator_Xlib* enumXlib = (SST_GraphicsEnumerator_Xlib*)enumerator;

	/* Only one adapter/screen supported */
	if(adapterId != 0 || screenId != 0)
		return;
	
	if(modesReturn == NULL)
		*modeCountReturn = 1;
	else
	{
		modesReturn[0].bpp = enumXlib->bpp;
		modesReturn[0].width = enumXlib->width;
		modesReturn[0].height = enumXlib->height;
		modesReturn[0].refreshRate = 0;
	}

}

/******************************************************************************/

void Xlib_GetEnumCurrentVideoMode(SST_GraphicsEnumerator enumerator, size_t adapterId, size_t screenId, SST_VideoMode* mode)
{
	SST_GraphicsEnumerator_Xlib* enumXlib = (SST_GraphicsEnumerator_Xlib*)enumerator;
	if(adapterId != 0 || screenId != 0)
		return;

	mode->bpp = enumXlib->bpp;
	mode->width = enumXlib->width;
	mode->height = enumXlib->height;
	mode->refreshRate = 0;
}

/******************************************************************************/

static void Xlib_DestroyGraphicsEnumerator(SST_GraphicsEnumerator enumerator)
{
	free(enumerator);
}

/******************************************************************************/
struct SST_WM_EnumFuncs Xlib_EnumFuncs = {
	Xlib_CreateGraphicsEnumerator,
	Xlib_GetEnumAdapterCount,
	Xlib_GetEnumAdapterName,
	Xlib_GetEnumScreenCount,
	Xlib_GetEnumVideoModes,
	Xlib_GetEnumCurrentVideoMode,
	Xlib_DestroyGraphicsEnumerator
};

