#	SST_Atomic_mips.asm
#	Author: Patrick Baggett <ptbaggett@762studios.com>
#	Created: 1/15/2013
#
#	Purpose:
#
#	32-bit assembly for atomic operations for MIPS CPUs. Targets MIPS32R2 ISA, but should run on
#   older MIPS machines (e.g. MIPS-III / Loongson).
#	Assembles with GNU as (doubtfully IRIX)
#
#	License:
#
#	This program is free software. It comes without any warranty, to
#	the extent permitted by applicable law. You can redistribute it
#	and/or modify it under the terms of the Do What The Fuck You Want
#	To Public License, Version 2, as published by Sam Hocevar. See
#	http://sam.zoy.org/wtfpl/COPYING for more details.

.text

#Don't reorder instructions
.set noreorder

# ELF symbol names
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

#===================================================================================
# Since pointers and integers are the same size on 32-bit code (GCC), many of the
# integer/pointer code paths are the same. This of course only holds true
# for 32-bit compiles on MIPS, which is exactly this file.
#===================================================================================

# MIPS has a "sync" instruction with a bitfield describing "what" to sync, sort of like SPARC's "membar" instruction.
# By default, "sync" means "sync 0" -- a full memory barrier including I/O devices/instructions. This is a very heavy-weight operation and used for things like ordering MMIO accesses
# MIPS32R2 defines "sync 0x10" as a full memory barrier that doesn't synchronize I/O, and "sync 0x04" as a "write/write" memory barrier. However,
# we can't use MIPS32R2 code only. But as it would turn out, it is OK because "sync <k>" is treated like "sync 0" in older MIPS CPUs, meaning full barrier,
# but it will automatically be faster on MIPS32R2 CPUs. Neat.


# TODO: not sure if this is a CPU hazard on any remotely recent MIPS CPU (i.e. not MIPS-I or MIPS-II)
# : beq $rs, $rt, someLabel	//compare rs to rt
# : addiu $rs, $rs, 1		//increment rs
# I can't find any literature that says this is not allowed on anything other than MIPS-I, which has no interlocks.

# void SST_Atomic_Add(volatile int* x, int value)
# void SST_Atomic_AddPtr(volatile void** x, int value)
# int SST_Atomic_AddReturn(volatile int* x, int value)
# void* SST_Atomic_AddPtrReturn(volatile void** x, int value)
SST_Atomic_Add:
SST_Atomic_AddPtr:
SST_Atomic_AddReturn:
SST_Atomic_AddPtrReturn:
	sync 0x10					# sync_mb
	
1:
	ll $t4, 0($a0)				# t4 <- *x
	addu $t5, $t4, $a1			# t5 <- t4 + value
	sc $t5, 0($a0)				# try { *x <- t5 }, set t5 = 1/0 depending
	beqz $t5,1b					# if failure, retry
	addu $v0, $t4, $a1			# (delay slot) $v0 <- *x + value (return value)
	
	jr $ra						# return
	sync 0x04					# (delay slot) sync_wmb

# void SST_Atomic_And(volatile int* x, int value)
# int SST_Atomic_AndReturn(volatile int* x, int value)
SST_Atomic_And:
SST_Atomic_AndReturn:
	sync 0x10					# sync_mb
	
1:
	ll $t4, 0($a0)				# t4 <- *x
	and $t5, $t4, $a1			# t5 <- t4 & value
	sc $t5, 0($a0)				# try { *x <- t5 }, set t5 = 1/0 depending
	beqz $t5,1b					# if failure, retry
	and $v0, $t4, $a1			# (delay slot) compute return value
	
	jr $ra						# return
	sync 0x04					# (delay slot) sync_wmb

# void SST_Atomic_Or(volatile int* x, int value)
# int SST_Atomic_OrReturn(volatile int* x, int value)
SST_Atomic_Or:
SST_Atomic_OrReturn:
	sync 0x10					# sync_mb
	
1:
	ll $t4, 0($a0)				# t4 <- *x
	or $t5, $t4, $a1			# t5 <- t4 | value
	sc $t5, 0($a0)				# try { *x <- t5 }, set t5 = 1/0 depending
	beqz $t5,1b					# if failure, retry
	or $v0, $t4, $a1			# (delay slot) compute return value
	
	jr $ra						# return
	sync 0x04					# (delay slot) sync_wmb

