#	Makefile
#	Author: Patrick Baggett <ptbaggett@762studios.com>
#	Created: 12/20/2011
#
#	Purpose:
#
#	Main makefile for 762 Studios. Requires GNU Make
#
#	License:
#
#	This program is free software. It comes without any warranty, to
#	the extent permitted by applicable law. You can redistribute it
#	and/or modify it under the terms of the Do What The Fuck You Want
#	To Public License, Version 2, as published by Sam Hocevar. See
#	http://sam.zoy.org/wtfpl/COPYING for more details.

ROOTDIR := $(shell pwd)

.PHONY: atomic concurrency crypto math random os net 

# This sets flags for the type of compiler in use.
# Sets IS_GCC, IS_ICC or IS_CC.
include BuildConfig/DetectCompiler.rules

#Detect platform (OS + architecture)
# -> This sets $OS and $ARCH for us.
include BuildConfig/DetectPlatform.rules

#Include platform specific build rules
include BuildConfig/Makefile.$(OS).$(ARCH)

#Detect libraries associated with this platform
include BuildConfig/DetectLibs.rules

PLATFORM := $(OS)-$(ARCH)

#Make distribution folder for libs
DIST ?= $(ROOTDIR)/Bin/$(ARCH)
$(shell mkdir -p $(DIST))

# HAS_SCIPY = $(shell python -c "import scipy")

override LDFLAGS += $(OS_LDFLAGS)
override CXXFLAGS += $(OS_CXXFLAGS) -I$(ROOTDIR)/Include -I$(ROOTDIR)/Lib/Include
override CFLAGS += $(OS_CFLAGS) -I$(ROOTDIR)/Include -I$(ROOTDIR)/Lib/Include

export #Make sure sub-makes get the variables

release:
	@echo Building ZEngine in \"Release\" mode for $(PLATFORM)
	$(MAKE) -C libsst-atomic TARGET=release
	$(MAKE) -C libsst-concurrency TARGET=release
	$(MAKE) -C libsst-os TARGET=release
	$(MAKE) -C libsst-crypto TARGET=release
	$(MAKE) -C libsst-random TARGET=release
	$(MAKE) -C libsst-math TARGET=release all
	$(MAKE) -C libsst-net TARGET=release
	$(MAKE) -C libsst-glapi TARGET=release
	$(MAKE) -C libsst-wm TARGET=release

debug:
	@echo Building ZEngine in \"Debug\" mode  for $(PLATFORM)
	$(MAKE) -C libsst-atomic CFLAGS="$(CFLAGS) -g -D_DEBUG" TARGET=debug
	$(MAKE) -C libsst-concurrency CFLAGS="$(CFLAGS) -g -D_DEBUG" TARGET=debug
	$(MAKE) -C libsst-os CFLAGS="$(CFLAGS) -g -D_DEBUG" TARGET=debug
	$(MAKE) -C libsst-crypto CFLAGS="$(CFLAGS) -g -D_DEBUG" TARGET=debug
	$(MAKE) -C libsst-random CFLAGS="$(CFLAGS) -g -D_DEBUG" TARGET=debug
	$(MAKE) -C libsst-math CFLAGS="$(CFLAGS) -g -D_DEBUG" TARGET=debug all
	$(MAKE) -C libsst-net CFLAGS="$(CFLAGS) -g -D_DEBUG" TARGET=debug
	$(MAKE) -C libsst-glapi CFLAGS="$(CFLAGS) -g -D_DEBUG" TARGET=debug
	$(MAKE) -C libsst-wm CFLAGS="$(CFLAGS) -g -D_DEBUG" TARGET=debug

clean:
	@echo Cleaning ZEngine.
	$(MAKE) -C libsst-atomic clean
	$(MAKE) -C libsst-concurrency clean
	$(MAKE) -C libsst-os clean
	$(MAKE) -C libsst-crypto clean
	$(MAKE) -C libsst-random clean
	$(MAKE) -C libsst-math clean
	$(MAKE) -C libsst-net clean
	$(MAKE) -C libsst-glapi clean
	$(MAKE) -C libsst-wm clean

cleanall: clean
	$(MAKE) -C libsst-math code
	
math:
	@echo Building libsst-$@ in \"Debug\" mode for $(PLATFORM)
	$(MAKE) -C libsst-$@ CFLAGS="$(CFLAGS)" TARGET=release all

atomic:
	@echo Building libsst-$@ in \"Debug\" mode for $(PLATFORM)
	$(MAKE) -C libsst-$@ CFLAGS="$(CFLAGS)" TARGET=release

os:
	@echo Building libsst-$@ in \"Debug\" mode for $(PLATFORM)
	$(MAKE) -C libsst-$@ CFLAGS="$(CFLAGS)" TARGET=release

crypto:
	@echo Building libsst-$@ in \"Debug\" mode for $(PLATFORM)
	$(MAKE) -C libsst-$@ CFLAGS="$(CFLAGS)" TARGET=release
	
random:
	@echo Building libsst-$@ in \"Debug\" mode for $$(PLATFORM)
	$(MAKE) -C libsst-$@ CFLAGS="$(CFLAGS)" TARGET=release

concurrency: 
	@echo Building libsst-$@ in \"Debug\" mode for $(PLATFORM)
	$(MAKE) -C libsst-$@ CFLAGS="$(CFLAGS)" TARGET=release

net:
	@echo Building libsst-$@ in \"Debug\" mode for $(PLATFORM)
	$(MAKE) -C libsst-$@ CFLAGS="$(CFLAGS)" TARGET=release

glapi:
	@echo Building libsst-$@ in \"Debug\" mode for $(PLATFORM)
	$(MAKE) -C libsst-$@ CFLAGS="$(CFLAGS)" TARGET=release

wm:
	@echo Building libsst-$@ in \"Release\" mode for $(PLATFORM)
	$(MAKE) -C libsst-$@ CFLAGS="$(CFLAGS)" TARGET=release

clobber:
	@echo Cleaning All Auto-Generated Code
	$(MAKE) -C libsst-math code


all: release debug

