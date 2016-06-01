/*
	SST_Time_POSIX.c
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 5/29/2013

	Purpose: 

	libsst-os timing functions for POSIX systems

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

/*
	Sadly, MacOS X does not implement clock_gettime(), so it has its own file
*/

#include <SST/SST_Time.h>
#include <time.h>

struct timespec freq;

static clockid_t timeSource =
#if defined(CLOCK_MONOTONIC_RAW)	/* Linux >= 2.6.28 */
	CLOCK_MONOTONIC_RAW;
#else
	CLOCK_MONOTONIC;
#endif

int __libsst_init_time()
{
	struct timespec v;
	int clkOk = (clock_gettime(timeSource, &v) > 0);

	if(!clkOk)
	{
		#if defined(CLOCK_MONOTONIC_RAW)
		timeSource = CLOCK_MONOTONIC;
		clkOk = (clock_gettime(timeSource, &v) > 0);
		if(!clkOk)
		#else
		timeSource = CLOCK_REALTIME;
		#endif


		if(clock_gettime(timeSource, &v) < 0)
			return 0;
	}
	return 1;
}

uint64_t SST_OS_GetMicroTime()
{
	struct timespec v;

	clock_gettime(timeSource, &v);

	return (uint64_t)((v.tv_sec * 1000000) + (v.tv_nsec / 1000));
}

uint64_t SST_OS_GetMilliTime()	/* Not be confused with Miller Time (TM) :D */
{
	struct timespec v;

	clock_gettime(timeSource, &v);

	return (uint64_t)((v.tv_sec * 1000) + (v.tv_nsec / 1000000));
}

double SST_OS_GetFloatingTime()
{
	struct timespec v;

	clock_gettime(timeSource, &v);

	return (double)v.tv_sec + (v.tv_nsec / 1000000000.0);
}


