#	libsst-concurrency/sources-common.mk
#	Author: Patrick Baggett <ptbaggett@762studios.com>
#	Created: 12/23/2011
#
#	Purpose:
#
#	List of source files for common to all systems. This reduces the amount
#	of copy/pasting for different OS configurations.
#
#	License:
#
#	This program is free software. It comes without any warranty, to
#	the extent permitted by applicable law. You can redistribute it
#	and/or modify it under the terms of the Do What The Fuck You Want
#	To Public License, Version 2, as published by Sam Hocevar. See
#	http://sam.zoy.org/wtfpl/COPYING for more details.

SRC += \
	SST_Once.c \
	SST_ReadWriteLock.c \
	SST_ThreadBarrier.c
