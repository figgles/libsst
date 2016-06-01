/*
	SST_WMWindow_RaspPi.c
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 1/8/2013

	Purpose:

	Window emulation for native Raspberry Pi port

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#include <SST/SST_WMWindow.h>
#include "RaspPiPrivate.h"
#include "EventQueue.h"

#define WINDOW_LAYER 2000

/******************************************************************************/

static void destroyWin(SST_Window_RaspPi* win)
{
	/* Only after an element is removed can the resource under it
	be deleted. */
	if(win->element != 0)
	{
		DISPMANX_UPDATE_HANDLE_T update;

		update = vc_dispmanx_update_start(0);
		vc_dispmanx_element_remove(update, win->element);
		vc_dispmanx_update_submit_sync(update);
	}

	if(win->softwareImage != 0)
		vc_dispmanx_resource_delete(win->softwareImage);

	free(win);
}

/******************************************************************************/

SST_DisplayTarget SST_WM_CreateDisplayTarget(size_t adapterIndex, size_t screenIndexOrMultihead)
{
	SST_DisplayTarget_RaspPi* displayTarget;

	/* > 1 adapters not supported, multihead not supported */
	if(screenIndexOrMultihead != 0 || adapterIndex != 0)
		return NULL;

	displayTarget = (SST_DisplayTarget_RaspPi*)malloc(sizeof(SST_DisplayTarget_RaspPi));
	if(displayTarget == NULL)
		return NULL;

	/* Initialize lock for user events */
	if(pthread_mutex_init(&displayTarget->eventLock, NULL) != 0)
	{
		free(displayTarget);
		return NULL;
	}

	if(InitEQ(&displayTarget->eventQueue) == 0)
	{
		pthread_mutex_destroy(&displayTarget->eventLock);
		free(displayTarget);
		return NULL;
	}

	if(InitEQ(&displayTarget->userEventQueue) == 0)
	{
		DestroyEQ(&displayTarget->eventQueue);	
		pthread_mutex_destroy(&displayTarget->eventLock);
		free(displayTarget);
		return NULL;
	}

	/* Save fields */
	displayTarget->firstWindow = NULL;
	displayTarget->relativeMouse = 0;
	displayTarget->display = vc_dispmanx_display_open(DISPMANX_ID_MAIN_LCD);
	memset(displayTarget->keymapBitvector, 0, sizeof(displayTarget->keymapBitvector));

	return (SST_DisplayTarget)displayTarget;
}

/******************************************************************************/

size_t SST_WM_GetDisplayTargetScreenCount(SST_DisplayTarget target)
{
	(void)target;
	return 1;
}

/******************************************************************************/

SST_Window SST_WM_CreateWindowOnScreen(SST_DisplayTarget target, size_t screenIndex, uint32_t x, uint32_t y, uint32_t width, uint32_t height, const char* title)
{
	SST_Window_RaspPi* win;
	SST_DisplayTarget_RaspPi* displayTarget = (SST_DisplayTarget_RaspPi*)target;
	SST_WMEvent* event;
	DISPMANX_UPDATE_HANDLE_T update;
	VC_DISPMANX_ALPHA_T alpha;
	VC_RECT_T srcRect, dstRect;

	/* Title is not used */
	(void)title;

	/* Must be on screen 0 */
	if(screenIndex != 0)
		return NULL;

	/* Allocate SST window structure */
	win = (SST_Window_RaspPi*)calloc(1, sizeof(SST_Window_RaspPi));
	if(win == NULL)
		return NULL;

	/* link the window */
	displayTarget->firstWindow = win;
	win->next = displayTarget->firstWindow;
	win->owner = displayTarget;
	win->x = x;
	win->y = y;
	win->w = width;
	win->h = height;

	srcRect.x = srcRect.y = 0;
	srcRect.width = width << 16; srcRect.height = height << 16;

	dstRect.x = x; dstRect.y = y;
	dstRect.width = width; dstRect.height = height;

	/* TODO: clip these so they make sense */

	alpha.flags = DISPMANX_FLAGS_ALPHA_FIXED_ALL_PIXELS; 
	alpha.opacity = 0xFF; 
	alpha.mask = 0; 

	update = vc_dispmanx_update_start(0);
	win->element = vc_dispmanx_element_add(update, displayTarget->display,
				WINDOW_LAYER,
				&dstRect,
				0, &srcRect, /* no source data */
				DISPMANX_PROTECTION_NONE, /* no content protection */
				&alpha, NULL,	/* Alpha/clamp/transform parameters */
				VC_IMAGE_ROT0); /* No rotation required */
				
				
	vc_dispmanx_update_submit_sync(update);
	
	/* Add a SSTWMEVENT_CREATED event */
	event = AllocSlotInEQ(&displayTarget->eventQueue);
	if(event != NULL)
	{
		event->window = win;
		event->type = SSTWMEVENT_CREATED;
		memset(&event->details, 0, sizeof(event->details));
	}

	return (SST_Window)win;
}

/******************************************************************************/

