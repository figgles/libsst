/*
	SST_WMRender_RaspPi.c
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 6/25/2013

	Purpose:

	Software rendering support for Raspberry Pi 

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#include "RaspPiPrivate.h"
#include <SST/SST_WMWindow.h>

#define ROUNDUP(val, power) ((val + (power)-1) & ~((power)-1))

/******************************************************************************/

int SST_WM_EnableSoftwareRendering(SST_Window window)
{
	SST_Window_RaspPi* win = (SST_Window_RaspPi*)window;
	DISPMANX_UPDATE_HANDLE_T update;

	/* Each pixel is 4 bytes.  */
	uint32_t pitch = win->w * sizeof(uint32_t);
	uint32_t dummy;

	/* Pitch must be a multiple of 32 bytes, so round up */
	pitch = ROUNDUP(pitch, 32);

	/* TODO: what does vc_dispmanx_resource_create() return on error? */
	/* Last parameter "dummy" is always set to zero according to source code, must be from other videocore versions */
	win->softwareImage = vc_dispmanx_resource_create(VC_IMAGE_ARGB8888, win->w, win->h, &dummy);
	win->softwareBackbuffer = calloc(win->h, pitch);
	win->softwarePitch = pitch;

	/* TODO: wtf, why << 16 */
	vc_dispmanx_rect_set(&win->softwareRect, 0, 0, win->w << 16, win->h << 16 );

	if(win->softwareBackbuffer == NULL)
		return 0;

	/* Update dispmanx to bind the new image to the */
	update = vc_dispmanx_update_start(0);
	vc_dispmanx_element_change_source(update, win->element, win->softwareImage);
	vc_dispmanx_update_submit_sync(update);

	return 1;
}

/******************************************************************************/

void SST_WM_DisableSoftwareRendering(SST_Window window)
{
	SST_Window_RaspPi* win = (SST_Window_RaspPi*)window;
	DISPMANX_UPDATE_HANDLE_T update;

	/* Update dispmanx; remove the resource from the window element */
	update = vc_dispmanx_update_start(0);

	vc_dispmanx_element_change_source(update, win->element, 0);

	vc_dispmanx_update_submit_sync(update);

	/* Now we can delete the resource */
	if(win->softwareImage != 0)
	{
		vc_dispmanx_resource_delete(win->softwareImage);
		win->softwareImage = 0;
	}

	if(win->softwareBackbuffer)
	{
		free(win->softwareBackbuffer);
		win->softwareBackbuffer = NULL;
	}
}

/******************************************************************************/

void* SST_WM_LockBackbuffer(SST_Window window, size_t* pitchReturn)
{
	SST_Window_RaspPi* win = (SST_Window_RaspPi*)window;

	*pitchReturn = win->softwarePitch;

	return win->softwareBackbuffer;
}

/******************************************************************************/

void SST_WM_UnlockBackbuffer(SST_Window window)
{
	SST_Window_RaspPi* win = (SST_Window_RaspPi*)window;
	VC_RECT_T blit;

	blit.x = blit.y = 0;
	blit.width = win->w;
	blit.height = win->h;

	/* Push the pixels to the resource */
	vc_dispmanx_resource_write_data(win->softwareImage, VC_IMAGE_ARGB8888, win->softwarePitch, win->softwareBackbuffer, &blit);

}

