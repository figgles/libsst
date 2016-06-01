/*
	SST_OSInit.c
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 5/29/2013

	Purpose: 

	libsst-os initialization function

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

extern void __libsst_init_endian();
extern void __libsst_init_pagesize();
extern void __libsst_init_mmapsize();
extern int __libsst_init_time();
extern int __libsst_init_user();

int SST_OS_Init()
{
	__libsst_init_endian();
	__libsst_init_pagesize();
	__libsst_init_mmapsize();

	return __libsst_init_time() && __libsst_init_user();
}
