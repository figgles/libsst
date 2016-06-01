#	libsst-os/Source/sources-POSIX.mk
#	Author: Patrick Baggett <ptbaggett@762studios.com>
#	Created: 12/23/2011
#
#	Purpose:
#
#	List of source files for POSIX-compliant systems. This reduces the amount
#   of copy/pasting for different UNIX configurations.
#
#	License:
#
#	This program is free software. It comes without any warranty, to
#	the extent permitted by applicable law. You can redistribute it
#	and/or modify it under the terms of the Do What The Fuck You Want
#	To Public License, Version 2, as published by Sam Hocevar. See
#	http://sam.zoy.org/wtfpl/COPYING for more details.

SRC := \
	SST_DynLib_POSIX.c \
	SST_FileSys_POSIX.c \
	SST_File_POSIX.c \
	SST_SysMem_POSIX.c \
	SST_CPU_POSIX.c \
	SST_Mmap_POSIX.c \
	SST_User_POSIX.c \
	SST_Alloc.c \
	SST_Assert.c \
	SST_Assert_Generic.c \
	SST_Endian.c \
	SST_SafeArithmetic.c \
	SST_OSInit.c \
	
# MacOS X doesn't have POSIX realtime extension, so it needs a different implementation. Le sigh.
ifeq ($(OS),Darwin)
	SRC += SST_Time_MacOSX.c
else
	SRC += SST_Time_POSIX.c
endif
