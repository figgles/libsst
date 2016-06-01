/*
	SST_WMVideoMode_Win32.c
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 6/26/2012

	Purpose: 

	Video mode setting functions

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#include "Win32Private.h"
#include "../APIPrivate.h"

/*************************************************************************/

static int Win32_SetVideoModeOnScreen(SST_DisplayTarget target, size_t screenIndex, const SST_VideoMode* vmode)
{
	DEVMODEA devMode;
	SST_DisplayTarget_Win32* displayTarget = (SST_DisplayTarget_Win32*)target;
	const DISPLAY_DEVICEA* dev = &displayTarget->devs[screenIndex];

	memset(&devMode, 0, sizeof(devMode));
	devMode.dmSize = sizeof(devMode);
	devMode.dmBitsPerPel = vmode->bpp;
	devMode.dmPelsWidth = vmode->width;
	devMode.dmPelsHeight = vmode->height;
	devMode.dmDisplayFrequency = vmode->refreshRate;
	devMode.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;

	return (ChangeDisplaySettingsExA(dev->DeviceName, &devMode, NULL, CDS_FULLSCREEN, NULL) == DISP_CHANGE_SUCCESSFUL);
}

/*************************************************************************/

static int Win32_GetVideoModeOnScreen(SST_DisplayTarget target, size_t screenIndex, SST_VideoMode* vmodeReturn)
{
	SST_DisplayTarget_Win32* displayTarget = (SST_DisplayTarget_Win32*)target;
	const DISPLAY_DEVICEA* dev = &displayTarget->devs[screenIndex];
	DEVMODEA devMode;
	int ok = 0;

	devMode.dmSize = sizeof(devMode);

	if(EnumDisplaySettingsA(dev->DeviceName, ENUM_CURRENT_SETTINGS, &devMode))
	{
		vmodeReturn->bpp = devMode.dmBitsPerPel;
		vmodeReturn->width = devMode.dmPelsWidth;
		vmodeReturn->height = devMode.dmPelsHeight;
		vmodeReturn->refreshRate = devMode.dmDisplayFrequency;

		if(vmodeReturn->refreshRate == 1)
			vmodeReturn->refreshRate = SST_DEFAULT_REFRESHRATE;

		ok = 1;
	}

	return ok;
}

const struct SST_WM_VideoModeFuncs Win32_VideoModeFuncs = {
	Win32_SetVideoModeOnScreen,
	Win32_GetVideoModeOnScreen
};
