@	SST_Atomic_arm.asm
@	Author: Patrick Baggett <ptbaggett@762studios.com>
@	Created: 6/21/2012
@
@	Purpose:
@
@	32-bit assembly for atomic operations for ARMv6+ CPUs
@	Assembles with GNU as 
@
@	License:
@
@	This program is free software. It comes without any warranty, to
@	the extent permitted by applicable law. You can redistribute it
@	and/or modify it under the terms of the Do What The Fuck You Want
@	To Public License, Version 2, as published by Sam Hocevar. See
@	http://sam.zoy.org/wtfpl/COPYING for more details.

.text

@Don't use thumb mode, use full ARM mode
.arm 

@ ELF symbol names
.global SST_Atomic_Add
.global SST_Atomic_AddPtr
.global SST_Atomic_And
.global SST_Atomic_Or
.global SST_Atomic_Xor
.global SST_Atomic_Not
.global SST_Atomic_AddReturn
.global SST_Atomic_AddPtrReturn
.global SST_Atomic_AndReturn
.global SST_Atomic_OrReturn
.global SST_Atomic_XorReturn
.global SST_Atomic_NotReturn
.global SST_Atomic_ExchangeAdd
.global SST_Atomic_ExchangeAddPtr
.global SST_Atomic_Exchange
.global SST_Atomic_ExchangePtr
.global SST_Atomic_CAS
.global SST_Atomic_CASPtr
.global SST_Atomic_LoadAcquire
.global SST_Atomic_LoadAcquirePtr
.global SST_Atomic_StoreRelease
.global SST_Atomic_StoreReleasePtr


.type SST_Atomic_Add, %function
.type SST_Atomic_AddPtr, %function
.type SST_Atomic_And, %function
.type SST_Atomic_Or, %function
.type SST_Atomic_Xor, %function
.type SST_Atomic_Not, %function
.type SST_Atomic_AddReturn, %function
.type SST_Atomic_AddPtrReturn, %function
.type SST_Atomic_AndReturn, %function
.type SST_Atomic_OrReturn, %function
.type SST_Atomic_XorReturn, %function
.type SST_Atomic_NotReturn, %function
.type SST_Atomic_ExchangeAdd, %function
.type SST_Atomic_ExchangeAddPtr, %function
.type SST_Atomic_Exchange, %function
.type SST_Atomic_ExchangePtr, %function
.type SST_Atomic_CAS, %function
.type SST_Atomic_CASPtr, %function
.type SST_Atomic_LoadAcquire, %function
.type SST_Atomic_LoadAcquirePtr, %function
.type SST_Atomic_StoreRelease, %function
.type SST_Atomic_StoreReleasePtr, %function

@=======================================================================
@ Since pointers and integers are the same size on GCC, many of the
@ integer/pointer code paths are the same. This of course only holds true
@ for 32-bit compiles on ARM, which is exactly this file.
@=======================================================================

@ I've merged the Atomic_XXX and Atomic_XXXReturn functions. The difference
@ is 1 mov instruction -- not really worth making separate functions.

@ void SST_Atomic_Add(volatile int* x, int value)
@ void SST_Atomic_AddPtr(volatile void* x, uintptr_t value)
SST_Atomic_Add:
SST_Atomic_AddPtr:
SST_Atomic_AddReturn:
SST_Atomic_AddPtrReturn:
	mcr p15, 0, r0, c7, c10, 5	@ memory barrier
	
	_again8:
	ldrex r2, [r0]				@ r2 <- *x
	add r2, r2, r1				@ r2 += value
	strex r3, r2, [r0]			@ try { *x <- r2 }
	teq r3, #0					@ success?
	bne _again8					@ No, reload and retry
	
	mcr p15, 0, r0, c7, c10, 5	@ memory barrier
	mov r0, r2					@ Setup return value 
	bx lr						@ Return

@ void SST_Atomic_And(volatile int* x, int value)
SST_Atomic_And:
SST_Atomic_AndReturn:
	mcr p15, 0, r0, c7, c10, 5	@ memory barrier
	
	_again7:
	ldrex r2, [r0]				@ r2 <- *x
	and r2, r2, r1				@ r2 &= value
	strex r3, r2, [r0]			@ try { *x <- r2 }
	teq r3, #0					@ success?
	bne _again7					@ No, reload and retry
	
	mcr p15, 0, r0, c7, c10, 5	@ memory barrier
	mov r0, r2					@ Setup return value 
	bx lr						@ Return

