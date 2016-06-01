;	SST_Atomic_x86-64.asm
;	Author: Patrick Baggett <ptb1@762studios.com>
;	Created: 12/20/2011
;
;	Purpose:
;
;	64-bit assembly for atomic operations using the SysV x86-64 ABI
;	Assembles with YASM 1.1/NASM 2.0+
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
;rdi		| Not used	| 1st arg
;rsi		| Not used	| 2nd arg
;rcx		| 1st arg	| 3rd arg
;rdx		| 2nd arg	| 4th arg
;r8			| 3rd arg	| 5th arg
;r9			| 4th arg	| 6th arg

[bits 64]
[segment .text]

; ELF symbol names (UNIX)
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


; Mach-O symbol names (MacOS X)
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


;=======================================================================
; Pointers and integers are different sized (64 bits vs 32 bits) so
; each SST_Atomic_XxxxPtr() function uses the full 64-bit registers.
;=======================================================================

;====================================================
; UNIX/ELF ABI
;====================================================

;void SST_Atomic_Add(volatile int* x, int value)
 SST_Atomic_Add:
_SST_Atomic_Add:
	lock add [rdi], esi
	ret

;void SST_Atomic_AddPtr(volatile void** x, int value)
 SST_Atomic_AddPtr:
_SST_Atomic_AddPtr:
	lock add [rdi], rsi
	ret

; void SST_Atomic_And(volatile int* x, int value)
 SST_Atomic_And:
_SST_Atomic_And:
	lock and [rdi], esi
	ret

; void SST_Atomic_Or(volatile int* x, int value)
 SST_Atomic_Or:
_SST_Atomic_Or:
	lock or [rdi], esi
	ret

; void SST_Atomic_Xor(volatile int* x, int value)
 SST_Atomic_Xor:
_SST_Atomic_Xor:
	lock xor [rdi], esi
	ret

; void SST_Atomic_Not(volatile int* x)
 SST_Atomic_Not:
_SST_Atomic_Not:
	lock not DWORD [rdi]
	ret

; int SST_Atomic_AddReturn(volatile int* x, int value)
 SST_Atomic_AddReturn:
_SST_Atomic_AddReturn:
	mov eax, esi
	lock xadd [rdi], eax		; eax contains orig value before xadd
	add eax, esi			; now add 'value' (in esi) to get the sum that was stored in *x
	ret

; int SST_Atomic_AddReturn(volatile void** x, int value)
 SST_Atomic_AddPtrReturn:
_SST_Atomic_AddPtrReturn:
	mov rax, rsi
	lock xadd [rdi], rax		; rax contains orig value before xadd
	add rax, rsi			; now add 'value' (in rsi) to get the sum that was stored in *x
	ret

; int SST_Atomic_AndReturn(volatile int* x, int value)
 SST_Atomic_AndReturn:
_SST_Atomic_AndReturn:
	mov eax, [rdi]	  ;eax = *x
	mov edx, eax	  ;edx = *x 
try_again_1:
	and edx, esi	  ;edx <- *x & value

	lock cmpxchg [rdi], edx	;if(eax == *x) *x = edx, else eax = *x
	jz done_1				;success -> *x was successfully updated. It's new value is in edx
	mov edx, eax			;failure -> *x was changed previous, new value is in eax. Copy that new value to edx, lets try again
	jmp try_again_1
done_1:
	mov eax,edx				;edx has the value (*x & value), so mov to eax for return value
	ret	

 SST_Atomic_OrReturn:
_SST_Atomic_OrReturn:
	mov eax, [rdi]	  ;eax = *x
	mov edx, eax	  ;edx = *x 
try_again_2:
	or edx, esi	  ;edx <- *x | value

	lock cmpxchg [rdi], edx	;if(eax == *x) *x = edx, else eax = *x
	jz done_2				;success -> *x was successfully updated. It's new value is in edx
	mov edx, eax			;failure -> *x was changed previous, new value is in eax. Copy that new value to edx, lets try again
	jmp try_again_2
done_2:
	mov eax,edx				;edx has the value (*x | value), so mov to eax for return value
	ret	

 SST_Atomic_XorReturn:
_SST_Atomic_XorReturn:
	mov eax, [rdi]	  ;eax = *x
	mov edx, eax	  ;edx = *x 
