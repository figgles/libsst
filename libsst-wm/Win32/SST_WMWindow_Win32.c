/*
	SST_WMWindow_Win32.c
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 6/1/2012

	Purpose: 

	Window creation (Win32)

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#include <SST/SST_WMWindow.h>
#include "Win32Private.h"
#include "../EventQueue.h"
#include "../APIPrivate.h"

static LONG regRefCount = 0;



/*************************************************************************/

static SST_DisplayTarget Win32_CreateDisplayTarget(size_t adapterIndex, size_t screenIndexOrMultihead)
{
	DISPLAY_DEVICEA* devs;
	size_t devCount;
	SST_DisplayTarget_Win32* displayTarget;
	

	/* Get Win32 devices */
	devs = get_win32devs(&devCount);
	if(devs == NULL)
		return NULL;

	/* Filter the list */
	devCount = filter_win32devs(devs, devCount, adapterIndex);
	if(devCount == 0)
	{
		HeapFree(GetProcessHeap(), 0, devs);
		return NULL;
	}

	/* Not doing multihead? */
	if(screenIndexOrMultihead != SST_MULTIHEAD)
	{
		/* Does the screen index exceed the number of attached screens? */
		if(screenIndexOrMultihead >= devCount)
		{
			/* Failure */
			HeapFree(GetProcessHeap(), 0, devs);
			return NULL;
		}

	}

	/* Allocate a display target structure */
	displayTarget = (SST_DisplayTarget_Win32*)HeapAlloc(GetProcessHeap(), 0, sizeof(SST_DisplayTarget_Win32));
	if(displayTarget == NULL)
	{
		/* Failure */
		HeapFree(GetProcessHeap(), 0, devs);
		return NULL;
	}

	/* Initialize user event queue */
	if(!InitEQ(&displayTarget->userEventQueue))
	{
		/* Failure */
		HeapFree(GetProcessHeap(), 0, displayTarget);
		HeapFree(GetProcessHeap(), 0, devs);
		return NULL;
	}


	InitializeCriticalSection(&displayTarget->userEventLock);
	displayTarget->devs = devs;
	displayTarget->screenCount = devCount;
	displayTarget->screenIndex = screenIndexOrMultihead;
	displayTarget->firstWindow = NULL;
	displayTarget->relativeMouse = FALSE;

	/* Register class if the refcount == 1 */
	if(InterlockedIncrement(&regRefCount) == 1)
	{
		WNDCLASSEXA wc;

		memset(&wc, 0, sizeof(wc));
		wc.cbSize = sizeof(wc);
		wc.lpszClassName = SST_WINCLASS;
		wc.hInstance = GetModuleHandleA(NULL);
		wc.lpfnWndProc = libsstWndProc;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wc.style = CS_OWNDC;
		wc.hbrBackground = (HBRUSH)(uintptr_t)(COLOR_WINDOW+1);
		RegisterClassExA(&wc);
	}

	return (SST_DisplayTarget)displayTarget;
}

/*************************************************************************/

static size_t Win32_GetDisplayTargetScreenCount(SST_DisplayTarget target)
{
	SST_DisplayTarget_Win32* displayTarget = (SST_DisplayTarget_Win32*)target;

	/*
	Multihead -> real screen count
	Otherwise -> 1
	*/
	if(displayTarget->screenIndex == SST_MULTIHEAD)
		return displayTarget->screenCount;

	return 1;
}

/*************************************************************************/
	
