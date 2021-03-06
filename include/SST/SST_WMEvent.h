/*
	SST_WMEvent.h
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 1/7/2012

	Purpose: 

	Window events

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#pragma once

#ifndef _SST_WMEVENT_H
#define _SST_WMEVENT_H

#include <SST/SST_WMTypes.h>
#include <SST/SST_WMKeys.h>

typedef enum SST_WMEventType
{
	/* Window events */
	SSTWMEVENT_CREATED,		/**< Sent once when a window is created */
	SSTWMEVENT_RESIZED,		/**< Sent when user resizes a window or when SST_WM_ResizeWindow() is used */
	SSTWMEVENT_MOVED,		/**< Sent when user drags a window or when SST_WM_MoveWindow() is used */
	SSTWMEVENT_MINIMIZED,	/**< Sent when the window is minimized */
	SSTWMEVENT_RESTORED,	/**< Sent when the window is restored from minimized or maximized */
	SSTWMEVENT_LOSEFOCUS,	/**< Sent when the window loses focus */
	SSTWMEVENT_GAINFOCUS,	/**< Sent when the window gains focus */
	SSTWMEVENT_CLOSE,		/**< Sent when the window was attempted to be closed */

	/* Mouse events */
	SSTWMEVENT_MOUSEMOVED,	/**< Sent when the user moves the mouse */
	SSTWMEVENT_MOUSEWHEEL,	/**< Sent when the user moves the mouse wheel */
	SSTWMEVENT_MOUSEDOWN,	/**< Sent when the user presses a button on the mouse */
	SSTWMEVENT_MOUSEUP,		/**< Sent when the user releases a button on the mouse */
	SSTWMEVENT_MOUSERELMOVED, /**< Sent when the user moves the mouse and the mouse is in relative mode */
	
	/* Keyboard events */
	SSTWMEVENT_KEYDOWN,
	SSTWMEVENT_KEYUP,
	
	SSTWMEVENT_USERBASE = 0x7FFFFFFu	/**< Base value at which events aren't examined by libsst-wm */
} SST_WMEventType;

/*************************************************************************/

typedef struct SST_WMWindowEvent
{
	uint32_t x, y;
} SST_WMWindowEvent;

/*************************************************************************/

typedef struct SST_WMMouseEvent
{
	uint32_t x, y;
	uint32_t button;
} SST_WMMouseEvent;

/*************************************************************************/

typedef struct SST_WMScrollEvent
{
	float vscroll, hscroll;
} SST_WMScrollEvent;

/*************************************************************************/

typedef struct SST_WMRelMouseEvent
{
	int32_t relx, rely;
} SST_WMRelMouseEvent;

/*************************************************************************/

typedef struct SST_WMKeyEvent
{
	uint32_t utf32;
	uint32_t modifierState;
	SST_WMKey key;
} SST_WMKeyEvent;

/*************************************************************************/

typedef struct SST_WMUserEvent
{
	void* userptr;
	uint32_t userdata;
} SST_WMUserEvent;

/*************************************************************************/

/* Event union type */
typedef union SST_WMEventUnion
{
	SST_WMWindowEvent winEvent;
	SST_WMMouseEvent mouseEvent;
	SST_WMScrollEvent scrollEvent;
	SST_WMRelMouseEvent relMouseEvent;
	SST_WMKeyEvent keyEvent;
	SST_WMUserEvent userEvent;
} SST_WMEventUnion;

/*************************************************************************/

/* Event structure generated by various functions */
typedef struct SST_WMEvent
{
	SST_Window window;			/**< Window reported against (NULL for user events) */
	SST_WMEventType type;		/**< Event type */
	SST_WMEventUnion details;	/**< Event details (data) */
} SST_WMEvent;

/*************************************************************************/

/* Create a user event value given some zero-based value */
#define SSTWMEVENT_USER(x)	(  ((uint32_t)SSTWMEVENT_USERBASE) + ((uint32_t)(x)) )
#define SSTWMEVENT_USERTYPE(x)	((SST_WMEventType)  SSTWMEVENT_USER(x))


#ifdef __cplusplus
extern "C" {
#endif
	
	/*
		SST_WM_GetEvent()

		Attempts to get an event from the queue, returning non-zero if an event is 
		found, otherwise if no event if found, this returns zero and doesn't modify
		the input.

		@param target - The display target
		@param eventReturn - Point to event structure to contain the new event if one is found
		@return (int) - Non-zero if an event is found, zero otherwise.
	*/
	int SST_WM_GetEvent(SST_DisplayTarget target, SST_WMEvent* eventReturn);

	/*
		SST_WM_SendUserEvent()

		Sends a user event. The event queue is limited only by available memory, so sending
		user events faster than they can be processed will result in running out of memory
		over time.

		@param target - The display target
		@param event - The event to send
		@return (int) - Non-zero if the event was successfully copied and posted, zero if out of memory.
	*/
	int SST_WM_SendUserEvent(SST_DisplayTarget target, const SST_WMEvent* event);

#ifdef __cplusplus
}
#endif


#endif
