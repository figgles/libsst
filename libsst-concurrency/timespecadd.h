/*
	timespecadd.h
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 4/11/2012

	Purpose: 

	Inline code for adding struct timespec, common in UNIX APIs.

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#pragma once

#ifndef _SST_CONCURRENCY_TIMESPECADD_H
#define _SST_CONCURRENCY_TIMESPECADD_H
#include <SST/SST_Build.h> /* INLINE definition */

/*
	Compute t1 += t2 in a way that UNIX doesn't bitch. Adding the
	tv_nsec fields is bad when they exceed 1B nsec (i.e. 1 sec), so
	one must add and then check for overflow. Assumed that t1, t2
	have tv_nsec fields that are each < 1e9
*/
static INLINE void _sst_add_timespec(struct timespec* t1, const struct timespec* t2)
{
	t1->tv_sec += t2->tv_sec;
	t1->tv_nsec += t2->tv_nsec;

	if(t1->tv_nsec > 1000000000)
	{
		t1->tv_nsec -= 1000000000;
		t1->tv_sec += 1;
	}
}


#endif
