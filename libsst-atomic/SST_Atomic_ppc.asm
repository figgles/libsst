/*
	SST_Atomic_ppc.asm
	Author: Patrick Baggett
	Created: 7/20/2012

	Purpose:
	
	32-bit assembly for Power Architecture processors.
	Assembles with GNU as.

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.
*/

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

/*
	This is for 32-bit Power arch, so the pointer versions are the same as
	the non-pointer versions.
	These are all leaf functions, so r3-r11 are legal to use.
*/

/* void SST_Atomic_Add(volatile int* x, int value) */
/* void SST_Atomic_AddPtr(volatile void* x, int value) */
/* void* SST_Atomic_AddPtrReturn(volatile void* x, int value) */
/* int   SST_Atomic_AddReturn(volatile int* x, int value) */
SST_Atomic_Add:
SST_Atomic_AddPtr:
SST_Atomic_AddReturn:
SST_Atomic_AddPtrReturn:
	mr r5, r3	/* r5 = x */
	sync		/* mem barrier */

1:
	lwarx r6, 0, r5		/* r6 = *x */
	add r3, r6, r4		/* return_value = r6 + value */
	add r6, r6, r4		/* r6 += value */
	stwcx. r6, 0, r5	/* try { *x = sum } */ 
	bne- 1b			/* retry? */
	
	isync			/* order future L/S instructions */
	blr


/* void SST_Atomic_And(volatile int* x, int value) */
/* int   SST_Atomic_AndReturn(volatile int* x, int value) */
SST_Atomic_And:
SST_Atomic_AndReturn:
	mr r5, r3	/* r5 = x */
	sync		/* mem barrier */

1:
	lwarx r6, 0, r5		/* r6 = *x */
	and r3, r6, r4		/* return_value = r6 & value */
	and r6, r6, r4		/* r6 &= value */
	stwcx. r6, 0, r5	/* try { *x = result } */ 
	bne- 1b			/* retry? */
	
	isync			/* order future L/S instructions */
	blr



/* void SST_Atomic_Or(volatile int* x, int value) */
/* int   SST_Atomic_OrReturn(volatile int* x, int value) */
SST_Atomic_Or:
SST_Atomic_OrReturn:
	mr r5, r3	/* r5 = x */
	sync		/* mem barrier */

1:
	lwarx r6, 0, r5		/* r6 = *x */
	or r3, r6, r4		/* return_value = r6 | value */
	or  r6, r6, r4		/* r6 |= value */
	stwcx. r6, 0, r5	/* try { *x = result } */ 
	bne- 1b			/* retry? */
	
	isync			/* order future L/S instructions */
	blr

/* void SST_Atomic_Xor(volatile int* x, int value) */
/* int   SST_Atomic_XorReturn(volatile int* x, int value) */
SST_Atomic_Xor:
SST_Atomic_XorReturn:
	mr r5, r3	/* r5 = x */
	sync		/* mem barrier */

1:
	lwarx r6, 0, r5		/* r6 = *x */
	xor r3, r6, r4		/* return_value = r6 ^ value */
	xor r6, r6, r4		/* r6 ^= value */
	stwcx. r6, 0, r5	/* try { *x = result } */ 
	bne- 1b			/* retry? */
	
	isync			/* order future L/S instructions */
	blr

/* void SST_Atomic_Not(volatile int* x) */
/* int   SST_Atomic_NotReturn(volatile int* x) */
SST_Atomic_Not:
SST_Atomic_NotReturn:
	mr r4, r3	/* r4 = x */
	sync		/* mem barrier */

1:
	lwarx r3, 0, r4		/* r3 = *x */
	nor r3, r3, r3		/* r5 = ~r5 */
	stwcx. r3, 0, r4	/* try { *x = sum } */ 
	bne- 1b			/* retry? */
	
	isync			/* order future L/S instructions */
	blr

/* int SST_Atomic_Exchange(volatile int* x, int value) */
/* int SST_Atomic_ExchangePtr(volatile void** x, void* value) */
SST_Atomic_Exchange:
SST_Atomic_ExchangePtr:
	mr r5, r3	/* r5 = x */
	sync		/* mem barrier */

1:
	lwarx r3, 0, r5		/* try { return_value = *x */
	stwcx. r4, 0, r5	/*       *x = value } */ 
	bne- 1b				/* retry? */
	
	isync				/* order future L/S instructions */
	blr

/* int SST_Atomic_CAS(volatile int* dest, int compare, int newValue) */
SST_Atomic_CAS:
SST_Atomic_CASPtr:
	mr r6, r3	/* r6 = dest */
	sync		/* mem barrier */

1:
	lwarx r3, 0, r6		/* return_value = *dest */
	cmpw r4, r3			/* if(return_value != compare) */
	bne- 2f				/*     return return_value; */
	stwcx. r5, 0, r6	/* else { *dest = newValue } */ 
	bne- 1b				/* retry? */
	isync				/* order future L/S instructions */
2:
	blr

/* void* SST_Atomic_ExchangeAdd(volatile void* x, int value) */
/* int   SST_Atomic_(volatile int* x, int value) */
SST_Atomic_ExchangeAdd:
SST_Atomic_ExchangeAddPtr:
	mr r5, r3	/* r5 = x */
	sync		/* mem barrier */

1:
	lwarx r3, 0, r5		/* r3 = *x */
	add r6, r3, r4		/* r6 = *x + value */
	stwcx. r6, 0, r5	/* try { *x = sum } */ 
	bne- 1b			/* retry? */
	
	isync			/* order future L/S instructions */
	blr

/* int SST_Atomic_LoadAcquire(const volatile int* src);	*/
/* void* SST_Atomic_LoadAcquirePtr(const volatile void** src); */
SST_Atomic_LoadAcquire:
SST_Atomic_LoadAcquirePtr:
	lw r3, 0, r3
	isync				/* order future L/S instructions */
	blr
		
/* void SST_Atomic_StoreRelease(volatile int* dest, int value); */
/* void SST_Atomic_StoreReleasePtr(volatile void** dest, void* value); */
SST_Atomic_StoreRelease:
SST_Atomic_StoreReleasePtr:
	lwsync
	stw r4, 0, r3
	blr
