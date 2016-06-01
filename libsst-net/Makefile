#	libsst-net/Makefile
#	Author: Patrick Baggett <ptbaggett@762studios.com>
#	Created: 12/03/2012
#
#	Purpose:
#
#	Makefile for libsst-net
#
#	License:
#
#	This program is free software. It comes without any warranty, to
#	the extent permitted by applicable law. You can redistribute it
#	and/or modify it under the terms of the Do What The Fuck You Want
#	To Public License, Version 2, as published by Sam Hocevar. See
#	http://sam.zoy.org/wtfpl/COPYING for more details.

BINNAME := $(DIST)/libsst-net.a
ifeq ($(TARGET),debug)
	BINNAME := $(subst .a,_d.a, $(BINNAME))
endif

SRC := SST_NetAddress.c \
	SST_NetSocket.c \

ifeq ($(SUBSYSTEM),Solaris)
	include sources-POSIX.mk
else	
	# Add platform specific code
	include sources-$(SUBSYSTEM).mk
endif

OBJ := $(addprefix obj/$(ARCH)/$(TARGET)/,$(subst .c,.o,$(SRC)))

$(shell mkdir -p obj/$(ARCH)/$(TARGET))

$(BINNAME): $(OBJ)
	$(AR) cru $@ $+
	$(RANLIB) $@

# CLEAN
clean:
	@-rm -r -f obj $(DIST)/libsst-net*.a

# *.c files to *.o files
obj/$(ARCH)/$(TARGET)/%.o: %.c
	@echo CC $@
	@$(CC) $(CFLAGS) -c $*.c -o obj/$(ARCH)/$(TARGET)/$*.o
