/*
	SST_WMDialogBox_RaspPi.c
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 6/25/2013

	Purpose:

	Simple dialog box window 

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#include "RaspPiPrivate.h"

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

/******************************************************************************/

int SST_WM_ShowDialogBox(SST_DisplayTarget target, SST_Window parent, const char* caption, const char* message, const char** buttons, int nrButtons)
{
	/* TODO: helluvalota work */
	(void)target;
	(void)parent;
	(void)caption;
	(void)message;
	(void)buttons;
	(void)nrButtons;

	return 0;
}

