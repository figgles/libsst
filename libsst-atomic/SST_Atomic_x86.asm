;	SST_Atomic_x86.asm
;	Author: Patrick Baggett <ptbaggett@762studios.com>
;	Created: 11/15/2011
;
;	Purpose:
;
;	32-bit assembly for atomic operations for x86 CPUs
;	Assembles with YASM 1.1/NASM 2.0+
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
[global _SST_Atomic_Add]
[global _SST_Atomic_AddPtr]
[global _SST_Atomic_And]
[global _SST_Atomic_Or]
[global _SST_Atomic_Xor]
[global _SST_Atomic_Not]
[global _SST_Atomic_AddReturn]
[global _SST_Atomic_AddPtrReturn]
[global _SST_Atomic_AndReturn]
[global _SST_Atomic_OrReturn]
[global _SST_Atomic_XorReturn]
[global _SST_Atomic_NotReturn]
[global _SST_Atomic_ExchangeAdd]
[global _SST_Atomic_ExchangeAddPtr]
[global _SST_Atomic_Exchange]
[global _SST_Atomic_ExchangePtr]
[global _SST_Atomic_CAS]
[global _SST_Atomic_CASPtr]
[global _SST_Atomic_LoadAcquire]
[global _SST_Atomic_LoadAcquirePtr]
[global _SST_Atomic_StoreRelease]
[global _SST_Atomic_StoreReleasePtr]

; ELF symbol names
[global SST_Atomic_Add]
[global SST_Atomic_AddPtr]
[global SST_Atomic_And]
[global SST_Atomic_Or]
[global SST_Atomic_Xor]
[global SST_Atomic_Not]
[global SST_Atomic_AddReturn]
[global SST_Atomic_AddPtrReturn]
[global SST_Atomic_AndReturn]
[global SST_Atomic_OrReturn]
[global SST_Atomic_XorReturn]
[global SST_Atomic_NotReturn]
[global SST_Atomic_ExchangeAdd]
[global SST_Atomic_ExchangeAddPtr]
[global SST_Atomic_Exchange]
[global SST_Atomic_ExchangePtr]
[global SST_Atomic_CAS]
[global SST_Atomic_CASPtr]
[global SST_Atomic_LoadAcquire]
[global SST_Atomic_LoadAcquirePtr]
[global SST_Atomic_StoreRelease]
[global SST_Atomic_StoreReleasePtr]

;=======================================================================
; Since pointers and integers are the same on GCC/MSVC, many of the
; integer/pointer code paths are the same. This of course only holds true
; for 32-bit compiles on x86, which is exactly this file.
;=======================================================================


;void SST_Atomic_Add(volatile int* x, int value)
;void SST_Atomic_AddPtr(volatile void* x, uintptr_t value)
_SST_Atomic_AddPtr:
_SST_Atomic_Add:
 SST_Atomic_AddPtr:
 SST_Atomic_Add:
	mov edx, [esp+4]
	mov eax, [esp+8]
	lock add [edx], eax
	ret


; void SST_Atomic_And(volatile int* x, int value)
_SST_Atomic_And:
 SST_Atomic_And:
	mov edx, [esp+4]
	mov eax, [esp+8]
	lock and [edx], eax
	ret

; void SST_Atomic_Or(volatile int* x, int value)
_SST_Atomic_Or:
 SST_Atomic_Or:
	mov edx, [esp+4]
	mov eax, [esp+8]
	lock or [edx], eax
	ret

; void SST_Atomic_Xor(volatile int* x, int value)
_SST_Atomic_Xor:
 SST_Atomic_Xor:
	mov edx, [esp+4]
	mov eax, [esp+8]
	lock xor [edx], eax
	ret

; void SST_Atomic_Not(volatile int* x)
_SST_Atomic_Not:
 SST_Atomic_Not:
	mov edx, [esp+4]
	lock not DWORD [edx]
	ret

; int SST_Atomic_AddReturn(volatile int* x, int value)
_SST_Atomic_AddReturn:
_SST_Atomic_AddPtrReturn:
 SST_Atomic_AddReturn:
 SST_Atomic_AddPtrReturn:
	mov edx, [esp+4]
	mov eax, [esp+8]
	lock xadd [edx], eax
	add eax, [esp+8]
	ret

; int SST_Atomic_AndReturn(volatile int* x, int value)
_SST_Atomic_AndReturn:
 SST_Atomic_AndReturn:
	push ebx  ;save ebx
	
	mov ecx, [esp+8]	  ;ecx = x
	mov ebx, [esp+12]	  ;ebx = value

	mov edx, [ecx]	  ;edx = *x
	mov eax, edx	  ;eax = edx = *x
try_again_1:
	and edx, ebx	  ;edx = *x & value

	lock cmpxchg [ecx], edx	;if(eax == *x) *x = edx, else eax = *x
	jz done_1				;*x was modified. It's new value is in edx
	mov edx, eax			;copy that new value to edx, lets try again
	jmp try_again_1
done_1:
	xchg edx, eax			;edx has the value (*x & value), so swap edx and eax
	pop ebx        ;restore ebx
	ret	

