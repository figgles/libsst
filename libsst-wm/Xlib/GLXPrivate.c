/*
	GLXPrivate.c
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 1/11/2013

	Purpose:

	OpenGL on X Windows (GLX) utility code

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#include <SST/SST_WMOpenGL.h>
#include "XlibPrivate.h"
#include <dlfcn.h>
#include <string.h>
#include <stdio.h>

/* GL constants */
#define GL_VERSION 0x1F02

/* GLX constants */
#define GLX_DOUBLEBUFFER		5
#define GLX_STEREO				6
#define GLX_AUX_BUFFERS			7
#define GLX_RED_SIZE			8
#define GLX_GREEN_SIZE			9
#define GLX_BLUE_SIZE			10
#define GLX_ALPHA_SIZE			11
#define GLX_DEPTH_SIZE			12
#define GLX_STENCIL_SIZE		13
#define GLX_RGBA_TYPE			0x8014
/* GLX_ARB_multisample */
#define GLX_SAMPLE_BUFFERS_ARB	100000
#define GLX_SAMPLES_ARB			100001

#define GLX_PBUFFER_HEIGHT		0x8040
#define GLX_PBUFFER_WIDTH		0x8041

/* GLX_ARB_create_context[_profile] */
#define GLX_CONTEXT_MAJOR_VERSION_ARB				0x2091
#define GLX_CONTEXT_MINOR_VERSION_ARB				0x2092
#define GLX_CONTEXT_FLAGS_ARB						0x2094
#define GLX_CONTEXT_PROFILE_MASK_ARB				0x9126
#define GLX_CONTEXT_DEBUG_BIT_ARB					0x0001
#define GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB		0x0002
#define GLX_CONTEXT_CORE_PROFILE_BIT_ARB			0x00000001
#define GLX_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB	0x00000002

GLXFunctions glX = { 0 };

static void setupAttribs(int* glxAttr, const SST_OpenGLContextAttributes* attribs, Bool supportsMultisample);
static int* addAttr(int* ptr, int attr, int value)
{
	ptr[0] = attr;
	ptr[1] = value;
	return ptr + 2;
}

/******************************************************************************/

int loadGLX()
{
	const int flags = RTLD_LAZY | RTLD_GLOBAL;
	void* libGL;

	/* Set all values to null/0/false */
	memset(&glX, 0, sizeof(GLXFunctions));

	/* Load OpenGL library with proper DT_SONAME */
	libGL = dlopen("libGL.so.1", flags);
	if(libGL == NULL)
	{
		/* Failed...try generic name for it */
		libGL = dlopen("libGL.so", flags);
		if(libGL == NULL)
			return 0;
	}

	/* Resolve symbols */
	glX.QueryExtension = dlsym(libGL, "glXQueryExtension");
	glX.QueryVersion = dlsym(libGL, "glXQueryVersion");
	glX.QueryExtensionsString = dlsym(libGL, "glXQueryExtensionsString");
	glX.ChooseFBConfig = dlsym(libGL, "glXChooseFBConfig");
	glX.CreateNewContext = dlsym(libGL, "glXCreateNewContext");
	glX.DestroyContext = dlsym(libGL, "glXDestroyContext");
	glX.MakeContextCurrent = dlsym(libGL, "glXMakeContextCurrent");
	glX.GetCurrentContext = dlsym(libGL, "glXGetCurrentContext");
	glX.SwapBuffers = dlsym(libGL, "glXSwapBuffers");
	glX.CreatePbuffer = dlsym(libGL, "glXCreatePbuffer");
	glX.DestroyPbuffer = dlsym(libGL, "glXDestroyPbuffer");
	glX.CreateContextAttribsARB = dlsym(libGL, "glXCreateContextAttribsARB");

	/* On Linux, glXGetProcAddressARB() is statically exported from libGL.so as part of LSB. However,
	on non-LSB compliant or other UNIX systems, the -ARB version may not exist. Try the unsuffixed
	form if the -ARB variant does not exist. */
	glX.GetProcAddressARB = dlsym(libGL, "glXGetProcAddressARB");
	if(glX.GetProcAddressARB == NULL)
		glX.GetProcAddressARB = dlsym(libGL, "glXGetProcAddress");

	/* Save library handle */
	glX.libGL = libGL;
	return 1;
}

/******************************************************************************/

void unloadGLX()
{
	dlclose(glX.libGL);
}

/******************************************************************************/

