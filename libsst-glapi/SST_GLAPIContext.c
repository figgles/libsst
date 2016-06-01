/*
	SST_GLAPIContext.c
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 12/12/2012

	Purpose: 

	GL API context init/shutdown

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#include <SST/SST_GLAPI.h>
#include <stdlib.h>
#include <string.h>

#include "GLAPIPrivate.h"

/*************************************************************************/

/* Thread-local variable with GLAPI context */
#ifdef _WIN32
	__declspec(thread) SST_GLAPI* __sstglctx = NULL;
#else
	__thread SST_GLAPI* __sstglctx = NULL;
#endif

/*************************************************************************/

/* strdup() implementation */
static char* dupstr(const char* s);

/* Unload libGL / libGL name, erase pointers */
static void freeGLAPI(SST_GLAPI* api);

/*************************************************************************/

int SST_GLAPI_InitForThread(const char* libGLName)
{
	SST_GLAPI* api = __sstglctx;
	void* libGL;
	char* libName;
	GLAPIResolver resolver;
	
	/*
		Generally, we need to:
		1) Open the libGL implementation
		2) Verify that this is in fact, an OpenGL implementation
		3) Resolve the OpenGL symbols
		
		We have to take care to unload the old libGL first, and
		make sure to re-use the same SST_GLAPI value in the TLS
		area. If no SST_GLAPI TLS value exists, create and store it.
	*/
	
	/* Free any previous API in use */
	if(api != NULL)
		freeGLAPI(api);

	/* No libGL name provided? */
	if(libGLName == NULL)
		libGLName = defaultLibGLName();	/* Use default */
		
	/* Duplicate the name of the library for future reference */
	libName = dupstr(libGLName);
	if(libName == NULL)
		return 0;

	/* Attempt to open libGL by name */
	libGL = openLibGL(libName);
	if(libGL == NULL)
	{
		closeLibGL(libGL);
		free(libName);
		return 0;
	}

	/* Get pointer to symbol resolving function. If this isn't a valid libGL
	implementation, this will fail (e.g. specifying "libc.so.6" would fail here) */
	if(getResolver(libGL, &resolver) == 0)
	{
		closeLibGL(libGL);
		free(libName);
		return 0;
	}
	
	/* No SST_GLAPI for this thread -- allocate it now */
	if(api == NULL)
	{
		api = (SST_GLAPI*)calloc(1, sizeof(SST_GLAPI));
		if(api == NULL)
		{
			closeLibGL(libGL);
			free(libName);
			return 0;
		}
		
		/* Save API pointer */
		__sstglctx = api;
	}
	
	/* Resolve all symbols and save libGL handle */
	resolveGLAPI(&resolver, api);
	api->libGL = libGL;
	api->libGLName = libName;
	
	return 1;
}

/*************************************************************************/

void SST_GLAPI_ShutdownForThread()
{
	SST_GLAPI* api = __sstglctx;
	
	if(api != NULL)
	{
		freeGLAPI(api);
		free(api);
		__sstglctx = NULL;
	}
}

/*************************************************************************/

SST_GLAPI* SST_GLAPI_GetThreadGLAPI()
{
	return __sstglctx;
}

/*************************************************************************/

int SST_GLAPI_CopyForThread(const SST_GLAPI* newapi)
{
	SST_GLAPI* api = __sstglctx;
	void* libGL;
	char* libGLName;
	
	if(newapi->libGL != NULL && newapi->libGLName != NULL)
	{
		/* Re-open libGL (to increment reference count) */
		libGL = openLibGL(newapi->libGLName);
		if(libGL == NULL)
			return 0;
		
		/* Duplicate libGL name */
		libGLName = dupstr(newapi->libGLName);
		if(libGLName == NULL)
		{
			closeLibGL(libGL);
			return 0;
		}
	}
	else /* Not using a libGL implementation (e.g. user functions) */
	{
		libGL = NULL;
		libGLName = NULL;
	}
	
	/* No previous API pointer? */
	if(api == NULL)
	{
		/* Allocate a new one */
		api = (SST_GLAPI*)calloc(1, sizeof(SST_GLAPI));
		if(api == NULL)
		{
			if(libGL != NULL)
				closeLibGL(libGL);
			if(libGLName != NULL)
				free(libGLName);
			return 0;
		}
			
		/* Save API pointer */
		__sstglctx = api;

	}

	/* Copy API, but save the new libGL name and libGL handle */
	memcpy(api, newapi, sizeof(SST_GLAPI));
	api->libGL = libGL;
	api->libGLName = libGLName;
	
	return 1;
}

/*************************************************************************/

/* strdup() implementation */
static char* dupstr(const char* s)
{
	size_t len;
	char* copy;
	
	len = strlen(s);
	copy = malloc(len+1);
	if(copy == NULL)
		return NULL;
	
	/* Copy whole string (including null terminator) */
	memcpy(copy, s, len+1);

	return copy;
}

/*************************************************************************/

static void freeGLAPI(SST_GLAPI* api)
{
	/* Free name of library in use */
	if(api->libGLName)
		free(api->libGLName);
	
	/* Close the library itself */
	if(api->libGL)
		closeLibGL(api->libGL);
	
	/* In case we downgrade in GL version, erase previous pointers */
	memset(api, 0, sizeof(SST_GLAPI));
}

