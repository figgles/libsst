/*
	Win32Private.h
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 1/7/2012

	Purpose: 

	Private defintions and functions for Win32 implementation of libsst-wm

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#pragma once

#ifndef _WIN32PRIVATE_H
#define _WIN32PRIVATE_H

#include <windows.h>
#include <windowsx.h> /* More Win32 macros */
#include <GL/gl.h>
#include <SST/SST_WMTypes.h>
#include "../EventQueue.h"

#define ADAPTER_NAME_STRLEN 128
#define STRLEN_GUID	((size_t)64) /* Storage enough to hold a Win32 GUID if it was written as a string of hex characters with dashes (need only like 36-38) */
#define MIN_BPP 24 /* Minimum BPP for a mode to be considered */
#define SST_WINCLASS	"libsstwm"
#define SST_DLGCLASS	"libsstwmdlg"
#define MAX_GL_ATTRS 32

/*************************************************************************/

typedef HGLRC (WINAPI * pf_wglCreateContext)(HDC hdc);
typedef BOOL (WINAPI * pf_wglMakeCurrent)(HDC hdc, HGLRC hglrc);
typedef PROC (WINAPI * pf_wglGetProcAddress)(LPCSTR lpszProc);
typedef BOOL (WINAPI * pf_wglDeleteContext)(HGLRC hglrc);
typedef BOOL (WINAPI * pf_wglShareLists)(HGLRC hglrc1, HGLRC hglrc2);
typedef HGLRC (WINAPI * pf_wglGetCurrentContext)(void);
typedef HDC (WINAPI * pf_wglGetCurrentDC)(void);
typedef const char* (WINAPI * pf_wglGetExtensionsStringARB)(HDC hdc);
typedef BOOL (WINAPI * pf_wglChoosePixelFormatARB)(HDC hdc, const int* piAttribIList, const FLOAT* pfAttribFList, UINT nMaxFormats, int* piFormats, UINT* nNumFormats);
typedef HGLRC (WINAPI * pf_wglCreateContextAttribsARB)(HDC hDC, HGLRC hshareContext, const int *attribList);
typedef BOOL (WINAPI * pf_wglGetPixelFormatAttribivARB)(HDC hdc, int iPixelFormat, int iLayerPlane, UINT nAttributes, const int *piAttributes, int *piValues);

/*************************************************************************/

/*
	Note about memory management -- these functions all use the Win32 API (HeapAlloc()/HeapFree()) instead of the CRT functions (malloc()/free()).
	This is so that it has less of dependency on the CRT.
*/

/*************************************************************************/

/* Structure to maps an adapter-display pair to a DISPLAY_DEVICE */
typedef struct ASMapEntry
{
	SST_VideoMode defaultVmode;
	const DISPLAY_DEVICEA* dev;
	SST_VideoMode* vmodes;
	size_t adapter;
	size_t screen;
	size_t vmodeCount;
} ASMapEntry;

/*************************************************************************/

typedef struct FindMonitorInfo
{
	const DISPLAY_DEVICEA* dev;	/* Name of the device we are trying to find a matching HMONITOR for */
	BOOL foundIt;				/* Did we find it? */
	LONG top, left;				/* Monitor corner (top,left) */
	LONG bottom, right;
} FindMonitorInfo;


/*************************************************************************/

typedef struct SST_GraphicsEnumerator_Win32
{
	char* adapterNames;
	DISPLAY_DEVICEA* devsFound;
	size_t* screenCount;
	ASMapEntry* ASMap;


	size_t adapterCount;
	size_t devCount;
	size_t ASPairCount;
} SST_GraphicsEnumerator_Win32;

/*************************************************************************/

typedef struct SST_DisplayTarget_Win32
{
	CRITICAL_SECTION userEventLock;	/* Lock protection user events */
	EventQueue userEventQueue;
	DISPLAY_DEVICEA* devs;			/* Array of devices representing this display target */
	struct SST_Window_Win32* firstWindow;	/* First window in a list of windows */
	size_t screenCount;
	size_t screenIndex;
	BOOL relativeMouse;
} SST_DisplayTarget_Win32;

