#	libsst-random/Makefile
#	Author: Patrick Baggett <ptbaggett@762studios.com>
#	Created: 2/26/2012
#
#	Purpose:
#
#	Makefile for libsst-random
#
#	License:
#
#	This program is free software. It comes without any warranty, to
#	the extent permitted by applicable law. You can redistribute it
#	and/or modify it under the terms of the Do What The Fuck You Want
#	To Public License, Version 2, as published by Sam Hocevar. See
#	http://sam.zoy.org/wtfpl/COPYING for more details.

BINNAME := $(DIST)/libsst-random.a
ifeq ($(TARGET),debug)
	BINNAME := $(subst .a,_d.a, $(BINNAME))
endif

SRC := SST_CMWC.c \
	SST_Mersenne.c \
	SST_SimplexNoise.c \
	SST_PRNG.c \
	SST_SimplexNoise.c \
	SST_SmallPRNG.c

OBJ := $(addprefix obj/$(ARCH)/$(TARGET)/,$(subst .c,.o,$(SRC)) )

$(shell mkdir -p obj/$(ARCH)/$(TARGET))

$(BINNAME): $(OBJ)
	$(AR) cru $@ $+
	$(RANLIB) $@

# CLEAN
clean:
	@-rm -r -f obj $(DIST)/libsst-random*.a

# *.c files to *.o files
obj/$(ARCH)/$(TARGET)/%.o: %.c
	@echo CC $@
	@$(CC) $(CFLAGS) -c $*.c -o obj/$(ARCH)/$(TARGET)/$*.o
