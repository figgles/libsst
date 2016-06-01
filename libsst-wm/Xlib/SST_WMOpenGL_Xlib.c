/*
	SST_WMOpenGL_Xlib.c
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 1/13/2013

	Purpose:

	OpenGL context creation on X Windows

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/
#include <SST/SST_WMOpenGL.h>
#include "XlibPrivate.h"
#include "GLXPrivate.h"
#include "APIPrivate.h"

/*
	NOTE: We don't include <GL/gl.h> because it may not exist! Many embedded Linux
	systems now ship with OpenGL|ES only, and because of that, they don't have
	headers for full OpenGL. This API supports both, so we can't assume any OpenGL
	headers (either regular or "ES") exist.
*/

/******************************************************************************/

static SST_OpenGLContext Xlib_CreateOpenGLContext(SST_DisplayTarget target, SST_WMOpenGLType apiType, const SST_OpenGLContextAttributes* attribs, SST_OpenGLContextAttributes* selectedAttribsReturn)
{
	SST_DisplayTarget_Xlib* displayTarget = (SST_DisplayTarget_Xlib*)target;
	SST_OpenGLContext glctx;
	Bool usingGLX = True;
	Display* display = displayTarget->display;

	/* If using GL|ES, only EGL will do */
	if(apiType == SSTGL_OPENGL_ES)
		usingGLX = False;
	else /* We can use either GLX or EGL to create a full GL context */
	{
		/* Not loaded -> fail */
		if(!isGLXLoaded())
			usingGLX = False;
			
		/* The client has GLX libraries, but does the server support it? */
		if(!isGLXSupported(display))
			usingGLX = False;

		/* GLX isn't supported */
		if(usingGLX == False)
		{
			/* TODO: try EGL */
			return NULL;
		}

	}


	if(usingGLX)
	{
		glctx = GLXCreateOpenGLContext(displayTarget, apiType, attribs, selectedAttribsReturn);
	}
	else
	{
		/* TODO: Add EGL path */
		return NULL;
	}

	return glctx;
}

/******************************************************************************/

static SST_OpenGLContext Xlib_CreateSlaveOpenGLContext(SST_OpenGLContext masterGLContext)
{
	SST_OpenGLContext_Xlib* master = (SST_OpenGLContext_Xlib*)masterGLContext;
	SST_OpenGLContext_Xlib* slave;

	#if 0
	HWND hInvisWnd;
	FindMonitorInfo fmi;
	HDC hDC = NULL;
	HGLRC hGLRC = NULL;
	BOOL ok;
	const WGLFunctions* wgl = &master->wgl;

	/* Since the slave context merely needs to be on *a* screen controlled by the display target, just use the first one */
	findMonitor(&master->displayTarget->devs[0], &fmi);
	if(!fmi.foundIt)
		return NULL;

	/* Make 1x1 hidden window that doesn't appear in the titlebar and has no borders */
	hInvisWnd = CreateWindowExA(WS_EX_TOOLWINDOW, SST_WINCLASS, "(temp)", WS_POPUP, fmi.left, fmi.top, 1, 1, NULL, NULL, GetModuleHandleA(NULL), NULL);
	if(hInvisWnd == NULL)
		return NULL;
	ShowWindow(hInvisWnd, SW_HIDE);

	/* Allocate context structure */
	slave = HeapAlloc(GetProcessHeap(), 0, sizeof(SST_OpenGLContext_Win32));
	if(slave == NULL)
	{
		DestroyWindow(hInvisWnd);
		return NULL;
	}

	ok = FALSE;
	hDC = GetDC(hInvisWnd);

	/* If master context was done using legacy functions... */
	if(master->isLegacy)
	{
		PIXELFORMATDESCRIPTOR pfd;

		/* Get the PFD for this pixel foramt */
		DescribePixelFormat(hDC, master->pixelFormat, sizeof(pfd), &pfd);

		/* Set it */
		if(SetPixelFormat(hDC, master->pixelFormat, &pfd))
		{
			hGLRC = wgl->CreateContext(hDC);
			if(hGLRC != NULL)
			{
				if(wgl->ShareLists(master->context, hGLRC))
					ok = TRUE;
			}
		}

	}
	else /* Modern OpenGL functions */
	{
		if(SetPixelFormat(hDC, master->pixelFormat, NULL))
		{
			HGLRC oldRC;
			HDC oldDC;

			oldDC = wgl->GetCurrentDC();
			oldRC = wgl->GetCurrentContext();

			/* Bind master context so we can call wgl extension functions. Note that we're using
			the invisible window's HDC. This should work because we just set the pixel format to be
			identical to the master context, meaning they should be compatible */
			if(wgl->MakeCurrent(hDC, master->context))
			{
				int attrs[16];
				int* ptr = attrs;
				int ctxFlags;

				if(master->debugEnabled)
					ctxFlags |= WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB;

				ptr = addAttr(ptr, WGL_CONTEXT_MAJOR_VERSION_ARB, master->ctxVersion[0]);
				ptr = addAttr(ptr, WGL_CONTEXT_MINOR_VERSION_ARB, master->ctxVersion[1]);
				ptr = addAttr(ptr, WGL_CONTEXT_LAYER_PLANE_ARB, 0);

				/* If WGL_ARB_create_context_profile is supported, add a profile mask */
				if(wgl->supportsProfiles)
					ptr = addAttr(ptr, WGL_CONTEXT_PROFILE_MASK_ARB, (master->legacyEnabled ? WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB : WGL_CONTEXT_CORE_PROFILE_BIT_ARB));

				/* Legacy-free? */
				if(!master->legacyEnabled)
					ctxFlags |= WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB;

				/* Debug mode? */
				if(master->debugEnabled)
					ctxFlags |= WGL_CONTEXT_DEBUG_BIT_ARB;

				ptr = addAttr(ptr, WGL_CONTEXT_FLAGS_ARB, ctxFlags);
				*ptr = 0;

				/* Create the new context, sharing with the master context */
				hGLRC = wgl->CreateContextAttribsARB(hDC, master->context, attrs);
				if(hGLRC != NULL)
					ok = TRUE;
			}

			/* Restore old context */
			wgl->MakeCurrent(oldDC, oldRC);
		}
	}

	/* Done with the DC */
	if(hDC)
		ReleaseDC(hInvisWnd, hDC);

	/* Did we succeed in making the slave context? */
	if(ok)
	{
		/* Set up slave context info */
		slave->context = hGLRC;
		slave->displayTarget = master->displayTarget;
		slave->hDCActive = NULL;
		slave->hSlaveWnd = hInvisWnd;
		slave->isLegacy = master->isLegacy;
		slave->opengl32 = LoadLibraryA("opengl32.dll"); /* Need to increase ref count for opengl32.dll */
		slave->pixelFormat = master->pixelFormat;
		slave->wgl = master->wgl; /* TODO: should be safe, right? context dependent, but same device/GL impl... */
		slave->ctxVersion[0] = master->ctxVersion[0];
		slave->ctxVersion[1] = master->ctxVersion[1];
		slave->legacyEnabled = master->legacyEnabled;
		slave->debugEnabled = master->debugEnabled;
	}
	else /* Failure, clean up */
	{
		if(hGLRC)
			master->wgl.DeleteContext(hGLRC);

		DestroyWindow(hInvisWnd);

		HeapFree(GetProcessHeap(), 0, slave);
		slave = NULL;
	}
	#endif
	return slave;
}

