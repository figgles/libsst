/*
	SST_WMDialogBox_Win32.c
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 1/5/2013

	Purpose: 

	Model

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#include "Win32Private.h"

#define BUTTON_HSPACE	16	/* Space on either side of a button */
#define BUTTON_VSPACE	16	/* Space between top of button and dialog text */
#define TEXT_HSPACE 16
#define TEXT_VSPACE 16

typedef struct DialogBoxData
{
	const char* message;
	int lenMessage;
	int buttonId;
	int exitTime;
} DialogBoxData;

/*************************************************************************/

static LONG dlgRegCount = 0;

/*************************************************************************/

static LRESULT WINAPI libsstDlgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

static HWND createButton(HWND owner, int id, const char* label, int x, int y, int w, int h);

/*************************************************************************/

int Win32_ShowDialogBox(SST_DisplayTarget target, SST_Window parent, const char* caption, const char* message, const char** buttons, int nrButtons)
{
	SST_Window_Win32* win = (SST_Window_Win32*)parent;
	SST_DisplayTarget_Win32* displayTarget = (SST_DisplayTarget_Win32*)target;
	HWND hWnd;
	HWND hParentWnd = NULL;
	MSG msg;
	HDC hDC;
	HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);

	/* Compute size of a button. This is absolutely arcane, but the 50x14 units and the /4 /8 are documented. Somewhere... */
	uint32_t units = (uint32_t)GetDialogBaseUnits();
	int horiz = (int)MulDiv((units & 0xFF), 50, 4);
	int vert = (int)MulDiv((units >> 16), 14, 8);
	int w, h;
	int returnCode;

	/* Window rectangle computation */
	DWORD style = WS_CAPTION | WS_SYSMENU | WS_CLIPCHILDREN;
	DWORD styleEx = 0;
	RECT r;
	RECT textRect;
	RECT centerOn;
	DialogBoxData* dlgData;

	/* Allocate dialog box data */
	dlgData = (DialogBoxData*)HeapAlloc(GetProcessHeap(), 0, sizeof(DialogBoxData));
	if(dlgData == NULL)
		return -1;

	dlgData->message = message;
	dlgData->lenMessage = (int)strlen(message);
	dlgData->buttonId = -1;
	dlgData->exitTime = 0;
	/*
		First, figure out a good area to center the dialog box on. It's highly unintuitive to have it
		it mapped in the top-left corner. We center it on the parent window (if possible) or the monitor
		otherwise.
	*/

	/* Have a parent window? */
	if(win != NULL)
	{
		/* Then center on it */
		hParentWnd = win->hWnd;
		GetWindowRect(hParentWnd, &centerOn);
	}
	else /* Otherwise center on default display */
	{
		FindMonitorInfo fmi;

		/* Attempt to find the monitor associated with a display device */
		findMonitor(&displayTarget->devs[0], &fmi);

		/* Didn't find it? */
		if(!fmi.foundIt)
			return -1;

		/* Center on the monitor */
		centerOn.top = fmi.top;
		centerOn.left = fmi.left;
		centerOn.bottom = fmi.bottom;
		centerOn.right = fmi.right;
	}

	/* Start the window as if it was at (0,0) */
	r.top = 0;
	r.left = 0;
	r.bottom = 2*BUTTON_VSPACE+vert;	/* Enough space for a button and vertical padding above and below it */
	r.right = (LONG)nrButtons*(horiz + BUTTON_HSPACE)+BUTTON_HSPACE;

	/* Now we need to compute the area requried to display the text. This will be summed with the area required for the buttons on the Y axis, but
	the X axis will be the maximum of the two. */
	/* 1) Create a fake DC to compute the size of the text's rect */
	hDC = CreateDC("DISPLAY", NULL, NULL, NULL);
	SelectObject(hDC, (HGDIOBJ)hFont);

	/* 2) Actually  compute the rect using DrawTextEx() and DT_CALCRECT. */
	memset(&textRect, 0, sizeof(textRect));
	DrawTextExA(hDC, (LPSTR)dlgData->message, dlgData->lenMessage, &textRect, DT_CALCRECT | DT_TOP | DT_LEFT, NULL);
	DeleteDC(hDC);

	/* 3) Add a border around the entire thing */
	textRect.bottom += 2*TEXT_VSPACE;
	textRect.right += 2*TEXT_HSPACE;

	/* For the X-axis, we want the maximum of the amount of space it takes to display buttons and text */
	if(r.right < textRect.right)
		r.right = textRect.right;
	
	/* For the Y-aaxis, just append space to the top of dialog box for the text rect */
	r.bottom += textRect.bottom;

	/* Move the window to the center of the screen: */
	/* 1) Compute width and height of window */
	w = r.right - r.left; 
	h = r.bottom - r.top;

	AdjustWindowRectEx(&r, style, FALSE, styleEx);

	/* After we adjusted the size of the window so that the client area is constant, we need
	to move it back to (0,0). */
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

	/* 2) Adjust so it fits on the screen by doing: `adjust = (center - size) /2` */
	r.left += ((centerOn.right - centerOn.left) - w) / 2;
	r.right += ((centerOn.right - centerOn.left) - w) / 2;
	r.top += ((centerOn.bottom - centerOn.top) - h) / 2;
	r.bottom += ((centerOn.bottom - centerOn.top) - h) / 2;

	/* You can't create a window without registering the class, so let's do it now. Since
	this function has "Concurrent" access, use an atomic operation to decide if it is necessary. */
	if(InterlockedIncrement(&dlgRegCount) == 1)
	{
		WNDCLASSEXA wc;

		memset(&wc, 0, sizeof(wc));
		wc.cbSize = sizeof(wc);
		wc.lpszClassName = SST_DLGCLASS;
		wc.hInstance = GetModuleHandleA(NULL);
		wc.lpfnWndProc = libsstDlgProc;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wc.style = CS_OWNDC;
		wc.hbrBackground = (HBRUSH)(uintptr_t)(COLOR_WINDOW+1);
		RegisterClassExA(&wc);
	} /* TODO: I suppose it is possible that someone could turn this into a race condition. Priority = lowest */

	/* FINALLY, create the dialog window */
	hWnd = CreateWindowExA(styleEx,
		SST_DLGCLASS,
		caption,
		style,
		r.left, r.top, /* XY position */
		r.right-r.left, r.bottom-r.top, /* Size */
		hParentWnd,
		(NULL),
		GetModuleHandleA(NULL),
		NULL);
	
	/* Made the window successfully? */
	if(hWnd != NULL)
	{
		int i;
		POINT bottomRight;
		RECT clientRect;
		SetWindowLongPtrA(hWnd, GWLP_USERDATA, (LONG_PTR)dlgData);		

		ShowWindow(hWnd, SW_SHOW);

		/* Get the coordinates of the bottom right pixel */
		GetClientRect(hWnd, &clientRect);
		bottomRight.x = clientRect.right;
		bottomRight.y = clientRect.bottom;

		/* Create the dialog buttons in reverse order starting at the right end of the dialog and moving left */
		for(i=0; i<nrButtons; i++)
		{
			HWND hButton = createButton(hWnd, nrButtons-1-i, buttons[nrButtons-1-i], bottomRight.x-((i+1)*(BUTTON_HSPACE+horiz)), bottomRight.y-(BUTTON_VSPACE+vert), horiz, vert);

			/* Set the font on them too */
			SendMessage(hButton, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
		}

		do 
		{
			while(PeekMessageA(&msg, hWnd, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessageA(&msg);
			}
		} while(!dlgData->exitTime);
	}

	returnCode = dlgData->buttonId;

	HeapFree(GetProcessHeap(), 0,dlgData);
	return returnCode;
}

/*************************************************************************/

static LRESULT WINAPI libsstDlgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	DialogBoxData* dlgData = (DialogBoxData*)GetWindowLongPtrA(hWnd, GWLP_USERDATA);	


	switch(msg)
	{
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			RECT r;
			HDC hDC;
			
			
			if(dlgData)
			{
				hDC = BeginPaint(hWnd, &ps);

				SelectObject(hDC, GetStockObject(DEFAULT_GUI_FONT));

				GetClientRect(hWnd, &r);

				r.left += TEXT_HSPACE;
				r.right -= TEXT_HSPACE;
				r.top += TEXT_VSPACE;
				r.bottom -= TEXT_VSPACE;

				DrawTextExA(hDC, (LPSTR)dlgData->message, dlgData->lenMessage, &r, DT_TOP | DT_LEFT, NULL);
				EndPaint(hWnd, &ps);
			}
			return 0;
			break;
		}

		/* Aborting the dialog */
		case WM_CLOSE:
			dlgData->buttonId = -1;
			dlgData->exitTime = 1;
			DestroyWindow(hWnd);
			return 0;
			break;
		
		case WM_COMMAND:
		{
			if(HIWORD(wParam) == BN_CLICKED)
			{
				dlgData->buttonId = (int)LOWORD(wParam);
				dlgData->exitTime = 1;

				DestroyWindow(hWnd);
			}
			return 0;
			break;
		}

	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

/*************************************************************************/

static HWND createButton(HWND owner, int id, const char* label, int x, int y, int w, int h)
{
	HWND hWnd = CreateWindowExA(0,
		"BUTTON",
		label,
		WS_TABSTOP|WS_VISIBLE|
		WS_CHILD|BS_DEFPUSHBUTTON,
		x, y,
		w, h,
		owner,
		(HMENU)(uintptr_t)id,
		GetModuleHandleA(NULL),
		NULL);
	return hWnd;
}

