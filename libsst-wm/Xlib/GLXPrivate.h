/*
	GLXPrivate.h
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 1/11/2013

	Purpose:

	OpenGL on X Windows (GLX) utility code

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#pragma once

#ifndef _GLXPRIVATE_H
#define _GLXPRIVATE_H

#include <X11/Xlib.h>
#include <SST/SST_WMOpenGL.h>

struct SST_DisplayTarget_Xlib;

#define MAX_GL_ATTRS 32

/* glx.h types */
typedef XID GLXDrawable;
typedef XID GLXWindow;
typedef XID GLXPbuffer;
typedef struct __fakeGLXContext* GLXContext;
typedef struct __fakeGLXFBConfig* GLXFBConfig;

typedef Bool (*pf_glXQueryExtension)(Display* dpy, int* errorBase, int* eventBase);
typedef Bool (*pf_glXQueryVersion)(Display* dpy, int* major, int* minor);
typedef const char* (*pf_glXQueryExtensionsString)(Display* dpy, int screen);
typedef GLXFBConfig* (*pf_glXChooseFBConfig)(Display* dpy, int screen, const int* attrib_list, int* nelements);
typedef GLXContext (*pf_glXCreateNewContext)(Display* dpy, GLXFBConfig config, int render_type, GLXContext share_list, Bool direct);
typedef void (*pf_glXDestroyContext)(Display* dpy, GLXContext ctx);
typedef Bool (*pf_glXMakeContextCurrent)(Display* display, GLXDrawable draw, GLXDrawable read, GLXContext ctx);
typedef GLXContext (*pf_glXGetCurrentContext)(void);
typedef void (*pf_glXSwapBuffers)(Display * dpy, GLXDrawable drawable);
typedef GLXPbuffer (*pf_glXCreatePbuffer)(Display* dpy, GLXFBConfig config, const int* attrib_list);
typedef void (*pf_glXDestroyPbuffer)(Display* dpy, GLXPbuffer pbuf);
typedef GLXContext (*pf_glXCreateContextAttribsARB)(Display* dpy, GLXFBConfig config, GLXContext share_context, Bool direct, const int* attrib_list);

typedef void* (*pf_glXGetProcAddressARB)(const char* procName);

typedef struct GLXFunctions
{
	pf_glXQueryExtension QueryExtension;
	pf_glXQueryVersion QueryVersion;
	pf_glXQueryExtensionsString QueryExtensionsString;
	pf_glXChooseFBConfig ChooseFBConfig;
	pf_glXCreateNewContext CreateNewContext;
	pf_glXDestroyContext DestroyContext;
	pf_glXMakeContextCurrent MakeContextCurrent;
	pf_glXGetCurrentContext GetCurrentContext;
	pf_glXSwapBuffers SwapBuffers;
	pf_glXCreatePbuffer CreatePbuffer;
	pf_glXDestroyPbuffer  DestroyPbuffer;
	pf_glXCreateContextAttribsARB CreateContextAttribsARB;
	pf_glXGetProcAddressARB GetProcAddressARB;

	Bool supportsCreateContextARB;
	Bool supportsProfiles;
	Bool supportsMultisample;
	void* libGL;
} GLXFunctions;

extern GLXFunctions glX;

/* Load libGL and resolve GLX symbols */
int loadGLX();

/* Unload libGL */
void unloadGLX();

/* Check if libGL was loaded */
int isGLXLoaded();

/* Check if GLX is supported by the X server, and a usable version */
int isGLXSupported(Display* display);

/* Create a GLX context */
SST_OpenGLContext GLXCreateOpenGLContext(struct SST_DisplayTarget_Xlib* target, SST_WMOpenGLType apiType, const SST_OpenGLContextAttributes* attribs, SST_OpenGLContextAttributes* selectedAttribsReturn);

#endif


