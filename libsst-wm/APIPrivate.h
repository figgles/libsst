/*
	APIPrivate.h
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 4/29/2014

	Purpose:

	Private API used internally for different WM drivers

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#pragma once

#ifndef _APIPRIVATE_H
#define _APIPRIVATE_H

#include <SST/SST_WM.h>
#include "EventQueue.h"

struct SST_WM_WindowFuncs
{
	SST_DisplayTarget (*CreateDisplayTarget)(size_t adapterIndex, size_t screenIndexOrMultihead);
	size_t (*GetDisplayTargetScreenCount)(SST_DisplayTarget target);
	SST_Window (*CreateWindowOnScreen)(SST_DisplayTarget target, size_t screenIndex, uint32_t x, uint32_t y, uint32_t width, uint32_t height, const char* title);
	SST_DisplayTarget (*GetWindowDisplayTarget)(SST_Window window);
	void (*SetWindowText)(SST_Window window, const char* titleBar);
	void (*GetWindowRect)(SST_Window window, SST_Rect* rectReturn);
	void (*MoveWindowOnScreen)(SST_Window window, size_t screenIndex, uint32_t x, uint32_t y);
	void (*ResizeWindow)(SST_Window window, uint32_t width, uint32_t height);
	int (*ShowDialogBox)(SST_DisplayTarget target, SST_Window parent, const char* caption, const char* message, const char** buttons, int nrButtons);
	void (*SetWindowState)(SST_Window window, SST_WMWindowState state, uint32_t param);
	void (*SetDisplayTargetState)(SST_DisplayTarget target, SST_WMDisplayTargetState state, uint32_t param);
	void (*DestroyWindow)(SST_Window window);
	void (*DestroyDisplayTarget)(SST_DisplayTarget target);	
};

struct SST_WM_EnumFuncs
{
	SST_GraphicsEnumerator (*CreateGraphicsEnumerator)(void);
	size_t (*GetEnumAdapterCount)(SST_GraphicsEnumerator enumerator);
	void (*GetEnumAdapterName)(SST_GraphicsEnumerator enumerator, size_t adapterIndex, char* nameReturn, size_t* bufferSize);
	size_t (*GetEnumScreenCount)(SST_GraphicsEnumerator enumerator, size_t adapterIndex);
	void (*GetEnumVideoModes)(SST_GraphicsEnumerator enumerator, size_t adapterIndex, size_t screenIndex, SST_VideoMode* modesReturn, size_t* modeCountReturn);
	void (*GetEnumCurrentVideoMode)(SST_GraphicsEnumerator enumerator, size_t adapterIndex, size_t screenIndex, SST_VideoMode* mode);
	void (*DestroyGraphicsEnumerator)(SST_GraphicsEnumerator enumerator);	
};

struct SST_WM_EventFuncs
{
	int (*GetEvent)(SST_DisplayTarget target, SST_WMEvent* eventReturn);
	
	/* These aren't public API, but they are driver-specific */
	EventQueue* (*getUserEventQueue)(SST_DisplayTarget target);
	void (*lockUserEventQueue)(SST_DisplayTarget target);
	void (*unlockUserEventQueue)(SST_DisplayTarget target);
};

struct SST_WM_OpenGLFuncs
{
	SST_OpenGLContext (*CreateOpenGLContext)(SST_DisplayTarget target, SST_WMOpenGLType apiType, const SST_OpenGLContextAttributes* attribs, SST_OpenGLContextAttributes* selectedAttribsReturn);
	SST_OpenGLContext(*CreateSlaveOpenGLContext)(SST_OpenGLContext masterGLContext);
	void (*SwapOpenGLBuffers)(SST_OpenGLContext ctx);
	int (*BindOpenGLContext)(SST_OpenGLContext ctx, SST_Window window);
	void (*DestroyOpenGLContext)(SST_OpenGLContext ctx);
};

struct SST_WM_RenderFuncs
{
	int (*EnableSoftwareRendering)(SST_Window window);
	void (*DisableSoftwareRendering)(SST_Window window);
	void* (*LockBackbuffer)(SST_Window window, size_t* pitchReturn);
	void (*UnlockBackbuffer)(SST_Window window);	
};

struct SST_WM_VideoModeFuncs
{
	int (*SetVideoModeOnScreen)(SST_DisplayTarget target, size_t screenIndex, const SST_VideoMode* vmode);
	int (*GetVideoModeOnScreen)(SST_DisplayTarget target, size_t screenIndex, SST_VideoMode* vmodeReturn);

};

struct SST_WM_Driver
{
	const char* name;
	int (*init)();
	void (*shutdown)();
	const struct SST_WM_WindowFuncs* window;		/* SST_WMWindow.h */
	const struct SST_WM_EnumFuncs* enumf;			/* SST_WMEnum.h */
	const struct SST_WM_EventFuncs* event;		/* SST_WMEvent.h */
	const struct SST_WM_OpenGLFuncs* opengl;		/* SST_WMOpenGL.h */
	const struct SST_WM_RenderFuncs* render;		/* SST_WMREnder.h */
	const struct SST_WM_VideoModeFuncs* video;	/* SST_WMVideoMode.h */
};


#endif
