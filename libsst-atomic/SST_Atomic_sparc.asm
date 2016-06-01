/*
	SST_Atomic_sparc.asm
	Author: Patrick Baggett
	Created: 12/28/2011

	Purpose:
	
	32-bit assembly for SPARCv9 processors (aka v8+)
	Older SPARC CPUs (e.g. sun4m) are not supported.
	Assembles with Solaris assembler or GNU as.

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
	This is for 32-bit SPARC code, so the pointer versions are the same as
	the non-pointer versions.
	These are all leaf functions, so %o0-%o5 and %g1 are legal to use.
*/

/* void SST_Atomic_Add(volatile int* x, int value) */
/* void SST_Atomic_AddPtr(volatile void* x, int value) */
/* void* SST_Atomic_AddPtrReturn(volatile void* x, int value) */
/* int   SST_Atomic_AddReturn(volatile int* x, int value) */
SST_Atomic_Add:
SST_Atomic_AddPtr:
SST_Atomic_AddReturn:
SST_Atomic_AddPtrReturn:
	ld [%o0], %o4		/* o4 = *x */
	1:
	add %o1, %o4, %o5	/* o5 = *x + value */
	cas [%o0], %o4, %o5	/* compare and swap */

	cmp %o4, %o5		/* compare what was in mem with our value */	
	bne,a,pn %icc, 1b	/* not the same -> try again. */
	mov %o5, %o4		/* restore o4, it should contain *x */
	
	/* membar #StoreStore | #StoreLoad	 Force stores to complete before loads */

	retl			/* Success */
	add %o1, %o5, %o0	/* could do nop, but delay slot is free.
				then we can make the "Return" versions 
				use the same code path */



/* void SST_Atomic_And(volatile int* x, int value) */
/* int   SST_Atomic_AndReturn(volatile int* x, int value) */
SST_Atomic_And:
SST_Atomic_AndReturn:
	ld [%o0], %o4		/* o4 = *x */
	1:
	and %o1, %o4, %o5	/* o5 = *x & value */
	cas [%o0], %o4, %o5	/* compare and swap */

	cmp %o4, %o5		/* compare what was in mem with our value */	
	bne,a,pn %icc, 1b	/* not the same -> try again. */
	mov %o5, %o4		/* restore o4, it should contain *x */
	
	/* membar #StoreStore | #StoreLoad	 Force stores to complete before loads */

	retl			/* Success */
	and %o1, %o5, %o0	/* could do nop, but delay slot is free.
				then we can make the "Return" versions 
				use the same code path */



/* void SST_Atomic_Or(volatile int* x, int value) */
/* int   SST_Atomic_OrReturn(volatile int* x, int value) */
SST_Atomic_Or:
SST_Atomic_OrReturn:
	ld [%o0], %o4		/* o4 = *x */
	1:
	or %o1, %o4, %o5	/* o5 = *x | value */
	cas [%o0], %o4, %o5	/* compare and swap */

	cmp %o4, %o5		/* compare what was in mem with our value */	
	bne,a,pn %icc, 1b	/* not the same -> try again. */
	mov %o5, %o4		/* restore o4, it should contain *x */
	
	/* membar #StoreStore | #StoreLoad	 Force stores to complete before loads */

	retl			/* Success */
	or %o1, %o5, %o0	/* could do nop, but delay slot is free.
				then we can make the "Return" versions 
				use the same code path */


/* void SST_Atomic_Xor(volatile int* x, int value) */
/* int   SST_Atomic_XorReturn(volatile int* x, int value) */
SST_Atomic_Xor:
SST_Atomic_XorReturn:
	ld [%o0], %o4		/* o4 = *x */
	1:
	xor %o1, %o4, %o5	/* o5 = *x | value */
	cas [%o0], %o4, %o5	/* compare and swap */

	cmp %o4, %o5		/* compare what was in mem with our value */	
	bne,a,pn %icc, 1b	/* not the same -> try again. */
	mov %o5, %o4		/* restore o4, it should contain *x */
	
	/* membar #StoreStore | #StoreLoad	 Force stores to complete before loads */

	retl			/* Success */
	xor %o1, %o5, %o0	/* could do nop, but delay slot is free.
				then we can make the "Return" versions 
				use the same code path */

/* void SST_Atomic_Not(volatile int* x) */
/* int   SST_Atomic_NotReturn(volatile int* x) */
SST_Atomic_Not:
SST_Atomic_NotReturn:
	ld [%o0], %o4		/* o4 = *x */
	1:
	not %o4, %o5	/* o5 = ~*x */
	cas [%o0], %o4, %o5	/* compare and swap */

	cmp %o4, %o5		/* compare what was in mem with our value */	
	bne,a,pn %icc, 1b	/* not the same -> try again. */
	mov %o5, %o4		/* restore o4, it should contain *x */
	
	/* membar #StoreStore | #StoreLoad	 Force stores to complete before loads */

	retl			/* Success */
	not %o4, %o0		/* could do nop, but delay slot is free.
				then we can make the "Return" versions 
				use the same code path */

/* int SST_Atomic_Exchange(volatile int* x, int value) */
/* int SST_Atomic_ExchangePtr(volatile void** x, void* value) */
SST_Atomic_Exchange:
SST_Atomic_ExchangePtr:
	swap [%o0], %o1	/* swap(*x, value) */
	retl
	mov %o1, %o0	/* move return value to %o0 */
/* NOTE: SPARCv9 manual calls the "swap" instruction deprecated. I don't
   understand why. "cas" could fail, when really, we don't care if the 
   value changed, we care about ensuring that only 1 thread gets that value,
   i.e. if 3 threads execute "swap" at the same time using 3 different values,
   it is undefined which value is the final value, but each thread gets a
   different value (thus, it is atomic).
*/

/* int SST_Atomic_CAS(volatile int* dest, int compare, int newValue) */
SST_Atomic_CAS:
SST_Atomic_CASPtr:
	cas [%o0], %o1, %o2
	retl
	mov %o2, %o0

/* void* SST_Atomic_ExchangeAdd(volatile void* x, int value) */
/* int   SST_Atomic_(volatile int* x, int value) */
SST_Atomic_ExchangeAdd:
SST_Atomic_ExchangeAddPtr:
	ld [%o0], %o4		/* o4 = *x */
	1:
	add %o1, %o4, %o5	/* o5 = *x + value */
	cas [%o0], %o4, %o5	/* compare and swap */

	cmp %o4, %o5		/* compare what was in mem with our value */	
	bne,a,pn %icc, 1b	/* not the same -> try again. */
	mov %o5, %o4		/* restore o4, it should contain *x */
	
	/* membar #StoreStore | #StoreLoad	 Force stores to complete before loads */

	retl			/* Success */
	mov %o4, %o0		/* %o4 = value before add */

/* int SST_Atomic_LoadAcquire(const volatile int* src);	*/
/* void* SST_Atomic_LoadAcquirePtr(const volatile void** src); */
SST_Atomic_LoadAcquire:
SST_Atomic_LoadAcquirePtr:
	ld [%o0], %o0
	membar #LoadStore | #LoadLoad
	retl
	nop
		
/* void SST_Atomic_StoreRelease(volatile int* dest, int value); */
/* void SST_Atomic_StoreReleasePtr(volatile void** dest, void* value); */
SST_Atomic_StoreRelease:
SST_Atomic_StoreReleasePtr:
	membar #LoadStore | #StoreStore
	retl
	st %o1, [%o0]
