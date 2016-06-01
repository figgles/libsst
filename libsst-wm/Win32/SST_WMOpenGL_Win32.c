/*
	SST_WMOpenGL_Win32.c
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 6/28/2012

	Purpose:

	OpenGL context creation

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/
#include <SST/SST_WMOpenGL.h>
#include "Win32Private.h"
#include "../APIPrivate.h"
#include <GL/gl.h>

/*
	NOTE: Herein lines madness. Abandon faith all ye who would enter.

	Windows has been notoriously bad at keeping up with OpenGL progress. In particular, to get a modern context,
	one must:

	1) Create a fake window
	2) Select a fake pixel format
	4) Create a fake GL context
	5) Bind that context
	6) Resolve the wglGetExtensionStringARB() symbol
	7) Call wglGetExtensionStringARB() and check for various WGL extensions
	8) Resolve required extensions
	9) Select a real pixel format
	10) Create a real context

	This doesn't even consider the complexity of handling issues such as pushing/popping the current OpenGL context
	so that calling SST_WM_CreateOpenGLContext() doesn't result in losing the currently active context, or providing
	fallbacks in case the person wants GL <= 2.x and doesn't have the GL >= 3.x WGL extensions. So much madness.
*/

/* Create a temporary 1x1 window that is invisible */
static HWND createTmpWindow(SST_DisplayTarget_Win32* copyFrom);

/* Create OpenGL context that would probably work with Windows 95 */
static SST_OpenGLContext legacyCreateOpenGLContext(SST_DisplayTarget_Win32* win, const SST_OpenGLContextAttributes* attribs, SST_OpenGLContextAttributes* selectedAttribsReturn, HMODULE opengl32, WGLFunctions* wgl);

/* Use wglChoosePixelFormatARB() to find a useful pixel format */
static int modernChoosePixelFormat(HDC hDC, WGLFunctions* wgl, const SST_OpenGLContextAttributes* attribs);

/* Get selected pixel format return value information */
static void modernGetPixelInfo(HDC hDC, int format, WGLFunctions* wgl, SST_OpenGLContextAttributes* selectedAttribsReturn);

static int* addAttr(int* ptr, int x, int y)
{
	ptr[0] = x;
	ptr[1] = y;
	return ptr + 2;
}

/*************************************************************************/

