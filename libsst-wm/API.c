/*
	API.c
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 1/8/2013

	Purpose:
	
 	The libsst-wm API. Mostly calls into the current driver.


	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/
#include "APIPrivate.h"
#include <stdlib.h>
#include <stdio.h>

/******************************************************************************/

#if defined(HAVE_XLIB)
extern struct SST_WM_Driver XlibDriver;
#endif

#if defined(_WIN32)
extern struct SST_WM_Driver Win32Driver;
#endif

/******************************************************************************/

const static struct SST_WM_Driver* drivers[] = {
	#if defined(HAVE_XLIB)
	&XlibDriver,
	#endif
	#if defined(_WIN32)
	&Win32Driver,
	#endif
	NULL
};

static const struct SST_WM_Driver* driver = NULL;

/******************************************************************************/

int SST_WM_Init(void) {
	size_t i;
	/* Try to initialize a driver. If it fails, then try the next. First successful one wins */
	for(i=0; drivers[i] != NULL; i++) {
		if(drivers[i]->init() != 0) {
			driver = drivers[i];
			printf("libsst-wm: Using driver \"%s\"", driver->name);
			return 1;
		}
	}

	/* No suitable driver found */
	return 0;
}

/******************************************************************************/

void SST_WM_Shutdown(void) {
	if(driver != NULL) {
		driver->shutdown();
		driver = NULL;
	}
}

/******************************************************************************/

SST_DisplayTarget SST_WM_CreateDisplayTarget(size_t adapterIndex, size_t screenIndexOrMultihead) {
	return driver->window->CreateDisplayTarget(adapterIndex, screenIndexOrMultihead);
}

/******************************************************************************/

size_t SST_WM_GetDisplayTargetScreenCount(SST_DisplayTarget target) {
	return driver->window->GetDisplayTargetScreenCount(target);
}

/******************************************************************************/

SST_Window SST_WM_CreateWindowOnScreen(SST_DisplayTarget target, size_t screenIndex, uint32_t x, uint32_t y, uint32_t width, uint32_t height, const char* title) {
	return driver->window->CreateWindowOnScreen(target, screenIndex, x, y, width, height, title);
}

/******************************************************************************/

SST_DisplayTarget SST_WM_GetWindowDisplayTarget(SST_Window window) {
	return driver->window->GetWindowDisplayTarget(window);
}

/******************************************************************************/

void SST_WM_SetWindowText(SST_Window window, const char* titleBar) {
	driver->window->SetWindowText(window, titleBar);
}

/******************************************************************************/

void SST_WM_GetWindowRect(SST_Window window, SST_Rect* rectReturn) {
	driver->window->GetWindowRect(window, rectReturn);
}

/******************************************************************************/

void SST_WM_MoveWindowOnScreen(SST_Window window, size_t screenIndex, uint32_t x, uint32_t y) {
	driver->window->MoveWindowOnScreen(window, screenIndex, x, y);
}

/******************************************************************************/

void SST_WM_ResizeWindow(SST_Window window, uint32_t width, uint32_t height) {
	driver->window->ResizeWindow(window, width, height);
}

/******************************************************************************/

int SST_WM_ShowDialogBox(SST_DisplayTarget target, SST_Window parent, const char* caption, const char* message, const char** buttons, int nrButtons) {
	return driver->window->ShowDialogBox(target, parent, caption, message, buttons, nrButtons);
}

/******************************************************************************/

void SST_WM_SetWindowState(SST_Window window, SST_WMWindowState state, uint32_t param) {
	driver->window->SetWindowState(window, state, param);
}

/******************************************************************************/

void SST_WM_SetDisplayTargetState(SST_DisplayTarget target, SST_WMDisplayTargetState state, uint32_t param) {
	driver->window->SetDisplayTargetState(target, state, param);
}

/******************************************************************************/

void SST_WM_DestroyWindow(SST_Window window) {
	driver->window->DestroyWindow(window);
}

/******************************************************************************/

void SST_WM_DestroyDisplayTarget(SST_DisplayTarget target) {
	driver->window->DestroyDisplayTarget(target);
}	

/******************************************************************************/

SST_GraphicsEnumerator SST_WM_CreateGraphicsEnumerator(void) {
	return driver->enumf->CreateGraphicsEnumerator();
}

/******************************************************************************/

size_t SST_WM_GetEnumAdapterCount(SST_GraphicsEnumerator enumerator) {
	return driver->enumf->GetEnumAdapterCount(enumerator);
}

/******************************************************************************/

