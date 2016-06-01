/*
	SST_WMWindow_Xlib.c
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 1/8/2013

	Purpose:

	Window creation (Xlib)

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#include <SST/SST_WMWindow.h>
#include "XlibPrivate.h"
#include "XI2Private.h"
#include "EventQueue.h"
#include "APIPrivate.h"
#include <stdio.h>

static void destroyWin(SST_Window_Xlib* win);

/* Extended Window Manager Hints (http://standards.freedesktop.org/wm-spec/wm-spec-latest.html) */
static int ewmh_supported(SST_DisplayTarget_Xlib* displayTarget, SST_Window_Xlib* win);
static void ewmh_setFullscreen(SST_Window_Xlib* win, int fullscreen);

/******************************************************************************/

static SST_DisplayTarget Xlib_CreateDisplayTarget(size_t adapterIndex, size_t screenIndexOrMultihead)
{
	SST_DisplayTarget_Xlib* displayTarget;
	#ifdef HAVE_XINPUT2
	XI2Functions XI;
	#endif
	Display* display;

	/* > 1 adapters not supported, multihead not supported */
	if(screenIndexOrMultihead != 0 || adapterIndex != 0)
		return NULL;

	/* Open the X display */
	display = X.OpenDisplay(NULL);
	if(display == NULL)
		return NULL;

	/* If we can open a display, then we're connected to the X server,
	so that is good enough. */

	/* Allocate a display target structure */
	displayTarget = (SST_DisplayTarget_Xlib*)malloc(sizeof(SST_DisplayTarget_Xlib));
	if(displayTarget == NULL)
	{
		X.CloseDisplay(display);
		return NULL;
	}

	/* Initialize lock for user events */
	if(pthread_mutex_init(&displayTarget->eventLock, NULL) != 0)
	{
		X.CloseDisplay(display);
		free(displayTarget);
		return NULL;
	}

	if(InitEQ(&displayTarget->eventQueue) == 0)
	{
		pthread_mutex_destroy(&displayTarget->eventLock);
		X.CloseDisplay(display);
		free(displayTarget);
		return NULL;
	}
	
	if(InitEQ(&displayTarget->userEventQueue) == 0)
	{
		DestroyEQ(&displayTarget->eventQueue);
		pthread_mutex_destroy(&displayTarget->eventLock);
		X.CloseDisplay(display);
		free(displayTarget);
		return NULL;
	}
	

	/* Save fields */
	displayTarget->display = display;
	displayTarget->firstWindow = NULL;
	displayTarget->relativeMouse = 0;
	displayTarget->ewmhSupport = -1;
	displayTarget->atomWmProtocols = X.InternAtom(display, "WM_PROTOCOLS", True);
	displayTarget->atomWmDeleteWindow = X.InternAtom(display, "WM_DELETE_WINDOW", False);
	memset(displayTarget->keymapBitvector, 0, sizeof(displayTarget->keymapBitvector));

	/* XInput2: Verify that server supports XI2 (sets */
	#ifdef HAVE_XINPUT2
	if(XI2_IsLoaded())
		XI2_IsSupportedOnConnection(displayTarget);
	#endif

	return (SST_DisplayTarget)displayTarget;
}

/******************************************************************************/

static size_t Xlib_GetDisplayTargetScreenCount(SST_DisplayTarget target)
{
	(void)target;
	return 1;
}

/******************************************************************************/

