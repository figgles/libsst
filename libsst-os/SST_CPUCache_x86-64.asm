;	SST_CPUCache_x86-64.asm
;	Author: Patrick Baggett <ptbaggett@762studios.com>
;	Created: 12/23/2011
;
;	Purpose: 
;
;	64-bit assembly for x86 CPU cache functions for the SysV ABI. Assembles with YASM 1.1/NASM 2.0+
;
;	License:
;
;	This program is free software. It comes without any warranty, to
;	the extent permitted by applicable law. You can redistribute it
;	and/or modify it under the terms of the Do What The Fuck You Want
;	To Public License, Version 2, as published by Sam Hocevar. See
;	http://sam.zoy.org/wtfpl/COPYING for more details.

; Win64 and UNIX calling conventions differ for x64-64. I know, it's absurd.
; Because of this, there are separate implementation for Win64 and x64-64 UNIX (Linux, *BSD, Solaris, MacOS X, etc.)
; Here is the break down:
;
; REGISTER	| Win64		| UNIX
;-----------+-----------+----------
;rax		| Retval	| Retval
;rsi		| Not used	| 1st arg
;rdi		| Not used	| 2nd arg
;rcx		| 1st arg	| 3rd arg
;rdx		| 2nd arg	| 4th arg
;r8			| 3rd arg	| 5th arg
;r9			| 4th arg	| 6th arg

[bits 64]
[segment .text]

; ELF symbol names
[global SST_OS_GetCacheLineSize]
[global SST_OS_FlushDCRange]
[global SST_OS_InvalidateICRange]
[global SST_OS_SyncCache]


;uint32_t SST_OS_GetCacheLineSize()
;no args, so win64 and unix abis are the same
 SST_OS_GetCacheLineSize:
	push rbx
	mov eax, 0x80000006		;Cache info command
	cpuid
	movzx rax, cl			;ECX bits 0-7 = L2 cache line size (TODO: what about L1?)
	pop rbx
	ret

;SST_OS_InvalidateICRange(void* base, size_t range)
SST_OS_InvalidateICRange:

	;A jmp instruction is sufficient. x86 CPUs have self-snooping caches.
	jmp do_serialize
 do_serialize:
 
	ret
	
; void SST_OS_SyncCache()
SST_OS_SyncCache:
	mfence
	ret

;void SST_OS_FlushDCRange(void* base, size_t range)
 SST_OS_FlushDCRange:
 
	call SST_OS_GetCacheLineSize	;Get the cache line size
	
	dc_flush_more1:		;do {
	clflush [rcx]
	add rcx, rax		;base += cache_line_size
	sub rdx, rax		;range -= cache_line_size
	
	cmp rcx, 0
	jg dc_flush_more1	; } while(range > 0)
	
	ret