/*************************************************************************/

typedef struct SST_Window_Win32
{
	WINDOWPLACEMENT wp;
	EventQueue eventQueue;
	struct SST_Window_Win32* next;
	SST_DisplayTarget_Win32* owner;
	HWND hWnd;
	BOOL isFullscreen;
	BOOL setPixelFormat; /* If TRUE, then SetPixelFormat() was called on this window */


	/* Software rendering support */
	HBITMAP softwareImage;
	HDC softwareDC;
	void* softwareBackbuffer;
	size_t softwarePitch;

} SST_Window_Win32;

/*************************************************************************/

typedef struct WGLFunctions
{
	pf_wglCreateContext CreateContext;
	pf_wglMakeCurrent MakeCurrent;
	pf_wglGetProcAddress GetProcAddress;
	pf_wglDeleteContext DeleteContext;
	pf_wglShareLists ShareLists;
	pf_wglGetCurrentContext GetCurrentContext;
	pf_wglGetCurrentDC GetCurrentDC;

	/* WGL Extensions */
	pf_wglGetExtensionsStringARB GetExtensionsStringARB;
	pf_wglChoosePixelFormatARB ChoosePixelFormatARB;
	pf_wglCreateContextAttribsARB CreateContextAttribsARB;
	pf_wglGetPixelFormatAttribivARB GetPixelFormatAttribivARB;

	BOOL supportsProfiles;
	BOOL supportsMultisample;
} WGLFunctions;

/*************************************************************************/

typedef struct SST_OpenGLContext_Win32
{
	WGLFunctions wgl;
	SST_DisplayTarget_Win32* displayTarget;
	HMODULE opengl32;
	HGLRC context;
	HDC hDCActive;
	HWND hSlaveWnd; /* Slave contexts use a dummy window. Regular (master) GL contexts have this as NULL */
	int pixelFormat;
	short ctxVersion[2]; /* context version major/minor */
	BOOL isLegacy;	/* Did we use legacy context creation functions? */
	BOOL legacyEnabled; /* Did we use legacy OpenGL (< 3.0) context support? */
	BOOL debugEnabled;	/* Did we use debug OpenGL context support? */
} SST_OpenGLContext_Win32;

/*************************************************************************/

DISPLAY_DEVICEA* get_win32devs(size_t* devCountReturn);

char* get_adapters(const DISPLAY_DEVICEA* devsFound, size_t devCount, size_t* adapterCountReturn, char** adapterGUIDReturn);

/*
	Filter a list of Win32 devices in-place; modify list so that only relevant Win32 devices are returned.
	For example, if there are 3 devices: { Gpu0Screen0, Gpu1Screen0, Gpu1Screen1}, and adapterIndex == 1,
	then this returns { Gpu1Screen0, Gpu1Screen1 } in place. The number of devices in the filtered list are
	returned (in the example, 2).
*/
size_t filter_win32devs(DISPLAY_DEVICEA* devsFound, size_t devCount, size_t adapterIndex);

ASMapEntry* build_asmap(const DISPLAY_DEVICEA* devsFound, const char* adapterGUIDs, size_t devCount, size_t adapterCount, size_t* screenCount, size_t* mapSizeReturn);

SST_VideoMode* get_vmodes(const DISPLAY_DEVICEA* dev, size_t* modeCountReturn, SST_VideoMode* defaultMode);

LRESULT WINAPI libsstWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

void resolveWGLSymbols(HMODULE opengl32, WGLFunctions* wgl);
void resolveWGLExtSymbols(HDC hDC, WGLFunctions* wgl);

void findMonitor(const DISPLAY_DEVICEA* dev, FindMonitorInfo* fmi);

/* WGL_ARB_multisample */
#define WGL_SAMPLE_BUFFERS_ARB					0x2041
#define WGL_SAMPLES_ARB							0x2042