static SST_OpenGLContext Win32_CreateOpenGLContext(SST_DisplayTarget target, SST_WMOpenGLType apiType, const SST_OpenGLContextAttributes* attribs, SST_OpenGLContextAttributes* selectedAttribsReturn)
{
	HMODULE opengl32;
	HWND hTmpWnd, hTmpWnd2;
	HDC hTmpDC, hTmpDC2, oldDC = NULL;
	HGLRC hTmpCtx, oldRC = NULL;
	PIXELFORMATDESCRIPTOR pfd;
	WGLFunctions wgl;
	SST_DisplayTarget_Win32* displayTarget = (SST_DisplayTarget_Win32*)target;
	SST_OpenGLContext_Win32* glctx;
	int format;
	int OK;

	/* Win32 doesn't have OpenGL ES AFAIK. */
	if(apiType == SSTGL_OPENGL_ES)
		return NULL;

	/* Load opengl32.dll */
	opengl32 = LoadLibraryA("opengl32.dll");
	if(opengl32 == NULL)
		return NULL;

	memset(&wgl, 0, sizeof(wgl));
	resolveWGLSymbols(opengl32, &wgl);

	/*
		OK, this next code attempts to create an invisible window which can then be used
		to bind a fake GL context to. This allows us to grab WGL extensions for advanced
		OpenGL context creation (i.e. forward compatible contexts). If this isn't supported,
		then old style context creation will be used as a fallback.
	*/
	hTmpWnd = createTmpWindow(displayTarget);
	if(hTmpWnd == NULL)
	{
		FreeLibrary(opengl32);
		return NULL;
	}

	/* Grab the window's DC */
	hTmpDC = GetDC(hTmpWnd);

	/* Initialize pixel format descriptor to find 24-bit color / double-buffered / render to window */
	memset(&pfd, 0, sizeof(pfd));
	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_DRAW_TO_WINDOW;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cRedBits = 8;
	pfd.cGreenBits = 8;
	pfd.cBlueBits = 8;
	pfd.cDepthBits = 24;
	pfd.iLayerType = PFD_MAIN_PLANE;

	/* Attempt to find a matching pixel format */
	OK = 0;
	hTmpCtx = NULL;
	format = ChoosePixelFormat(hTmpDC, &pfd);
	if(format > 0)
	{
		/* Attempt to set the pixel format */
		OK = (int)SetPixelFormat(hTmpDC, format, &pfd);
		if(OK)
		{
			/* Create the context */
			hTmpCtx = wgl.CreateContext(hTmpDC);
			OK = (hTmpCtx != NULL);

			/* Bind it */
			if(OK)
			{
				/* Save old context */
				oldDC = wgl.GetCurrentDC();
				oldRC = wgl.GetCurrentContext();

				OK = (int)wgl.MakeCurrent(hTmpDC, hTmpCtx);
			}
		}
	}

	/* Failed in any of these steps? */
	if(!OK)
	{
		if(hTmpCtx != NULL)
		{
			wgl.DeleteContext(hTmpCtx);

			/* Restore old context (since wglMakeCurrent() failed with new context) */
			wgl.MakeCurrent(oldDC, oldRC);

		}
		ReleaseDC(hTmpWnd, hTmpDC);
		DestroyWindow(hTmpWnd);
		FreeLibrary(opengl32);
		return NULL;
	}

	/* Resolve context-specific strings */
	resolveWGLExtSymbols(hTmpDC, &wgl);

	/* Only "legacy" context functions allowed? */
	if(wgl.ChoosePixelFormatARB == NULL || wgl.CreateContextAttribsARB == NULL)
	{
		/* Remove temporary context / window, they aren't needed for legacy contexts */
		wgl.MakeCurrent(oldDC, oldRC);
		wgl.DeleteContext(hTmpCtx);
		ReleaseDC(hTmpWnd, hTmpDC);
		DestroyWindow(hTmpWnd);

		/* Just make a legacy context */
		return legacyCreateOpenGLContext(displayTarget, attribs, selectedAttribsReturn, opengl32, &wgl);
	}
	else /* "Modern" context creation */
	{
		#define MAX_CTX_ATTRS 16
		int contextAttrs[MAX_CTX_ATTRS];
		int* ptr;
		HGLRC hGLRC;
		size_t i;
		int ctxFlags = 0;

		/* Create another set of temporary handles. Since we already called
		SetPixelFormat() on hTmpDC, we can't set it to the new pixel format
		that we picked with modernChoosePixelFormat(). Thus, if we do wglCreateContext() with
		hTmpDC, we'll get an invalid context. Instead, create a new window/DC and use the new
		pixel format. */
		hTmpWnd2 = createTmpWindow(displayTarget);
		hTmpDC2 = GetDC(hTmpWnd2);

		/* Choose a pixel format */
		format = modernChoosePixelFormat(hTmpDC2, &wgl, attribs);
		if(format == 0)
		{
			wgl.MakeCurrent(oldDC, oldRC);
			wgl.DeleteContext(hTmpCtx);
			ReleaseDC(hTmpWnd, hTmpDC);
			DestroyWindow(hTmpWnd);
		}
		SetPixelFormat(hTmpDC2, format, NULL);

		i = 0;

		if(attribs->debugEnabled)
			ctxFlags |= WGL_CONTEXT_DEBUG_BIT_ARB;
		ptr = contextAttrs;
		ptr = addAttr(ptr, WGL_CONTEXT_MAJOR_VERSION_ARB, attribs->contextVersionMajor);
		ptr = addAttr(ptr, WGL_CONTEXT_MINOR_VERSION_ARB, attribs->contextVersionMinor);
		ptr = addAttr(ptr, WGL_CONTEXT_LAYER_PLANE_ARB, 0);

		/* If WGL_ARB_create_context_profile is supported, add a profile mask */
		if(wgl.supportsProfiles)
			ptr = addAttr(ptr, WGL_CONTEXT_PROFILE_MASK_ARB, (attribs->legacyEnabled ? WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB : WGL_CONTEXT_CORE_PROFILE_BIT_ARB));

		/* Legacy-free? */
		if(!attribs->legacyEnabled)
			ctxFlags |= WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB;

		/* Debug mode? */
		if(attribs->debugEnabled)
			ctxFlags |= WGL_CONTEXT_DEBUG_BIT_ARB;

		ptr = addAttr(ptr, WGL_CONTEXT_FLAGS_ARB, ctxFlags);
		*ptr = 0;



		/* Create the OpenGL context */
		hGLRC = wgl.CreateContextAttribsARB(hTmpDC2, NULL, contextAttrs);
		glctx = (SST_OpenGLContext_Win32*)HeapAlloc(GetProcessHeap(), 0, sizeof(SST_OpenGLContext_Win32));
		if(hGLRC == NULL || glctx == NULL)
		{
			if(hGLRC != NULL)
				wgl.DeleteContext(hGLRC);
			if(glctx != NULL)
				HeapFree(GetProcessHeap(), 0, glctx);
			wgl.MakeCurrent(oldDC, oldRC);
			wgl.DeleteContext(hTmpCtx);
			ReleaseDC(hTmpWnd, hTmpDC);
			DestroyWindow(hTmpWnd);
			ReleaseDC(hTmpWnd2, hTmpDC2);
			DestroyWindow(hTmpWnd2);

			return NULL;
		}
		glctx->displayTarget = displayTarget;
		glctx->context = hGLRC;
		glctx->hDCActive = NULL;
		glctx->hSlaveWnd = NULL;
		glctx->opengl32 = opengl32;
		glctx->pixelFormat = format;
		glctx->wgl = wgl;
		glctx->isLegacy = FALSE;
		glctx->ctxVersion[0] = (short)attribs->contextVersionMajor;
		glctx->ctxVersion[1] = (short)attribs->contextVersionMinor;
		glctx->legacyEnabled = attribs->legacyEnabled? TRUE : FALSE;
		glctx->debugEnabled = attribs->debugEnabled? TRUE : FALSE;

		if(selectedAttribsReturn)
		{
			modernGetPixelInfo(hTmpDC2, format, &wgl, selectedAttribsReturn);
			selectedAttribsReturn->contextVersionMajor = attribs->contextVersionMajor;
			selectedAttribsReturn->contextVersionMinor = attribs->contextVersionMinor;
			selectedAttribsReturn->legacyEnabled = (attribs->legacyEnabled ? 1 : 0);
			selectedAttribsReturn->debugEnabled = (ctxFlags & WGL_CONTEXT_DEBUG_BIT_ARB ? 1 : 0);
		}

		/* Delete temporary window */
		wgl.MakeCurrent(oldDC, oldRC);
		wgl.DeleteContext(hTmpCtx);
		ReleaseDC(hTmpWnd, hTmpDC);
		DestroyWindow(hTmpWnd);
		ReleaseDC(hTmpWnd2, hTmpDC2);
		DestroyWindow(hTmpWnd2);
	}

	return glctx;
}

