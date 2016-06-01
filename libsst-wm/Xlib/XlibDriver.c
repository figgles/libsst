/*
	XlibDriver.c
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 5/14/2014

	Purpose:

	Xlib driver for libsst-wm

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#include "APIPrivate.h"
#include "XlibPrivate.h"
#include "XI2Private.h"
#include "GLXPrivate.h"

extern const struct SST_WM_WindowFuncs Xlib_WindowFuncs;
extern const struct SST_WM_EnumFuncs Xlib_EnumFuncs;
extern const struct SST_WM_EventFuncs Xlib_EventFuncs;
extern const struct SST_WM_OpenGLFuncs Xlib_OpenGLFuncs;
extern const struct SST_WM_RenderFuncs Xlib_RenderFuncs;
extern const struct SST_WM_VideoModeFuncs Xlib_VideoModeFuncs;

/******************************************************************************/

int Xlib_init()
{
	if(getenv("LIBSST_NO_XLIB"))
		return 0;
	
	if(loadXlib() == 0)
		return 0;

	#ifdef HAVE_XINPUT2
	XI2_Load(); /* may fail, but that's OK */
	#endif


	loadGLX();
	return 1;
}

/******************************************************************************/

void Xlib_shutdown()
{
	#ifdef HAVE_XINPUT2
	XI2_Unload();
	#endif

	unloadGLX();
	
	unloadXlib();
}

/******************************************************************************/

const struct SST_WM_Driver XlibDriver = {
	"Xlib Driver",
	Xlib_init,
	Xlib_shutdown,
	&Xlib_WindowFuncs,
	&Xlib_EnumFuncs,
	&Xlib_EventFuncs,
	&Xlib_OpenGLFuncs,
	&Xlib_RenderFuncs,
	&Xlib_VideoModeFuncs
};
