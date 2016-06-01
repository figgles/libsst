/*
	SST_GLAPIResolve_Win32.c
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 12/12/2012

	Purpose: 

	Runtime OpenGL symbol resolution (Win32)

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#include <windows.h>
#include "GLAPIPrivate.h"

typedef void* (WINAPI*pf_wglGetProcAddress)(const char* symbol);

typedef struct GLAPIResolver_Win32
{
	pf_wglGetProcAddress pwglGetProcAddress;
	HMODULE hDLL;
} GLAPIResolver_Win32;

/*************************************************************************/

void* openLibGL(const char* path)
{
	return (void*)LoadLibraryA(path);
}

/*************************************************************************/

void closeLibGL(void* libGL)
{
	FreeLibrary((HMODULE)libGL);
}

/*************************************************************************/

int getResolver(void* oglLib, GLAPIResolver* res)
{
	HMODULE hDLL = (HMODULE)oglLib;
	GLAPIResolver_Win32* resolver = (GLAPIResolver_Win32*)res;

	resolver->pwglGetProcAddress = (pf_wglGetProcAddress)GetProcAddress(hDLL, "wglGetProcAddress");
	resolver->hDLL = hDLL;
	
	return (resolver->pwglGetProcAddress != NULL);
}

/*************************************************************************/

/* Return default OpenGL library name for platform */
const char* defaultLibGLName()
{
	return "opengl32.dll";
}

/*************************************************************************/

void* resolveGLSymbol(const GLAPIResolver* res, const char* name)
{
	void* sym;
	const GLAPIResolver_Win32* resolver = (const GLAPIResolver_Win32*)res;
	
	/* Try core (GL 1.1) symbol resolution first */
	sym = (void*)GetProcAddress(resolver->hDLL, name);
	
	/* If that fails, try wglGetProcAddress() for extension GL stuff */
	if(sym == NULL)
		sym = resolver->pwglGetProcAddress(name);
		
	return sym;
}

/*************************************************************************/