static SST_Window Win32_CreateWindowOnScreen(SST_DisplayTarget target, size_t screenIndex, uint32_t x, uint32_t y, uint32_t width, uint32_t height, const char* title)
{
	RECT r;
	DWORD style, styleEx;
	HWND hWnd;
	SST_Window_Win32* win;
	SST_DisplayTarget_Win32* displayTarget = (SST_DisplayTarget_Win32*)target;
	FindMonitorInfo fmi;

	/* Attempt to find the monitor associated with a display device */
	findMonitor(&displayTarget->devs[screenIndex], &fmi);

	/* Didn't find it? */
	if(!fmi.foundIt)
		return NULL;

	/* Allocate SST window structure */
	win = (SST_Window_Win32*)HeapAlloc(GetProcessHeap(), 0, sizeof(SST_Window_Win32));
	if(win == NULL)
		return NULL;

	win->owner = displayTarget;
	win->next = displayTarget->firstWindow;
	win->owner = displayTarget;
	win->isFullscreen = FALSE;
	win->setPixelFormat = FALSE;
	win->softwareBackbuffer = NULL;
	win->softwareDC = NULL;
	win->softwareImage = NULL;
	win->softwarePitch = 0;

	/* These styles may be useful later.
			DWORD style = (Fullscreen ? WS_POPUP : WS_CAPTION | WS_SYSMENU);
			DWORD styleEx = (Multihead2ndWindow? WS_EX_TOOLWINDOW : WS_EX_APPWINDOW);
	*/
	style = WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;
	styleEx = WS_EX_APPWINDOW;

	/* Start the window relative to those coordinates */
	r.top = 0;
	r.left = 0;
	r.bottom = (LONG)height;
	r.right = (LONG)width;
	AdjustWindowRectEx(&r, style, FALSE, styleEx);

	if(r.top != 0)
	{
		LONG d = -r.top;

		r.top = 0;
		r.bottom += d;
	}
	if(r.left != 0)
	{
		LONG d = -r.left;

		r.left = 0;
		r.right += d;
	}

	r.top += fmi.top + (LONG)y;
	r.left += fmi.left + (LONG)x;
	r.bottom += r.top;
	r.right += r.left;


	hWnd = CreateWindowExA(
		styleEx,
		SST_WINCLASS,
		title,
		style,
		r.left, r.top, /* XY position */
		r.right-r.left, r.bottom-r.top, /* Position */
		NULL, /* parent window */
		NULL, GetModuleHandleA(NULL), win);

	/* Failed to create window */
	if(hWnd == NULL)
	{
		HeapFree(GetProcessHeap(), 0, win);
		return NULL;
	}

	/* Save window info */
	win->hWnd = hWnd;

	ShowWindow(hWnd, SW_SHOW);

	/* Link window as new root */
	displayTarget->firstWindow = win;

	return (SST_Window)win;
}

/*************************************************************************/
	
static SST_DisplayTarget Win32_GetWindowDisplayTarget(SST_Window window)
{
	SST_Window_Win32* win = (SST_Window_Win32*)window;

	return win->owner;
}

/*************************************************************************/

static void Win32_SetWindowText(SST_Window window, const char* titleBar)
{
	SST_Window_Win32* win = (SST_Window_Win32*)window;

	SetWindowTextA(win->hWnd, titleBar);
}

/*************************************************************************/
	
static void Win32_GetWindowRect(SST_Window window, SST_Rect* rectReturn)
{
	SST_Window_Win32* win = (SST_Window_Win32*)window;
	MONITORINFO info;
	RECT rectClient;
	RECT rectWin;

	/* Get info about the monitor the window is on */
	info.cbSize = sizeof(info);
	if(!GetMonitorInfoA(MonitorFromWindow(win->hWnd, MONITOR_DEFAULTTONEAREST), &info))
		return;

	/* This returns (0,0) - (w,h). I don't know why they bother using a RECT instead
	of a POINT structure, since the top/left is always (0,0). */
	GetClientRect(win->hWnd, &rectClient);

	GetWindowRect(win->hWnd, &rectWin);

	rectReturn->x = (uint32_t)(rectWin.left - info.rcMonitor.left);
	rectReturn->y = (uint32_t)(rectWin.top - info.rcMonitor.top);
	rectReturn->width = (uint32_t)rectClient.right;
	rectReturn->height = (uint32_t)rectClient.bottom;
}

/*************************************************************************/

