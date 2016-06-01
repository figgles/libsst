/*
	SST_User_Win32.c
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 12/23/2011

	Purpose: 

	libsst-os user information functions for Win32 systems (Windows 7 or later)

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#define _CRT_SECURE_NO_WARNINGS /* strncpy() isn't deprecated, stupid programming is */

#include "Win32Private.h"
#include <userenv.h>
#include <SST/SST_User.h>
#include <malloc.h>	//_alloca() on Win32

static HMODULE advapi32_dll = NULL;
static BOOL (WINAPI * pfOpenProcessToken)(_In_ HANDLE ProcessHandle, _In_ DWORD DesiredAccess, _Out_ PHANDLE TokenHandle) = NULL;
static BOOL (WINAPI * pfGetUserNameA)(_Out_ LPSTR lpBuffer, _Inout_ LPDWORD lpnSize) = NULL;

static HMODULE userenv_dll = NULL;
static BOOL (WINAPI * pfGetUserProfileDirectoryA)(_In_ HANDLE hToken,_Out_opt_ LPSTR lpProfileDir, _Inout_ LPDWORD lpcchSize) = NULL;

void libsst_free_user()
{
	pfOpenProcessToken = NULL;
	pfGetUserNameA = NULL;
	pfGetUserProfileDirectoryA = NULL;

	if(advapi32_dll)
	{
		FreeLibrary(advapi32_dll);
		advapi32_dll = NULL;
	}

	if(userenv_dll)
	{
		FreeLibrary(userenv_dll);
		userenv_dll = NULL;
	}
}

int __libsst_init_user()
{
	advapi32_dll = LoadLibraryA("advapi32.dll");
	if(advapi32_dll == NULL)
		return 0;

	userenv_dll = LoadLibraryA("userenv.dll");
	if(userenv_dll == NULL)
	{
		FreeLibrary(advapi32_dll);
		return 0;
	}

	/* Load all symbols */
	/* advapi32.dll */
	pfOpenProcessToken = (BOOL (WINAPI*)(HANDLE,DWORD,PHANDLE))GetProcAddress(advapi32_dll, "OpenProcessToken");
	pfGetUserNameA = (BOOL (WINAPI*)(LPSTR, LPDWORD))GetProcAddress(advapi32_dll, "GetUserNameA");

	/* userenv.dll */
	pfGetUserProfileDirectoryA = (BOOL (WINAPI*)(HANDLE, LPSTR,LPDWORD))GetProcAddress(userenv_dll, "GetUserProfileDirectoryA");

	/* Verify all loaded */
	if(pfOpenProcessToken == NULL || pfGetUserNameA == NULL || pfGetUserProfileDirectoryA ==  NULL)
	{
		libsst_free_user();
		return 0;
	}

	return 1;
}



int SST_OS_GetUserName(char* usernameReturn, int bufferSize)
{
	DWORD size;

	/* User is querying the username size */
	if(usernameReturn == NULL)
	{
		char dummy[1];

		/* This *should* generate the insufficient buffer error. When it does, it returns
		the correct size in 'size'. */
		size = sizeof(dummy);
		pfGetUserNameA(dummy, &size);

		/* Make sure it really did. */
		if(GetLastError() == ERROR_INSUFFICIENT_BUFFER)
			return (int)size-1;

		/* Some other error :( */
		return -1;
	}

	size = (DWORD)bufferSize;
	if(pfGetUserNameA(usernameReturn, &size) == FALSE)
	{
		/* GetUserName() returns false on insufficient space, but that is OK.
		However, errors for any other reason isn't OK, so catch them here. */
		if(GetLastError() != ERROR_INSUFFICIENT_BUFFER)
			return -2;
	}

	return (int)(size-1);
}

int SST_OS_GetUserRealName(char* realnameReturn, int bufferSize)
{
	/* TODO: better implementation here plz */
	return SST_OS_GetUserName(realnameReturn, bufferSize);
}

int SST_OS_GetUserHomeDirectory(char* homedirReturn, int bufferSize)
{
	HANDLE hToken = NULL;
	DWORD size;
	int retcode;

	#ifdef _DEBUG
	if(homedirReturn && bufferSize < 0)
		return -1;
	#endif

	if(pfOpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken) == FALSE)
		return -2;

	/* User is querying the username size */
	if(homedirReturn == NULL)
	{
		char dummy[1]; /* See comment block */
		size = 0;

		/*
			Bug in GetUserProfileDirectoryA() impl: NULL for 2nd param should be allowed but isn't.

			MSDN: "If the buffer specified by lpProfileDir is not large enough or lpProfileDir is NULL, the function fails
			and this parameter receives the necessary buffer size, including the terminating null character."

			However, in practice, when I set the second param to NULL, `size` remains zero.
		*/


		pfGetUserProfileDirectoryA(hToken, dummy, &size);

		if(size == 0)
			retcode = -3;
		else
			retcode = (int)(size-1);
	}
	else /* Actually getting the size */
	{
		/* Set the size to the user provided size and query*/
		size = (DWORD)bufferSize;
		if(pfGetUserProfileDirectoryA(hToken, homedirReturn, &size) == FALSE)
		{

			/* This gets tricky: the function doesn't write partial paths, so we have to first detect
			if the error was due to buffer size */
			if(GetLastError() == ERROR_INSUFFICIENT_BUFFER)
			{
				char* tmpbuf = (char*)_alloca(size);

				/* OK, now we've ensured we have a correctly-sized buffer, so call it again. */
				if(pfGetUserProfileDirectoryA(hToken, tmpbuf, &size) == FALSE)
				{
					/* Failed second time around, doh -- give up */
					retcode = -4;
				}
				else
				{
					/* Success -- copy n-1 characters, then null terminate */
					strncpy(homedirReturn, tmpbuf, bufferSize-1);
					homedirReturn[bufferSize-1] = 0;
					retcode = (int)size-1;
				}
			}
		}
		else /* Success */
			retcode = (int)(size-1);
	}

	CloseHandle(hToken);
	return retcode;
}