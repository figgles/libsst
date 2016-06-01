#	SST_Atomic_mips64.asm
#	Author: Patrick Baggett <ptbaggett@762studios.com>
#	Created: 7/1/2013
#
#	Purpose:
#
#	64-bit assembly for atomic operations for MIPS CPUs. Targets MIPS64R2 ISA, but should run on
#   	older MIPS machines (e.g. MIPS-III / Loongson).
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

# Unbelievable. binutils-2.22 doesn't support register names in n64 (-mabi=64) mode, but it does in o32 (-mabi=32)
# Here are the symbolic names for registers used
# $v0-$v1 = $2-$3
# $a0-$a4 = $4-$7
# $t4-$t5 = $8-$9
# $ra = $31


# MIPS has a "sync" instruction with a bitfield describing "what" to sync, sort of like SPARC's "membar" instruction.
# By default, "sync" means "sync 0" -- a full memory barrier including I/O devices/instructions. This is a very heavy-weight operation and used for things like ordering MMIO accesses
# MIPS64R2 defines "sync 0x10" as a full memory barrier that doesn't synchronize I/O, and "sync 0x04" as a "write/write" memory barrier. However,
# we can't use MIPS64R2 code only. But as it would turn out, it is OK because "sync <k>" is treated like "sync 0" in older MIPS CPUs, meaning full barrier,
# but it will automatically be faster on MIPS32R2 CPUs. Neat.

# void SST_Atomic_Add(volatile int* x, int value)
# int SST_Atomic_AddReturn(volatile int* x, int value)
SST_Atomic_Add:
SST_Atomic_AddReturn:
	sync 0x10					# sync_mb
	
1:
	ll $12, 0($4)				# t4 <- *x
	addu $13, $12, $5			# t5 <- t4 + value
	sc $13, 0($4)				# try { *x <- t5 }, set t5 = 1/0 depending
	beqz $13,1b					# if failure, retry
	addu $2, $12, $5			# (delay slot) $2 <- *x + value (return value)
	
	jr $31						# return
	sync 0x04					# (delay slot) sync_wmb

# void SST_Atomic_AddPtr(volatile void** x, int value)
# void* SST_Atomic_AddPtrReturn(volatile void** x, int value)
SST_Atomic_AddPtr:
SST_Atomic_AddPtrReturn:
	sync 0x10				# sync_mb
1:
	lld $12, 0($4)				# t4 <- *x
	daddu $13, $12, $5			# t5 <- t4 + value
	scd $13, 0($4)				# try { *x <- t5 }, set t5 = 1/0 depending
	beqz $13,1b					# if failure, retry
	daddu $2, $12, $5			# (delay slot) $2 <- *x + value (return value)
	
	jr $31					# return
	sync 0x04				# (delay slot) sync_wmb



# void SST_Atomic_And(volatile int* x, int value)
# int SST_Atomic_AndReturn(volatile int* x, int value)
SST_Atomic_And:
SST_Atomic_AndReturn:
	sync 0x10					# sync_mb
	
1:
	ll $12, 0($4)				# t4 <- *x
	and $13, $12, $5			# t5 <- t4 & value
	sc $13, 0($4)				# try { *x <- t5 }, set t5 = 1/0 depending
	beqz $13,1b					# if failure, retry
	and $2, $12, $5			# (delay slot) compute return value
	
	jr $31						# return
	sync 0x04					# (delay slot) sync_wmb

# void SST_Atomic_Or(volatile int* x, int value)
# int SST_Atomic_OrReturn(volatile int* x, int value)
SST_Atomic_Or:
SST_Atomic_OrReturn:
	sync 0x10					# sync_mb
	
1:
	ll $12, 0($4)				# t4 <- *x
	or $13, $12, $5			# t5 <- t4 | value
	sc $13, 0($4)				# try { *x <- t5 }, set t5 = 1/0 depending
	beqz $13,1b					# if failure, retry
	or $2, $12, $5			# (delay slot) compute return value
	
	jr $31						# return
	sync 0x04					# (delay slot) sync_wmb

# void SST_Atomic_Xor(volatile int* x, int value)
# int SST_Atomic_XorReturn(volatile int* x, int value)
SST_Atomic_XorReturn:
SST_Atomic_Xor:
	sync 0x10					# sync_mb
	
1:
	ll $12, 0($4)				# t4 <- *x
	xor $13, $12, $5			# t5 <- t4 ^ value
	sc $13, 0($4)				# try { *x <- t5 }, set t5 = 1/0 depending
	beqz $13,1b					# if failure, retry
	xor $2, $12, $5			# (delay slot) Nothing to do
	
	jr $31						# return
	sync 0x04					# (delay slot) sync_wmb

# void SST_Atomic_Not(volatile int* x)
SST_Atomic_Not:
SST_Atomic_NotReturn:
	sync 0x10					# sync_mb
	