int isGLXLoaded()
{
	return (glX.libGL != NULL);
}

/******************************************************************************/

int isGLXSupported(Display* display)
{
	int major = 0, minor = 0;
	int combined;
	const char* ext;

	/* Query if the X server supports GLX. If it doesn't, then nothing to do */
	if(glX.QueryExtension(display, NULL, NULL) == False)
	{
		fprintf(stderr, "%s:GLX extension not supported on this connection.\n", "libsst-wm");
		return 0;
	}

	/* Query the version; we need 1.3 or later */
	if(glX.QueryVersion(display, &major, &minor) == False)
	{
		fprintf(stderr, "%s:Unable to query GLX version.\n", "libsst-wm");
		return 0;
	}

	/* Fail on less than 1.3 */
	combined = (major << 8) | minor;
	if(combined < 0x13)
	{
		fprintf(stderr, "%s:GLX version 1.3 required, found %d.%d\n", "libsst-wm", major, minor);
		return 0;
	}

	ext = glX.QueryExtensionsString(display, DefaultScreen(display));

	/* "GLX_ARB_create_context" and "GLX_ARB_create_context_profile" might both match the first strstr(),
	but "GLX_ARB_create_context_profile" requires the former, so it's all good.
	TODO: write less stupid extension checker - one day may not be true */
	if(combined >= 0x14) /* GLX 1.4 required for GLX_ARB_create_context */
	{
		glX.supportsCreateContextARB = (Bool)(strstr(ext, "GLX_ARB_create_context") != NULL);
		glX.supportsProfiles = (Bool)(strstr(ext, "GLX_ARB_create_context_profile") != NULL);
	}
	else /* Don't have GLX 1.4, so can't possibly have these */
	{
		glX.supportsCreateContextARB = False;
		glX.supportsProfiles = False;
	}

	glX.supportsMultisample = (Bool)(strstr(ext, "GLX_ARB_multisample") != NULL);

	return 1;
}

/******************************************************************************/

