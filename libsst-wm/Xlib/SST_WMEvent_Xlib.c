/*
	SST_WMEvent_Xlib.c
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 1/8/2013

	Purpose:

	Window event functions (Xlib)

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#include <SST/SST_WMEvent.h>
#include "XlibPrivate.h"
#include "APIPrivate.h"

static SST_WMKey XlibKeyToSSTKey(XEvent* e, uint32_t* utf32Return);

#ifdef HAVE_XINPUT2
static void handleXI2Event(SST_DisplayTarget_Xlib*, XGenericEventCookie* cookie);
#endif

/******************************************************************************/

static int Xlib_GetEvent(SST_DisplayTarget target, SST_WMEvent* eventReturn)
{
	XEvent e;
	SST_DisplayTarget_Xlib* displayTarget = (SST_DisplayTarget_Xlib*)target;
	Display* display = displayTarget->display;
	EventQueue* q = &displayTarget->eventQueue;

	/* Read all X events */
	while(X.Pending(display))
	{
		SST_Window_Xlib* win = NULL;
		SST_Window_Xlib* next;
		SST_WMEvent* event;
		#ifdef HAVE_XINPUT2
		XGenericEventCookie* cookie = &e.xcookie;
		#endif
		int up = 1;

		X.NextEvent(display, &e);

		/* Find the window for which this matches and save into 'win' */
		next = displayTarget->firstWindow;
		while(next)
		{
			/* Window ID matches this event? */
			if(next->xwin == e.xany.window)
			{
				/* Found it, stop here */
				win = next;
				break;
			}

			next = next->next;
		}

		#ifdef HAVE_XINPUT2
		/* Handle X extension events */
		if(cookie->type == GenericEvent && cookie->extension == displayTarget->xi2opcode)
		{
			X.GetEventData(display, cookie);
			handleXI2Event(displayTarget, cookie);
			X.FreeEventData(display, cookie);
			continue;
		}
		#endif

		/* Event doesn't apply to any window we own, ignore it */
		if(win == NULL)
			continue;

		switch(e.type)
		{
			/* Moved mouse */
			case MotionNotify:
			{
				//Ignore MotionNotify when using relative mouse movements
				if(!displayTarget->relativeMouse)
				{
					event = AllocSlotInEQ(q);
					if(event)
					{
						event->window = win;
						event->type = SSTWMEVENT_MOUSEMOVED;
						event->details.mouseEvent.x = (uint32_t)e.xmotion.x;
						event->details.mouseEvent.y = (uint32_t)e.xmotion.y;
						event->details.mouseEvent.button = 0;
					}
				}
				break;
			}

			case ButtonPress: up = 0; /* Intentional fall through */
			case ButtonRelease:
			{
				const uint32_t button = e.xbutton.button;

				event = AllocSlotInEQ(q);
				if(event)
				{
					event->window = win;

					/* Button press (1 - 3) */
					if(button >= Button1 && button <= Button3)
					{
						event->type = (up ? SSTWMEVENT_MOUSEUP : SSTWMEVENT_MOUSEDOWN);
						event->details.mouseEvent.x = (uint32_t)e.xbutton.x;
						event->details.mouseEvent.y = (uint32_t)e.xbutton.y;
						event->details.mouseEvent.button = SST_MB1 + (button - Button1);
					}
					else if(e.type == ButtonPress)	/* Scroll wheel. Button4 = scroll up, Button5 = scroll down. */
					{								/* X will send two events: press/release for a single scroll. Only send 1 event */
						event->type = SSTWMEVENT_MOUSEWHEEL;
						event->details.scrollEvent.vscroll = (button == Button4 ? 1.0f : -1.0f);
						event->details.scrollEvent.hscroll = 0.0f; /* TODO: how to get horizonal scroll wheel? */
					}

				}

				break;
			}

			case KeyPress: up = 0; /* Intentional fall through */
			case KeyRelease:
			{
				uint32_t modState = 0;
				uint8_t whichBit   = e.xkey.keycode % 8;
				uint32_t whichByte = e.xkey.keycode / 8;

				/*
				X will autorepeat with a bunch of keyd release messages. We only want the key up, so it looks like:
					PPPPPPPPPPPPPR
				instead of:
					PRPRPRPRPRPRPR

				To find this out, when receive a KeyRelease message, we check if there is another KeyPress message with the same
				exact time. If so, we ignore this KeyRelease message.
				*/
				if(e.xany.type == KeyRelease)
				{
					if(X.Pending(display))
					{
						XEvent nextEvent;
						X.PeekEvent(display, &nextEvent);

						if(	nextEvent.type == KeyPress &&					/* Opposite of KeyRelease */
							nextEvent.xkey.keycode == e.xkey.keycode &&		/* Same key code */
							nextEvent.xkey.time == e.xkey.time)				/* Same time */
						{
							/* Ignore it */
							continue;
						}
					}

					/* OK, really is a key release then -- unset this bit */
					displayTarget->keymapBitvector[whichByte] &= ~(1 << whichBit);

				}
				else
				{

					if(displayTarget->keymapBitvector[whichByte] >> whichBit)
						modState |= SSTKEYMOD_REPEAT;

					/* TODO: how to set SSTKEYMOD_REPEAT flag? Maybe use XQueryKeymap()? */
					displayTarget->keymapBitvector[whichByte] |= (1 << whichBit);

				}


				event = AllocSlotInEQ(q);
				if(event)
				{
					SST_WMKey key;
					uint32_t utf32;

					key = XlibKeyToSSTKey(&e, &utf32);

					event->window = win;
					event->type = (up ? SSTWMEVENT_KEYUP : SSTWMEVENT_KEYDOWN);
					event->details.keyEvent.key = key;
					event->details.keyEvent.utf32 =  utf32;
					event->details.keyEvent.modifierState = modState;

				}
				break;
			}

			/* Window shown */
			case Expose:
			{
				/* TODO: software rendering should blit image */
				break;
			}

			case ConfigureNotify:
			{
			    /* Clients are told to ignore this message if override_redirect is true. */
			    if(e.xconfigure.override_redirect == False)
			    {
			        const XConfigureEvent* xc = (const XConfigureEvent*)&e.xconfigure;

			        /* Check if window moved */
			        if(win->lastX != xc->x || win->lastY != xc->y)
			        {
                        event = AllocSlotInEQ(q);
                        if(event)
                        {
                            event->window = win;
                            event->type = SSTWMEVENT_MOVED;
                            event->details.winEvent.x = (uint32_t)(xc->x < 0 ? 0 : xc->x);
                            event->details.winEvent.y = (uint32_t)(xc->y < 0 ? 0 : xc->y);
                        }
			        }

			        if(win->lastWidth != xc->width || win->lastHeight != xc->height)
			        {
                        event = AllocSlotInEQ(q);
                        if(event)
                        {
                            event->window = win;
                            event->type = SSTWMEVENT_RESIZED;
                            event->details.winEvent.x = (uint32_t)xc->width;
                            event->details.winEvent.y = (uint32_t)xc->height;
                        }

			            win->lastWidth = xc->width;
			            win->lastHeight = xc->height;
			        }

			    }
			    break;
			}

			case ClientMessage:
			{
				/* Close window attempt? */
				if(e.xclient.message_type == displayTarget->atomWmProtocols &&
				(Atom)e.xclient.data.l[0] == displayTarget->atomWmDeleteWindow)
				{
					event = AllocSlotInEQ(q);
					if(event)
					{
						event->window = win;
						event->type = SSTWMEVENT_CLOSE;
						memset(&event->details, 0, sizeof(event->details));
					}
				}
				break;
			}
		}
	}

	/* Dequeue for user events first */
	if(RemoveFromEQ(&displayTarget->userEventQueue, eventReturn))
		return 1;

	/* Remove system events next */
	if(RemoveFromEQ(&displayTarget->eventQueue, eventReturn))
		return 1;

	return 0;
}

