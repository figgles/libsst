/*
	Win32Private.c
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 6/1/2012

	Purpose: 

	Private defintions and functions for Win32 implementation of libsst-wm

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#include "Win32Private.h"
#include <SST/SST_WMRender.h>

static SST_WMKey Win32KeyToSSTKey(WPARAM vkey, LPARAM lParam);
static int extSupported(const char* extlist, const char* s);
static BOOL CALLBACK findMonitorCallback(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData);

DISPLAY_DEVICEA* get_win32devs(size_t* devCountReturn)
{
	DWORD devID = 0;
	BOOL cont;
	DISPLAY_DEVICEA* devsFound = NULL;
	size_t devCount = 0;
	size_t i;
	HANDLE hProcessHeap;

	hProcessHeap = GetProcessHeap();

	do
	{
		/* Initialize device structure */
		DISPLAY_DEVICEA dev;
		memset(&dev, 0, sizeof(dev));
		dev.cb = sizeof(dev);

		/* Try to enumerator the next device */
		cont = EnumDisplayDevicesA(NULL, devID, &dev, 0);
		if(cont)
		{
			if(	(dev.StateFlags & DISPLAY_DEVICE_ACTIVE) && /* Device must be active */
				((dev.StateFlags & DISPLAY_DEVICE_MIRRORING_DRIVER) == 0)) /* Device must not be a mirror (i.e. fake) */
			{
				void* ptr;

				/* Attempt Heap[Re]Alloc(). Don't leak memory if it does! */
				if(devsFound == NULL)
					ptr = HeapAlloc(hProcessHeap, 0, (devCount+1) * sizeof(DISPLAY_DEVICEA));
				else
					ptr = HeapReAlloc(hProcessHeap, 0, devsFound, (devCount+1)* sizeof(DISPLAY_DEVICEA));
				if(ptr == NULL)
				{
					/* The Heap[Re]Alloc() call failed, so if there is any memory that was allocated, HeapFree() it now */
					if(devsFound != NULL)
						HeapFree(hProcessHeap, 0, devsFound);

					/* Failure -> out of memory */
					return NULL;
				}

				devsFound = (DISPLAY_DEVICEA*)ptr;

				devsFound[devCount] = dev;
				devCount++;
			}
		}

		/* Try the next Win32 device */
		devID++;
	} while(cont);

	/* No graphics adapters found! */
	if(devsFound == NULL)
		return NULL;

	/* Search for the Win32 "primary device" -- make sure it is always the first device in the list. The
	"primary device" flag is only set on one of these structures, so once we find it, we can stop. */
	for(i=0; i<devCount; i++)
	{
		if((devsFound[i].StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE) && i != 0)
		{
			/* Swap with slot 0 */
			DISPLAY_DEVICEA tmp;

			memcpy(&tmp, &devsFound[0], sizeof(DISPLAY_DEVICEA));
			memcpy(&devsFound[0], &devsFound[i], sizeof(DISPLAY_DEVICEA));
			memcpy(&devsFound[i], &tmp, sizeof(DISPLAY_DEVICEA));
			break;
		}
	}

	*devCountReturn = devCount;
	return devsFound;
}

/*************************************************************************/

char* get_adapters(const DISPLAY_DEVICEA* devsFound, size_t devCount, size_t* adapterCountReturn, char** adapterGUIDReturn)
{
	char* adapterNames = NULL;
	char* adapterGUIDs = NULL;
	size_t adapterCount = 0;
	size_t i;
	HANDLE hProcessHeap;

	hProcessHeap = GetProcessHeap();

	/*
		We now have an array of DISPLAY_DEVICEs. These represent individual screens, not the actual number
		of adapters. To find that out, we'll have to count the number of unique occurrences of the graphics
		card's GUID in the DeviceKey field.

		The DeviceKey field of DISPLAY_DEVICE is this long registry key, specifically, in the format of:
		
		"\Registry\Machine\System\CurrentControlSet\Control\Video\{<long GUID>}\<screen id>"

		For example, the last part might be something like "{deadc0de-1122-3344}\0000"
		The part in the {}s is unique per card, so we count how many unique strings there are to
		figure out how many graphics adapters there are.
	*/

	/* A quick note about 'adapterNames'. It is one "char*", but logically, it is an array of fixed-length
	strings. Every 'STRLEN_GUID' bytes is a string, so string at index 'k' is '&adapterNames[k*STRLEN_GUID]' */

	for(i=0; i<devCount; i++)
	{
		/* Copy the string between the {}s */
		char* start;
		char* end;
		char* rdp;
		char tmpGuid[STRLEN_GUID];
		void* ptr;

		/*
			RDP devices have "RDP" in the name and no '{'. There will
			only be one, so we can break out early.
		*/
		rdp = strstr(devsFound[i].DeviceKey, "RDP");

		/* Find pointers to the { and } characters. */
		start = strchr(devsFound[i].DeviceKey, '{');

		/* Found RDP device? */
		if(rdp != NULL && start == NULL && devCount == 1)
		{
			char* guid;
			char* name;
			
			guid = HeapAlloc(hProcessHeap, 0, STRLEN_GUID);
			if(guid == NULL)
				return NULL;

			name = HeapAlloc(hProcessHeap, 0, ADAPTER_NAME_STRLEN);
			if(name == NULL)
			{
				HeapFree(hProcessHeap, 0, guid);
				return NULL;
			}

			/* This is the one and only RDP device. */
			strcpy(name, devsFound[i].DeviceString);
			strcpy(guid, "fake guid");
			*adapterCountReturn = 1;
			*adapterGUIDReturn = guid;

			return name;
		}

		end = strchr(start, '}');

		/* Copy the characters in between */
		memcpy(tmpGuid, start+1, (end - start - 1));
		tmpGuid[end-start-1] = 0;

		/* Check the array for matches */
		if(adapterGUIDs)
		{
			size_t j;
			int found = 0;

			for(j=0; j<adapterCount; j++)
			{
				if(!strcmp(&adapterGUIDs[j*STRLEN_GUID], tmpGuid))
				{
					found = 1;
					break;
				}
			}

			/* Try next device */
			if(found)
				continue;

		}

		/* -> No match -- add this adapter to the list of adapters */

		/* Expand array of GUIDs */
		if(adapterGUIDs == NULL)
			ptr = HeapAlloc(hProcessHeap, 0, (adapterCount+1) * STRLEN_GUID);
		else
			ptr = HeapReAlloc(hProcessHeap, 0, adapterGUIDs, (adapterCount+1) * STRLEN_GUID);
		if(ptr == NULL)
		{
			/* Clean up */
			if(adapterGUIDs)
				HeapFree(hProcessHeap, 0, adapterGUIDs);
			if(adapterNames)
				HeapFree(hProcessHeap, 0, adapterNames);

			/* Return out of memory */
			return NULL;
		} /* <- all error handling */


		adapterGUIDs = (char*)ptr;
		
		/* Copy the new adapter name over */
		strcpy(&adapterGUIDs[adapterCount*STRLEN_GUID], tmpGuid);

		/* Expand array of adapter names */
		if(adapterNames == NULL)
			ptr = HeapAlloc(hProcessHeap, 0, (adapterCount+1) * ADAPTER_NAME_STRLEN);
		else
			ptr = HeapReAlloc(hProcessHeap, 0, adapterNames, (adapterCount+1) * ADAPTER_NAME_STRLEN);
		if(ptr == NULL)
		{
			HeapFree(hProcessHeap, 0, adapterGUIDs); /* This must be non-NULL or else we would have failed by now */
			if(adapterNames != NULL)
				HeapFree(hProcessHeap, 0, adapterGUIDs);

			/* Return out of memory */
			return NULL;
		}
		adapterNames = (char*)ptr;

		/* Copy the new adapter name over */
		strcpy(&adapterNames[adapterCount*ADAPTER_NAME_STRLEN], devsFound[i].DeviceString);


		adapterCount++;
	} /* for each device -> look for unique graphics adapters */


	*adapterCountReturn = adapterCount;
	*adapterGUIDReturn = adapterGUIDs;
	return adapterNames;
}