/*************************************************************************/

static SST_OpenGLContext Win32_CreateSlaveOpenGLContext(SST_OpenGLContext masterGLContext)
{
	SST_OpenGLContext_Win32* master = (SST_OpenGLContext_Win32*)masterGLContext;
	SST_OpenGLContext_Win32* slave;
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

	return slave;
}

/*************************************************************************/

static void Win32_SwapOpenGLBuffers(SST_OpenGLContext ctx)
{
	SST_OpenGLContext_Win32* glctx = (SST_OpenGLContext_Win32*)ctx;

	SwapBuffers(glctx->hDCActive);
}

/*************************************************************************/

static int Win32_BindOpenGLContext(SST_OpenGLContext ctx, SST_Window window)
{
	SST_OpenGLContext_Win32* glctx = (SST_OpenGLContext_Win32*)ctx;
	SST_Window_Win32* win = (SST_Window_Win32*)window;

	/* Unbinding a context from a thread */
	if(ctx == NULL)
	{
		HMODULE opengl32;

		/* We actually need some WGL symbols. Oops. That's OK, we can just grab the symbol */
		pf_wglMakeCurrent sst_wglMakeCurrent;
		pf_wglGetCurrentDC sst_wglGetCurrentDC;

		/* We use LoadLibrary() instead of GetModuleHandle() so that we don't unmap the DLL
		in the middle of using it. */
		opengl32 = LoadLibraryA("opengl32.dll");
		if(opengl32)
		{
			HDC hDC;
			HWND hWnd;

			sst_wglMakeCurrent = (pf_wglMakeCurrent)GetProcAddress(opengl32, "wglMakeCurrent");
			sst_wglGetCurrentDC = (pf_wglGetCurrentDC)GetProcAddress(opengl32, "wglGetCurrentDC");

			/* Release the DC */
			hDC = sst_wglGetCurrentDC();
			hWnd = WindowFromDC(hDC);
			if(hDC != NULL && hWnd != NULL)
				ReleaseDC(hWnd, hDC);

			/* OK, unbind it */
			sst_wglMakeCurrent(NULL, NULL);

			FreeLibrary(opengl32);
		}

		/* OK */
		return 1;
	}
	else /* Have a valid context */
	{
		HDC hDC, oldDC;
		HGLRC oldRC;

		if(	(glctx->hSlaveWnd != NULL && win != NULL) || /* Slave context provided a SST_Window */
			(glctx->hSlaveWnd == NULL && win == NULL) /* Master context with no SST_Window */
			)
		{
			/* Both are illegal according the the functions */
			return 0;
		}

		/* Get old context info */
		oldDC = glctx->wgl.GetCurrentDC();
		oldRC = glctx->wgl.GetCurrentContext();

		/* First, are we re-binding the same context? If so, then just return "success" */
		if(	oldDC != NULL && oldRC != NULL &&
			oldDC == glctx->hDCActive && oldRC == glctx->context)
			return 1;

		/* Binding master context to a window */
		if(win != NULL)
		{
			hDC = GetDC(win->hWnd);

			/* Haven't set the pixel format for this window yet? */
			if(!win->setPixelFormat)
			{
				PIXELFORMATDESCRIPTOR pfd;
				DescribePixelFormat(hDC, glctx->pixelFormat, sizeof(pfd), &pfd);

				if(SetPixelFormat(hDC, glctx->pixelFormat, &pfd))
				{
					/* OK, mark that we've set this window's pixel format once, and we won't do it again. */
					win->setPixelFormat = TRUE;
				}
				else
				{
					/* Failed to set this window's pixel format, so we can't do much */
					return 0;
				}
			}
		}
		else /* Bind slave context */
		{
			hDC = GetDC(glctx->hSlaveWnd);

		}

		/* Make current */
		if(!glctx->wgl.MakeCurrent(hDC, glctx->context))
		{
			/* Failed -- restore old context settings */
			glctx->wgl.MakeCurrent(oldDC, oldRC);
			return 0;
		}

		/* Since we were successful, release the old DC */
		if(oldDC)
		{
			HWND hWnd = WindowFromDC(oldDC);
			if(hWnd)
				ReleaseDC(hWnd, oldDC);
		}

		/* Save window / DC */
		glctx->hDCActive = hDC;
	}

	return 1;
}