SST_OpenGLContext GLXCreateOpenGLContext(SST_DisplayTarget_Xlib* displayTarget, SST_WMOpenGLType apiType, const SST_OpenGLContextAttributes* attribs, SST_OpenGLContextAttributes* selectedAttribsReturn)
{
	int attr[MAX_GL_ATTRS];
	Display* display = displayTarget->display;
	GLXFBConfig* configs;
	GLXFBConfig fbconfig;
	GLXContext ctx;
	int nrConfigs = 0;
	SST_OpenGLContext_Xlib* GLctx;
	uint8_t major, minor;
	GLXPbuffer pb;
	const int pbattr[5] = { GLX_PBUFFER_WIDTH, 1, GLX_PBUFFER_HEIGHT, 1, None };

	/* GLX cannot be used to do anything other than standard OpenGL */
	if(apiType != SSTGL_OPENGL)
		return NULL;

	/* GLX doesn't support multisampling, but it was explicitly requested */
	if(!glX.supportsMultisample && attribs->multisampleFactor > 1)
		return NULL;

	/* Copy SST attributes to GLX attributes */
	setupAttribs(attr, attribs, glX.supportsMultisample);

	/* Get a list of configs -- we're going to only use the first one though */
	configs = glX.ChooseFBConfig(display, DefaultScreen(display), attr, &nrConfigs);
	if(configs == NULL)
		return NULL;

	/* Copy first FBConfig entry, free array */
	fbconfig = *configs;
	X.Free(configs);

	/* Use the new create context functions? */
	if(glX.supportsCreateContextARB)
	{
		int attr[32];
		int* ptr = &attr[0];
		int ctxFlags = 0;

		/* Set the major/minor version */
		ptr = addAttr(ptr, GLX_CONTEXT_MAJOR_VERSION_ARB, attribs->contextVersionMajor);
		ptr = addAttr(ptr, GLX_CONTEXT_MINOR_VERSION_ARB, attribs->contextVersionMinor);

		/* If GLX_ARB_create_context_profile is supported, add a profile mask */
		if(glX.supportsProfiles)
			ptr = addAttr(ptr, GLX_CONTEXT_PROFILE_MASK_ARB, (attribs->legacyEnabled ? GLX_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB : GLX_CONTEXT_CORE_PROFILE_BIT_ARB));

		/* Enable/disable forward compatibility */
		if(!attribs->legacyEnabled)
			ctxFlags |= GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB;

		/* Debug mode? */
		if(attribs->debugEnabled)
			ctxFlags |= GLX_CONTEXT_DEBUG_BIT_ARB;

		ptr = addAttr(ptr, GLX_CONTEXT_FLAGS_ARB, ctxFlags);
		*ptr = None;


		ctx = glX.CreateContextAttribsARB(display, fbconfig, NULL, True, attr);
		if(ctx == NULL)
			return NULL;

	}
	else /* Use older GLX 1.3 glXCreateNewContext() function */
	{
		/* Attempt to create an OpenGL context */
		ctx = glX.CreateNewContext(display, fbconfig, GLX_RGBA_TYPE, NULL, True);
		if(ctx == NULL)
			return NULL;
	}

	/* In order to check the version number, we're going to need to create
	a temporary context. I'm using a Pbuffer to do so. */
	pb = glX.CreatePbuffer(display, fbconfig, pbattr);
	if(pb == None)
	{
		glX.DestroyContext(display, ctx);
		return NULL;
	}

	/* Activate it */
	if(glX.MakeContextCurrent(display, pb, pb, ctx))
	{
		const char* (*pglGetString)(unsigned int);
		const char* version;

		/* Check libGL for this */
		pglGetString = dlsym(glX.libGL, "glGetString");

		version = pglGetString(GL_VERSION);

		major = (uint8_t)(version[0] - '0'); /* "X.Y" -> [0]:major, [2]:minor */
		minor = (uint8_t)(version[2] - '0');

		/* Save context version information */
		if(selectedAttribsReturn != NULL)
		{
			selectedAttribsReturn->contextVersionMajor = (uint8_t)major;
			selectedAttribsReturn->contextVersionMinor = (uint8_t)minor;
		}

		/* OK, we have the information we need. Unbind the context and destroy the Pbuffer */
		glX.MakeContextCurrent(display, None, None, NULL);
		glX.DestroyPbuffer(display, pb);

		/* If the major version is too low or the major version is OK, but the minor version is lacking, then fail */
		if(major < attribs->contextVersionMajor || (major == attribs->contextVersionMajor && minor < attribs->contextVersionMinor))
		{
			glX.DestroyContext(display, ctx);
			return NULL;
		}
	}
	else /* Failed to make current */
	{
		glX.DestroyContext(display, ctx);
		glX.DestroyPbuffer(display, pb);
		return NULL;
	}



	GLctx = (SST_OpenGLContext_Xlib*)malloc(sizeof(SST_OpenGLContext_Xlib));
	if(GLctx == NULL)
	{
		glX.DestroyContext(display, ctx);
		return NULL;
	}

	GLctx->glxcontext = ctx;
	GLctx->displayTarget = displayTarget;
	GLctx->ctxVersion[0] = major;
	GLctx->ctxVersion[1] = minor;

	return GLctx;
}

/******************************************************************************/

static void setupAttribs(int* glxAttr, const SST_OpenGLContextAttributes* attribs, Bool supportsMultisample)
{
	int* ptr = glxAttr;
	int r, b, g;


	switch(attribs->colorBits)
	{
		/* Since these values are "at least", 5-5-5 and 5-6-5 configurations can use the same number */
		case 15:
		case 16:
			r = g = b = 5;
			break;

		case 24:
			r = g = b = 8;

	}

	ptr = addAttr(ptr, GLX_DOUBLEBUFFER, True);
	ptr = addAttr(ptr, GLX_STEREO, (attribs-> stereoEnabled != 0));
	ptr = addAttr(ptr, GLX_RED_SIZE, r);
	ptr = addAttr(ptr, GLX_GREEN_SIZE, r);
	ptr = addAttr(ptr, GLX_BLUE_SIZE, b);
	ptr = addAttr(ptr, GLX_ALPHA_SIZE, ((int)attribs->alphaBits) & 0xFF);
	ptr = addAttr(ptr, GLX_DEPTH_SIZE, ((int)attribs->depthBits) & 0xFF);
	ptr = addAttr(ptr, GLX_STENCIL_SIZE, ((int)attribs->stencilBits) & 0xFF);

	/* Add multisample attributes as appropriate */
	if(attribs->multisampleFactor > 1 && supportsMultisample)
	{
		ptr = addAttr(ptr, GLX_SAMPLE_BUFFERS_ARB, 1);
		ptr = addAttr(ptr, GLX_SAMPLES_ARB, ((int)attribs->multisampleFactor) & 0xFF);
	}

	/* End attribute list */
	*ptr = None;

}