SST_DisplayTarget SST_WM_GetWindowDisplayTarget(SST_Window window)
{
	SST_Window_RaspPi* win = (SST_Window_RaspPi*)window;

	return win->owner;
}

/******************************************************************************/

void SST_WM_SetWindowText(SST_Window window, const char* titleBar)
{
	/* There is no way to do this; Ignore. */
	(void)window;
	(void)titleBar;
}
/******************************************************************************/

void SST_WM_GetWindowRect(SST_Window window, SST_Rect* rectReturn)
{
	SST_Window_RaspPi* win = (SST_Window_RaspPi*)window;

	rectReturn->x = win->x;
	rectReturn->y = win->y;
	rectReturn->width = win->w;
	rectReturn->height = win->h;
	return;
}

/******************************************************************************/

void SST_WM_MoveWindowOnScreen(SST_Window window, size_t screenIndex, uint32_t x, uint32_t y)
{
	SST_Window_RaspPi* win = (SST_Window_RaspPi*)window;

	/* Only allow operations on screen 0 */
	if(screenIndex != SST_SAME_SCREEN && screenIndex != 0)
		return;

	/* TODO: verify these coords make any sense */
	win->x = x;
	win->y = y;
	/* TODO: send message */
}

/******************************************************************************/

void SST_WM_ResizeWindow(SST_Window window, uint32_t width, uint32_t height)
{
	SST_Window_RaspPi* win = (SST_Window_RaspPi*)window;
	/* TODO: verify these coords make any sense */
	win->w = width;
	win->h = height;	
	/* TODO: send a message */	
}

/******************************************************************************/

void SST_WM_SetWindowState(SST_Window window, SST_WMWindowState state, uint32_t param)
{
	SST_Window_RaspPi* win = (SST_Window_RaspPi*)window;

	switch(state)
	{
		case SSTWS_SHOWN:
		{
			/* Map or unmap the window respectively */
			if(param == 0)
			{
				/* TODO: hide window */
			}
			else
			{
				/* TODO: show window */
			}

			break;
		}

		/* Turn on/off resizeability */
		case SSTWS_RESIZEABLE:
		{
			/* No-op. */
			break;
		}

		case SSTWS_FULLSCREEN:
		{

			/* Enabling fullscreen? */
			if(param && !win->isFullscreen)
			{
				/* TODO: save old X/Y/W/H */
				win->isFullscreen = 1;
			}
			else if(win->isFullscreen)
			{
				/* TODO: restore old X/Y/W/H */
				win->isFullscreen = 0;
			}

			break;
		}

		case SSTWS_MINIMIZED:
		{
			if(param == 0) /* Maximize */
			{
				/* TODO: maximize? */
			}
			else /* Minimize */
			{
				/* TODO: minimize? */
			}
			break;
		}

		default: break;
	}
}

/******************************************************************************/

void SST_WM_SetDisplayTargetState(SST_DisplayTarget target, SST_WMDisplayTargetState state, uint32_t param)
{
	SST_DisplayTarget_RaspPi* displayTarget = (SST_DisplayTarget_RaspPi*)target;

	switch(state)
	{
		case SSTDTS_RELMOUSE:
		{
			/* Disabling? */
			if(displayTarget->relativeMouse && param == 0)
			{
				/* TODO */
			}
			else if(!displayTarget->relativeMouse && param != 0) /* Enabling? */
			{
				/* TODO */
			}

			break;
		}
	}
}

/******************************************************************************/

void SST_WM_DestroyWindow(SST_Window window)
{
	SST_DisplayTarget_RaspPi* displayTarget;
	SST_Window_RaspPi* win = (SST_Window_RaspPi*)window;
	SST_Window_RaspPi* nextWin;

	displayTarget = win->owner;
	nextWin = displayTarget->firstWindow;

	/* Special case: root window */
	if(nextWin == win)
	{
		/* Set new root to be this->next */
		displayTarget->firstWindow = win->next;
	}
	else
	{
		int found = 0;

		/* Check list */
		while(nextWin)
		{
			/* Did we find the window? */
			if(nextWin->next == win)
			{
				/* Remove this window from the linked list */
				nextWin->next = win->next;
				found = 1;
				break;
			}
			else
				nextWin = nextWin->next;
		}

		/* Don't destroy another display target's window */
		if(!found)
			return;

	}

	/* Actually destroy the window window */
	destroyWin(win);
}

/******************************************************************************/

void SST_WM_DestroyDisplayTarget(SST_DisplayTarget target)
{
	SST_DisplayTarget_RaspPi* displayTarget = (SST_DisplayTarget_RaspPi*)target;
	SST_Window_RaspPi* window = displayTarget->firstWindow;

	/* Destroy window */
	while(window)
	{
		SST_Window_RaspPi* next = window->next;
		destroyWin(window);
		window = next;
	}
		
	/* Delete any events */
	DestroyEQ(&displayTarget->eventQueue);
	DestroyEQ(&displayTarget->userEventQueue);
	pthread_mutex_destroy(&displayTarget->eventLock);

	vc_dispmanx_display_close(displayTarget->display);

	/* Free structure */
	free(displayTarget);

}

/******************************************************************************/