static void Win32_MoveWindowOnScreen(SST_Window window, size_t screenIndex, uint32_t x, uint32_t y)
{
	FindMonitorInfo fmi;
	SST_Window_Win32* win = (SST_Window_Win32*)window;
	SST_DisplayTarget_Win32* displayTarget = win->owner;
	int px, py;

	if(screenIndex != SST_SAME_SCREEN)
	{
		/* Atttempt to find the monitor associated with a display device */
		findMonitor(&displayTarget->devs[screenIndex], &fmi);
		
		/* Didn't find it? (monitor unplugged?) */
		if(!fmi.foundIt)
			return;

		/* New position = monitor base + offset */
		px = (int)x + (int)fmi.top;
		py = (int)y + (int)fmi.left;
	}
	else /* Move relative to the same screen */
	{
		MONITORINFO info;

		/* Get info about the monitor the window is on */
		info.cbSize = sizeof(info);
		if(!GetMonitorInfoA(MonitorFromWindow(win->hWnd, MONITOR_DEFAULTTONEAREST), &info))
			return;
		
		px = (int)x + (int)info.rcMonitor.left;
		py = (int)y + (int)info.rcMonitor.top;
	}

	SetWindowPos(win->hWnd, NULL,
		px, py,
		0, 0,
		SWP_NOOWNERZORDER | SWP_NOSIZE);

}

/*************************************************************************/

static void Win32_ResizeWindow(SST_Window window, uint32_t width, uint32_t height)
{
	SST_Window_Win32* win = (SST_Window_Win32*)window;
	RECT r;
	BOOL hasMenu;
	HWND hParent;

	/* Get the client & window rect */
	GetClientRect(win->hWnd, &r);

	r.right = r.left + (LONG)width;
	r.bottom = r.top + (LONG)height;

	hParent = (HWND)GetWindowLongPtrA(win->hWnd, GWLP_HWNDPARENT);
	if(hParent == NULL)
		hasMenu = (GetMenu(win->hWnd) != NULL);
	else
		hasMenu = FALSE;


	AdjustWindowRectEx(&r, GetWindowLongA(win->hWnd, GWL_STYLE), hasMenu, GetWindowLongA(win->hWnd, GWL_EXSTYLE));

	SetWindowPos(win->hWnd, NULL, 0, 0, r.right - r.left, r.bottom - r.top, SWP_NOOWNERZORDER | SWP_NOMOVE);
}

/*************************************************************************/
	
