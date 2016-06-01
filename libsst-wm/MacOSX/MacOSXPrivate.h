/*
	MacOSXPrivate.h
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 1/7/2012

	Purpose: 

	Private defintions and functions for MacOS X implementation of libsst-wm

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#pragma once

#ifndef _MACOSXPRIVATE_H
#define _MACOSXPRIVATE_H

typedef struct SST_GraphicsEnumerator_MacOSX
{
	size_t nrAdapters;
	size_t nrScreens;
} SST_GraphicsEnumerator_MacOSX;

#endif

