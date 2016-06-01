/*
	SST_GLAPIResolve_Xlib.c
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 12/12/2012

	Purpose: 

	Runtime OpenGL symbol resolution (Xlib)

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

typedef void* (*pf_glXGetProcAddressARB)(const char* symbol);

typedef struct GLAPIResolver_Xlib
{
	pf_glXGetProcAddressARB pglXGetProcAddressARB;
} GLAPIResolver_Xlib;

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
	GLAPIResolver_Xlib* resolver = (GLAPIResolver_Xlib*)res;

	resolver->pglXGetProcAddressARB = (pf_glXGetProcAddressARB)dlsym(oglLib, "glXGetProcAddressARB");
	
	/* The -ARB variant doesn't exist? Try without */
	if(resolver->pglXGetProcAddressARB == NULL)
		resolver->pglXGetProcAddressARB = (pf_glXGetProcAddressARB)dlsym(oglLib, "glXGetProcAddress");

	return (resolver->pglXGetProcAddressARB != NULL);
}

/******************************************************************************/

const char* defaultLibGLName()
{
	return "libGL.so.1";
}

/******************************************************************************/

void* resolveGLSymbol(const GLAPIResolver* res, const char* name)
{
	const GLAPIResolver_Xlib* resolver = (const GLAPIResolver_Xlib*)res;
	
	return resolver->pglXGetProcAddressARB(name);
}

/******************************************************************************/

