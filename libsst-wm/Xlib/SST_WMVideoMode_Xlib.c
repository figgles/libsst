/*
	SST_WMVideoMode_Xlib.c
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 1/8/2013

	Purpose:

	Video mode setting functions (Xlib)

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#include "XlibPrivate.h"
#include "APIPrivate.h"
/*
	Right now, these are essentially no-ops. Later, some real mechanism needs to be used:

	1) [Preferred] XRandR extension
	2) XF86VideoMode extension

	That will get good and messy then. In particular, if a set of headers isn't available for the platform,
	then it basically won't compile. Seems like I need to re-write a few definitions in-line, and of course,
	link dynamically and do proper version queries (*.so doesn't mean server actually supports it).
*/

/******************************************************************************/

static int Xlib_SetVideoModeOnScreen(SST_DisplayTarget target, size_t screenIndex, const SST_VideoMode* vmode)
{
	SST_DisplayTarget_Xlib* displayTarget = (SST_DisplayTarget_Xlib*)target;
	Display* display = displayTarget->display;
	int xscreen;

	/* Must be screen 0 */
	if(screenIndex != 0)
		return 0;

	xscreen = DefaultScreen(display);

	/* Since we aren't changing the display mode, just verify it matches */
	if(vmode->bpp != (uint32_t)DefaultDepth(display, xscreen) ||
		vmode->width != (uint32_t)DisplayWidth(display, xscreen) ||
		vmode->height != (uint32_t)DisplayHeight(display, xscreen) ||
		vmode->refreshRate != 0)
	{
		return 0;
	}

	return 1;
}

/******************************************************************************/

static int Xlib_GetVideoModeOnScreen(SST_DisplayTarget target, size_t screenIndex, SST_VideoMode* vmodeReturn)
{
	SST_DisplayTarget_Xlib* displayTarget = (SST_DisplayTarget_Xlib*)target;
	Display* display = displayTarget->display;
	int xscreen;

	/* Must be screen 0 */
	if(screenIndex != 0)
		return 0;

	xscreen = DefaultScreen(display);
	vmodeReturn->bpp = (uint32_t)DefaultDepth(display, xscreen);
	vmodeReturn->width = (uint32_t)DisplayWidth(display, xscreen);
	vmodeReturn->height = (uint32_t)DisplayHeight(display, xscreen);
	vmodeReturn->refreshRate = 0;

	return 1;
}

/******************************************************************************/

const struct SST_WM_VideoModeFuncs Xlib_VideoModeFuncs = {
	Xlib_SetVideoModeOnScreen,
	Xlib_GetVideoModeOnScreen
};

