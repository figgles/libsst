/*
	GLAPIPrivate.h
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 1/18/2013

	Purpose: 

	Private header for libsst-glapi.
	Not to be distributed as part of public SDK

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/
#pragma once

#ifndef _GLAPIPRIVATE_H
#define _GLAPIPRIVATE_H

#include <pstdint.h> /* uintptr_t */

struct SST_GLAPI;

typedef struct GLAPIResolver
{
	void* privateFields[2];	/* Platform dependent fields */
} GLAPIResolver;

/* THESE ARE PLATFORM SPECIFIC { */

/* Load libGL by name */
void* openLibGL(const char* path);

/* Close libGL by name */
void closeLibGL(void* libGL);

/* Get a resolver struct */
int getResolver(void* oglLib, GLAPIResolver* resolver);

/* Return default OpenGL library name for platform */
const char* defaultLibGLName();

/* Resolve a GL symbol */
void* resolveGLSymbol(const GLAPIResolver* resolver, const char* name);

/* } END PLATFORM-SPECIFIC */

/* Resolve ALL GL symbols */
void resolveGLAPI(const GLAPIResolver* resolver, struct SST_GLAPI* api);



#endif

