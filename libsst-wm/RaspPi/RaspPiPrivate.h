/*
	RaspPiPrivate.h
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 6/25/2013

	Purpose:

	Private defintions and functions for Raspberry Pi implementation of
	libsst-wm

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#pragma once

#ifndef _RASPPIPRIVATE_H
#define _RASPPIPRIVATE_H

#include <bcm_host.h>
#include <pthread.h>

#include <SST/SST_WMTypes.h>
#include "EventQueue.h"

/******************************************************************************/

struct SST_Window_RaspPi;

typedef struct SST_DisplayTarget_RaspPi
{	
	EventQueue eventQueue;
	EventQueue userEventQueue;
	uint8_t keymapBitvector[32];	/* Bitmap similar to XQueryKeymap() */
	pthread_mutex_t eventLock;	/* Lock protecting user events */
	struct SST_Window_RaspPi* firstWindow;	/* Window */
	int relativeMouse;
	DISPMANX_DISPLAY_HANDLE_T display;
} SST_DisplayTarget_RaspPi;

/******************************************************************************/

typedef struct SST_Window_RaspPi
{
	SST_DisplayTarget_RaspPi* owner;
	struct SST_Window_RaspPi* next;
	int isFullscreen;
	uint32_t x, y;
	uint32_t w, h;

	DISPMANX_ELEMENT_HANDLE_T element;

	/* Software rendering support */
	void* softwareBackbuffer;
	uint32_t softwarePitch;
	DISPMANX_RESOURCE_HANDLE_T  softwareImage;
	VC_RECT_T softwareRect;
} SST_Window_RaspPi;

/******************************************************************************/

typedef struct SST_OpenGLContext_RaspPi
{
	SST_DisplayTarget_RaspPi* displayTarget;
	uint16_t ctxVersion[2]; /* context version major/minor */
	int debugEnabled;	/* Did we use debug OpenGL context support? */

	/* EGL fields */
	/* TODO */
} SST_OpenGLContext_RaspPi;

/******************************************************************************/

#endif
