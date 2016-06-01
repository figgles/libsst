#	libsst-crypto/Makefile
#	Author: Patrick Baggett <ptbaggett@762studios.com>
#	Created: 12/23/2011
#
#	Purpose:
#
#	Makefile for libsst-crypto
#
#	License:
#
#	This program is free software. It comes without any warranty, to
#	the extent permitted by applicable law. You can redistribute it
#	and/or modify it under the terms of the Do What The Fuck You Want
#	To Public License, Version 2, as published by Sam Hocevar. See
#	http://sam.zoy.org/wtfpl/COPYING for more details.

BINNAME := $(DIST)/libsst-crypto.a
ifeq ($(TARGET),debug)
	BINNAME := $(subst .a,_d.a, $(BINNAME))
endif

SRC := SST_Hash.c 

OBJ := $(addprefix obj/$(ARCH)/$(TARGET)/,$(subst .c,.o,$(SRC)) )

$(shell mkdir -p obj/$(ARCH)/$(TARGET))

$(BINNAME): $(OBJ)
	$(AR) cru $@ $+
	$(RANLIB) $@

# CLEAN
clean:
	@-rm -r -f obj $(DIST)/libsst-crypto*.a

# *.c files to *.o files
obj/$(ARCH)/$(TARGET)/%.o: %.c
	@echo CC $@
	@$(CC) $(CFLAGS) -c $*.c -o obj/$(ARCH)/$(TARGET)/$*.o
