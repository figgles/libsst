/*
	XlibPrivate.c
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 1/8/2013

	Purpose:

	Private defintions and functions for Xlib implementation of libsst-wm

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#include "XlibPrivate.h"
#include <dlfcn.h>

XlibFunctions X;

/******************************************************************************/

int loadXlib()
{
	const int flags = RTLD_LAZY | RTLD_GLOBAL;
	void* xlib;

	X.xlib = NULL;
    
	/* Try opening the correct SONAME version of libX11 */
	xlib = dlopen("libX11.so.6", flags);

	/* Didn't work? */
	if(xlib == NULL)
	{
		/* Try a super-generic version */
		xlib = dlopen("libX11.so", flags);
		if(xlib == NULL)
			return 0;

	}

	/* Resolve symbols */
	X.OpenDisplay = dlsym(xlib, "XOpenDisplay");
	X.CloseDisplay = dlsym(xlib, "XCloseDisplay");
	X.MoveWindow = dlsym(xlib, "XMoveWindow");
	X.ResizeWindow = dlsym(xlib, "XResizeWindow");
	X.MapRaised = dlsym(xlib, "XMapRaised");
	X.MapWindow = dlsym(xlib, "XMapWindow");
	X.UnmapWindow = dlsym(xlib, "XUnmapWindow");
	X.StoreName = dlsym(xlib, "XStoreName");
	X.DestroyWindow = dlsym(xlib, "XDestroyWindow");
	X.CreateSimpleWindow = dlsym(xlib, "XCreateSimpleWindow");
	X.GetGeometry = dlsym(xlib, "XGetGeometry");
	X.GetWindowProperty = dlsym(xlib,"XGetWindowProperty");
	X.Pending = dlsym(xlib, "XPending");
	X.NextEvent = dlsym(xlib, "XNextEvent");
	X.PeekEvent = dlsym(xlib, "XPeekEvent");
	X.SendEvent = dlsym(xlib, "XSendEvent");
	X.Flush = dlsym(xlib, "XFlush");
	X.Sync = dlsym(xlib, "XSync");
	X.InternAtom = dlsym(xlib, "XInternAtom");
	X.SetWMProtocols = dlsym(xlib, "XSetWMProtocols");
	X.IconifyWindow = dlsym(xlib, "XIconifyWindow");
	X.Free = dlsym(xlib, "XFree");
	X.SelectInput = dlsym(xlib, "XSelectInput");
	X.LookupString = dlsym(xlib, "XLookupString");
	X.QueryKeymap = dlsym(xlib, "XQueryKeymap");
	X.QueryExtension = dlsym(xlib, "XQueryExtension");
	X.GetEventData = dlsym(xlib, "XGetEventData");
	X.FreeEventData = dlsym(xlib, "XFreeEventData");


	/* Save handle */
	X.xlib = xlib;

	return 1;
}

/******************************************************************************/

void unloadXlib()
{
	if(X.xlib != NULL)
		dlclose(X.xlib);
}