/******************************************************************************/

static EventQueue* Xlib_getUserEventQueue(SST_DisplayTarget target)
{

	SST_DisplayTarget_Xlib* displayTarget = (SST_DisplayTarget_Xlib*)target;
	return &displayTarget->userEventQueue;
}

/******************************************************************************/
static void Xlib_lockUserEventQueue(SST_DisplayTarget target)
{
	SST_DisplayTarget_Xlib* displayTarget = (SST_DisplayTarget_Xlib*)target;
	pthread_mutex_lock(&displayTarget->eventLock);
}

/******************************************************************************/

static void Xlib_unlockUserEventQueue(SST_DisplayTarget target)
{
	SST_DisplayTarget_Xlib* displayTarget = (SST_DisplayTarget_Xlib*)target;
	pthread_mutex_unlock(&displayTarget->eventLock);
}

/******************************************************************************/

static SST_WMKey XlibKeyToSSTKey(XEvent* e, uint32_t* utf32Return)
{
	uint8_t chars[8];
	uint32_t utf32;

	KeySym keycode;

	X.LookupString(&e->xkey, (char*)chars, sizeof(chars), &keycode, NULL);

	/* TODO: figure out how to extract multicharacter values */
	utf32 = (uint32_t)chars[0];

	/* X allows Ctrl+[a-z] to generate some weird characters */
	if(utf32 < 0x20u)
		utf32 = 0;

	*utf32Return = utf32;

	/* 0 - 9 */
	if(keycode >= XK_0 && keycode <= XK_9)
		return (SST_WMKey)(SSTWMKEY_0 + (keycode - XK_0));

	/* Keypad 0 - 9 */
	if(keycode >= XK_KP_0 && keycode <= XK_KP_9)
		return (SST_WMKey)(SSTWMKEY_KEYPAD_0 + (keycode - XK_KP_0));

	/* Capital A-Z */
	if(keycode >= XK_A && keycode <= XK_Z)
		return (SST_WMKey)(SSTWMKEY_A + (keycode - XK_A));

	/* Lower case A-Z */
	if(keycode >= XK_a && keycode <= XK_z)
		return (SST_WMKey)(SSTWMKEY_A + (keycode - XK_a));

	/* Function keys (F1-F15) */
	if(keycode >= XK_F1 && keycode <= XK_F15)
		return (SST_WMKey)(SSTWMKEY_F1 + (keycode - XK_F1));

	switch(keycode)
	{

		case XK_BackSpace: return SSTWMKEY_BACKSPACE;
		case XK_Tab: return SSTWMKEY_TAB;
		case XK_Return: return SSTWMKEY_RETURN;

		case XK_Escape: return SSTWMKEY_ESCAPE;
		case XK_space: return SSTWMKEY_SPACE;
		case XK_Caps_Lock: return SSTWMKEY_CAPSLOCK;
#if 0
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
#endif

		//Keypad
		case XK_KP_Enter: return SSTWMKEY_KEYPAD_ENTER;
		case XK_Num_Lock: return SSTWMKEY_NUMLOCK;
		case XK_KP_Decimal: return SSTWMKEY_KEYPAD_PERIOD;
		case XK_KP_Divide: return SSTWMKEY_KEYPAD_DIVIDE;
		case XK_KP_Multiply: return SSTWMKEY_KEYPAD_MULTIPLY;
		case XK_KP_Subtract: return SSTWMKEY_KEYPAD_MINUS;
		case XK_KP_Add: return SSTWMKEY_KEYPAD_PLUS;

		/* Arrow keys */
		case XK_Up: return SSTWMKEY_ARROW_UP;
		case XK_Down: return SSTWMKEY_ARROW_DOWN;
		case XK_Left: return SSTWMKEY_ARROW_LEFT;
		case XK_Right: return SSTWMKEY_ARROW_RIGHT;

		/* The page up/down block */
		case XK_Insert: return SSTWMKEY_INSERT;
		case XK_Home: return SSTWMKEY_HOME;
		case XK_End: return SSTWMKEY_END;
		case XK_Page_Up: return SSTWMKEY_PAGEUP;
		case XK_Page_Down: return SSTWMKEY_PAGEDOWN;
		case XK_Delete: return SSTWMKEY_DELETE;

		case XK_Shift_L: return SSTWMKEY_LEFTSHIFT;
		case XK_Shift_R: return SSTWMKEY_RIGHTSHIFT;
		case XK_Control_L: return SSTWMKEY_LEFTCONTROL;
		case XK_Control_R: return SSTWMKEY_RIGHTCONTROL;
		case XK_Alt_L: return SSTWMKEY_LEFTALT;
		case XK_Alt_R: return SSTWMKEY_RIGHTALT;
		case XK_Super_L: return SSTWMKEY_LEFTSUPER;
		case XK_Super_R: return SSTWMKEY_RIGHTSUPER;
#if 0
		/* Misc */
		case VK_SNAPSHOT: return SSTWMKEY_PRINTSCREEN;
		case VK_SCROLL: return SSTWMKEY_SCROLLLOCK;
		case VK_PAUSE: return SSTWMKEY_PAUSE;
#endif
		case XK_asciitilde: return SSTWMKEY_TILDE; /*  `~ key  */

		default: break;
	}

	return SSTWMKEY_NONE;
}

/******************************************************************************/

#ifdef HAVE_XINPUT2
static void handleXI2Event(SST_DisplayTarget_Xlib* displayTarget, XGenericEventCookie* cookie)
{
	XIDeviceEvent* ev = (XIDeviceEvent*)cookie->data;
	EventQueue* q = &displayTarget->eventQueue;
	SST_WMEvent* event;

	switch(ev->evtype)
	{
		case XI_RawButtonPress:
		case XI_RawButtonRelease:
			break;
    		
		case XI_RawMotion:
		{
			XIRawEvent* re = (XIRawEvent*)cookie->data;
			
			event = AllocSlotInEQ(q);
			if(event)
			{
				event->window = NULL; /* TODO: ... ?*/
				event->type = SSTWMEVENT_MOUSERELMOVED;
				event->details.relMouseEvent.relx = (int32_t)re->raw_values[0];
				event->details.relMouseEvent.rely = (int32_t)re->raw_values[1];
			}            
			break;
		}
	}
}
#endif

const struct SST_WM_EventFuncs Xlib_EventFuncs = {
	Xlib_GetEvent,
	Xlib_getUserEventQueue,
	Xlib_lockUserEventQueue,
	Xlib_unlockUserEventQueue
};

