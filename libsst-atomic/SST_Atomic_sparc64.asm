/*
	SST_Atomic_sparc64.asm
	Author: Patrick Baggett
	Created: 4/3/2012

	Purpose:
	
	64-bit assembly for SPARCv9 processors 
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
	This is for 64-bit SPARC code, so the pointer versions are different 
	from the non-pointer versions.
	These are all leaf functions, so %o0-%o5 and %g1 are legal to use.

	On TSO model, only "membar #StoreLoad" is a true barrier, the
	rest are no-ops. This code assumes RMO. 
*/

/* void SST_Atomic_Add(volatile int* x, int value) */
/* int   SST_Atomic_AddReturn(volatile int* x, int value) */
SST_Atomic_Add:
SST_Atomic_AddReturn:
	ld [%o0], %o4		/* o4 = *x */
	1:
	add %o1, %o4, %o5	/* o5 = *x + value */
	cas [%o0], %o4, %o5	/* compare and swap */

	cmp %o4, %o5		/* compare what was in mem with our value */	
	bne,a,pn %icc, 1b	/* not the same -> try again. */
	mov %o5, %o4		/* restore o4, it should contain *x */
	
	retl			/* Success */
	add %o1, %o5, %o0	/* return sum */

/******************************************************************************/

/* void SST_Atomic_AddPtr(volatile void* x, int value) */
/* void* SST_Atomic_AddPtrReturn(volatile void* x, int value) */
SST_Atomic_AddPtr:
SST_Atomic_AddPtrReturn:
	ldx [%o0], %o4		/* o4 = *x */
	1:
	add %o1, %o4, %o5	/* o5 = *x + value */
	casx [%o0], %o4, %o5	/* compare and swap */

	cmp %o4, %o5		/* compare what was in mem with our value */	
	bne,a,pn %xcc, 1b	/* not the same -> try again. */
	mov %o5, %o4		/* restore o4, it should contain *x */
	
	retl			/* Success */
	add %o1, %o5, %o0	/* return sum */

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
	
	retl			/* Success */
	not %o4, %o0		/* could do nop, but delay slot is free.
				then we can make the "Return" versions 
				use the same code path */

/* int SST_Atomic_Exchange(volatile int* x, int value) */
SST_Atomic_Exchange:
	ld [%o0], %o4		/* o4 = *x */
	1:
	mov %o1, %o5		/* o5 = value */
	cas [%o0], %o4, %o5	/* compare and swap */

	cmp %o4, %o5		/* compare what was in mem with our value */	
	bne,a,pn %icc, 1b	/* not the same -> try again. */
	mov %o5, %o4		/* restore o4, it should contain *x */
	
	membar #StoreStore | #LoadStore	 /* Ensure ordering */

	retl			/* Success */
	mov %o4, %o0

/* int SST_Atomic_ExchangePtr(volatile void** x, void* value) */
SST_Atomic_ExchangePtr:
	ldx [%o0], %o4		/* o4 = *x */
	1:
	mov %o1, %o5		/* o5 = value */
	casx [%o0], %o4, %o5	/* compare and swap */

	cmp %o4, %o5		/* compare what was in mem with our value */	
	bne,a,pn %xcc, 1b	/* not the same -> try again. */
	mov %o5, %o4		/* restore o4, it should contain *x */
	
	membar #StoreStore | #LoadStore	 /* Ensure ordering */

	retl			/* Success */
	mov %o4, %o0

/* int SST_Atomic_CAS(volatile int* dest, int compare, int newValue) */
SST_Atomic_CAS:
	cas [%o0], %o1, %o2
	retl
	mov %o2, %o0

SST_Atomic_CASPtr:
	casx [%o0], %o1, %o2
	retl
	mov %o2, %o0

/* void* SST_Atomic_ExchangeAdd(volatile int* x, int value) */
SST_Atomic_ExchangeAdd:
	ld [%o0], %o4		/* o4 = *x */
	1:
	add %o1, %o4, %o5	/* o5 = *x + value */
	cas [%o0], %o4, %o5	/* compare and swap */

	cmp %o4, %o5		/* compare what was in mem with our value */	
	bne,a,pn %icc, 1b	/* not the same -> try again. */
	mov %o5, %o4		/* restore o4, it should contain *x */
	
	retl			/* Success */
	mov %o4, %o0		/* %o4 = value before add */


SST_Atomic_ExchangeAddPtr:
	ldx [%o0], %o4		/* o4 = *x */
	1:
	add %o1, %o4, %o5	/* o5 = *x + value */
	casx [%o0], %o4, %o5	/* compare and swap */

	cmp %o4, %o5		/* compare what was in mem with our value */	
	bne,a,pn %xcc, 1b	/* not the same -> try again. */
	mov %o5, %o4		/* restore o4, it should contain *x */
	
	retl			/* Success */
	mov %o4, %o0		/* %o4 = value before add */
	
/* int SST_Atomic_LoadAcquire(const volatile int* src);	*/
SST_Atomic_LoadAcquire:
	ld [%o0], %o0
	membar #LoadStore | #LoadLoad
	retl
	nop

/* void* SST_Atomic_LoadAcquirePtr(const volatile void** src); */
SST_Atomic_LoadAcquirePtr:
	ldx [%o0], %o0
	membar #LoadStore | #LoadLoad
	retl
	nop
		
/* void SST_Atomic_StoreRelease(volatile int* dest, int value); */
SST_Atomic_StoreRelease:
	membar #LoadStore | #StoreStore
	retl
	st %o1, [%o0]

/* void SST_Atomic_StoreReleasePtr(volatile void** dest, void* value); */
SST_Atomic_StoreReleasePtr:
	membar #LoadStore | #StoreStore
	retl
	stx %o1, [%o0]