/*************************************************************************/

/*
	Filter a list of Win32 devices in-place; modify list so that only relevant Win32 devices are returned.
	For example, if there are 3 devices: { Gpu0Screen0, Gpu1Screen0, Gpu1Screen1}, and adapterIndex == 1,
	then this returns { Gpu1Screen0, Gpu1Screen1 } in place. The number of devices in the filtered list are
	returned (in the example, 2).
*/
size_t filter_win32devs(DISPLAY_DEVICEA* devsFound, size_t devCount, size_t adapterIndex)
{
	char* adapterGUIDs = NULL;
	char* GUID;
	size_t i;
	size_t adapterCount = 0;
	size_t matched = 0;
	size_t len = 0;
	HANDLE hProcessHeap;

	hProcessHeap = GetProcessHeap();

	/*
		STEP 1: Get list of adapter GUIDs
	*/
	for(i=0; i<devCount; i++)
	{
		/* Copy the string between the {}s */
		char* start;
		char* end;
		char* rdp;
		void* ptr;
		char tmpGuid[STRLEN_GUID];

		/*
			RDP devices have "RDP" in the name and no '{'. There will
			only be one, so we can return this immediately
		*/
		rdp = strstr(devsFound[i].DeviceKey, "RDP");

		/* Find pointers to the { and } characters. */
		start = strchr(devsFound[i].DeviceKey, '{');

		if(rdp != NULL && start == NULL && adapterIndex == 0 && devCount == 1)
		{
			/* This is the one and only RDP device. Just return that it's already all good. */
			return 1;
		}
		end = strchr(start, '}');

		/* GUIDs are constant length, but we save the length here in case it ever changes */
		if(len == 0)
			len = end - start - 1;

		/* Copy the characters in between */
		memcpy(tmpGuid, start+1, (end - start - 1));
		tmpGuid[end-start-1] = 0;


		/* Check the array for matches */
		if(adapterGUIDs)
		{
			size_t j;
			int found = 0;

			for(j=0; j<adapterCount; j++)
			{
				if(!strcmp(&adapterGUIDs[j*STRLEN_GUID], tmpGuid))
				{
					found = 1;
					break;
				}
			}

			/* Try next device */
			if(found)
				continue;

		}

		/* -> No match -- add this adapter to the list of adapters */

		/* Expand array of GUIDs */
		if(adapterGUIDs == NULL)
			ptr = HeapAlloc(hProcessHeap, 0, (adapterCount+1) * STRLEN_GUID);
		else
			ptr = HeapReAlloc(hProcessHeap, 0, adapterGUIDs, (adapterCount+1) * STRLEN_GUID);
		if(ptr == NULL)
		{
			/* Clean up */
			if(adapterGUIDs)
				HeapFree(hProcessHeap, 0, adapterGUIDs);

			/* Return out of memory */
			return 0;
		} /* <- all error handling */


		adapterGUIDs = (char*)ptr;
		
		/* Copy the new adapter name over */
		strcpy(&adapterGUIDs[adapterCount*STRLEN_GUID], tmpGuid);

		adapterCount++;
	} /* for each device -> look for unique graphics adapters */

	/* Invalid index? */
	if(adapterCount <= adapterIndex)
	{
		if(adapterGUIDs != NULL)
			HeapFree(hProcessHeap, 0, adapterGUIDs);
		return 0;
	}

	/*
		STEP 2: Filter list based on adapter GUIDs
	*/
	GUID = &adapterGUIDs[adapterIndex*STRLEN_GUID];
	for(i=0; i<devCount; i++)
	{
		char* start;

		/* Find pointer to start of GUID */
		start = strchr(devsFound[i].DeviceKey, '{') + 1;

		/* Does this display device match the GUID of the adapter we're interested in? */
		if(memcmp(start, GUID, len) == 0)
		{
			/* Is it not already in place? */
			if(matched < i)
			{
				/* Move from current location to correct location. Since 'matched' only increases
				we examine a device and find it matching, it can never be larger than the current
				device index we're examining (i.e. we can't have matched 5 devices but only examined
				3). Thus, 'matched' is always <= 'i', so we'll never overwrite an index we needed to
				keep around. */
				memmove(&devsFound[matched], &devsFound[i], sizeof(DISPLAY_DEVICEA));
			}

			matched++;
		}

	}

	/* Return number of adapters matched */
	HeapFree(hProcessHeap, 0, adapterGUIDs);
	return matched;
}