/*************************************************************************/

static void Win32_DestroyOpenGLContext(SST_OpenGLContext ctx)
{
	SST_OpenGLContext_Win32* glctx = (SST_OpenGLContext_Win32*)ctx;

	if(glctx->hSlaveWnd)
		DestroyWindow(glctx->hSlaveWnd);

	glctx->wgl.DeleteContext(glctx->context);
	FreeLibrary(glctx->opengl32);

	HeapFree(GetProcessHeap(), 0, glctx);
}

/*************************************************************************/

static HWND createTmpWindow(SST_DisplayTarget_Win32* copyFrom)
{
	HWND hTmpWnd;
	FindMonitorInfo fmi;

	/* Find the first monitor */
	findMonitor(&copyFrom->devs[0], &fmi);
	if(!fmi.foundIt)
		return NULL;

	/* Make 1x1 hidden window that doesn't appear in the titlebar and has no borders */
	hTmpWnd = CreateWindowExA(WS_EX_TOOLWINDOW, SST_WINCLASS, "(temp)", WS_POPUP, fmi.left, fmi.top, 1, 1, NULL, NULL, GetModuleHandleA(NULL), NULL);
	if(hTmpWnd == NULL)
		return NULL;

	ShowWindow(hTmpWnd, SW_HIDE);

	return hTmpWnd;
}