static void Win32_SetWindowState(SST_Window window, SST_WMWindowState state, uint32_t param)
{
	SST_Window_Win32* win = (SST_Window_Win32*)window;

	switch(state)
	{
		case SSTWS_SHOWN:
		{
			int cmd;
			if(param == 0)
				cmd = SW_HIDE;
			else
				cmd = SW_SHOW;

			ShowWindow(win->hWnd, cmd);
			break;
		}

		/* Turn on/off resizeability */
		case SSTWS_RESIZEABLE:
		{
			DWORD style;
			RECT rect;
			POINT tl, br;

			/* Get info about the window */
			style = GetWindowLongA(win->hWnd, GWL_STYLE);
			GetClientRect(win->hWnd, &rect);

			tl.x = rect.left;
			tl.y = rect.top;

			br.x = rect.right;
			br.y = rect.bottom;

			ClientToScreen(win->hWnd, &tl);
			ClientToScreen(win->hWnd, &br);

			rect.left = tl.x;
			rect.top = tl.y;
			rect.right = br.x;
			rect.bottom = br.y;


			if(param == 0)
				style &= ~(WS_THICKFRAME | WS_MAXIMIZEBOX);
			else
				style |= (WS_THICKFRAME | WS_MAXIMIZEBOX);

			AdjustWindowRectEx(&rect, style, (GetMenu(win->hWnd) ? TRUE : FALSE),  GetWindowLongA(win->hWnd, GWL_EXSTYLE));
			SetWindowLongA(win->hWnd, GWL_STYLE, (LONG)style);

			/* MSDN: "Certain window data is cached, so changes you make using SetWindowLong() will not take effect until you
			call the SetWindowPos() function." So, let's update it... */
			SetWindowPos(win->hWnd, NULL,
				rect.left, rect.top,
				rect.right - rect.left,
				rect.bottom - rect.top,
				SWP_NOZORDER | SWP_FRAMECHANGED);
			break;
		}

		case SSTWS_FULLSCREEN:
		{
			DWORD style;

			/* Enabling fullscreen? */
			if(param && !win->isFullscreen)
			{
				MONITORINFO info;
				RECT r;
				POINT pt;

				/* Get current window style */
				style = GetWindowLongA(win->hWnd, GWL_STYLE);

				/* Save info about the window so when we exit fullscreen, we're good */
				win->wp.length = sizeof(win->wp);
				GetWindowPlacement(win->hWnd, &win->wp);
				GetWindowRect(win->hWnd, &r);
				pt.x = r.top;
				pt.y = r.left;

				
				
				/* Get info about the monitor the window is on */
				info.cbSize = sizeof(MONITORINFO);
				GetMonitorInfo(MonitorFromPoint(pt, MONITOR_DEFAULTTONEAREST), &info);

				/* Remove title bar, caption, etc. */
				SetWindowLong(win->hWnd, GWL_STYLE, style & (~WS_OVERLAPPEDWINDOW));

				/* Move & resize to cover entire screen */
				SetWindowPos(win->hWnd, HWND_TOP,
					(int)info.rcMonitor.left, (int)info.rcMonitor.top, /* Position window in the top-left corner */
					(int)(info.rcMonitor.right - info.rcMonitor.left), /* Width = width of monitor */
					(int)(info.rcMonitor.bottom - info.rcMonitor.top), /* Height = height of monitor */
					SWP_NOOWNERZORDER | SWP_FRAMECHANGED); /* Don't change*/


				win->isFullscreen = TRUE;
			}
			else if(win->isFullscreen) /* Disabling fullscreen */
			{
				style = GetWindowLongA(win->hWnd, GWL_STYLE);
				SetWindowLong(win->hWnd, GWL_STYLE, style | WS_OVERLAPPEDWINDOW);

				/* Restore old window placement */
				SetWindowPlacement(win->hWnd, &win->wp);
				SetWindowPos(win->hWnd, NULL, 0, 0, 0, 0,
					SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_FRAMECHANGED);

				win->isFullscreen = FALSE;
			}

			break;
		}

		case SSTWS_MINIMIZED:
		{
			int cmd;
			if(param == 0)
			{
				SST_WMEvent* event;
				cmd = SW_RESTORE;

				/* Win32 doesn't send a restore message if pragmatically restored, so do it ourselves */
				event = AllocSlotInEQ(&win->eventQueue);
				if(event)
				{
					event->window = win;
					event->type = SSTWMEVENT_RESTORED;
					memset(&event->details, 0, sizeof(event->details));
				}
			}
			else
				cmd = SW_MINIMIZE;

			ShowWindow(win->hWnd, cmd);
			break;
		}

		default: break;
	}
}

/*************************************************************************/