try_again_3:
	xor edx, esi	  ;edx <- *x ^ value

	lock cmpxchg [rdi], edx	;if(eax == *x) *x = edx, else eax = *x
	jz done_3				;success -> *x was successfully updated. It's new value is in edx
	mov edx, eax			;failure -> *x was changed previous, new value is in eax. Copy that new value to edx, lets try again
	jmp try_again_3
done_3:
	mov eax,edx				;edx has the value (*x ^ value), so mov to eax for return value
	ret	


; int SST_Atomic_NotReturn(volatile int* x)
 SST_Atomic_NotReturn:
_SST_Atomic_NotReturn:
	mov eax, [rdi]	  ;eax = *x
	mov edx, eax	  ;edx = *x 
try_again_4:
	not edx

	lock cmpxchg [rdi], edx	;if(eax == *x) *x = edx, else eax = *x
	jz done_4				;success -> *x was successfully updated. It's new value is in edx
	mov edx, eax			;failure -> *x was changed previous, new value is in eax. Copy that new value to edx, lets try again
	jmp try_again_4
done_4:
	mov eax,edx				;edx has the value (~*x), so mov to eax for return value
	ret	

;int SST_Atomic_Exchange(volatile int* x, int value)
 SST_Atomic_Exchange:
_SST_Atomic_Exchange:
	lock xchg [rdi], esi
	mov eax, esi
	ret

;void* SST_Atomic_ExchangePtr(volatile void** x, void* value)
 SST_Atomic_ExchangePtr:
_SST_Atomic_ExchangePtr:
	lock xchg [rdi], rsi
	mov rax, rsi
	ret
	
;int SST_Atomic_ExchangeAdd(volatile int* x, int value);
 SST_Atomic_ExchangeAdd:
_SST_Atomic_ExchangeAdd:
	lock xadd [rdi],esi
	mov eax, esi
	ret

;void* SST_Atomic_ExchangeAddPtr(volatile void** x, int value);
 SST_Atomic_ExchangeAddPtr:
_SST_Atomic_ExchangeAddPtr:
	lock xadd [rdi],rsi
	mov rax, rsi
	ret

;int SST_Atomic_CAS(int* dest, int compare, int newValue);
 SST_Atomic_CAS:
_SST_Atomic_CAS:
	;rdi <- dest
	;rsi <- compare
	;rdx <- newValue
	mov eax, esi
	lock cmpxchg [rdi], edx 	;compare [rdi] with eax | swap with edx if equal, else store [rdi] into eax
	ret

;void* SST_Atomic_CASPtr(void** dest, void* compare, void* newValue);
 SST_Atomic_CASPtr:
_SST_Atomic_CASPtr:
	;rdi <- dest
	;rsi <- compare
	;rdx <- newValue
	mov rax, rsi
	lock cmpxchg [rdi], rdx 	;compare [rdi] with rax | swap with rdx if equal, else store [rdi] into rax
	ret



; int SST_Atomic_LoadAcquire(const volatile int* src);	
; NOTE: x86 has strong memory ordering, thus no barrier is necessary, except for compiler barrier to reordering instructions
 SST_Atomic_LoadAcquire:
_SST_Atomic_LoadAcquire:
	mov eax, [rdi]
	ret
	
; void* SST_Atomic_LoadAcquirePtr(const volatile void** src);
; NOTE: x86 has strong memory ordering, thus no barrier is necessary, except for compiler barrier to reordering instructions
 SST_Atomic_LoadAcquirePtr:
_SST_Atomic_LoadAcquirePtr:
 mov rax, [rdi]
	ret
	
; void SST_Atomic_StoreRelease(volatile int* dest, int value);
; NOTE: x86 has strong memory ordering, thus no barrier is necessary, except for compiler barrier to reordering instructions
 SST_Atomic_StoreRelease:
_SST_Atomic_StoreRelease:
	mov [rdi], esi
	ret
	
; void SST_Atomic_StoreReleasePtr(volatile void** dest, void* value);
; NOTE: x86 has strong memory ordering, thus no barrier is necessary, except for compiler barrier to reordering instructions
 SST_Atomic_StoreReleasePtr:
_SST_Atomic_StoreReleasePtr:
	mov [rdi], rsi
	ret