/*************************************************************************/

static SST_OpenGLContext legacyCreateOpenGLContext(SST_DisplayTarget_Win32* displayTarget, const SST_OpenGLContextAttributes* attribs, SST_OpenGLContextAttributes* selectedAttribsReturn, HMODULE opengl32, WGLFunctions* wgl)
{
	PIXELFORMATDESCRIPTOR pfd;
	HWND hWnd;
	HDC hDC, oldDC = NULL;
	HGLRC hGLRC, oldRC = NULL;
	int format;
	int major, minor;
	const char* version;
	const GLubyte* (APIENTRY *sst_glGetString)(GLenum);
	SST_OpenGLContext_Win32* ctx;
	BYTE rgb[3] = { 1, 1, 1 };

	/* No multisample support, but 2x or greater MSAA requested -> fail */
	if(attribs->multisampleFactor > 1)
	{
		FreeLibrary(opengl32);
		return NULL;
	}

	/* Allocate a GL context */
	ctx = (SST_OpenGLContext_Win32*)HeapAlloc(GetProcessHeap(), 0, sizeof(SST_OpenGLContext_Win32));
	if(ctx == NULL)
	{
		FreeLibrary(opengl32);
		return NULL;
	}

	/* Get window DC */
	hWnd = createTmpWindow(displayTarget);
	hDC = GetDC(hWnd);

	/* We can't do MSAA at all, though */
	if(attribs->multisampleFactor > 1)
	{
		FreeLibrary(opengl32);
		return NULL;
	}

	/* Figure out how to set up color bits. These are minimums. MSDN states that they
	are "Not used", but be safe anyways.  */
	if(attribs->colorBits == 24)
	{
		rgb[0] = rgb[1] = rgb[2] = 8;
	}
	else if(attribs->colorBits == 16 || attribs->colorBits == 15)
	{
		/* 555 or 565 color. Set all to 5 since "minimum" of 5 allows for 565 too */
		rgb[0] = rgb[1] = rgb[2] = 5;
	}

	/* Initialize the PFD */
	memset(&pfd, 0, sizeof(pfd));
	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_DRAW_TO_WINDOW | (attribs->stereoEnabled? PFD_STEREO : 0);
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = attribs->colorBits;
	pfd.cAlphaBits = attribs->alphaBits;
	pfd.cRedBits = rgb[0];
	pfd.cGreenBits = rgb[1];
	pfd.cBlueBits = rgb[2];
	pfd.cDepthBits = attribs->depthBits;
	pfd.cStencilBits = attribs->stencilBits;
	pfd.iLayerType = PFD_MAIN_PLANE;

	/* Get a compatiable pixel format */
	format = ChoosePixelFormat(hDC, &pfd);
	if(format == 0)
	{
		ReleaseDC(hWnd, hDC);
		DestroyWindow(hWnd);
		FreeLibrary(opengl32);
		return NULL;
	}

	/* Get info about the pixel format we're using */
	if(selectedAttribsReturn != NULL)
	{
		PIXELFORMATDESCRIPTOR spfd;
		DescribePixelFormat(hDC, format, sizeof(spfd), &spfd);

		selectedAttribsReturn->alphaBits = pfd.cAlphaBits;
		selectedAttribsReturn->colorBits = pfd.cColorBits;
		selectedAttribsReturn->contextVersionMajor = 0;
		selectedAttribsReturn->contextVersionMinor = 0;
		selectedAttribsReturn->depthBits = pfd.cDepthBits;
		selectedAttribsReturn->multisampleFactor = 1;
		selectedAttribsReturn->stencilBits = pfd.cStencilBits;
		selectedAttribsReturn->stereoEnabled = (pfd.dwFlags & PFD_STEREO);


	}

	/* Set the pixel format for the device */
	if(!SetPixelFormat(hDC, format, &pfd))
	{
		ReleaseDC(hWnd, hDC);
		DestroyWindow(hWnd);
		FreeLibrary(opengl32);
		return NULL;
	}

	/* Create the GL context */
	hGLRC = wgl->CreateContext(hDC);
	if(hGLRC == NULL)
	{
		ReleaseDC(hWnd, hDC);
		DestroyWindow(hWnd);
		FreeLibrary(opengl32);
		return NULL;
	}

	/* Activate the context to see if correct version was set */
	oldDC = wgl->GetCurrentDC();
	oldRC = wgl->GetCurrentContext();
	if(!wgl->MakeCurrent(hDC, hGLRC))
	{
		wgl->DeleteContext(hGLRC);
		ReleaseDC(hWnd, hDC);
		DestroyWindow(hWnd);
		FreeLibrary(opengl32);
		return NULL;
	}

	/* Resolve glGetString() and call it to check version number matching */
	sst_glGetString = (const GLubyte* (APIENTRY*)(GLenum name))GetProcAddress(opengl32, "glGetString");
	version = (const char*)sst_glGetString(GL_VERSION);
	major = (int)(version[0] - '0'); /* "X.Y" -> [0]:major, [2]:minor */
	minor = (int)(version[2] - '0');

	/* Got version info. Detach our context, restore old one */
	wgl->MakeCurrent(oldDC, oldRC);

	/* Save context version information */
	if(selectedAttribsReturn != NULL)
	{
		selectedAttribsReturn->contextVersionMajor = (uint8_t)major;
		selectedAttribsReturn->contextVersionMinor = (uint8_t)minor;
	}

	/* If the major version is too low or the major version is OK, but the minor version is lacking, then fail */
	if(major < attribs->contextVersionMajor ||
		(major == attribs->contextVersionMajor && minor < attribs->contextVersionMinor))
	{
		wgl->DeleteContext(hGLRC);
		ReleaseDC(hWnd, hDC);
		DestroyWindow(hWnd);
		FreeLibrary(opengl32);
		return NULL;
	}

	ReleaseDC(hWnd, hDC);
	DestroyWindow(hWnd);

	ctx->displayTarget = displayTarget;
	ctx->hSlaveWnd = NULL;
	ctx->hDCActive = NULL;
	ctx->opengl32 = opengl32;
	ctx->wgl = *wgl;
	ctx->pixelFormat = format;
	ctx->context = hGLRC;
	ctx->isLegacy = TRUE;
	ctx->ctxVersion[0] = (short)major;
	ctx->ctxVersion[1] = (short)minor;
	ctx->legacyEnabled = FALSE; /* These refer to profiles in GL >= 3.x contexts. Here they are meaningless, so set to false */
	ctx->debugEnabled = FALSE;

	return (SST_OpenGLContext)ctx;
}