/*************************************************************************/

ASMapEntry* build_asmap(const DISPLAY_DEVICEA* devsFound, const char* adapterNames, size_t devCount, size_t adapterCount, size_t* screenCount, size_t* mapSizeReturn)
{
	size_t i;
	size_t j;
	size_t mapSize = 0;
	ASMapEntry* ASMap = NULL;
	HANDLE hProcessHeap;

	hProcessHeap = GetProcessHeap();

	for(i=0; i<devCount; i++)
	{
		const char* start = strchr(devsFound[i].DeviceKey, '{');
		const char* end = strchr(start, '}');
		const size_t size = (size_t)(end - start - 1);
		const DISPLAY_DEVICEA* thisDev = &devsFound[i];

		for(j=0; j<adapterCount; j++)
		{
			/* Matches the adapter? */
			if(strncmp(start+1, &adapterNames[j*STRLEN_GUID], size) == 0)
			{
				void* ptr;

				/* Convert the ID to an integer */
				size_t screenId = screenCount[j];

				/* This adapter has one more screen */
				screenCount[j] += 1;

				/* Increase map size */
				if(ASMap == NULL)
					ptr = HeapAlloc(hProcessHeap, 0, (mapSize+1) * sizeof(ASMapEntry));
				else
					ptr = HeapReAlloc(hProcessHeap, 0, ASMap, (mapSize+1) * sizeof(ASMapEntry));
				if(ptr == NULL)
				{
					if(ASMap)
						HeapFree(hProcessHeap, 0, ASMap);
					return NULL;
				}

				/* Insert into the map */
				ASMap = (ASMapEntry*)ptr;

				ASMap[mapSize].adapter = j;
				ASMap[mapSize].screen = screenId;
				ASMap[mapSize].dev = thisDev;
				mapSize += 1;

			} /* if device name matches adapter name */
		} /* try each adapter */
	} /* for each Win32 DISPLAY_DEVICE structure... */


	*mapSizeReturn = mapSize;
	return ASMap;
}

/*************************************************************************/

SST_VideoMode* get_vmodes(const DISPLAY_DEVICEA* dev, size_t* modeCountReturn, SST_VideoMode* defaultMode)
{
	SST_VideoMode* vmodes;
	size_t modeCount = 0;
	DEVMODEA devMode;
	DWORD mode = 0;

	devMode.dmSize = sizeof(devMode);
	vmodes = NULL;

	if(!EnumDisplaySettingsA(dev->DeviceName, ENUM_CURRENT_SETTINGS, &devMode))
		return NULL;

	defaultMode->bpp = (uint32_t)devMode.dmBitsPerPel;
	defaultMode->width = (uint32_t)devMode.dmPelsWidth;
	defaultMode->height = (uint32_t)devMode.dmPelsHeight;
	defaultMode->refreshRate = (uint32_t)devMode.dmDisplayFrequency;

	if(defaultMode->refreshRate == 1)
		defaultMode->refreshRate = 0;

	/* Enumerate all display mode settings */
	while(EnumDisplaySettingsA(dev->DeviceName, mode, &devMode))
	{
		if(devMode.dmBitsPerPel >= MIN_BPP) /* Ignore low color modes */
		{
			void* ptr;

			if(vmodes == NULL)
				ptr = HeapAlloc(GetProcessHeap(), 0, (modeCount+1) * sizeof(SST_VideoMode));
			else
				ptr = HeapReAlloc(GetProcessHeap(), 0, vmodes, (modeCount+1) * sizeof(SST_VideoMode));
			if(ptr == NULL)
			{
				if(vmodes)
					HeapFree(GetProcessHeap(), 0, vmodes);
			}

			vmodes = (SST_VideoMode*)ptr;

			vmodes[modeCount].bpp = (uint32_t)devMode.dmBitsPerPel;
			vmodes[modeCount].width = (uint32_t)devMode.dmPelsWidth;
			vmodes[modeCount].height = (uint32_t)devMode.dmPelsHeight;
			vmodes[modeCount].refreshRate = (uint32_t)devMode.dmDisplayFrequency;

			/* Sometimes a value of 0 or 1 is returned to indicate "default". Normalize to just 0 */
			if(vmodes[modeCount].refreshRate == 1)
				vmodes[modeCount].refreshRate = 0;
			
			modeCount += 1;
		}
		mode++;
	}

	*modeCountReturn = modeCount;
	return vmodes;
}

/*************************************************************************/

