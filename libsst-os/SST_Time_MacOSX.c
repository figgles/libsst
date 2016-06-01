/*
	SST_Time_MacOSX.c
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 5/30/2013

	Purpose: 

	libsst-os timing functions for MacOSX systems

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#include <SST/SST_Time.h>
#include <mach/mach_time.h>

/******************************************************************************/

static mach_timebase_info_data_t info;

/******************************************************************************/

int __libsst_init_time()
{
	return (mach_timebase_info(&info) == KERN_SUCCESS);
}

/******************************************************************************/

static uint64_t absToNsec(uint64_t abstime)
{
	return abstime * info.numer  / info.denom;
}

/******************************************************************************/

uint64_t SST_OS_GetMicroTime()
{	
	return absToNsec(mach_absolute_time()) / 1000;
}

/******************************************************************************/

uint64_t SST_OS_GetMilliTime()
{
	return absToNsec(mach_absolute_time()) / 1000000;
}

/******************************************************************************/

double SST_OS_GetFloatingTime()
{
	return absToNsec(mach_absolute_time()) / 1000000000.0;
}