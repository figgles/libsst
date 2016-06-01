/*
	SST_Time_Win32.c
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 5/29/2013

	Purpose: 

	libsst-os timing functions for Win32

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#include <SST/SST_Time.h>
#include <windows.h>

static LARGE_INTEGER freq; /* Frequency, as 64-bit integer */
static double dfreq; /* Frequency, as a double value */

/*
	Quick note about frequencies:

	x86 PCs typically have various sources of timers, but these 3 are the most common:
	* RDTSC -- x86 instruction to read a cycle counter, varies per CPU but can be in the low GHz range.
	* ACPI -- Advanced Configuration and Power Interface timer, about 3.57 MHz (so, about 280 nanosecond accuracy)
	* i8254 -- Intel chip on keyboard, about 1.193 MHz (so, about 838 nanosecond accuracy)
*/

int __libsst_init_time()
{
	BOOL ok = QueryPerformanceFrequency(&freq);
	if(ok)
		dfreq = (double)freq.QuadPart;

	return (int)ok;
}

uint64_t SST_OS_GetRawTime()
{
	LARGE_INTEGER v;
	QueryPerformanceCounter(&v);

	return (uint64_t)v.QuadPart;
}

uint64_t SST_OS_GetRawFrequency()
{
	return (uint64_t)freq.QuadPart;
}

uint64_t SST_OS_GetMicroTime()
{
	LARGE_INTEGER v;
	QueryPerformanceCounter(&v);

	return (uint64_t)((v.QuadPart * 1000LL * 1000LL) / freq.QuadPart);
}

uint64_t SST_OS_GetMilliTime()	/* Not be confused with Miller Time (TM) :D */
{
	LARGE_INTEGER v;
	QueryPerformanceCounter(&v);

	return (uint64_t)((v.QuadPart * 1000LL) / freq.QuadPart);
}

double SST_OS_GetFloatingTime()
{
	LARGE_INTEGER v;
	QueryPerformanceCounter(&v);

	return (double)v.QuadPart / dfreq;

}