@ void SST_Atomic_Or(volatile int* x, int value)
SST_Atomic_Or:
SST_Atomic_OrReturn:
	mcr p15, 0, r0, c7, c10, 5	@ memory barrier
	
	_again6:
	ldrex r2, [r0]				@ r2 <- *x
	orr r2, r2, r1				@ r2 |= value
	strex r3, r2, [r0]			@ try { *x <- r2 }
	teq r3, #0					@ success?
	bne _again6					@ No, reload and retry
	
	mcr p15, 0, r0, c7, c10, 5	@ memory barrier
	mov r0, r2					@ Setup return value 
	bx lr						@ Return

@ void SST_Atomic_Xor(volatile int* x, int value)
SST_Atomic_Xor:
SST_Atomic_XorReturn:
	mcr p15, 0, r0, c7, c10, 5	@ memory barrier
	
	_again5:
	ldrex r2, [r0]				@ r2 <- *x
	eor r2, r2, r1				@ r2 ^= value
	strex r3, r2, [r0]			@ try { *x <- r2 }
	teq r3, #0					@ success?
	bne _again5					@ No, reload and retry
	
	mcr p15, 0, r0, c7, c10, 5	@ memory barrier
	mov r0, r2					@ Setup return value 
	bx lr						@ Return

@ void SST_Atomic_Not(volatile int* x)
SST_Atomic_Not:
SST_Atomic_NotReturn:
	mcr p15, 0, r0, c7, c10, 5	@ memory barrier
	
	_again4:
	ldrex r2, [r0]				@ r2 <- *x
	mvn r2, r2		 			@ r2 = ~value
	strex r3, r2, [r0]			@ try { *x <- r2 }
	teq r3, #0					@ success?
	bne _again4					@ No, reload and retry
	
	mcr p15, 0, r0, c7, c10, 5	@ memory barrier
	mov r0, r2					@ Setup return value 
	bx lr						@ Return


@ int SST_Atomic_Exchange(volatile int* x, int value)
@ void* SST_Atomic_ExchangePtr(volatile void** x, void* value)
SST_Atomic_Exchange:
SST_Atomic_ExchangePtr:
	mcr p15, 0, r0, c7, c10, 5	@ memory barrier

	_again3:
	ldrex r2, [r0]				@ r2 <- *x
	strex r3, r1, [r0]			@ try { *x <- r1 }
	teq r3, #0					@ success?
	bne _again3					@ No, reload and retry
	
	mcr p15, 0, r0, c7, c10, 5	@ memory barrier
	mov r0, r2					@ Setup return value 
	bx lr						@ Return
	
@ int SST_Atomic_ExchangeAdd(volatile int* x, int value);
@ void* SST_Atomic_ExchangeAddPtr(volatile void** x, int value);
SST_Atomic_ExchangeAdd:
SST_Atomic_ExchangeAddPtr:
	mcr p15, 0, r0, c7, c10, 5	@ memory barrier
	push {r4}

	_again2:
	ldrex r2, [r0]				@ r2 <- *x
	mov r4, r2					@ r4 <- *x
	add r2, r2, r1				@ r2 += value
	strex r3, r2, [r0]			@ try { *x <- r2 }
	teq r3, #0					@ success?
	bne _again2				 	@ No, reload and retry

	mcr p15, 0, r0, c7, c10, 5	@ memory barrier
	mov r0, r4					@ Setup return value as the old value of *x
	pop {r4}
	bx lr						@ Return

	
@ int SST_Atomic_CAS(int* dest, int compare, int newValue);
@ void* SST_Atomic_CASPtr(void** dest, void* compare, void* newValue);
SST_Atomic_CAS:
SST_Atomic_CASPtr:
	mcr p15, 0, r0, c7, c10, 5	@ memory barrier
	push {r4}
	mov r4, #0

	_again1:
	ldrex r3, [r0]				@ r3 <- *dest
	teq r3, r1					@ if(r3 == compare) {
	strexeq r4, r2, [r0]		@     try { *dest <- newValue } }
	teq r4, #0					@ success?
	bne _again1					@ No, reload and retry

	mcr p15, 0, r0, c7, c10, 5	@ memory barrier
	mov r0, r3					@ Setup return value as the value of *dest
	pop {r4}
	bx lr						@ Return

	

SST_Atomic_LoadAcquire:
SST_Atomic_LoadAcquirePtr:
	ldr r0, [r0]
	mcr p15, 0, r0, c7, c10, 5	@ memory barrier
	bx lr

SST_Atomic_StoreRelease:
SST_Atomic_StoreReleasePtr:	
	mcr p15, 0, r0, c7, c10, 5	@ memory barrier
	str r1, [r0]
	bx lr