/******************************************************************************/

static void Xlib_SwapOpenGLBuffers(SST_OpenGLContext ctx)
{
	SST_OpenGLContext_Xlib* glctx = (SST_OpenGLContext_Xlib*)ctx;

	if(glctx->glxcontext)
		glX.SwapBuffers(glctx->displayTarget->display, glctx->win);
	else
	{
		/* TODO: eglSwapBuffers() */
	}
}

/******************************************************************************/

static int Xlib_BindOpenGLContext(SST_OpenGLContext ctx, SST_Window window)
{
	SST_OpenGLContext_Xlib* glctx = (SST_OpenGLContext_Xlib*)ctx;
	SST_Window_Xlib* win = (SST_Window_Xlib*)window;

	/* Unbinding a context from a thread */
	if(ctx == NULL)
	{

		/* GLX: Unbind context */
		if(glctx->glxcontext)
		{
			glX.MakeContextCurrent(glctx->displayTarget->display, None, None, NULL);

			glctx->win = None;
		}
		else
		{
			/* TODO: EGL implementation */
		}

		/* OK */
		return 1;
	}

	/* GLX*/
	if(glctx->glxcontext)
	{

		/* Binding master context to a window */
		if(win != NULL)
		{
			if(glX.MakeContextCurrent(glctx->displayTarget->display, win->xwin, win->xwin, glctx->glxcontext))
			{
				glctx->win = win->xwin;
				return 1;
			}

			/* Failed to bind */
			return 0;
		}
		else /* Bind slave context */
		{
			/* TODO: bind to a slave's pbuffer, I guess? */
		}
	}
	else /* Otherwise EGL */
	{
		/* TODO: EGL */
	}

	return 0;
}

/******************************************************************************/

static void Xlib_DestroyOpenGLContext(SST_OpenGLContext ctx)
{
	SST_OpenGLContext_Xlib* glctx = (SST_OpenGLContext_Xlib*)ctx;

#if 0
	if(glctx->hSlaveWnd)
		DestroyWindow(glctx->hSlaveWnd);
#endif

	/* Destroy the OpenGL context */
	glX.DestroyContext(glctx->displayTarget->display, glctx->glxcontext);

	/* Free memory used by our GL context */
	free(glctx);
}

/******************************************************************************/
const struct SST_WM_OpenGLFuncs Xlib_OpenGLFuncs = {
	Xlib_CreateOpenGLContext,
	Xlib_CreateSlaveOpenGLContext,
	Xlib_SwapOpenGLBuffers,
	Xlib_BindOpenGLContext,
	Xlib_DestroyOpenGLContext
};