static void Win32_SetDisplayTargetState(SST_DisplayTarget target, SST_WMDisplayTargetState state, uint32_t param)
{
	SST_DisplayTarget_Win32* displayTarget = (SST_DisplayTarget_Win32*)target;

	switch(state)
	{
		case SSTDTS_RELMOUSE:
		{
			RAWINPUTDEVICE rawMouse = { 0x01, 0x02, 0, NULL }; /* Mouse: UsagePage = 1, Usage = 2 */

			/* Disabling? */
			if(displayTarget->relativeMouse && param == 0)
			{
				rawMouse.dwFlags |= RIDEV_REMOVE;

				/* Attempt to unregister raw mouse. If successful, set 'relativeMouse' to FALSE */
				if(RegisterRawInputDevices(&rawMouse, 1, sizeof(RAWINPUTDEVICE)))
				{
					displayTarget->relativeMouse = FALSE;
					ClipCursor(NULL);
					ShowCursor(TRUE);
				}
			}
			else if(!displayTarget->relativeMouse && param != 0) /* Enabling? */
			{
				if(RegisterRawInputDevices(&rawMouse, 1, sizeof(RAWINPUTDEVICE)))
				{
					HWND active;
					SST_Window_Win32* win;

					displayTarget->relativeMouse = TRUE;
					ShowCursor(FALSE);

					/* Decide if this window belows to any in this display target, if so, lock cursor into it */
					active = GetActiveWindow();
					win = displayTarget->firstWindow;

					while(win)
					{
						/* It does belong to this display target, so lock it into place */
						if(win->hWnd == active)
						{
							LONG cx, cy;
							RECT rect;

							GetWindowRect(win->hWnd, &rect);
							cx = (rect.left + rect.right) / 2;
							cy = (rect.top + rect.bottom) / 2;

							/* Ensure cursor cannot leave the center of the window */
							rect.left = cx-1;
							rect.right = cx+1;
							rect.top = cy-1;
							rect.bottom = cy+1;
							ClipCursor(&rect);
							break;
						}
						else
							win = win->next;
					}
				}
			}

			break;
		}
	}
}

/*************************************************************************/
	
static void Win32_DestroyWindow(SST_Window window)
{
	SST_DisplayTarget_Win32* displayTarget;
	SST_Window_Win32* win = (SST_Window_Win32*)window;
	SST_Window_Win32* nextWin;

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
	/* Actually destroy the Win32 window */
	DestroyWindow(win->hWnd);

	if(win->softwareBackbuffer)
		HeapFree(GetProcessHeap(), 0, win->softwareBackbuffer);
	if(win->softwareDC)
		DeleteDC(win->softwareDC);
	if(win->softwareImage)
		DeleteObject(win->softwareImage);


	/* TODO empty message queue? */

	/* Free the window */
	HeapFree(GetProcessHeap(), 0, win);
}

/*************************************************************************/

static void Win32_DestroyDisplayTarget(SST_DisplayTarget target)
{
	SST_DisplayTarget_Win32* displayTarget = (SST_DisplayTarget_Win32*)target;
	SST_Window_Win32* window = displayTarget->firstWindow;

	/* Destroy all windows */
	while(window)
	{
		/* Save the next window */
		SST_Window_Win32* next = window->next;

		/* Actually destroy the Win32 window handle */
		DestroyWindow(window->hWnd);
		HeapFree(GetProcessHeap(), 0, window);

		/*
			TODO: should we empty the message queue of all messages owned by this window? Do
			they automatically get removed? Aiiyeeee!
		*/

		/* Move to next window */
		window = next;
	}

	/* Delete user event queue lock */
	DeleteCriticalSection(&displayTarget->userEventLock);


	/* Free structures */
	DestroyEQ(&displayTarget->userEventQueue);
	HeapFree(GetProcessHeap(), 0, displayTarget->devs);
	HeapFree(GetProcessHeap(), 0, displayTarget);

	/* Unregister */
	if(InterlockedDecrement(&regRefCount) == 0)
		UnregisterClassA(SST_WINCLASS, GetModuleHandleA(NULL));
}

extern int Win32_ShowDialogBox(SST_DisplayTarget target, SST_Window parent, const char* caption, const char* message, const char** buttons, int nrButtons);

const struct SST_WM_WindowFuncs Win32_WindowFuncs = {
	Win32_CreateDisplayTarget,
	Win32_GetDisplayTargetScreenCount,
	Win32_CreateWindowOnScreen,
	Win32_GetWindowDisplayTarget,
	Win32_SetWindowText,
	Win32_GetWindowRect,
	Win32_MoveWindowOnScreen,
	Win32_ResizeWindow,
	Win32_ShowDialogBox,
	Win32_SetWindowState,
	Win32_SetDisplayTargetState,
	Win32_DestroyWindow,
	Win32_DestroyDisplayTarget
};
