//	SST_Atomic_ia64.asm
//	Author: Patrick Baggett
//	Created: 4/16/2012
//
//	Purpose:
//	
//	Assembly for Itanium processors (aka ia64)
//	Assembles with Intel ias assembler or GNU as.
//
//	License:
//
//	This program is free software. It comes without any warranty, to
//	the extent permitted by applicable law. You can redistribute it
//	and/or modify it under the terms of the Do What The Fuck You Want
//	To Public License, Version 2, as published by Sam Hocevar. See
//	http://sam.zoy.org/wtfpl/COPYING for more details.


.global SST_Atomic_Add#
.global SST_Atomic_AddReturn#
.global SST_Atomic_AddPtr#
.global SST_Atomic_AddPtrReturn#
.global SST_Atomic_And#
.global SST_Atomic_AndReturn#
.global SST_Atomic_Or#
.global SST_Atomic_OrReturn#
.global SST_Atomic_Xor#
.global SST_Atomic_XorReturn#
.global SST_Atomic_Not#
.global SST_Atomic_NotReturn#
.global SST_Atomic_Exchange#
.global SST_Atomic_ExchangePtr#
.global SST_Atomic_ExchangeAdd#
.global SST_Atomic_ExchangeAddPtr#
.global SST_Atomic_CAS#
.global SST_Atomic_CASPtr#
.global SST_Atomic_LoadAcquire#
.global SST_Atomic_LoadAcquirePtr#
.global SST_Atomic_StoreRelease#
.global SST_Atomic_StoreReleasePtr#
.section .text

.align 32

// SST_Atomic_Add(volatile int* x, int value);
// x = r32, value = r33
SST_Atomic_Add: 
SST_Atomic_AddReturn:
	mf
	ld4.bias r31 = [r32];;		//ensure all memory operations happen first, then load *x into r31
	
	mov ar.ccv = r31			//Set CCV to be *x
	add r8 = r31, r33;;			//generated summed r8 = (*x + value)
 
try_again1:
	cmpxchg4.acq r30 = [r32], r8, ar.ccv;;	//compare [r32] to CCV, exchange with r8 is successful. r30 <- *x
	
	mov ar.ccv = r30						//CCV <- r30
	cmp4.ne.unc p15, p0 = r30, r31			//compare old value in *x with new value in *x
	add r8 = r33, r30						//set up return value r8 = value + *x (new)
	mov r31 = r30							//set up old *x to be the new value if we need to loop again
	(p15) br.cond.dptk.few try_again1;;		//branch if old *x != new *x

	br.ret.sptk.many b0;;


// SST_Atomic_AddPtr(volatile void** x, int value);
// x = r32, value = r33
SST_Atomic_AddPtr: 
SST_Atomic_AddPtrReturn:
	sxt4 r29 = r33;;				//sign extend value to 64-bit quantity
	mf
	ld8.bias r31 = [r32];;		//ensure all memory operations happen first, then load *x into r31
	
	mov ar.ccv = r31			//Set CCV to be *x
	add r8 = r31, r29;;			//generated summed r8 = (*x + value)
 
try_again2:
	cmpxchg8.acq r30 = [r32], r8, ar.ccv;;	//compare [r32] to CCV, exchange with r8 is successful. r30 <- *x
	
	mov ar.ccv = r30						//CCV <- r30
	cmp.ne.unc p15, p0 = r30, r31			//compare old value in *x with new value in *x
	add r8 = r29, r30						//set up return value r8 = value + *x (new)
	mov r31 = r30							//set up old *x to be the new value if we need to loop again
	(p15) br.cond.dptk.few try_again2;;		//branch if old *x != new *x

	br.ret.sptk.many b0;;



// SST_Atomic_And(volatile int* x, int value);
// x = r32, value = r33
SST_Atomic_And: 
SST_Atomic_AndReturn:
	mf
	ld4.bias r31 = [r32];;		//ensure all memory operations happen first, then load *x into r31
	
	mov ar.ccv = r31			//Set CCV to be *x
	and r8 = r31, r33;;			//generated r8 = (*x & value)
 
try_again3:
	cmpxchg4.acq r30 = [r32], r8, ar.ccv;;	//compare [r32] to CCV, exchange with r8 is successful. r30 <- *x
	
	mov ar.ccv = r30						//CCV <- r30
	cmp4.ne.unc p15, p0 = r30, r31			//compare old value in *x with new value in *x
	and r8 = r33, r30						//set up return value r8 = value & *x (new)
	mov r31 = r30							//set up old *x to be the new value if we need to loop again
	(p15) br.cond.dptk.few try_again3;;		//branch if old *x != new *x

	br.ret.sptk.many b0;;


// SST_Atomic_Or(volatile int* x, int value);
// x = r32, value = r33
SST_Atomic_Or: 
SST_Atomic_OrReturn:
	mf
	ld4.bias r31 = [r32];;		//ensure all memory operations happen first, then load *x into r31
	
	mov ar.ccv = r31			//Set CCV to be *x
	or r8 = r31, r33;;			//generated r8 = (*x | value)
 
try_again4:
	cmpxchg4.acq r30 = [r32], r8, ar.ccv;;	//compare [r32] to CCV, exchange with r8 is successful. r30 <- *x
	
	mov ar.ccv = r30						//CCV <- r30
	cmp4.ne.unc p15, p0 = r30, r31			//compare old value in *x with new value in *x
	or r8 = r33, r30						//set up return value r8 = value | *x (new)
	mov r31 = r30							//set up old *x to be the new value if we need to loop again
	(p15) br.cond.dptk.few try_again4;;		//branch if old *x != new *x

	br.ret.sptk.many b0;;


