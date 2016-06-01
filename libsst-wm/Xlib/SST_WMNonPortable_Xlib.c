/*
	SST_WMNonPortable_Xlib.c
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 1/8/2012

	Purpose:

	Non-portable API calls in libsst-wm for the Xlib platform

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#include "XlibPrivate.h"

/******************************************************************************/

Display* SST_WM_GetDisplayX11(SST_Window window)
{
	SST_Window_Xlib* win = (SST_Window_Xlib*)window;

	return win->owner->display;
}

/******************************************************************************/

Window SST_WM_GetWindowX11(SST_Window window)
{
	SST_Window_Xlib* win = (SST_Window_Xlib*)window;

	return win->xwin;
}