/*************************************************************************/

static int modernChoosePixelFormat(HDC hDC, WGLFunctions* wgl, const SST_OpenGLContextAttributes* attribs)
{
	int attrs[MAX_GL_ATTRS];
	int format;
	int* ptr = attrs;
	UINT nrFormats;
	BOOL ok;


	/* Set up basic attributes */
	ptr = addAttr(ptr, WGL_DRAW_TO_WINDOW_ARB, GL_TRUE);
	ptr = addAttr(ptr, WGL_SUPPORT_OPENGL_ARB, GL_TRUE);
	ptr = addAttr(ptr, WGL_DOUBLE_BUFFER_ARB, GL_TRUE);
	ptr = addAttr(ptr, WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB);
	ptr = addAttr(ptr, WGL_COLOR_BITS_ARB, attribs->colorBits);
	ptr = addAttr(ptr, WGL_ALPHA_BITS_ARB, attribs->alphaBits);
	ptr = addAttr(ptr, WGL_DEPTH_BITS_ARB, attribs->depthBits);
	ptr = addAttr(ptr, WGL_STENCIL_BITS_ARB, attribs->stencilBits);
	ptr = addAttr(ptr, WGL_STEREO_ARB, attribs->stereoEnabled ? GL_TRUE : GL_FALSE); /* Must be GL_TRUE || GL_FALSE, not just "non-zero" */

	/* Multisampling requested? */
	if(attribs->multisampleFactor > 1)
	{
		/* Is it supported? */
		if(wgl->supportsMultisample)
		{
			ptr = addAttr(ptr, WGL_SAMPLE_BUFFERS_ARB, 1);
			ptr = addAttr(ptr, WGL_SAMPLES_ARB, attribs->multisampleFactor);
		}
		else
			return 0;
	}
	*ptr = 0;

	nrFormats = 0;
	/* Attempt to get pixel formats that match ours */
	ok = wgl->ChoosePixelFormatARB(hDC, attrs, NULL, 1, &format, &nrFormats);

	/* This can return success with 0 formats, so check if it was actually "successful" in finding > 0 formats */
	if(!ok || nrFormats == 0)
		return 0;

	return format;
}

