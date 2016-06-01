/*
	SST_WMRender_Win32.c
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 9/19/2012

	Purpose:

	Software rendering support (Win32)

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#include "Win32Private.h"
#include "../APIPrivate.h"
#include <SST/SST_WMWindow.h>

/*************************************************************************/

static int Win32_EnableSoftwareRendering(SST_Window window)
{
	SST_Window_Win32* win = (SST_Window_Win32*)window;
	HDC hDC;
	HDC hDCTmp;
	HBITMAP hBMP;
	RECT r;

	hDCTmp = GetDC(win->hWnd);
	hDC = CreateCompatibleDC(hDCTmp);

	if(GetDeviceCaps(hDCTmp, BITSPIXEL) != 32)
	{
		DeleteDC(hDC);
		return 0;
	}

	GetClientRect(win->hWnd, &r);

	hBMP = CreateCompatibleBitmap(hDCTmp, r.right, r.bottom);
	SelectObject(hDC, hBMP);

	ReleaseDC(win->hWnd, hDCTmp);

	win->softwareDC = hDC;
	win->softwareImage = hBMP;
	win->softwareBackbuffer = HeapAlloc(GetProcessHeap(), 0, (SIZE_T)r.right * (SIZE_T)r.bottom * 4);
	win->softwarePitch = r.right * 4;

	return 1;
}

/*************************************************************************/

static void Win32_DisableSoftwareRendering(SST_Window window)
{
	SST_Window_Win32* win = (SST_Window_Win32*)window;

	if(win->softwareBackbuffer)
		HeapFree(GetProcessHeap(), 0, win->softwareBackbuffer);
	if(win->softwareDC)
		DeleteDC(win->softwareDC);
	if(win->softwareImage)
		DeleteObject(win->softwareImage);
}

/*************************************************************************/

static void* Win32_LockBackbuffer(SST_Window window, size_t* pitchReturn)
{
	SST_Window_Win32* win = (SST_Window_Win32*)window;

	*pitchReturn = win->softwarePitch;

	return win->softwareBackbuffer;
}

/*************************************************************************/

static void Win32_UnlockBackbuffer(SST_Window window)
{
	SST_Window_Win32* win = (SST_Window_Win32*)window;
	InvalidateRect(win->hWnd, NULL, FALSE);
	UpdateWindow(win->hWnd);
}

struct SST_WM_RenderFuncs Win32_RenderFuncs = {
	Win32_EnableSoftwareRendering,
	Win32_DisableSoftwareRendering,
	Win32_LockBackbuffer,
	Win32_UnlockBackbuffer
};
