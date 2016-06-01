/*
	SST_WMNonPortable_Win32.c
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 6/1/2012

	Purpose: 

	Non-portable API calls in libsst-wm for the Win32 platform

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#include "Win32Private.h"

HWND SST_WM_GetHWNDWin32(SST_Window window)
{
	return ((SST_Window_Win32*)window)->hWnd;
}

