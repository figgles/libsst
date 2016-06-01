/*
	SST_DynLib_POSIX.c
	Author: Patrick Baggett <ptb1@762studios.com>
	Created: 12/23/2011

	Purpose: 

	libsst-os dynamic linking functions for POSIX systems

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#include <SST/SST_DynLib.h>
#include <SST/SST_Assert.h>

#include <stdlib.h>
#include <dlfcn.h>
#include <string.h>

/******************************************************************************/

SST_DynLib SST_OS_LoadDynLib(const char* path)
{
	SST_OS_DebugAssert(path != NULL, "Path may not be NULL");

	
	return (SST_DynLib)dlopen(path, RTLD_LAZY);
}

/******************************************************************************/

SST_DynLibFunc SST_OS_GetLibSymbol(SST_DynLib lib, const char* symbol)
{
	uintptr_t tmp;

	SST_OS_DebugAssert(lib != NULL, "Library may not be NULL");
	SST_OS_DebugAssert(symbol != NULL, "Library may not be NULL");

	tmp = (uintptr_t)dlsym((void*)lib, symbol);

	return (SST_DynLibFunc)tmp;
}

/******************************************************************************/

void SST_OS_CloseDynLib(SST_DynLib lib)
{
	SST_OS_DebugAssert(lib != NULL, "Library may not be NULL");

	dlclose((void*)lib);
}

/******************************************************************************/

int SST_OS_DynLibName(char* libnameOut, const char* libnameIn)
{
	SST_OS_DebugAssert(libnameIn != NULL, "Library name may not be NULL");

	if(libnameOut == NULL)
		return 3+(int)strlen(libnameIn)+3; /* strlen("lib")+strlen(libnameIn)+strlen(".so") */

	libnameOut[0] = 'l'; /* 	strcpy(libnameOut, "lib") */
	libnameOut[1] = 'i';
	libnameOut[2] = 'b';
	
	strcpy(libnameOut+3, libnameIn);
	strcat(libnameOut, ".so");

	return 0;
}
