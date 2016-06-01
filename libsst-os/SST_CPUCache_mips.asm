/*
	SST_CPUCache_mips.asm
	Author: Patrick Baggett <ptb1@762studios.com>
	Created: 7/20/2012

	Purpose: 

	32-bit assembly for MIPS CPU cache functions

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

/* ELF symbol names */
.global SST_OS_GetCacheLineSize
.global SST_OS_FlushDCRange
.global SST_OS_InvalidateICRange
.global SST_OS_SyncCache


/* uint32_t SST_OS_GetCacheLineSize() */
SST_OS_GetCacheLineSize:
	jr $ra	
	li $v0, 64
	
/* SST_OS_InvalidateICRange(void* base, size_t range) */
SST_OS_InvalidateICRange:
	jr $ra	
	nop
	
SST_OS_FlushDCRange:
	sync
	jr $ra	
	nop
	
/* void SST_OS_SyncCache() */
SST_OS_SyncCache:
	sync
	jr $ra	
	nop
