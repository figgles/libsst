/*
	SST_GLAPIResolve_MacOSX.c
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 4/16/2013

	Purpose: 

	Runtime OpenGL symbol resolution (MacOSX)

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#include <dlfcn.h>
#include <string.h>
#include "GLAPIPrivate.h"

/* Path to libGL by default */
#define LIBGL_PATH	"/System/Library/Frameworks/OpenGL.framework/libGL.dylib"

/******************************************************************************/

void* openLibGL(const char* path)
{
	return dlopen(path, RTLD_GLOBAL | RTLD_NOW);
}

/******************************************************************************/

void closeLibGL(void* libGL)
{
	dlclose(libGL);
}

/******************************************************************************/

int getResolver(void* oglLib, GLAPIResolver* res)
{
	res->privateFields[0] = oglLib;
		
	return 1;
}

/******************************************************************************/

const char* defaultLibGLName()
{
	return LIBGL_PATH;
}

/******************************************************************************/

void* resolveGLSymbol(const GLAPIResolver* res, const char* name)
{
	return dlsym(res->privateFields[0], name);	
}

/******************************************************************************/

