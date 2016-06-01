/*
	SST_User_POSIX.c
	Author: Patrick Baggett <ptb1@762studios.com>
	Created: 12/23/2011

	Purpose: 

	libsst-os user account information functions for POSIX platforms

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <string.h>

int __libsst_init_user() { return 1; }

/******************************************************************************/

int SST_OS_GetUserName(char* usernameReturn, int bufferSize)
{
	uid_t euid;
	struct passwd pwd;
	struct passwd* ptrpwd = NULL;
	char buf[1024];
	int len;

	/* Here we using the POSIX '95 extension for reentrant functions */
	euid = geteuid();
	if(getpwuid_r(euid, &pwd, buf, sizeof(buf), &ptrpwd) != 0)
		return -1;

	/* getpwuid_r() will return 0 to indicate success, but it does not indicate that a matching
	record was found, just that the arguments weren't incorrect. Check if *ptrpwd is still NULL,
	which means the record wasn't found. */
	if(ptrpwd == NULL)
		return 0;
	
	len = (int)strlen(pwd.pw_name);

	/* Is the user just querying the length? */
	if(usernameReturn == NULL)
		return len;
	

	/* Expected case: (more than) enough space -> just do strcpy() */
	if(bufferSize >= len+1)
	{
		strcpy(usernameReturn, pwd.pw_name);
		return len;
	}

	/* Exceptional case: less than enough space. Copy 'bufferSize'-1 characters, then add NULL terminator. */
	memcpy(usernameReturn, pwd.pw_name, bufferSize-1);
	usernameReturn[bufferSize-1] = 0;

	return len;
}

/******************************************************************************/

int SST_OS_GetUserRealName(char* realnameReturn, int bufferSize)
{
	uid_t euid;
	struct passwd pwd;
	struct passwd* ptrpwd = NULL;
	char buf[1024];
	int len;

	/* Here we using the POSIX '95 extension for reentrant functions */
	euid = geteuid();
	if(getpwuid_r(euid, &pwd, buf, sizeof(buf), &ptrpwd) != 0)
		return -1;

	/* getpwuid_r() will return 0 to indicate success, but it does not indicate that a matching
	record was found, just that the arguments weren't incorrect. Check if *ptrpwd is still NULL,
	which means the record wasn't found. */
	if(ptrpwd == NULL)
		return 0;
	
	len = (int)strlen(pwd.pw_gecos);

	/* Is the user just querying the length? */
	if(realnameReturn == NULL)
		return len;
	

	/* Expected case: (more than) enough space -> just do strcpy() */
	if(bufferSize >= len+1)
	{
		strcpy(realnameReturn, pwd.pw_gecos);
		return len;
	}

	/* Exceptional case: less than enough space. Copy 'bufferSize'-1 characters, then add NULL terminator. */
	memcpy(realnameReturn, pwd.pw_gecos, bufferSize-1);
	realnameReturn[bufferSize-1] = 0;

	return len;
}

/******************************************************************************/

int SST_OS_GetUserHomeDirectory(char* homedirReturn, int bufferSize)
{
	uid_t euid;
	struct passwd pwd;
	struct passwd* ptrpwd = NULL;
	char buf[1024];
	int len;

	/* Here we using the POSIX '95 extension for reentrant functions */
	euid = geteuid();
	if(getpwuid_r(euid, &pwd, buf, sizeof(buf), &ptrpwd) != 0)
		return -1;

	/* getpwuid_r() will return 0 to indicate success, but it does not indicate that a matching
	record was found, just that the arguments weren't incorrect. Check if *ptrpwd is still NULL,
	which means the record wasn't found. */
	if(ptrpwd == NULL)
		return 0;
	
	len = (int)strlen(pwd.pw_dir);

	/* Is the user just querying the length? */
	if(homedirReturn == NULL)
		return len;
	

	/* Expected case: (more than) enough space -> just do strcpy() */
	if(bufferSize >= len+1)
	{
		strcpy(homedirReturn, pwd.pw_dir);
		return len;
	}

	/* Exceptional case: less than enough space. Copy 'bufferSize'-1 characters, then add NULL terminator. */
	memcpy(homedirReturn, pwd.pw_dir, bufferSize-1);
	homedirReturn[bufferSize-1] = 0;

	return len;
}

