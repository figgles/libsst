#	libsst-concurrency/sources-POSIX.mk
#	Author: Patrick Baggett <ptbaggett@762studios.com>
#	Created: 12/23/2011
#
#	Purpose:
#
#	List of source files for POSIX-compliant systems. This reduces the amount
#	of copy/pasting for different UNIX configurations
#
#	License:
#
#	This program is free software. It comes without any warranty, to
#	the extent permitted by applicable law. You can redistribute it
#	and/or modify it under the terms of the Do What The Fuck You Want
#	To Public License, Version 2, as published by Sam Hocevar. See
#	http://sam.zoy.org/wtfpl/COPYING for more details.

SRC := \
	SST_Mutex_POSIX.c \
	SST_Event_POSIX.c \
	SST_Thread_POSIX.c \
	SST_ReadWriteLock.c \
	SST_TLS_POSIX.c \
	SST_Semaphore_POSIX.c 

# MacOS X doesn't have decent semaphore implementation, use home-rolled solution
ifeq ($(OS),Darwin)
	SRC := $(subst SST_Semaphore_POSIX.c,SST_Semaphore_MacOSX.c, $(SRC))
endif

