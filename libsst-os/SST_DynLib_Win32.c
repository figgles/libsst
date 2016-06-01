/*
	SST_DynLib_Win32.c
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 12/23/2011

	Purpose: 

	libsst-os dynamic linking functions for Win32 systems (Windows 7 or later)

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#include "Win32Private.h"
#include <SST/SST_Assert.h>
#include <SST/SST_DynLib.h>
#include <string.h>

/*************************************************************************/

SST_DynLib SST_OS_LoadDynLib(const char* path)
{
	SST_OS_DebugAssert(path != NULL, "Path may not be NULL");

	return (SST_DynLib)LoadLibraryExA(path, NULL, 0);
}

/*************************************************************************/

SST_DynLibFunc SST_OS_GetLibSymbol(SST_DynLib lib, const char* symbol)
{
	SST_OS_DebugAssert(lib != NULL, "Library may not be NULL");
	SST_OS_DebugAssert(symbol != NULL, "Library may not be NULL");

	return (SST_DynLibFunc)GetProcAddress((HMODULE)lib, symbol);
}

/*************************************************************************/

void SST_OS_CloseDynLib(SST_DynLib lib)
{
	SST_OS_DebugAssert(lib != NULL, "Library may not be NULL");

	FreeLibrary((HMODULE)lib);
}

/*************************************************************************/

int SST_OS_DynLibName(char* libnameOut, const char* libnameIn)
{
	SST_OS_DebugAssert(libnameIn != NULL, "Library name may not be NULL");

	if(libnameOut == NULL)
		return (int)strlen(libnameIn)+4; /* +strlen(".dll") */

	strcpy(libnameOut, libnameIn);
	strcat(libnameOut, ".dll");

	return 0;
}
