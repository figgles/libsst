#	libsst-glapi/Makefile
#	Author: Patrick Baggett <ptbaggett@762studios.com>
#	Created: 12/12/2012
#
#	Purpose:
#
#	Makefile for libsst-glapi
#
#	License:
#
#	This program is free software. It comes without any warranty, to
#	the extent permitted by applicable law. You can redistribute it
#	and/or modify it under the terms of the Do What The Fuck You Want
#	To Public License, Version 2, as published by Sam Hocevar. See
#	http://sam.zoy.org/wtfpl/COPYING for more details.

BINNAME := $(DIST)/libsst-glapi.a
ifeq ($(TARGET),debug)
	BINNAME := $(subst .a,_d.a, $(BINNAME))
endif

SRC := SST_GLAPIStruct.c \
	SST_GLAPIContext.c 

# Add platform specific code

ifeq ($(OS),Darwin)
    LIBGL_PLATFORM := MacOSX
else ifeq ($(SUBSYSTEM),Solaris)
    LIBGL_PLATFORM := POSIX
else
    LIBGL_PLATFORM := $(SUBSYSTEM)
endif

include sources-$(LIBGL_PLATFORM).mk

OBJ := $(addprefix obj/$(ARCH)/$(TARGET)/,$(subst .c,.o,$(SRC)))

$(shell mkdir -p obj/$(ARCH)/$(TARGET))

$(BINNAME): $(OBJ)
	$(AR) cru $@ $+
	$(RANLIB) $@


# *.c files to *.o files
obj/$(ARCH)/$(TARGET)/%.o: %.c
	@echo CC $@
	@$(CC) $(CFLAGS) -c $*.c -o obj/$(ARCH)/$(TARGET)/$*.o

# CLEAN
clean:
	@-rm -r -f obj $(DIST)/libsst-glapi*.a
