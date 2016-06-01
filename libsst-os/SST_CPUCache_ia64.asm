/*
	SST_CPUCache_ia64.asm
	Author: Patrick Baggett <ptb1@762studios.com>
	Created: 4/16/2012

	Purpose: 

	Itanium assembly for CPU cache functions

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

//Functions
.global SST_OS_GetCacheLineSize#
.global SST_OS_FlushDCRange#
.global SST_OS_InvalidateICRange#
.global SST_OS_SyncCache#

.section .text

/* uint32_t SST_OS_GetCacheLineSize() */
.align 32
SST_OS_GetCacheLineSize:
	
/* SST_OS_InvalidateICRange(void* base, size_t range) */
SST_OS_InvalidateICRange:
SST_OS_FlushDCRange:
	
/* void SST_OS_SyncCache() */
SST_OS_SyncCache:
	br.ret.sptk.many b0;;
