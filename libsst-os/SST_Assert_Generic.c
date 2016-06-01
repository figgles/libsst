/*
	SST_Assert_Generic.c
	Author: Patrick Baggett <ptb1@762studios.com>
	Created: 12/23/2011

	Purpose: 

	libsst-os assert functions portable for any system with a C standard library

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#include <SST/SST_Assert.h>

#include <stdio.h> /* printf() */
#include <stdlib.h> /* abort() */

/******************************************************************************/

void SST_OS_RuntimeAssertImpl(int condition, const char* condString, const char* msgString, const char* file, const char* func, int line)
{
	/* Assume likely success and exit early */
	if(condition)
		return;

	/* Call the runtime handler if we have one */
	if (sst_runtime_assert_handler != 0)
		if(sst_runtime_assert_handler(msgString, sst_runtime_assert_handler_arg))
			return;

	printf("The application has reached a runtime assertion failure! This means a serious problem has occurred and the program needs to close.\n\nProgrammer Info:\n\nFile \"%s\", line (%d) in function \"%s()\".\n\nFailed condition: \"%s\"\n\n"
		,
		file,
		line,
		func,
		condString);
	
	#ifdef _DEBUG	
		PORTABLE_TRAP();
	#else
		abort();
	#endif
}

/******************************************************************************/

void SST_OS_RuntimeAssertImplNoInfo(int cond, const char* msgString)
{
	/* Assume likely success and exit early */
	if(cond)
		return;

	/* Call the runtime handler if we have one */
	if (sst_runtime_assert_handler != 0)
		if(sst_runtime_assert_handler(msgString, sst_runtime_assert_handler_arg))
			return;

	printf("The application has reached a runtime assertion failure! This means a serious problem has occurred, and the application needs to close.\n");

	#ifdef _DEBUG	
		PORTABLE_TRAP();
	#else
		abort();
	#endif
}