_SST_Atomic_OrReturn:
 SST_Atomic_OrReturn:
	push ebx  ;save ebx
	
	mov ecx, [esp+8]	  ;ecx = x
	mov ebx, [esp+12]	  ;ebx = value

	mov edx, [ecx]	  ;edx = *x
	mov eax, edx	  ;eax = edx = *x
try_again_2:
	or edx, ebx	      ;edx = *x | value

	lock cmpxchg [ecx], edx	;if(eax == *x) *x = edx, else eax = *x
	jz done_2				;*x was modified. It's new value is in edx
	mov edx, eax			;copy that new value to edx, lets try again
	jmp try_again_2
done_2:
	xchg edx, eax			;edx has the value (*x | value), so swap edx and eax
	pop ebx ;restore ebx
	ret

_SST_Atomic_XorReturn:
 SST_Atomic_XorReturn:
	push ebx  ;save ebx
	
	mov ecx, [esp+8]	  ;ecx = x
	mov ebx, [esp+12]	  ;ebx = value

	mov edx, [ecx]	  ;edx = *x
	mov eax, edx	  ;eax = edx = *x
try_again_3:
	xor edx, ebx	      ;edx = *x ^ value

	lock cmpxchg [ecx], edx	;if(eax == *x) *x = edx, else eax = *x
	jz done_3				;*x was modified. It's new value is in edx
	mov edx, eax			;copy that new value to edx, lets try again
	jmp try_again_3
done_3:
	xchg edx, eax			;edx has the value (*x ^ value), so swap edx and eax
	pop ebx        ;restore ebx
	ret

; int SST_Atomic_NotReturn(volatile int* x)
; =============================================
_SST_Atomic_NotReturn:
 SST_Atomic_NotReturn:
	mov ecx, [esp+4]  ;ecx = x

	mov edx, [ecx]	  ;edx = *x
	mov eax, edx	  ;eax = edx = *x
try_again_4:
	not edx           ;edx = ~(*x)

	lock cmpxchg [ecx], edx	;if(eax == *x) *x = edx, else eax = *x
	jz done_4				;*x was modified. It's new value is in edx
	mov edx, eax			;copy that new value to edx, lets try again
	jmp try_again_4
done_4:
	xchg edx, eax			;edx has the value (~*x), so swap edx and eax
	ret

;int SST_Atomic_Exchange(volatile int* x, int value)
;void* SST_Atomic_ExchangePtr(volatile void** x, void* value)
_SST_Atomic_Exchange:
 SST_Atomic_Exchange:
_SST_Atomic_ExchangePtr:
 SST_Atomic_ExchangePtr:
	mov edx, [esp+4]
	mov eax, [esp+8]
	
	lock xchg [edx], eax
	ret
	
;int SST_Atomic_ExchangeAdd(volatile int* x, int value);
;void* SST_Atomic_ExchangeAddPtr(volatile void** x, int value);
_SST_Atomic_ExchangeAdd:
 SST_Atomic_ExchangeAdd:
_SST_Atomic_ExchangeAddPtr:
 SST_Atomic_ExchangeAddPtr:
	mov edx, [esp+4]
	mov eax, [esp+8]
	
	lock xadd [edx],eax		;Save [edx] to temp, store [edx]+eax into [edx], save
	ret
	
;int SST_Atomic_CAS(int* dest, int compare, int newValue);
;void* SST_Atomic_CASPtr(void** dest, void* compare, void* newValue);
_SST_Atomic_CAS:
 SST_Atomic_CAS:
_SST_Atomic_CASPtr:
 SST_Atomic_CASPtr:
	mov edx, [esp+4]	;edx <- dest
	mov eax, [esp+8]	;eax <- compare
	mov ecx, [esp+12]	;ecx <- newValue
	
	lock cmpxchg [edx], ecx 	;compare [edx] with eax | swap with ecx if equal, else store [edx] into eax
	ret

; int SST_Atomic_LoadAcquire(const volatile int* src);	
; void* SST_Atomic_LoadAcquirePtr(const volatile void** src);
; NOTE: x86 has strong memory ordering, thus no barrier is necessary, except for compiler barrier to reordering instructions
_SST_Atomic_LoadAcquire:
 SST_Atomic_LoadAcquire:
_SST_Atomic_LoadAcquirePtr:
 SST_Atomic_LoadAcquirePtr:
	mov eax, [esp+4]		;eax = ptr
	mov eax, [eax]			;eax = *ptr
	ret

; void SST_Atomic_StoreRelease(volatile int* dest, int value);
; void SST_Atomic_StoreReleasePtr(volatile void** dest, void* value);
; NOTE: x86 has strong memory ordering, thus no barrier is necessary, except for compiler barrier to reordering instructions
_SST_Atomic_StoreRelease:
 SST_Atomic_StoreRelease:
_SST_Atomic_StoreReleasePtr:
 SST_Atomic_StoreReleasePtr:
	mov edx, [esp+4]		;edx = dest
	mov eax, [esp+8]		;eax = value
	mov [edx], eax
	ret
