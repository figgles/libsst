/*
	SST_WMVideoMode_RaspPi.c
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 6/25/2013

	Purpose:

	Video mode setting functions for the Raspberry Pi

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#include "RaspPiPrivate.h"

/*
	Right now, these are essentially no-ops. The vc_tv_xxx API can be used
	to query and change the video mode
*/

/******************************************************************************/

int SST_WM_SetVideoModeOnScreen(SST_DisplayTarget target, size_t screenIndex, const SST_VideoMode* vmode)
{
	SST_DisplayTarget_RaspPi* displayTarget = (SST_DisplayTarget_RaspPi*)target;

	/* Must be screen 0 */
	if(screenIndex != 0)
		return 0;

	return 1;
}

/******************************************************************************/

int SST_WM_GetVideoModeOnScreen(SST_DisplayTarget target, size_t screenIndex, SST_VideoMode* vmodeReturn)
{
	SST_DisplayTarget_RaspPi* displayTarget = (SST_DisplayTarget_RaspPi*)target;

	/* Must be screen 0 */
	if(screenIndex != 0)
		return 0;

	vmodeReturn->bpp = 16; /* ? The HWS runs at what depth? */
	vmodeReturn->width = 0;
	vmodeReturn->height = 0;
	vmodeReturn->refreshRate = 0;

	return 1;
}
