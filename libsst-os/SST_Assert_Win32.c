/*
	SST_Assert_Win32.c
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 12/23/2011

	Purpose: 

	libsst-os assert functions for Win32 systems (Windows 7 or later)

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#define _CRT_SECURE_NO_WARNINGS /* Shhh, compiler */

#include <SST/SST_Assert.h>

#include "Win32Private.h"
#include <stdio.h> /* sprintf() */

/*************************************************************************/
void SST_OS_RuntimeAssertImpl(int condition, const char* condString, const char* msgString, const char* file, const char* func, int line)
{
	UINT flags;
	char buf[2048];
	int retcode;

	/* Assume likely success and exit early */
	if(condition)
		return;

	/* Call the runtime handler if we have one */
	if (sst_runtime_assert_handler != 0)
		retcode = sst_runtime_assert_handler(msgString, sst_runtime_assert_handler_arg);
	else
		retcode = 0;

	/* See if user handler returned non-zero (i.e. don't raise error) */
	if(retcode != 0)
		return;

	sprintf(buf, "The application has reached a runtime assertion failure! Normally, this means a serious problem, and the program should close.\n\nProgrammer Info:\n\nFile \"%s\", line (%d) in function \"%s()\".\n\nFailed condition: \"%s\"\n\n"

		#ifdef _DEBUG
		"Terminate application? (Click \"Cancel\" to debug)\n\n"
		#endif
		,
		file,
		line,
		func,
		condString);
	
	
	#ifdef _DEBUG
		flags = MB_YESNOCANCEL | MB_ICONERROR;
	#else
		flags = MB_OK | MB_ICONERROR; 
	#endif	
	retcode = MessageBoxA(NULL, buf, "libSST: Runtime assertion failure!", flags);
	
	
	#ifdef _DEBUG
	switch(retcode)
	{
		/* Yes -- terminate process */
		case IDYES:
			ExitProcess((UINT)line);
			/* No 'break' -- function never returns */
		
		/* No -- just continue */
		case IDNO:
			return;
		
		/* Cancel -- debug it */
		case IDCANCEL:
			PORTABLE_TRAP();
			break;
		}
	
	#else
		/* Ignore return value in release mode, just exit using the line number as the exit code. Since this is non-zero, it should signal to the OS that there was a problem. */
		(void)retcode;
		ExitProcess((UINT)line);
	#endif
}

/*************************************************************************/

void SST_OS_RuntimeAssertImplNoInfo(int cond, const char* msgString)
{
	UINT flags;
	int retcode;

	/* Assume likely success and exit early */
	if(cond)
		return;

	/* Call the runtime handler if we have one */
	if (sst_runtime_assert_handler != 0)
		retcode = sst_runtime_assert_handler(msgString, sst_runtime_assert_handler_arg);
	else
		retcode = 0;

	/* See if user handler returned non-zero (i.e. don't raise error) */
	if(retcode != 0)
		return;

	#ifdef _DEBUG
		flags = MB_YESNOCANCEL | MB_ICONERROR;
	#else
		flags = MB_OK | MB_ICONERROR; 
	#endif	
	retcode = MessageBoxA(NULL,
		/* Message */
		#ifdef _DEBUG
		"The application has reached a runtime assertion failure! Normally, this means a serious problem has occurred, and the program should close.\n\n"
		"Terminate application?"
		#else /* Release doesn't have an option to not close */
		"The application has reached a runtime assertion failure! This means a serious problem has occurred, and the application needs to close."
		#endif
		,
		
		"libSST: Runtime assertion failure!", flags);
	
	#ifdef _DEBUG
	switch(retcode)
	{		
		/* No -- just continue */
		case IDNO:
			return;
		
		/* Cancel -- debug it */
		case IDCANCEL:
			PORTABLE_TRAP();
			break;

		/* Yes -- terminate process */
		case IDYES:
			break;
	}
	
	#else
		/* Ignore return value in release mode, just exit. */
		(void)retcode;
	#endif

	/* dead code :( */
	ExitProcess(0xdeadc0de);
}


