/*
	XI2Private.h
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 5/13/2013

	Purpose:

	Private definitions and functions for XInput2 portion of Xlib driver. XI2 support
	is optional, but most systems that run a recent version of X will have it.

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/
#ifndef _XI2PRIVATE_H
#define _XI2PRIVATE_H

#ifdef HAVE_XINPUT2

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/extensions/XInput2.h>

/******************************************************************************/

typedef Status (*pf_XISelectEvents)(Display* display, Window win, XIEventMask* masks, int num_masks);
typedef Status (*pf_XIQueryVersion)(Display *display, int *major_version_inout, int *minor_version_inout);

/** Structure describing XInput2 functions used */
typedef struct XI2Functions {
	pf_XISelectEvents SelectEvents;
	pf_XIQueryVersion QueryVersion;    
	void* XI2lib;
} XI2Functions;

extern XI2Functions XI;

struct SST_DisplayTarget_Xlib;

/* Attempt to load XInput2 library */
void XI2_Load();

/* Check if XInput2 library was successfully loaded (X server may not support it though) */
int XI2_IsLoaded();

/* Unload XInput2 library */
void XI2_Unload();

/* Check if the connection to the X server supports XInput2. */
void XI2_IsSupportedOnConnection(struct SST_DisplayTarget_Xlib* displayTarget);

#endif

#endif