/*************************************************************************/

static void modernGetPixelInfo(HDC hDC, int format, WGLFunctions* wgl, SST_OpenGLContextAttributes* selectedAttribsReturn)
{
	int attrs[8];
	int values[8] = { 0 };
	int attrCount;

	attrs[0] = WGL_COLOR_BITS_ARB;
	attrs[1] = WGL_ALPHA_BITS_ARB;
	attrs[2] = WGL_DEPTH_BITS_ARB;
	attrs[3] = WGL_STENCIL_BITS_ARB;
	attrs[4] = WGL_STEREO_ARB;
	attrs[5] = WGL_SAMPLE_BUFFERS_ARB;

	/* Check multisample */
	attrCount = (wgl->supportsMultisample ? 6 : 5);


	wgl->GetPixelFormatAttribivARB(hDC, format, 0, attrCount, attrs, values);


	selectedAttribsReturn->colorBits = (uint8_t)values[0];
	selectedAttribsReturn->alphaBits = (uint8_t)values[1];
	selectedAttribsReturn->depthBits = (uint8_t)values[2];
	selectedAttribsReturn->stencilBits = (uint8_t)values[3];
	selectedAttribsReturn->stereoEnabled = (uint8_t)values[4];
	if(wgl->supportsMultisample)
		selectedAttribsReturn->multisampleFactor = (uint8_t)values[5];
	else
		selectedAttribsReturn->multisampleFactor = 1;

}

const struct SST_WM_OpenGLFuncs Win32_OpenGLFuncs = {
	Win32_CreateOpenGLContext,
	Win32_CreateSlaveOpenGLContext,
	Win32_SwapOpenGLBuffers,
	Win32_BindOpenGLContext,
	Win32_DestroyOpenGLContext
};
