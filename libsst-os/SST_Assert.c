/*
	SST_Assert.c
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 12/23/2011

	Purpose: 

	libsst-os common assert functions

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#include <SST/SST_Assert.h>
#include <stdlib.h> /* NULL */

/*************************************************************************/

SST_AssertHandlerFunc sst_debug_assert_handler = NULL; /* Handler function for debug asserts */
void* sst_debug_assert_handler_arg = NULL; /* Argument to the debug assert */
SST_AssertHandlerFunc sst_runtime_assert_handler = NULL; /* Handler function for runtime asserts */
void* sst_runtime_assert_handler_arg = NULL; /* Argument to the runtime assert */

/*************************************************************************/

void SST_OS_SetDebugAssertHandler(SST_AssertHandlerFunc _func, void *_arg)
{
	sst_debug_assert_handler = _func;
	sst_debug_assert_handler_arg = _arg;
}

/*************************************************************************/

void SST_OS_SetRuntimeAssertHandler(SST_AssertHandlerFunc _func, void *_arg)
{
	sst_runtime_assert_handler = _func;
	sst_runtime_assert_handler_arg = _arg;
}
