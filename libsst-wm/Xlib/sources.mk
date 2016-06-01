#	libsst-wm/Xlib/sources.mk
#	Author: Patrick Baggett <ptbaggett@762studios.com>
#	Created: 1/8/2013
#
#	Purpose:
#
#	List of source files for X Windows systems
#
#	License:
#
#	This program is free software. It comes without any warranty, to
#	the extent permitted by applicable law. You can redistribute it
#	and/or modify it under the terms of the Do What The Fuck You Want
#	To Public License, Version 2, as published by Sam Hocevar. See
#	http://sam.zoy.org/wtfpl/COPYING for more details.

ifeq ($(findstring -DHAVE_XLIB,$(CFLAGS)),-DHAVE_XLIB)
    SRC += \
	Xlib/SST_WMDialogBox_Xlib.c \
	Xlib/SST_WMEnum_Xlib.c \
	Xlib/SST_WMEvent_Xlib.c \
	Xlib/SST_WMOpenGL_Xlib.c \
	Xlib/SST_WMNonPortable_Xlib.c \
	Xlib/SST_WMVideoMode_Xlib.c \
	Xlib/SST_WMRender_Xlib.c \
	Xlib/SST_WMWindow_Xlib.c \
	Xlib/XlibPrivate.c \
	Xlib/GLXPrivate.c \
	Xlib/XI2Private.c \
	Xlib/XlibDriver.c

endif