LRESULT WINAPI libsstWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HANDLE hProcessHeap;
	SST_Window_Win32* win;
	uint32_t updown = 0;

	hProcessHeap = GetProcessHeap();
	#define GETWINPTR() win = (SST_Window_Win32*)GetWindowLongPtr(hWnd, GWLP_USERDATA)

	switch(msg)
	{
		case WM_PAINT:
		{
			GETWINPTR();
			if(win && win->softwareImage != NULL)
			{
				PAINTSTRUCT ps;
				RECT r;

				InvalidateRect(hWnd, NULL, FALSE);
				GetClientRect(win->hWnd, &r);
				
				BeginPaint(hWnd, &ps);                    /* store into a bitmap */
				SetMapMode(ps.hdc, MM_TEXT);                /* blit a bitmap */
				SetBitmapBits(win->softwareImage, r.right * r.bottom * 4, (void*)win->softwareBackbuffer);
				BitBlt(ps.hdc, 0, 0, r.right, r.bottom, win->softwareDC, 0, 0, SRCCOPY);
				EndPaint(hWnd, &ps);

			}
			else /* Ignore WM_PAINT */
				return DefWindowProc(hWnd, msg, wParam, lParam);

			break;
		}


		case WM_CREATE:
		{
			CREATESTRUCTA* createStruct = (CREATESTRUCTA*)lParam;
			SST_WMEvent* event;

			/* Get the pointer we passed to CreateWindow[Ex]() */
			win = (SST_Window_Win32*)createStruct->lpCreateParams;
			
			/* The window can be a temporary window, in which case lpCreateParams will be NULL. Don't
			throw an exception here. */
			if(win)
			{
				/* Initialize the event queue */
				if(!InitEQ(&win->eventQueue))
					return -1; /* Tell Windows to have CreateWindow[Ex]() fail */

				/* Get an event (it really shouldn't fail!) */
				event = AllocSlotInEQ(&win->eventQueue);
				if(event == NULL)
				{
					DestroyEQ(&win->eventQueue);
					return -1;
				}
				
				/* Set up SSTWMEVENT_CREATED */
				event->window = win;
				event->type = SSTWMEVENT_CREATED;
				memset(&event->details, 0, sizeof(event->details));

				/* Save window queue */
				SetWindowLongPtrA(hWnd, GWLP_USERDATA, (LONG_PTR)win);
			}
			break;
		}

		/********/

		case WM_DESTROY:
		{
			GETWINPTR();
			if(win != NULL)
			{
				/* Free all memory associated with it */
				DestroyEQ(&win->eventQueue);
			}

			break;
		}

		/********/

		case WM_CLOSE:
		{
			GETWINPTR();
			if(win)
			{
				SST_WMEvent* event;
				
				event = AllocSlotInEQ(&win->eventQueue);
				if(event)
				{
					event->window = win;
					event->type = SSTWMEVENT_CLOSE;
					memset(&event->details, 0, sizeof(event->details));
				}
			}
			break;
		}

		case WM_ACTIVATE:
		{
			GETWINPTR();
			if(win)
			{
				if(win->owner->relativeMouse)
				{
					WORD active = LOWORD(wParam);

					if(active == WA_ACTIVE || active == WA_CLICKACTIVE)
					{
						LONG cx, cy;
						RECT rect;

						GetWindowRect(win->hWnd, &rect);

						cx = (rect.left + rect.right) / 2;
						cy = (rect.top + rect.bottom) / 2;

						/* Ensure cursor cannot leave the center */
						rect.left = cx-1;
						rect.right = cx+1;
						rect.top = cy-1;
						rect.bottom = cy+1;

						ClipCursor(&rect);
					}
				}
			}
			break;
		}

		/********/

		case WM_SYSCOMMAND:
		{
			/* MSDN: In WM_SYSCOMMAND messages, the four low-order bits of the wParam parameter are used internally by the system. */
			const WPARAM command = wParam & 0xFFF0; 

			/* Restored */
			if(command == SC_RESTORE)
			{
				GETWINPTR();
				if(win)
				{
					SST_WMEvent* event;

					event = AllocSlotInEQ(&win->eventQueue);
					if(event)
					{
						event->window = win;
						event->type = SSTWMEVENT_RESTORED;
						memset(&event->details, 0, sizeof(event->details));
					}
				}
			}

			/* If you return 0, then the system assumes you performed the action (e.g. ShowWindow(hWnd, SW_MAXIMIZE). 
			To reduce code size, just use OS default behaviors. */
			return DefWindowProc(hWnd, msg, wParam, lParam);
		}

		/********/

		case WM_SETFOCUS:
		{
			GETWINPTR();
			if(win)
			{
				SST_WMEvent* event;

				event = AllocSlotInEQ(&win->eventQueue);
				if(event)
				{
					event->window = win;
					event->type = SSTWMEVENT_GAINFOCUS;
					memset(&event->details, 0, sizeof(event->details));
				}
			}
			break;
		}

		/********/

		case WM_KILLFOCUS:
		{
			GETWINPTR();
			if(win)
			{
				SST_WMEvent* event;

				event = AllocSlotInEQ(&win->eventQueue);
				if(event)
				{
					event->window = win;
					event->type = SSTWMEVENT_LOSEFOCUS;
					memset(&event->details, 0, sizeof(event->details));
				}
			}

			break;
		}

		/********/

		case WM_SIZE:
		{
			SST_WMEvent* event;
			switch(wParam) /* wParam has the type of resize */
			{
				case SIZE_MAXIMIZED:
				case SIZE_RESTORED: /* "Restored" here means (!maximized && !minimized). This is confusing since we have SC_RESTORED too. */
				{
					uint32_t x = (uint32_t)LOWORD(lParam);
					uint32_t y = (uint32_t)HIWORD(lParam);

					GETWINPTR();
					if(win && x > 0 && y > 0)
					{
						event = AllocSlotInEQ(&win->eventQueue);
						if(event)
						{
							event->window = win;
							event->type = SSTWMEVENT_RESIZED;
							event->details.winEvent.x = (uint32_t)LOWORD(lParam);
							event->details.winEvent.y = (uint32_t)HIWORD(lParam);

							if(win->softwareImage)
							{
								/* Recreate window resources */
								SST_WM_DisableSoftwareRendering(win);
								SST_WM_EnableSoftwareRendering(win);
							}
						}
					}
					break;
				}

				/* Minimize event */
				case SIZE_MINIMIZED:
				{
					GETWINPTR();
					if(win)
					{
						SST_WMEvent* event;

						event = AllocSlotInEQ(&win->eventQueue);
						if(event)
						{
							event->window = win;
							event->type = SSTWMEVENT_MINIMIZED;
							memset(&event->details, 0, sizeof(event->details));
						}
					}
					break;
				}

				/* Don't attempt to handle other messages */
				default: return DefWindowProc(hWnd, msg, wParam, lParam);
			}

			break;
		}

		/********/

		case WM_MOVE:
		{
			/*
				Note: On Windows 7 (maybe earlier) if the "System->Advanced->Performance Options->Show window contents while dragging"
				is set, you get a ton of WM_MOVE messages. I guess this is so that you can redraw the window as it moves. It floods
				the message queue pretty badly. There is no fix that I can tell of since it is intended behavior.
			*/
			GETWINPTR();
			if(win)
			{
				SST_WMEvent* event;

				event = AllocSlotInEQ(&win->eventQueue);
				if(event)
				{
					HMONITOR hMonitor;
					POINT pt;
					MONITORINFO info;

					pt.x = (LONG)((SHORT)LOWORD(lParam)); /* u16->s16->s32 */
					pt.y = (LONG)((SHORT)HIWORD(lParam)); /* u16->s16->s32 */

					info.cbSize = sizeof(info);

					/* Convert the coordinates to a position relative to the monitor they are on */
					hMonitor = MonitorFromPoint(pt, MONITOR_DEFAULTTONEAREST);
					if(hMonitor != NULL)
					{
						if(GetMonitorInfo(hMonitor, &info))
						{
							pt.x -= info.rcMonitor.left;
							pt.y -= info.rcMonitor.top;
						}
					}

					if(pt.x < 0)
						pt.x = 0;
					if(pt.y < 0)
						pt.y = 0;



					event->window = win;
					event->type = SSTWMEVENT_MOVED;
					event->details.winEvent.x = (uint32_t)pt.x;
					event->details.winEvent.y = (uint32_t)pt.y;
				}
			}
			break;
		}

		/********/

		case WM_MOUSEWHEEL:
		case WM_MOUSEHWHEEL:
		{
			GETWINPTR();
			if(win)
			{
				SST_WMEvent* event;

				event = AllocSlotInEQ(&win->eventQueue);
				if(event)
				{
					/* Compute scroll delta in terms of fractions of a whole line of text */
					float delta = ((float)GET_WHEEL_DELTA_WPARAM(wParam)) / (float)WHEEL_DELTA;

					event->type = SSTWMEVENT_MOUSEWHEEL;
					event->window = win;
					if(msg == WM_MOUSEWHEEL)
					{
						event->details.scrollEvent.vscroll = delta;
						event->details.scrollEvent.hscroll = 0;
					}
					else /* i.e. HWHEEL*/
					{
						event->details.scrollEvent.vscroll = 0;
						event->details.scrollEvent.hscroll = delta;
					}
				}
			}
			
			break;
		}
		
		/********/

		/* Left, middle, right mouse buttons */
		case WM_LBUTTONDOWN:
		case WM_MBUTTONDOWN:
		case WM_RBUTTONDOWN:
			updown = 1; /* Intentional fall through */
		case WM_LBUTTONUP:
		case WM_MBUTTONUP:
		case WM_RBUTTONUP:
		{
			/* 'updown' is either 1 (button down) or 0 (button up) at this point */

			GETWINPTR();
			if(win)
			{
				SST_WMEvent* event;

				event = AllocSlotInEQ(&win->eventQueue);
				if(event)
				{
					/* These coordinates are relative to the top of the window, so they are [0,w),[0,h) range */
					uint32_t x = (uint32_t)GET_X_LPARAM(lParam); 
					uint32_t y = (uint32_t)GET_Y_LPARAM(lParam);
					uint32_t button;

					if(msg == WM_LBUTTONDOWN || msg == WM_LBUTTONUP)
						button = SST_MBLEFT;
					else if(msg == WM_MBUTTONDOWN || msg == WM_MBUTTONUP)
						button = SST_MBMIDDLE;
					else
						button = SST_MBRIGHT;

					

					event->window = win;
					event->type = (updown ? SSTWMEVENT_MOUSEDOWN : SSTWMEVENT_MOUSEUP);
					event->details.mouseEvent.x = x;
					event->details.mouseEvent.y = y;
					event->details.mouseEvent.button = button;
				}
			}

			break;
		}

		/********/

		/* Extra mouse buttons (#4 & #5)*/
		case WM_XBUTTONDOWN:
			updown = 1; /* Intentional fall through */
		case WM_XBUTTONUP:
		{
			/* 'updown' is either 1 (button down) or 0 (button up) at this point */

			GETWINPTR();
			if(win)
			{
				SST_WMEvent* event;

				event = AllocSlotInEQ(&win->eventQueue);
				if(event)
				{
					/* These coordinates are relative to the top of the window, so they are [0,w),[0,h) range */
					uint32_t x = (uint32_t)GET_X_LPARAM(lParam); 
					uint32_t y = (uint32_t)GET_Y_LPARAM(lParam);
					uint32_t button;

					if(HIWORD(wParam) == XBUTTON1)
						button = SST_MB4;
					else
						button = SST_MB5;					

					event->window = win;
					event->type = (updown ? SSTWMEVENT_MOUSEDOWN : SSTWMEVENT_MOUSEUP);
					event->details.mouseEvent.x = x;
					event->details.mouseEvent.y = y;
					event->details.mouseEvent.button = button;
				}
			}
			/* MSDN: "An application should return TRUE from this message if it processes it. Doing so allows software
			that simulates this message on Windows systems earlier than Windows 2000 to determine whether the window
			procedure processed the message or called DefWindowProc to process it."
			
			Since we handle it, we return TRUE here. */
			return TRUE;
		}

		/********/

		case WM_INPUT:
		{
			GETWINPTR();
			if(win)
			{
				HRAWINPUT hRawInput = (HRAWINPUT)lParam;
				RAWINPUT inp;
				UINT size = sizeof(inp);

				/* Ignore WM_INPUT if not in relative mouse movement mode */
				if(!win->owner->relativeMouse)
					break;
				
				GetRawInputData(hRawInput, RID_INPUT, &inp, &size, sizeof(RAWINPUTHEADER));

				/* Mouse data */
				if(inp.header.dwType == RIM_TYPEMOUSE)
				{
					RAWMOUSE* mouse = &inp.data.mouse;
					if((mouse->usFlags & 0x01) == MOUSE_MOVE_RELATIVE && (mouse->lLastX != 0 || mouse->lLastY != 0))
					{							
						SST_WMEvent* event = AllocSlotInEQ(&win->eventQueue);
						if(event)
						{
							event->type = SSTWMEVENT_MOUSERELMOVED;
							event->window = win;
							event->details.relMouseEvent.relx = (int32_t)mouse->lLastX;
							event->details.relMouseEvent.rely = (int32_t)mouse->lLastY;

						}
					}
				}
			}
			break;
		}

		/********/

		case WM_MOUSEMOVE:
		{
			/* These coordinates are relative to the top of the window, so they are [0,w),[0,h) range */
			uint32_t x = (uint32_t)GET_X_LPARAM(lParam); 
			uint32_t y = (uint32_t)GET_Y_LPARAM(lParam);

			GETWINPTR();
			if(win)
			{
				SST_WMEvent* event;

				/* Ignore WM_MOUSEMOVE in relative mouse movement mode */
				if(win->owner->relativeMouse)
					break;


				event = AllocSlotInEQ(&win->eventQueue);
				if(event)
				{
					event->window = win;
					event->type = SSTWMEVENT_MOUSEMOVED;
					event->details.mouseEvent.x = x;
					event->details.mouseEvent.y = y;
					event->details.mouseEvent.button = 0;
				}
			}
			break;
		}

		case WM_SYSKEYDOWN:
		case WM_KEYDOWN:
			updown = 1; /* Intentional fall through */
		case WM_SYSKEYUP:
		case WM_KEYUP:
		{
			BYTE kbstate[256];
			WCHAR buf[32];
			SST_WMKey key;
			uint32_t modState = 0;
			uint32_t utf32 = 0;

			

			/* Windows doesn't send right/left VKs. However, using the scancode (in lParam), you can
			squeeze a right/left version out of it, e.g. VK_SHIFT -> { VK_LSHIFT || VK_RSHIFT }.
			
			The scan code is in bits 16-23 (i.e. 3rd byte if talking little-endian) */
			if(wParam == VK_CONTROL || wParam == VK_SHIFT || wParam == VK_MENU)
				wParam = (WPARAM)MapVirtualKeyA((UINT)((lParam >> 16) & 0xFF), MAPVK_VSC_TO_VK_EX);

			/* Translate the key, stopping if we don't successfully do so */
			key = Win32KeyToSSTKey(wParam, lParam);
			if(key == SSTWMKEY_NONE)
				break;
			
			/* TODO: Strictly, this isn't UTF-32, but UTF-16, so you can get multiple characters here.
			Ack. CJK languages are going to suffer strangeness. Need UTF-16 to UTF-32 (precombined). */
			GetKeyboardState(kbstate);
			if(ToUnicode((UINT)wParam, (UINT)(((lParam >> 16) & 0xFF) | (LPARAM)(updown<<31)), kbstate,buf, sizeof(buf) / sizeof(WCHAR), 0) > 0)
				utf32 = buf[0];

			/* MSDN: "Bit 30: The value is 1 if the key is down before the message is sent, or it is zero if the key is up."
			
			Use this to check for repeated WM messages. Obviously, this only applies to key "down" messages.
			*/
			if(lParam & (1<<30) && (msg == WM_SYSKEYDOWN || msg == WM_KEYDOWN))
				modState |= SSTKEYMOD_REPEAT;

			/* MSDN:  "If the high-order bit is 1, the key is down; otherwise, it is up." */
			if(kbstate[VK_SHIFT] & 0x80)
				modState |= SSTKEYMOD_SHIFT;
			if(kbstate[VK_CONTROL] & 0x80)
				modState |= SSTKEYMOD_CONTROL;
			if(kbstate[VK_MENU] & 0x80)
				modState |= SSTKEYMOD_ALT;

			GETWINPTR();
			if(win)
			{
				SST_WMEvent* event;

				event = AllocSlotInEQ(&win->eventQueue);
				if(event)
				{
					event->window = win;
					event->type = (updown ? SSTWMEVENT_KEYDOWN :  SSTWMEVENT_KEYUP);
					event->details.keyEvent.key = key;
					event->details.keyEvent.utf32 = utf32;
					event->details.keyEvent.modifierState = modState;

				}
			}
		}

		default:
			 return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	return 0;
}

