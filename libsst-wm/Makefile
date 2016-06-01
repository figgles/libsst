#	libsst-wm/Makefile
#	Author: Patrick Baggett <ptbaggett@762studios.com>
#	Created: 11/16/2012
#
#	Purpose:
#
#	Makefile for libsst-wm
#
#	License:
#
#	This program is free software. It comes without any warranty, to
#	the extent permitted by applicable law. You can redistribute it
#	and/or modify it under the terms of the Do What The Fuck You Want
#	To Public License, Version 2, as published by Sam Hocevar. See
#	http://sam.zoy.org/wtfpl/COPYING for more details.

BINNAME := $(DIST)/libsst-wm.a
ifeq ($(TARGET),debug)
	BINNAME := $(subst .a,_d.a, $(BINNAME))
endif

# Now, include the window system drivers (detection occurs inside)
#include Win32/sources.mk
#include RaspPi/sources.mk
include Xlib/sources.mk

SRC += API.c

OBJ := $(addprefix obj/$(ARCH)/$(TARGET)/,$(subst .m,.o,$(subst .c,.o,$(SRC))))
$(shell mkdir -p obj/$(ARCH)/$(TARGET))
$(shell mkdir -p obj/$(ARCH)/$(TARGET)/Xlib)
$(shell mkdir -p obj/$(ARCH)/$(TARGET)/RaspPi)
$(shell mkdir -p obj/$(ARCH)/$(TARGET)/Win32)
$(shell mkdir -p obj/$(ARCH)/$(TARGET)/MacOSX)

$(BINNAME): $(OBJ)
	$(AR) cru $@ $+
	$(RANLIB) $@

# CLEAN
clean:
	@-rm -r -f obj $(DIST)/libsst-wm*.a

# *.c files to *.o files
obj/$(ARCH)/$(TARGET)/%.o: %.c
	@echo CC $@
	@$(CC) -I. $(CFLAGS) -c $*.c -o obj/$(ARCH)/$(TARGET)/$*.o


# *.m files to *.o files (Mac)
obj/$(ARCH)/$(TARGET)/%.o: %.m
	@echo OBJCC $@
	@$(CC) $(CFLAGS) -c $*.m -o obj/$(ARCH)/$(TARGET)/$*.o
