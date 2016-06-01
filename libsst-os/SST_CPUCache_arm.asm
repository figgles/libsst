@	SST_CPUCache_arm.asm
@	Author: Patrick Baggett <ptbaggett@762studios.com>
@	Created: 6/21/2012
@
@	Purpose: 
@
@	32-bit assembly for ARMv6+ CPU cache functions. Assembles with GNU as
@
@	License:
@
@	This program is free software. It comes without any warranty, to
@	the extent permitted by applicable law. You can redistribute it
@	and/or modify it under the terms of the Do What The Fuck You Want
@	To Public License, Version 2, as published by Sam Hocevar. See
@	http://sam.zoy.org/wtfpl/COPYING for more details.

.text

@ ELF symbol names
.global SST_OS_GetCacheLineSize
.global SST_OS_FlushDCRange
.global SST_OS_InvalidateICRange
.global SST_OS_SyncCache


@ uint32_t SST_OS_GetCacheLineSize()
SST_OS_GetCacheLineSize:
	bx lr
	
@ void SST_OS_FlushDCRange(void* base, size_t range)
SST_OS_FlushDCRange:
	bx lr 

@ void SST_OS_InvalidateICRange(void* base, size_t range)
SST_OS_InvalidateICRange:
	bx lr 


@ void SST_OS_SyncCache()
SST_OS_SyncCache:
	bx lr