/*************************************************************************/

void resolveWGLSymbols(HMODULE opengl32, WGLFunctions* wgl)
{
	/* These can be resolved without an active context */
	wgl->CreateContext = (pf_wglCreateContext)GetProcAddress(opengl32, "wglCreateContext");
	wgl->MakeCurrent = (pf_wglMakeCurrent)GetProcAddress(opengl32, "wglMakeCurrent");
	wgl->GetProcAddress = (pf_wglGetProcAddress)GetProcAddress(opengl32, "wglGetProcAddress"); /* <- This line of code is ironic */
	wgl->DeleteContext = (pf_wglDeleteContext)GetProcAddress(opengl32, "wglDeleteContext");
	wgl->ShareLists = (pf_wglShareLists)GetProcAddress(opengl32, "wglShareLists");
	wgl->GetCurrentContext = (pf_wglGetCurrentContext)GetProcAddress(opengl32, "wglGetCurrentContext");
	wgl->GetCurrentDC = (pf_wglGetCurrentDC)GetProcAddress(opengl32, "wglGetCurrentDC");
}

/*************************************************************************/

void resolveWGLExtSymbols(HDC hDC, WGLFunctions* wgl)
{
	const char* ext;

	/* Use wglGetProcAddress(), not GetProcAddress() for this one */
	wgl->GetExtensionsStringARB = (pf_wglGetExtensionsStringARB)wgl->GetProcAddress("wglGetExtensionsStringARB");

	/* REALLY old WGL implementation, so stop. */
	if(wgl->GetExtensionsStringARB == NULL)
		return;
	
	/* Get extension string */
	ext = wgl->GetExtensionsStringARB(hDC);

	/* WGL_ARB_pixel_format: choosing advanced pixel formats (e.g. MSAA) */
	if(extSupported(ext, "WGL_ARB_pixel_format"))
	{
		wgl->ChoosePixelFormatARB = (pf_wglChoosePixelFormatARB)wgl->GetProcAddress("wglChoosePixelFormatARB");
		wgl->GetPixelFormatAttribivARB = (pf_wglGetPixelFormatAttribivARB)wgl->GetProcAddress("wglGetPixelFormatAttribivARB");
	}

	/* WGL_ARB_create_context: creating versioned contexts */
	if(extSupported(ext, "WGL_ARB_create_context"))
		wgl->CreateContextAttribsARB = (pf_wglCreateContextAttribsARB)wgl->GetProcAddress("wglCreateContextAttribsARB");

	/* WGL_ARB_create_context_profile: creating core / compatability / debug contexts */
	if(extSupported(ext, "WGL_ARB_create_context_profile"))
		wgl->supportsProfiles = TRUE;

	/* WGL_ARB_multisample: tokens for multisample contexts using WGL_ARB_pixel_format */
	if(extSupported(ext, "WGL_ARB_multisample"))
		wgl->supportsMultisample = TRUE;
}
/*************************************************************************/