static SST_Window Xlib_CreateWindowOnScreen(SST_DisplayTarget target, size_t screenIndex, uint32_t x, uint32_t y, uint32_t width, uint32_t height, const char* title)
{
	SST_Window_Xlib* win;
	SST_DisplayTarget_Xlib* displayTarget = (SST_DisplayTarget_Xlib*)target;
	Window xwin;
	Display* display = displayTarget->display;
	int screen = DefaultScreen(display);
	SST_WMEvent* event;

	/* Must be on screen 0 */
	if(screenIndex != 0)
		return 0;

	xwin = X.CreateSimpleWindow(display,
			RootWindow(display, screen),
			(int)x, (int)y,
			(int)width, (int)height,
			0, 0, /* border width/color */
			WhitePixel(display, screen)); /* background color */

	/* Set window's WM_PROTOCOLS property */
	X.SetWMProtocols(display, xwin, &displayTarget->atomWmDeleteWindow, 1);

	/* Set title bar text */
	X.StoreName(display, xwin, title);

	/* Map the window to the screen */
	X.MapRaised(display, xwin);

	/* Force the move, because some window managers just put windows wherever. Argh. */
	X.MoveWindow(display, xwin, (int)x, (int)y);

	X.SelectInput(display, xwin, KeyPressMask| KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask | ExposureMask | StructureNotifyMask);

	/* Display it now */
	X.Flush(display);

	/* Allocate SST window structure */
	win = (SST_Window_Xlib*)malloc(sizeof(SST_Window_Xlib));
	if(win == NULL)
		return NULL;

	win->owner = displayTarget;
	win->next = displayTarget->firstWindow;
	win->xwin = xwin;
	win->lastX = (uint32_t)x;
	win->lastY = (uint32_t)y;
	win->lastWidth = (uint32_t)width;
	win->lastHeight = (uint32_t)height;
	win->isFullscreen = 0;
	win->softwareBackbuffer = NULL;
	win->softwareImage = NULL;
	win->softwarePitch = 0;

	/* Link window as new root */
	displayTarget->firstWindow = win;

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

static SST_DisplayTarget Xlib_GetWindowDisplayTarget(SST_Window window)
{
	SST_Window_Xlib* win = (SST_Window_Xlib*)window;

	return win->owner;
}

/******************************************************************************/

static void Xlib_SetWindowText(SST_Window window, const char* titleBar)
{
	SST_Window_Xlib* win = (SST_Window_Xlib*)window;

	X.StoreName(win->owner->display, win->xwin, titleBar);
}

/******************************************************************************/

static void Xlib_GetWindowRect(SST_Window window, SST_Rect* rectReturn)
{
	SST_Window_Xlib* win = (SST_Window_Xlib*)window;
	Window dummyRoot;
	int x, y;
	unsigned int w, h;
	unsigned int dummy1, dummy2;

	X.GetGeometry(win->owner->display, win->xwin, &dummyRoot, &x, &y, &w, &h, &dummy1, &dummy2);

	rectReturn->x = (uint32_t)x;
	rectReturn->y = (uint32_t)y;
	rectReturn->width = (uint32_t)w;
	rectReturn->height = (uint32_t)h;
	return;
}

/******************************************************************************/

static void Xlib_MoveWindowOnScreen(SST_Window window, size_t screenIndex, uint32_t x, uint32_t y)
{
	SST_Window_Xlib* win = (SST_Window_Xlib*)window;

	/* Only allow operations on screen 0 */
	if(screenIndex != SST_SAME_SCREEN && screenIndex != 0)
		return;

	X.MoveWindow(win->owner->display, win->xwin, (int)x, (int)y);
	X.Sync(win->owner->display, False);
}

/******************************************************************************/

static void Xlib_ResizeWindow(SST_Window window, uint32_t width, uint32_t height)
{
	SST_Window_Xlib* win = (SST_Window_Xlib*)window;

	X.ResizeWindow(win->owner->display, win->xwin, width, height);
	X.Sync(win->owner->display, False);
}

/******************************************************************************/

static void Xlib_SetWindowState(SST_Window window, SST_WMWindowState state, uint32_t param)
{
	SST_Window_Xlib* win = (SST_Window_Xlib*)window;
	Display* display = win->owner->display;

	switch(state)
	{
		case SSTWS_SHOWN:
		{
			/* Map or unmap the window respectively */
			if(param == 0)
				X.UnmapWindow(display, win->xwin);
			else
				X.MapWindow(display, win->xwin);

			break;
		}

		/* Turn on/off resizeability */
		case SSTWS_RESIZEABLE:
		{
			/* TODO */
			break;
		}

		case SSTWS_FULLSCREEN:
		{
			/* If we haven't yet checked for EWMH support, do so now */
			if(win->owner->ewmhSupport == -1)
				win->owner->ewmhSupport = ewmh_supported(win->owner, win);

			/* Enabling fullscreen? */
			if(param && !win->isFullscreen)
			{

				/* Use EWMH */
				if(win->owner->ewmhSupport != 0)
					ewmh_setFullscreen(win, 1);

				win->isFullscreen = True;
			}
			else if(win->isFullscreen) /* Disabling fullscreen */
			{
				win->isFullscreen = False;

				if(win->owner->ewmhSupport != 0)
					ewmh_setFullscreen(win, 0);
			}

			break;
		}

		case SSTWS_MINIMIZED:
		{
			if(param == 0) /* Maximize */
				X.MapRaised(display, win->xwin);
			else /* Minimize */
				X.IconifyWindow(display, win->xwin, DefaultScreen(display));
			break;
		}

		default: break;
	}
}

/******************************************************************************/

static void Xlib_SetDisplayTargetState(SST_DisplayTarget target, SST_WMDisplayTargetState state, uint32_t param)
{
	SST_DisplayTarget_Xlib* displayTarget = (SST_DisplayTarget_Xlib*)target;
	switch(state)
	{
		case SSTDTS_RELMOUSE:
		{
			#ifdef HAVE_XINPUT2
			XIEventMask eventmask;
			uint8_t maskBytes[3];
				
			memset(maskBytes, 0, sizeof(maskBytes));

			eventmask.deviceid = XIAllMasterDevices;
			eventmask.mask_len = sizeof(maskBytes);
			eventmask.mask = maskBytes;

			if(!displayTarget->xi2Support)
			{
				printf("libsst-wm: XInput2 not supported; cannot use relative mouse mode.\n");
				return;
			}

			/* Disabling? */
			if(displayTarget->relativeMouse && param == 0)
			{
				displayTarget->relativeMouse = 0;
			}
			else if(!displayTarget->relativeMouse && param != 0) /* Enabling? */
			{
				printf("libsst-wm: enabling XI2 raw motion\n");
				XISetMask(maskBytes, XI_RawMotion); /* Macro invocation */
				displayTarget->relativeMouse = 1;
			}
			
			if(XI.SelectEvents(displayTarget->display, DefaultRootWindow(displayTarget->display), &eventmask, 1) == Success)
				printf("libsst-wm: relative mouse is %s!\n", param?"ON":"OFF");
			else
				printf("libsst-wm: failed to change relative mouse mode - XISelectEvents() returned failure\n");
			
			#else
			printf("libsst-wm: XI2 not compiled in, cannot use relative mouse mode.");
			#endif
			break;
		}
	}
}

/******************************************************************************/

static void Xlib_DestroyWindow(SST_Window window)
{
	SST_DisplayTarget_Xlib* displayTarget;
	SST_Window_Xlib* win = (SST_Window_Xlib*)window;
	SST_Window_Xlib* nextWin;

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

static void Xlib_DestroyDisplayTarget(SST_DisplayTarget target)
{
	SST_DisplayTarget_Xlib* displayTarget = (SST_DisplayTarget_Xlib*)target;
	SST_Window_Xlib* window = displayTarget->firstWindow;

	/* Destroy all windows */
	while(window)
	{
		/* Save the next window */
		SST_Window_Xlib* next = window->next;

		destroyWin(window);

		/* Move to next window */
		window = next;
	}

	DestroyEQ(&displayTarget->userEventQueue);
	DestroyEQ(&displayTarget->eventQueue);
	pthread_mutex_destroy(&displayTarget->eventLock);
	X.CloseDisplay(displayTarget->display);

	/* Free structures */
	free(displayTarget);

}

/******************************************************************************/

static void destroyWin(SST_Window_Xlib* win)
{
	/* TODO Destroy more */

	X.DestroyWindow(win->owner->display, win->xwin);
	free(win);
}

/******************************************************************************/

/* Check if extended window manager hints are supported */
static int ewmh_supported(SST_DisplayTarget_Xlib* displayTarget, SST_Window_Xlib* win)
{
	Atom actions;
	Atom actionFullscreen;
	Atom actualType;
	int format;
	unsigned long nrItems;
	unsigned long bytesAfterReturn;
	unsigned long i;
	Atom* propReturn;
	int foundit = 0;
	Display* display = displayTarget->display;

	actions = X.InternAtom(display, "_NET_WM_ALLOWED_ACTIONS", False);
	actionFullscreen = X.InternAtom(display, "_NET_WM_ACTION_FULLSCREEN", False);

	/* Get a list of atoms */
	if(X.GetWindowProperty(display, win->xwin, actions, 0, 1024, False, XA_ATOM, &actualType,
					&format,
					&nrItems,
					&bytesAfterReturn,
					(unsigned char**)&propReturn) != Success)
	{
		/* Nope */
		return 0;
	}

	/* Search through the list for the atom that matches the fullscreen atom */
	for(i=0; i<nrItems; i++)
	{
		if(propReturn[i] == actionFullscreen)
		{
			foundit = 1;
			break;
		}
	}

	/* Free atom list and return */
	X.Free(propReturn);

	return foundit;
}

/******************************************************************************/

/* Use extended window manager hints to set the window in/out of fullscreen mode */
static void ewmh_setFullscreen(SST_Window_Xlib* win, int fullscreen)
{
	XEvent event;
	Display* display = win->owner->display;

	event.xclient.type = ClientMessage;
	event.xclient.serial = 0;
	event.xclient.send_event = True;
	event.xclient.display = display;
	event.xclient.window = win->xwin;
	event.xclient.message_type = X.InternAtom(display, "_NET_WM_STATE", False);
	event.xclient.format = 32;
	event.xclient.data.l[0] = fullscreen;
	event.xclient.data.l[1] = X.InternAtom(display, "_NET_WM_STATE_FULLSCREEN", False);
	event.xclient.data.l[2] = 0;
	event.xclient.data.l[3] = 0;
	event.xclient.data.l[4] = 0;

	X.SendEvent(display, DefaultRootWindow(display), False, StructureNotifyMask | ResizeRedirectMask, &event);
}

extern int Xlib_ShowDialogBox(SST_DisplayTarget target, SST_Window parent, const char* caption, const char* message, const char** buttons, int nrButtons);

const struct SST_WM_WindowFuncs Xlib_WindowFuncs = {
	Xlib_CreateDisplayTarget,
	Xlib_GetDisplayTargetScreenCount,
	Xlib_CreateWindowOnScreen,
	Xlib_GetWindowDisplayTarget,
	Xlib_SetWindowText,
	Xlib_GetWindowRect,
	Xlib_MoveWindowOnScreen,
	Xlib_ResizeWindow,
	Xlib_ShowDialogBox,
	Xlib_SetWindowState,
	Xlib_SetDisplayTargetState,
	Xlib_DestroyWindow,
	Xlib_DestroyDisplayTarget
};

