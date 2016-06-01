/*
	SST_CPUCache_sparc64.asm
	Author: Patrick Baggett <ptb1@762studios.com>
	Created: 12/23/2011

	Purpose: 

	64-bit assembly for SPARCv9 CPU cache functions

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

.global SST_OS_GetCacheLineSize
.global SST_OS_FlushDCRange
.global SST_OS_InvalidateICRange
.global SST_OS_SyncCache


/* uint32_t SST_OS_GetCacheLineSize() */
SST_OS_GetCacheLineSize:
	retl
	or %g0, 64, %o0		/* kludge: it's 64. */	
	
/* SST_OS_InvalidateICRange(void* base, size_t range) */
SST_OS_InvalidateICRange:
SST_OS_FlushDCRange:
	add %o0, %o1, %o2	/* %o2 = end address */	

	1:
	flush %o0
	cmp %o0, %o2
	bcs %xcc,1b		/* branch on less than (unsigned) */
	add %o0, 8, %o0		/* FLUSH insn flushes a double word at a time */

	retl
	nop

/* void SST_OS_SyncCache() */
SST_OS_SyncCache:
	membar #Sync
	retl
	nop
