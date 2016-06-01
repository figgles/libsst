/*
	SST_WMRender_Xlib.c
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 1/8/2013

	Purpose:

	Software rendering support

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#include "XlibPrivate.h"
#include <SST/SST_WMWindow.h>
#include "APIPrivate.h"

/******************************************************************************/

int Xlib_EnableSoftwareRendering(SST_Window window)
{
	SST_Window_Xlib* win = (SST_Window_Xlib*)window;

	/* TODO: Use XPutImage or XShm extension */
	(void)win;

	return 0;
}

/******************************************************************************/

void Xlib_DisableSoftwareRendering(SST_Window window)
{
	SST_Window_Xlib* win = (SST_Window_Xlib*)window;

	/* TODO */
	(void)win;
}

/******************************************************************************/

void* Xlib_LockBackbuffer(SST_Window window, size_t* pitchReturn)
{
	SST_Window_Xlib* win = (SST_Window_Xlib*)window;

	*pitchReturn = win->softwarePitch;

	return win->softwareBackbuffer;
}

/******************************************************************************/

void Xlib_UnlockBackbuffer(SST_Window window)
{
	SST_Window_Xlib* win = (SST_Window_Xlib*)window;

	/* TODO: invalidate window rect and repaint */
	(void)win;
}

/******************************************************************************/

struct SST_WM_RenderFuncs Xlib_RenderFuncs = {
	Xlib_EnableSoftwareRendering,
	Xlib_DisableSoftwareRendering,
	Xlib_LockBackbuffer,
	Xlib_UnlockBackbuffer
};

