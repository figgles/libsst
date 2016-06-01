;	SST_Atomic_x86-64-win64.asm
;	Author: Patrick Baggett <ptbaggett@762studios.com>
;	Created: 12/27/2011
;
;	Purpose:
;
;	64-bit assembly for atomic operations using the Microsoft x64 ABI
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

; Win32 symbol names
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
; Pointers and integers are different sized (64 bits vs 32 bits) so
; each SST_Atomic_XxxxPtr() function uses the full 64-bit registers.
;=======================================================================


;====================================================
; MICROSOFT WIN64 ABI
;====================================================

;void SST_Atomic_Add(volatile int* x, int value)
SST_Atomic_Add:
	lock add [rcx], edx
	ret

;void SST_Atomic_AddPtr(volatile void** x, int value)
SST_Atomic_AddPtr:
	lock add [rcx], rdx
	ret

; void SST_Atomic_And(volatile int* x, int value)
SST_Atomic_And:
	lock and [rcx], edx
	ret

; void SST_Atomic_Or(volatile int* x, int value)
SST_Atomic_Or:
	lock or [rcx], edx
	ret

; void SST_Atomic_Xor(volatile int* x, int value)
SST_Atomic_Xor:
	lock xor [rcx], edx
	ret

; void SST_Atomic_Not(volatile int* x)
SST_Atomic_Not:
	lock not DWORD [rcx]
	ret

; int SST_Atomic_AddReturn(volatile int* x, int value)
SST_Atomic_AddReturn:
	mov eax, edx
	lock xadd [rcx], eax		; eax contains orig value before xadd
	add eax, edx				; now add 'value' (in edx) to get the sum that was stored in *x
	ret

; int SST_Atomic_AddReturn(volatile void** x, int value)
SST_Atomic_AddPtrReturn:
	mov rax, rdx
	lock xadd [rcx], rax		; rax contains orig value before xadd
	add rax, rdx			; now add 'value' (in rdx) to get the sum that was stored in *x
	ret

; int SST_Atomic_AndReturn(volatile int* x, int value)
SST_Atomic_AndReturn:
	mov eax, [rcx]		;eax = *x
	mov r8d, eax		;r8d = *x 
try_again_5:
	and r8d, edx		;r8d <- *x & value

	lock cmpxchg [rcx], r8d	;if(eax == *x) *x = r8d, else eax = *x
	jz done_5				;success -> *x was successfully updated. Its new value is in r8d.
	mov r8d, eax			;failure -> *x was changed previous, new value is in eax. Copy that new value to r8d, let's try again
	jmp try_again_5
done_5:
	mov eax,r8d				;r8d has the value (*x & value), so mov to eax for return value
	ret

SST_Atomic_OrReturn:
	mov eax, [rcx]		;eax = *x
	mov r8d, eax		;r8d = *x 
try_again_6:
	or r8d, edx		;r8d <- *x | value

	lock cmpxchg [rcx], r8d	;if(eax == *x) *x = r8d, else eax = *x
	jz done_6				;success -> *x was successfully updated. Its new value is in r8d.
	mov r8d, eax			;failure -> *x was changed previous, new value is in eax. Copy that new value to r8d, let's try again
	jmp try_again_6
done_6:
	mov eax,r8d				;r8d has the value (*x & value), so mov to eax for return value
	ret

SST_Atomic_XorReturn:
	mov eax, [rcx]		;eax = *x
	mov r8d, eax		;r8d = *x 
try_again_7:
	xor r8d, edx		;r8d <- *x ^ value

	lock cmpxchg [rcx], r8d	;if(eax == *x) *x = r8d, else eax = *x
	jz done_7				;success -> *x was successfully updated. Its new value is in r8d.
	mov r8d, eax			;failure -> *x was changed previous, new value is in eax. Copy that new value to r8d, let's try again
	jmp try_again_7
done_7:
	mov eax,r8d				;r8d has the value (*x & value), so mov to eax for return value
	ret

; int SST_Atomic_NotReturn(volatile int* x)
SST_Atomic_NotReturn:
	mov eax, [rcx]		;eax = *x
	mov r8d, eax		;r8d = *x 
try_again_8:
	not r8d				;r8d <- ~*x

	lock cmpxchg [rcx], r8d	;if(eax == *x) *x = r8d, else eax = *x
	jz done_8				;success -> *x was successfully updated. Its new value is in r8d.
	mov r8d, eax			;failure -> *x was changed previous, new value is in eax. Copy that new value to r8d, let's try again
	jmp try_again_8
done_8:
	mov eax,r8d				;r8d has the value (*x & value), so mov to eax for return value
	ret

;int SST_Atomic_Exchange(volatile int* x, int value)
SST_Atomic_Exchange:
	lock xchg [rcx], edx
	mov eax, edx
	ret

;void* SST_Atomic_ExchangePtr(volatile void** x, void* value)
SST_Atomic_ExchangePtr:
	lock xchg [rcx], rdx
	mov rax, rdx
	ret
	
;int SST_Atomic_ExchangeAdd(volatile int* x, int value);
SST_Atomic_ExchangeAdd:
	lock xadd [rcx], edx
	mov eax, edx
	ret

;void* SST_Atomic_ExchangeAddPtr(volatile void** x, int value);
SST_Atomic_ExchangeAddPtr:
	lock xadd [rcx], rdx
	mov rax, rdx
	ret

;int SST_Atomic_CAS(int* dest, int compare, int newValue);
SST_Atomic_CAS:
	;rcx <- dest
	;edx <- compare
	;r8d <- newValue
	mov eax, edx
	lock cmpxchg [rcx], r8d 	;compare [rcx] with eax | swap with r8d if equal, else store [rcx] into eax
	ret

;void* SST_Atomic_CASPtr(void** dest, void* compare, void* newValue);
SST_Atomic_CASPtr:
	;rcx <- dest
	;rdx <- compare
	;r8 <- newValue
	mov rax, rdx
	lock cmpxchg [rcx], r8		;compare [rcx] with rax | swap with r8 if equal, else store [rcx] into eax
	ret

; int SST_Atomic_LoadAcquire(const volatile int* src);	
; NOTE: x86 has strong memory ordering, thus no barrier is necessary, except for compiler barrier to reordering instructions
SST_Atomic_LoadAcquire:
	mov eax, [rcx]
	ret
	
; void* SST_Atomic_LoadAcquirePtr(const volatile void** src);
; NOTE: x86 has strong memory ordering, thus no barrier is necessary, except for compiler barrier to reordering instructions
SST_Atomic_LoadAcquirePtr:
	mov rax, [rcx]
	ret
	
; void SST_Atomic_StoreRelease(volatile int* dest, int value);
; NOTE: x86 has strong memory ordering, thus no barrier is necessary, except for compiler barrier to reordering instructions
SST_Atomic_StoreRelease:
	mov [rcx], edx
	ret
	
; void SST_Atomic_StoreReleasePtr(volatile void** dest, void* value);
; NOTE: x86 has strong memory ordering, thus no barrier is necessary, except for compiler barrier to reordering instructions
SST_Atomic_StoreReleasePtr:
	mov [rcx], rdx
	ret