/* WGL_ARB_pixel_format */
#define WGL_NUMBER_PIXEL_FORMATS_ARB            0x2000
#define WGL_DRAW_TO_WINDOW_ARB                  0x2001
#define WGL_DRAW_TO_BITMAP_ARB                  0x2002
#define WGL_ACCELERATION_ARB                    0x2003
#define WGL_NEED_PALETTE_ARB                    0x2004
#define WGL_NEED_SYSTEM_PALETTE_ARB             0x2005
#define WGL_SWAP_LAYER_BUFFERS_ARB              0x2006
#define WGL_SWAP_METHOD_ARB                     0x2007
#define WGL_NUMBER_OVERLAYS_ARB                 0x2008
#define WGL_NUMBER_UNDERLAYS_ARB                0x2009
#define WGL_TRANSPARENT_ARB                     0x200A
#define WGL_TRANSPARENT_RED_VALUE_ARB           0x2037
#define WGL_TRANSPARENT_GREEN_VALUE_ARB         0x2038
#define WGL_TRANSPARENT_BLUE_VALUE_ARB          0x2039
#define WGL_TRANSPARENT_ALPHA_VALUE_ARB         0x203A
#define WGL_TRANSPARENT_INDEX_VALUE_ARB         0x203B
#define WGL_SHARE_DEPTH_ARB                     0x200C
#define WGL_SHARE_STENCIL_ARB                   0x200D
#define WGL_SHARE_ACCUM_ARB                     0x200E
#define WGL_SUPPORT_GDI_ARB                     0x200F
#define WGL_SUPPORT_OPENGL_ARB                  0x2010
#define WGL_DOUBLE_BUFFER_ARB                   0x2011
#define WGL_STEREO_ARB                          0x2012
#define WGL_PIXEL_TYPE_ARB                      0x2013
#define WGL_COLOR_BITS_ARB                      0x2014
#define WGL_RED_BITS_ARB                        0x2015
#define WGL_RED_SHIFT_ARB                       0x2016
#define WGL_GREEN_BITS_ARB                      0x2017
#define WGL_GREEN_SHIFT_ARB                     0x2018
#define WGL_BLUE_BITS_ARB                       0x2019
#define WGL_BLUE_SHIFT_ARB                      0x201A
#define WGL_ALPHA_BITS_ARB                      0x201B
#define WGL_ALPHA_SHIFT_ARB                     0x201C
#define WGL_ACCUM_BITS_ARB                      0x201D
#define WGL_ACCUM_RED_BITS_ARB                  0x201E
#define WGL_ACCUM_GREEN_BITS_ARB                0x201F
#define WGL_ACCUM_BLUE_BITS_ARB                 0x2020
#define WGL_ACCUM_ALPHA_BITS_ARB                0x2021
#define WGL_DEPTH_BITS_ARB                      0x2022
#define WGL_STENCIL_BITS_ARB                    0x2023
#define WGL_AUX_BUFFERS_ARB                     0x2024

#define WGL_NO_ACCELERATION_ARB                 0x2025
#define WGL_GENERIC_ACCELERATION_ARB            0x2026
#define WGL_FULL_ACCELERATION_ARB               0x2027

#define WGL_SWAP_EXCHANGE_ARB                   0x2028
#define WGL_SWAP_COPY_ARB                       0x2029
#define WGL_SWAP_UNDEFINED_ARB                  0x202A

#define WGL_TYPE_RGBA_ARB                       0x202B
#define WGL_TYPE_COLORINDEX_ARB                 0x202C

/* WGL_ARB_create_context */
#define WGL_CONTEXT_MAJOR_VERSION_ARB		0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB		0x2092
#define WGL_CONTEXT_LAYER_PLANE_ARB			0x2093
#define WGL_CONTEXT_FLAGS_ARB				0x2094
#define WGL_CONTEXT_PROFILE_MASK_ARB		0x9126
#define WGL_CONTEXT_DEBUG_BIT_ARB		0x0001
#define WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB	0x0002
#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB	0x00000001
#define WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB 0x00000002
#define ERROR_INVALID_VERSION_ARB		0x2095
#define ERROR_INVALID_PROFILE_ARB		0x2096

#endif
