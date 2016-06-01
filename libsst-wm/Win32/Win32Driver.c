/*
	Win32Driver.c
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 12/18/2014

	Purpose:
	
 	Windows (Win32 API) driver for libsst-wm


	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/
#include "../APIPrivate.h"
#include "Win32Private.h"

extern const struct SST_WM_WindowFuncs Win32_WindowFuncs;
extern const struct SST_WM_EnumFuncs Win32_EnumFuncs;
extern const struct SST_WM_EventFuncs Win32_EventFuncs;
extern const struct SST_WM_OpenGLFuncs Win32_OpenGLFuncs;
extern const struct SST_WM_RenderFuncs Win32_RenderFuncs;
extern const struct SST_WM_VideoModeFuncs Win32_VideoModeFuncs;


/******************************************************************************/

int Win32_init()
{
	if(getenv("LIBSST_NO_WIN32"))
		return 0;


	return 1;
}

/******************************************************************************/

void Win32_shutdown()
{
	/* Nothing to do (now) */
	return;
}

/******************************************************************************/

const struct SST_WM_Driver Win32Driver = {
	"Win32 Driver",
	Win32_init,
	Win32_shutdown,
	&Win32_WindowFuncs,
	&Win32_EnumFuncs,
	&Win32_EventFuncs,
	&Win32_OpenGLFuncs,
	&Win32_RenderFuncs,
	&Win32_VideoModeFuncs
};
