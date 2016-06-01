/*
	XlibPrivate.h
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 1/8/2013

	Purpose:

	

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#pragma once

#ifndef _XLIBPRIVATE_H
#define _XLIBPRIVATE_H

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xproto.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <X11/keysym.h>

#include <pthread.h>

#include <SST/SST_WMTypes.h>
#include "EventQueue.h"
#include "GLXPrivate.h"
#include "XI2Private.h"

#define MIN_BPP 16 /* Minimum BPP for a mode to be considered. Some embedded systems use 16-bit color to save memory, so accept those too. */

/* XGenericEventCookie is required for XI2, but not present on Solaris 10, so fake it*/
#if defined(__sun) && !defined(HAVE_XINPUT2)
typedef void XGenericEventCookie;
#endif

/* Xlib C API */
typedef Display* (*pf_XOpenDisplay)(const char* s);
typedef void (*pf_XCloseDisplay)(Display* dpy);
typedef int (*pf_XMoveWindow)(Display* dpy, Window w, int x, int y);
typedef int (*pf_XResizeWindow)(Display* dpy, Window w, unsigned int x, unsigned int y);
typedef int (*pf_XMapRaised)(Display* dpy, Window w);
typedef int (*pf_XMapWindow)(Display* dpy, Window w);
typedef int (*pf_XUnmapWindow)(Display* dpy, Window w);
typedef int (*pf_XStoreName)(Display* dpy, Window w, const char* windowName);
typedef int (*pf_XDestroyWindow)(Display* dpy, Window w);
typedef Window (*pf_XCreateSimpleWindow)(Display*, Window parent, int x, int y, unsigned int w, unsigned int h, unsigned int borderWidth, unsigned long border, unsigned long background);
typedef Status (*pf_XGetGeometry)(Display* display, Drawable d, Window* root_return, int* x_return, int* y_return, unsigned int* width_return, unsigned int* height_return, unsigned int* border_width_return, unsigned int* depth_return);
typedef int (*pf_XGetWindowProperty)(Display *display, Window w, Atom property, long long_offset, long long_length, Bool _delete, Atom req_type, Atom* actual_type_return, int* actual_format_return, unsigned long* nitems_return, unsigned long* bytes_after_return, unsigned char** prop_return);
typedef int (*pf_XPending)(Display* display);
typedef int (*pf_XNextEvent)(Display* display, XEvent* event_return);
typedef int (*pf_XPeekEvent)(Display* display, XEvent* event_return);
typedef Status (*pf_XSendEvent)(Display *display, Window w, Bool propagate, long event_mask, XEvent *event_send);
typedef int (*pf_XFlush)(Display* display);
typedef int (*pf_XSync)(Display* display, Bool discard);
typedef Atom (*pf_XInternAtom)(Display* display, const char* name, Bool create);
typedef Status (*pf_XSetWMProtocols)(Display* display, Window w, Atom* protocols, int count);
typedef Status (*pf_XIconifyWindow)(Display* display, Window w, int screen_number);
typedef void (*pf_XFree)(void*);
typedef int (*pf_XSelectInput)(Display* display, Window w, long event_mask);
typedef int (*pf_XLookupString)(XKeyEvent* event_struct, char* buffer_return, int bytes_buffer, KeySym* keysym_return, XComposeStatus* status_in_out);
typedef int (*pf_XQueryKeymap)(Display *display, char keys_return[32]);
typedef Bool (*pf_XQueryExtension)(Display* display, const char* name,  int* major_opcode_return, int* first_event_return, int* first_error_return);
typedef Bool (*pf_XGetEventData)(Display *display, XGenericEventCookie *cookie); 
typedef void (*pf_XFreeEventData)(Display *display, XGenericEventCookie *cookie);

/******************************************************************************/

typedef struct XlibFunctions
{
	pf_XOpenDisplay OpenDisplay;
	pf_XCloseDisplay CloseDisplay;
	pf_XMoveWindow MoveWindow;
	pf_XResizeWindow ResizeWindow;
	pf_XMapRaised MapRaised;
	pf_XMapWindow MapWindow;
	pf_XUnmapWindow UnmapWindow;
	pf_XStoreName StoreName;
	pf_XDestroyWindow DestroyWindow;
	pf_XCreateSimpleWindow CreateSimpleWindow;
	pf_XGetGeometry GetGeometry;
	pf_XGetWindowProperty GetWindowProperty;
	pf_XPending Pending;
	pf_XNextEvent NextEvent;
	pf_XPeekEvent PeekEvent;
	pf_XSendEvent SendEvent;
	pf_XFlush Flush;
	pf_XSync Sync;
	pf_XInternAtom InternAtom;
	pf_XSetWMProtocols SetWMProtocols;
	pf_XIconifyWindow IconifyWindow;
	pf_XFree Free;
	pf_XSelectInput SelectInput;
	pf_XLookupString LookupString;
	pf_XQueryKeymap QueryKeymap;
	pf_XQueryExtension QueryExtension;
	pf_XGetEventData GetEventData;
	pf_XFreeEventData FreeEventData;

	void* xlib;
} XlibFunctions;

/******************************************************************************/

typedef struct SST_GraphicsEnumerator_Xlib
{
	uint32_t width;
	uint32_t height;
	uint32_t bpp;
} SST_GraphicsEnumerator_Xlib;

/******************************************************************************/

struct SST_Window_Xlib;

typedef struct SST_DisplayTarget_Xlib
{
	EventQueue eventQueue;
	uint8_t keymapBitvector[32];			/* Bitmap similar to XQueryKeymap() */
	pthread_mutex_t eventLock;				/* Lock protecting user events, since they may be freely added by other threads */
	EventQueue userEventQueue;
	Display* display;
	struct SST_Window_Xlib* firstWindow;
	int relativeMouse;                      /* Is relative mouse move enabled? */
	int ewmhSupport;						/* Extended WM Hints, -1: not checked, 0: not supported, else: supported */
	int xi2Support;                         /* XInput2 support, -1: not checked, 0: not supported, else: supported */
	int xi2opcode;                          /* XI2 opcode */
	Atom atomWmProtocols;
	Atom atomWmDeleteWindow;
} SST_DisplayTarget_Xlib;

/******************************************************************************/

typedef struct SST_Window_Xlib
{
	struct SST_Window_Xlib* next;
	SST_DisplayTarget_Xlib* owner;
	Window xwin;
	int isFullscreen;

	/* Because configure requests cover a wide variety of events,
	keep these "last" parameters to check if an event actually occured */
	int lastX, lastY;
	int lastWidth, lastHeight;

	/* Software rendering support */
	XImage* softwareImage;
	void* softwareBackbuffer;
	uint32_t softwarePitch;
} SST_Window_Xlib;

/******************************************************************************/

typedef struct SST_OpenGLContext_Xlib
{
	SST_DisplayTarget_Xlib* displayTarget;
	uint16_t ctxVersion[2]; /* context version major/minor */


	/* GLX Fields */
	int legacyEnabled; /* Did we use legacy GLX (< 1.4) context support? */
	GLXContext glxcontext;
	GLXFunctions glX;
	Window win;				/* Window context is bound to */

	/* EGL fields */

} SST_OpenGLContext_Xlib;

/******************************************************************************/

extern XlibFunctions X;

int loadXlib();
void unloadXlib();

#endif