// SST_Atomic_Xor(volatile int* x, int value);
// x = r32, value = r33
SST_Atomic_Xor: 
SST_Atomic_XorReturn:
	mf
	ld4.bias r31 = [r32];;		//ensure all memory operations happen first, then load *x into r31
	
	mov ar.ccv = r31			//Set CCV to be *x
	xor r8 = r31, r33;;			//generated r8 = (*x | value)
 
try_again5:
	cmpxchg4.acq r30 = [r32], r8, ar.ccv;;	//compare [r32] to CCV, exchange with r8 is successful. r30 <- *x
	
	mov ar.ccv = r30						//CCV <- r30
	cmp4.ne.unc p15, p0 = r30, r31			//compare old value in *x with new value in *x
	xor r8 = r33, r30						//set up return value r8 = value & *x (new)
	mov r31 = r30							//set up old *x to be the new value if we need to loop again
	(p15) br.cond.dptk.few try_again5;;		//branch if old *x != new *x

	br.ret.sptk.many b0;;


// SST_Atomic_Not(volatile int* x);
// x = r32
SST_Atomic_Not: 
SST_Atomic_NotReturn:
	mf
	ld4.bias r31 = [r32];;		//ensure all memory operations happen first, then load *x into r31
	
	mov ar.ccv = r31			//Set CCV to be *x
	andcm r8 = -1, r31;;				//generated r8 = ~(*x)
 
try_again6:
	cmpxchg4.acq r30 = [r32], r8, ar.ccv;;	//compare [r32] to CCV, exchange with r8 is successful. r30 <- *x
	
	mov ar.ccv = r30						//CCV <- r30 (in case compare failed)
	cmp4.ne.unc p15, p0 = r30, r31			//compare old value in *x with new value in *x
	andcm r8 = -1, r30						//set up return value r8 = ~*x (new)
	(p15) br.cond.dptk.few try_again6;;		//branch if old *x != new *x

	br.ret.sptk.many b0;;


// SST_Atomic_Exchange(volatile int* x, int value);
// x = r32, value = r33
SST_Atomic_Exchange: 
	mf
	xchg4 r8 = [r32], r33	
	br.ret.sptk.many b0;;


// SST_Atomic_ExchangePtr(volatile int* x, int value);
// x = r32, value = r33
SST_Atomic_ExchangePtr: 
	mf
	xchg8 r8 = [r32], r33	
	br.ret.sptk.many b0;;

// int SST_Atomic_ExchangeAdd(volatile int* x, int value)
SST_Atomic_ExchangeAdd:
	mf
	ld4.bias r31 = [r32];;	//ensure all memory operations happen first, then load *x into r31

	mov ar.ccv = r31		//Set CCV to be *x
	add	r30 = r31, r33;;	//r30 = *x + value

try_again9:
	cmpxchg4.acq r8 = [r32], r30, ar.ccv;;	//compare [r32] to CCV, exchange with r30 if successful. r8 <- *x
	mov ar.ccv = r8
	cmp4.ne.unc p15, p0 = r8, r31
	mov	r31 = r8
	add	r30 = r33, r8
  (p15)	br.cond.dptk.few try_again9;;
  
	br.ret.sptk.many b0;;

// int SST_Atomic_ExchangeAddPtr(volatile void** x, int value)
SST_Atomic_ExchangeAddPtr:
	sxt4 r29 = r33;;			//sign extend value to 64 bits
	mf
	ld8.bias r31 = [r32];;	//ensure all memory operations happen first, then load *x into r31

	mov ar.ccv = r31		//Set CCV to be *x
	add	r30 = r31, r29;;	//r30 = *x + value

try_again10:
	cmpxchg8.acq r8 = [r32], r30, ar.ccv;;	//compare [r32] to CCV, exchange with r30 if successful. r8 <- *x
	mov ar.ccv = r8
	cmp.ne.unc p15, p0 = r8, r31
	mov	r31 = r8
	add	r30 = r8, r29
  (p15)	br.cond.dptk.few try_again10;;
  
	br.ret.sptk.many b0;;

// x = r32, compare = r33, newValue = r34
SST_Atomic_CAS:
	mf
	ld4.bias r31 = [r32];;		//ensure all memory operations happen first, then load *x into r31
	mov ar.ccv = r33;;			//Set CCV to be *x
	cmpxchg4.acq r8 = [r32], r34, ar.ccv;;	//compare [r32] to CCV, exchange with r34 is successful. r8 <- *x
	br.ret.sptk.many b0;;

// x = r32, compare = r33, newValue = r34
SST_Atomic_CASPtr:
	mf
	ld8.bias r31 = [r32];;		//ensure all memory operations happen first, then load *x into r31
	mov ar.ccv = r33;;			//Set CCV to be *x
	cmpxchg8.acq r8 = [r32], r34, ar.ccv;;	//compare [r32] to CCV, exchange with r34 is successful. r8 <- *x
	br.ret.sptk.many b0;;

// int SST_Atomic_LoadAcquire(const volatile int* src);	
SST_Atomic_LoadAcquire:
	ld4.acq r8 = [r32];;		//Load-with-acquire into return value register r8
	br.ret.sptk.many b0;;

// void* SST_Atomic_LoadAcquirePtr(const volatile void** src);
SST_Atomic_LoadAcquirePtr:	
	ld8.acq r8 = [r32];;		//Load-with-acquire into return value register r8
	br.ret.sptk.many b0;;
	
// void SST_Atomic_StoreRelease(volatile int* dest, int value);
SST_Atomic_StoreRelease:
	st4.rel [r32] = r33;;		//Store with release
	br.ret.sptk.many b0;;


// void SST_Atomic_StoreReleasePtr(volatile void** dest, void* value);
SST_Atomic_StoreReleasePtr:
	st8.rel [r32] = r33;;		//Store with release
	br.ret.sptk.many b0;;