void SST_WM_GetEnumAdapterName(SST_GraphicsEnumerator enumerator, size_t adapterIndex, char* nameReturn, size_t* bufferSize) {
	driver->enumf->GetEnumAdapterName(enumerator, adapterIndex, nameReturn, bufferSize);
}

/******************************************************************************/

size_t SST_WM_GetEnumScreenCount(SST_GraphicsEnumerator enumerator, size_t adapterIndex) {
	return driver->enumf->GetEnumScreenCount(enumerator, adapterIndex);
}

/******************************************************************************/

void SST_WM_GetEnumVideoModes(SST_GraphicsEnumerator enumerator, size_t adapterIndex, size_t screenIndex, SST_VideoMode* modesReturn, size_t* modeCountReturn) {
	driver->enumf->GetEnumVideoModes(enumerator, adapterIndex, screenIndex, modesReturn, modeCountReturn);
}

/******************************************************************************/

void SST_WM_GetEnumCurrentVideoMode(SST_GraphicsEnumerator enumerator, size_t adapterIndex, size_t screenIndex, SST_VideoMode* mode) {
	driver->enumf->GetEnumCurrentVideoMode(enumerator, adapterIndex, screenIndex, mode);
}

/******************************************************************************/

void SST_WM_DestroyGraphicsEnumerator(SST_GraphicsEnumerator enumerator) {
	driver->enumf->DestroyGraphicsEnumerator(enumerator);
}

/******************************************************************************/

int SST_WM_GetEvent(SST_DisplayTarget target, SST_WMEvent* eventReturn) {
	return driver->event->GetEvent(target, eventReturn);
}

/******************************************************************************/

int SST_WM_SendUserEvent(SST_DisplayTarget target, const SST_WMEvent* event)
{
	EventQueue* eq;
	SST_WMEvent* newEvent;

	eq = driver->event->getUserEventQueue(target);

	driver->event->lockUserEventQueue(target);
	newEvent = AllocSlotInEQ(eq);		
	if(newEvent)
		memcpy(newEvent, event, sizeof(SST_WMEvent));
	driver->event->unlockUserEventQueue(target);

	return (newEvent != NULL);
}

/******************************************************************************/

SST_OpenGLContext SST_WM_CreateOpenGLContext(SST_DisplayTarget target, SST_WMOpenGLType apiType, const SST_OpenGLContextAttributes* attribs, SST_OpenGLContextAttributes* selectedAttribsReturn) {
	return driver->opengl->CreateOpenGLContext(target, apiType, attribs, selectedAttribsReturn);
}

/******************************************************************************/

SST_OpenGLContext SST_WM_CreateSlaveOpenGLContext(SST_OpenGLContext masterGLContext) {
	return driver->opengl->CreateSlaveOpenGLContext(masterGLContext);
}

/******************************************************************************/

void  SST_WM_SwapOpenGLBuffers(SST_OpenGLContext ctx) {
	driver->opengl->SwapOpenGLBuffers(ctx);
}

/******************************************************************************/

int SST_WM_BindOpenGLContext(SST_OpenGLContext ctx, SST_Window window) {
	return driver->opengl->BindOpenGLContext(ctx, window);
}

/******************************************************************************/

void SST_WM_DestroyOpenGLContext(SST_OpenGLContext ctx) {
	driver->opengl->DestroyOpenGLContext(ctx);
}

/******************************************************************************/

int SST_WM_EnableSoftwareRendering(SST_Window window) {
	return driver->render->EnableSoftwareRendering(window);
}

/******************************************************************************/

void SST_WM_DisableSoftwareRendering(SST_Window window) {
	driver->render->DisableSoftwareRendering(window);
}

/******************************************************************************/

void* SST_WM_LockBackbuffer(SST_Window window, size_t* pitchReturn) {
	return driver->render->LockBackbuffer(window, pitchReturn);
}

/******************************************************************************/

void SST_WM_UnlockBackbuffer(SST_Window window) {
	driver->render->UnlockBackbuffer(window);
}

/******************************************************************************/

int SST_WM_SetVideoModeOnScreen(SST_DisplayTarget target, size_t screenIndex, const SST_VideoMode* vmode) {
	return driver->video->SetVideoModeOnScreen(target,screenIndex,vmode);
}

/******************************************************************************/

int SST_WM_GetVideoModeOnScreen(SST_DisplayTarget target, size_t screenIndex, SST_VideoMode* vmodeReturn) {
	return driver->video->GetVideoModeOnScreen(target, screenIndex, vmodeReturn);
}
