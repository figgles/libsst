;	SST_CPUCache_x86.asm
;	Author: Patrick Baggett <ptbaggett@762studios.com>
;	Created: 12/23/2011
;
;	Purpose: 
;
;	32-bit assembly for x86 CPU cache functions. Assembles with YASM 1.1/NASM 2.0+
;
;	License:
;
;	This program is free software. It comes without any warranty, to
;	the extent permitted by applicable law. You can redistribute it
;	and/or modify it under the terms of the Do What The Fuck You Want
;	To Public License, Version 2, as published by Sam Hocevar. See
;	http://sam.zoy.org/wtfpl/COPYING for more details.

[bits 32]
[segment .text]

; Win32 symbol names
[global _SST_OS_GetCacheLineSize]
[global _SST_OS_FlushDCRange]
[global _SST_OS_InvalidateICRange]
[global _SST_OS_SyncCache]

; ELF symbol names
[global SST_OS_GetCacheLineSize]
[global SST_OS_FlushDCRange]
[global SST_OS_InvalidateICRange]
[global SST_OS_SyncCache]


;uint32_t SST_OS_GetCacheLineSize()
_SST_OS_GetCacheLineSize:
 SST_OS_GetCacheLineSize:
	push ebx
	mov eax, 0x80000006		;Cache info command
	cpuid
	movzx eax, cl			;ECX bits 0-7 = L2 cache line size (TODO: what about L1?)
	pop ebx
	ret
	
;void SST_OS_FlushDCRange(void* base, size_t range)
_SST_OS_FlushDCRange:
 SST_OS_FlushDCRange:
 
	call SST_OS_GetCacheLineSize	;Get the cache line size
	
	mov edx, [esp+4]	;edx = base
	mov ecx, [esp+8]	;ecx = range (in bytes)
	
	dc_flush_more:		;do {
	clflush [edx]
	add edx, eax		;base += cache_line_size
	sub ecx, eax		;range -= cache_line_size
	
	cmp ecx, 0
	jg dc_flush_more	; } while(range > 0)
	
	ret

;SST_OS_InvalidateICRange(void* base, size_t range)
_SST_OS_InvalidateICRange:
 SST_OS_InvalidateICRange:
 
	;A jmp instruction is sufficient. x86 CPUs have self-snooping caches.
	jmp do_serialize
 do_serialize:
 
	ret


; void SST_OS_SyncCache()
_SST_OS_SyncCache:
 SST_OS_SyncCache:
	mfence
	ret