# void SST_Atomic_Xor(volatile int* x, int value)
# int SST_Atomic_XorReturn(volatile int* x, int value)
SST_Atomic_XorReturn:
SST_Atomic_Xor:
	sync 0x10					# sync_mb
	
1:
	ll $t4, 0($a0)				# t4 <- *x
	xor $t5, $t4, $a1			# t5 <- t4 ^ value
	sc $t5, 0($a0)				# try { *x <- t5 }, set t5 = 1/0 depending
	beqz $t5,1b					# if failure, retry
	xor $v0, $t4, $a1			# (delay slot) Nothing to do
	
	jr $ra						# return
	sync 0x04					# (delay slot) sync_wmb

# void SST_Atomic_Not(volatile int* x)
SST_Atomic_Not:
SST_Atomic_NotReturn:
	sync 0x10					# sync_mb
	
1:
	ll $t4, 0($a0)				# t4 <- *x
	nor $t5, $t4, $0			# t5 <- ~t4
	sc $t5, 0($a0)				# try { *x <- t5 }, set t5 = 1/0 depending
	beqz $t5,1b					# if failure, retry
	nor $v0, $t4, $0			# (delay slot) compute return value
	
	jr $ra						# return
	sync 0x04					# (delay slot) sync_wmb


# int SST_Atomic_Exchange(volatile int* x, int value)
# void* SST_Atomic_ExchangePtr(volatile void** x, void* value)
SST_Atomic_Exchange:
SST_Atomic_ExchangePtr:
	sync 0x10					# sync_mb

	move $t4, $a1				# t4 <- value
	
1:
	ll $v0, 0($a0)				# v0 <- *x
	sc $t4, 0($a0)				# try { *x <- t4 }, set t4 = 1/0 depending
	beqz $t4,1b					# if failure, retry
	move $t4, $a1				# (delay slot) reload t4 <- value for retry
	
	jr $ra						# return
	sync 0x04					# (delay slot) sync_wmb

	
# int SST_Atomic_ExchangeAdd(volatile int* x, int value);
# void* SST_Atomic_ExchangeAddPtr(volatile void** x, int value);
SST_Atomic_ExchangeAdd:
SST_Atomic_ExchangeAddPtr:
	sync 0x10					# sync_mb
	
1:
	ll $v0, 0($a0)				# v0 <- *x
	addu $t4, $v0, $a1			# t4 <- v0 + value
	sc $t4, 0($a0)				# try { *x <- t4 }, set t4 = 1/0 depending
	beqz $t4,1b				# if failure, retry
	nop					# (delay slot) do nothing
	
	jr $ra					# return
	sync 0x04				# (delay slot) sync_wmb

	
# int SST_Atomic_CAS(int* dest, int compare, int newValue);
# void* SST_Atomic_CASPtr(void** dest, void* compare, void* newValue);
# a0 = dest, a1 = compare, a2 = newValue
SST_Atomic_CAS:
SST_Atomic_CASPtr:
	sync 0x10				# sync_mb
1:	
	move $t4, $a2				# t4 <- newValue
	ll $v0, 0($a0)				# v0 <- *dest (captures "old" value of *dest, also is the return value)
	bne $v0, $a1, 3f			# compare v0 with a1 ("compare"), and if not equal, exit loop
	nop					# (delay slot) do nothing
	sc $t4, 0($a0)				# try { *x <- t4 }, set t4 = 1/0 depending
	beqz $t4,1b				# if failure, retry
	nop					# (delay slot) do nothing
	
	sync 0x04				# sync_wmb

# Return
3:
	jr $ra					# return
	nop					# (delay slot) do nothing

SST_Atomic_LoadAcquire:
SST_Atomic_LoadAcquirePtr:
	lw	$v0, 0($a0)
	sync 0x11					# sync_acquire: LoadLoad | LoadStore
	jr $ra
	nop

SST_Atomic_StoreRelease:
SST_Atomic_StoreReleasePtr:
	sync 0x12					# sync_release: LoadStore | StoreStore
	jr $ra
	sw	$a1, 0($a0)

