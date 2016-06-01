#	libsst-atomic/Makefile
#	Author: Patrick Baggett <ptbaggett@762studios.com>
#	Created: 12/23/2011
#
#	Purpose:
#
#	Makefile for libsst-atomic, requires GNU "make"
#
#	License:
#
#	This program is free software. It comes without any warranty, to
#	the extent permitted by applicable law. You can redistribute it
#	and/or modify it under the terms of the Do What The Fuck You Want
#	To Public License, Version 2, as published by Sam Hocevar. See
#	http://sam.zoy.org/wtfpl/COPYING for more details.

# Should be invoked with:
#	TARGET := { release, debug }
#	ARCH := { x86, x86-64, sparc, sparc64, powerpc, powerpc64 }
#	ASM := assembler tool


BINNAME := $(DIST)/libsst-atomic.a
ifeq ($(TARGET),debug)
	BINNAME := $(subst libsst-atomic,libsst-atomic_d, $(BINNAME))
endif

# Architecture -> source file conversion
ASM_SRC := SST_Atomic_$(ARCH).asm


OBJ := $(addprefix obj/$(ARCH)/$(TARGET)/,$(subst .asm,.o,$(ASM_SRC)) ) 

$(shell mkdir -p obj/$(ARCH)/$(TARGET))

$(BINNAME): $(OBJ)
	$(AR) cru $@ $+
	$(RANLIB) $@

# CLEAN
clean:
	@-rm -r -f obj $(DIST)/libsst-atomic*.a
	

# *.asm files to *.o files
obj/$(ARCH)/$(TARGET)/%.o: %.asm
	@echo ASM $@
	@$(ASM) -o obj/$(ARCH)/$(TARGET)/$*.o $*.asm