1:
	ll $12, 0($4)				# t4 <- *x
	nor $13, $12, $0			# t5 <- ~t4
	sc $13, 0($4)				# try { *x <- t5 }, set t5 = 1/0 depending
	beqz $13,1b					# if failure, retry
	nor $2, $12, $0			# (delay slot) compute return value
	
	jr $31						# return
	sync 0x04					# (delay slot) sync_wmb


# int SST_Atomic_Exchange(volatile int* x, int value)
SST_Atomic_Exchange:
	sync 0x10					# sync_mb

	move $12, $5				# t4 <- value
	
1:
	ll $2, 0($4)				# v0 <- *x
	sc $12, 0($4)				# try { *x <- t4 }, set t4 = 1/0 depending
	beqz $12,1b					# if failure, retry
	move $12, $5				# (delay slot) reload t4 <- value for retry
	
	jr $31						# return
	sync 0x04					# (delay slot) sync_wmb

# void* SST_Atomic_ExchangePtr(volatile void** x, void* value)
SST_Atomic_ExchangePtr:
	sync 0x10				# sync_mb
	move $12, $5				# value for exchange
1:
	lld $2, 0($4)				# v0 <- *x
	scd $12, 0($4)				# try { *x <- t4 }, set t4 = 1/0 depending
	beqz $12,1b					# if failure, retry
	move $12, $5				# (delay slot) t4 <- value for retry

	jr $31					# return
	sync 0x04				# (delay slot) sync_wmb
	
# int SST_Atomic_ExchangeAdd(volatile int* x, int value);
SST_Atomic_ExchangeAdd:
	sync 0x10					# sync_mb
	
1:
	ll $2, 0($4)				# v0 <- *x
	addu $12, $2, $5			# t4 <- v0 + value
	sc $12, 0($4)				# try { *x <- t4 }, set t4 = 1/0 depending
	beqz $12,1b				# if failure, retry
	nop					# (delay slot) do nothing
	
	jr $31					# return
	sync 0x04				# (delay slot) sync_wmb

# void* SST_Atomic_ExchangeAddPtr(volatile void** x, int value);
SST_Atomic_ExchangeAddPtr:
	sync 0x10					# sync_mb
1:
	lld $2, 0($4)				# v0 <- *x
	daddu $12, $2, $5			# t4 <- v0 + value
	scd $12, 0($4)				# try { *x <- t4 }, set t4 = 1/0 depending
	beqz $12,1b				# if failure, retry
	nop					# (delay slot) do nothing
	
	jr $31					# return
	sync 0x04				# (delay slot) sync_wmb

	
	
# int SST_Atomic_CAS(int* dest, int compare, int newValue);
# a0 = dest, a1 = compare, a2 = newValue
SST_Atomic_CAS:
	sync 0x10				# sync_mb
1:	
	move $12, $6				# t4 <- newValue
	ll $2, 0($4)				# v0 <- *dest (captures "old" value of *dest, also is the return value)
	bne $2, $5, 3f			# compare v0 with a1 ("compare"), and if not equal, exit loop
	nop					# (delay slot) do nothing
	sc $12, 0($4)				# try { *x <- t4 }, set t4 = 1/0 depending
	beqz $12,1b				# if failure, retry
	nop					# (delay slot) do nothing
	
	sync 0x04				# sync_wmb

# Return
3:
	jr $31					# return
	nop					# (delay slot) do nothing

# void* SST_Atomic_CASPtr(void** dest, void* compare, void* newValue);
# a0 = dest, a1 = compare, a2 = newValue
SST_Atomic_CASPtr:
	sync 0x10				# sync_mb
1:	
	move $12, $6				# t4 <- newValue
	lld $2, 0($4)				# v0 <- *dest (captures "old" value of *dest, also is the return value)
	bne $2, $5, 3f			# compare v0 with a1 ("compare"), and if not equal, exit loop
	nop					# (delay slot) do nothing
	scd $12, 0($4)				# try { *x <- t4 }, set t4 = 1/0 depending
	beqz $12,1b				# if failure, retry
	nop					# (delay slot) do nothing
	
	sync 0x04				# sync_wmb

# Return
3:
	jr $31					# return
	nop					# (delay slot) do nothing

SST_Atomic_LoadAcquire:
	lw	$2, 0($4)
	sync 0x11					# sync_acquire: LoadLoad | LoadStore
	jr $31
	nop

SST_Atomic_StoreRelease:
	sync 0x12					# sync_release: LoadStore | StoreStore
	jr $31
	sw	$5, 0($4)

SST_Atomic_LoadAcquirePtr:
	ld	$2, 0($4)
	sync 0x11					# sync_acquire: LoadLoad | LoadStore
	jr $31
	nop

SST_Atomic_StoreReleasePtr:
	sync 0x12					# sync_release: LoadStore | StoreStore
	jr $31
	sd	$5, 0($4)