void findMonitor(const DISPLAY_DEVICEA* dev, FindMonitorInfo* fmi)
{
	fmi->dev = dev;
	fmi->foundIt = FALSE;

	EnumDisplayMonitors(NULL, NULL, findMonitorCallback, (LPARAM)fmi);
}

/*************************************************************************/

static int extSupported(const char* extlist, const char* s)
{
	const char* end;
	const char* start = extlist;
	size_t len = strlen(s);
	do
	{
		/* Look for substring */
		end = strstr(start, s);
		if(end != NULL)
		{
			const char* term;
			
			/* Check if end of string is null character or space */
			term = end + len;
			if(*term == '\0' || *term == ' ')
				return 1;

			/* Guess not... resume at end of string */
			while(*term != '\0' && *term != ' ')
				term++;

			start = term;
		}

	} while(end);

	return 0;
}

/*************************************************************************/

static SST_WMKey Win32KeyToSSTKey(WPARAM vkey, LPARAM lParam)
{
	//Virtual key values are all less than 0x100, but now the compiler knows that.
	unsigned char value = (unsigned char)(vkey & 0xFF); 
	
	if(value >= '0' && value <= '9')
		return (SST_WMKey)(SSTWMKEY_0 + (value - '0'));

	if(value >= 'A' && value <= 'Z')
		return (SST_WMKey)(SSTWMKEY_A + (value - 'A'));

	/* MSDN: "Bit 24: The value is 1 if it is an extended key; otherwise, it is 0."
	We use this to differentiate some keys */
	#define ISEXTENDED() (lParam & (1<<24)) 

	/*
		Any good compiler should be able to generate a table from this switch()
		since 'value' is defined to be a 0-255 value that maps to only enum elements
		with values <= 255. Asm output confirms MSVC/GCC do, no doubt ICC does as well.
	*/
	switch(value)
	{

		case VK_BACK: return SSTWMKEY_BACKSPACE;
		case VK_TAB: return SSTWMKEY_TAB;
		case VK_RETURN:
			if(ISEXTENDED())
				return SSTWMKEY_KEYPAD_ENTER;
			else
				return SSTWMKEY_RETURN;
		case VK_ESCAPE: return SSTWMKEY_ESCAPE;
		case VK_SPACE: return SSTWMKEY_SPACE;
		case VK_CAPITAL: return SSTWMKEY_CAPSLOCK;

		case VK_OEM_COMMA : return SSTWMKEY_COMMA;
		case VK_OEM_PERIOD: return SSTWMKEY_PERIOD;
		case VK_OEM_2: return SSTWMKEY_FORWARDSLASH; /* '/?' key */
		case VK_OEM_1: return SSTWMKEY_SEMICOLON; /* ';:' key */
		case VK_OEM_7: return SSTWMKEY_QUOTES; /* single-quote/double quotes key */
		case VK_OEM_4: return SSTWMKEY_OPENBRACKET; /* '{{' key */
		case VK_OEM_6: return SSTWMKEY_CLOSEBRACKET; /* ']}' key */
		case VK_OEM_5: return SSTWMKEY_BACKSLASH; /* '\|' key */
		case VK_OEM_MINUS : return SSTWMKEY_UNDERBAR;
		case VK_OEM_PLUS: return SSTWMKEY_EQUALS;

		//Keypad
		case VK_NUMLOCK: return SSTWMKEY_NUMLOCK;
		case VK_NUMPAD0: return SSTWMKEY_KEYPAD_0;
		case VK_NUMPAD1: return SSTWMKEY_KEYPAD_1;
		case VK_NUMPAD2: return SSTWMKEY_KEYPAD_2;
		case VK_NUMPAD3: return SSTWMKEY_KEYPAD_3;
		case VK_NUMPAD4: return SSTWMKEY_KEYPAD_4;
		case VK_NUMPAD5: return SSTWMKEY_KEYPAD_5;
		case VK_NUMPAD6: return SSTWMKEY_KEYPAD_6;
		case VK_NUMPAD7: return SSTWMKEY_KEYPAD_7;
		case VK_NUMPAD8: return SSTWMKEY_KEYPAD_8;
		case VK_NUMPAD9: return SSTWMKEY_KEYPAD_9;
		case VK_DECIMAL: return SSTWMKEY_KEYPAD_PERIOD;
		case VK_DIVIDE: return SSTWMKEY_KEYPAD_DIVIDE;
		case VK_MULTIPLY: return SSTWMKEY_KEYPAD_MULTIPLY;
		case VK_SUBTRACT: return SSTWMKEY_KEYPAD_MINUS;
		case VK_ADD: return SSTWMKEY_KEYPAD_PLUS;

		/* Arrow keys */
		case VK_UP: return SSTWMKEY_ARROW_UP;
		case VK_DOWN: return SSTWMKEY_ARROW_DOWN;
		case VK_LEFT: return SSTWMKEY_ARROW_LEFT;
		case VK_RIGHT: return SSTWMKEY_ARROW_RIGHT;

		/* The page up/down block */
		case VK_INSERT: return SSTWMKEY_INSERT;
		case VK_HOME: return SSTWMKEY_HOME;
		case VK_END: return SSTWMKEY_END;
		case VK_PRIOR: return SSTWMKEY_PAGEUP;
		case VK_NEXT: return SSTWMKEY_PAGEDOWN;
		case VK_DELETE: return SSTWMKEY_DELETE;
		
		/* Function Keys */
		case VK_F1: return SSTWMKEY_F1;
		case VK_F2: return SSTWMKEY_F2;
		case VK_F3: return SSTWMKEY_F3;
		case VK_F4: return SSTWMKEY_F4;
		case VK_F5: return SSTWMKEY_F5;
		case VK_F6: return SSTWMKEY_F6;
		case VK_F7: return SSTWMKEY_F7;
		case VK_F8: return SSTWMKEY_F8;
		case VK_F9: return SSTWMKEY_F9;
		case VK_F10: return SSTWMKEY_F10;
		case VK_F11: return SSTWMKEY_F11;
		case VK_F12: return SSTWMKEY_F12;
		case VK_F13: return SSTWMKEY_F13;
		case VK_F14: return SSTWMKEY_F14;
		case VK_F15: return SSTWMKEY_F15;

		case VK_LSHIFT: return SSTWMKEY_LEFTSHIFT;
		case VK_RSHIFT: return SSTWMKEY_RIGHTSHIFT;
		case VK_RCONTROL: return SSTWMKEY_RIGHTCONTROL;
		case VK_LCONTROL: return SSTWMKEY_LEFTCONTROL;
		case VK_LMENU: return SSTWMKEY_LEFTALT;
		case VK_RMENU: return SSTWMKEY_RIGHTALT;
		case VK_LWIN: return SSTWMKEY_LEFTSUPER;
		case VK_RWIN: return SSTWMKEY_RIGHTSUPER;

		/* Misc */
		case VK_SNAPSHOT: return SSTWMKEY_PRINTSCREEN;
		case VK_SCROLL: return SSTWMKEY_SCROLLLOCK;
		case VK_PAUSE: return SSTWMKEY_PAUSE;
		case VK_OEM_3: return SSTWMKEY_TILDE; /*  `~ key  */

		default: break;
	}

	return SSTWMKEY_NONE;
}

/*************************************************************************/

static BOOL CALLBACK findMonitorCallback(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData)
{
	FindMonitorInfo* fmi = (FindMonitorInfo*)dwData;
	MONITORINFOEXA info;

	/* Unused */
	(void)hdcMonitor;

	info.cbSize = sizeof(info);

	/* Get info about this monitor */
	if(GetMonitorInfoA(hMonitor, (MONITORINFO*)&info))
	{
		/* Check to see if device names match */
		if(strcmp(info.szDevice, fmi->dev->DeviceName) == 0)
		{
			/* Stop enumeration -- we found it! */
			fmi->top = lprcMonitor->top;
			fmi->left = lprcMonitor->left;
			fmi->bottom = lprcMonitor->bottom;
			fmi->right = lprcMonitor->right;
			fmi->foundIt = TRUE;
			return FALSE;
		}
	}

	/* Continue enumeration */
	return TRUE;
}
