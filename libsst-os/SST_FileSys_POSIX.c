/*
        SST_FileSys_POSIX.c
        Author: Patrick Baggett <ptbaggett@762studios.com>
        Created: 3/31/2012

        Purpose: 

        libsst-os file system querying for POSIX systems

        License:

        This program is free software. It comes without any warranty, to
        the extent permitted by applicable law. You can redistribute it
        and/or modify it under the terms of the Do What The Fuck You Want
        To Public License, Version 2, as published by Sam Hocevar. See
        http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#include <SST/SST_FileSys.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

/* In order to get alloca() on Solaris, <alloca.h> is needed */
#if defined(__SUNPRO_C)
	#include <alloca.h>
#endif

/* No PATH_MAX symbol */
#if !defined(PATH_MAX)

	#if defined(_POSIX_PATH_MAX) && 
		#define PATH_MAX _POSIX_PATH_MAX
	#else
		#define PATH_MAX 256 /* This is what _POSIX_PATH_MAX must be according to POSIX */
	#endif
#endif

typedef struct SST_Dir_POSIX
{
	char* canonPath;
	size_t canonPathLen;
	DIR* dirp;
} SST_Dir_POSIX;

SST_Dir SST_OS_OpenDirectory(const char* path)
{
	size_t len;
	char* canonPath;
	SST_Dir_POSIX* dh;
	DIR* dirp;

	/* Ensure no trailing slash */
	len = strlen(path);
	if(len == 0 || path[len-1] == '/')
		return NULL;

	/* Out of memory? */
	canonPath = (char*)malloc(PATH_MAX);
	if(!canonPath)
		return NULL;

	/* Allocate directory handle */
	dh = (SST_Dir_POSIX*)malloc(sizeof(SST_Dir_POSIX));
	if(!dh)
	{
		free(canonPath);
		return NULL;
	}
	
	/* Remove garbage "." and ".." from path, get canonical form */
	if(!realpath(path, canonPath))
	{	
		free(canonPath);
		free(dh);
		return NULL;
	}
	
	/* Attempt to open directory */
	dirp = opendir(canonPath);
	if(!dirp)
	{
		free(canonPath);
		free(dh);
		return NULL;
	}

	dh->canonPathLen = strlen(canonPath);
	dh->canonPath = canonPath;
	dh->dirp = dirp;
	
	return (SST_Dir)dh;
}

int SST_OS_ReadNextDirectoryEntry(SST_Dir dir, SST_FileInfo* fileInfoReturn)
{
	SST_Dir_POSIX* dh = (SST_Dir_POSIX*)dir;
	struct dirent* ent;
	size_t len;
	char* tmp;
	struct stat statbuf;
	
	/* Read next directory entry */
	ent = readdir(dh->dirp);
	if(!ent)
		return 0;
	
	/* Ignore "." and ".." */
	if(strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0)
			return SST_OS_ReadNextDirectoryEntry(dir, fileInfoReturn);
		
	len = strlen(ent->d_name);
	if(len >= SST_FILENAME_MAX)
		len = SST_FILENAME_MAX-1;
			
	memcpy(fileInfoReturn->name, ent->d_name, len);
	fileInfoReturn->name[len] = 0;
	fileInfoReturn->nameLen = len;

	tmp = (char*)alloca(dh->canonPathLen + len + 2); /* +2 because of "/" character and NULL */
		
	/* Construct `canonPath` + '/' + `ent->d_name` + '\0' */
	memcpy(tmp, dh->canonPath, dh->canonPathLen);
	tmp[dh->canonPathLen] = '/';
	memcpy(&tmp[dh->canonPathLen+1], ent->d_name, len);
	tmp[dh->canonPathLen+1+len] = '\0';
	
	if(stat(tmp, &statbuf) == 0)
	{

		/* Save result */
		fileInfoReturn->isDir = S_ISDIR(statbuf.st_mode);
		fileInfoReturn->size = (fileInfoReturn->isDir ? 0 : (size_t)statbuf.st_size);
	}
	else /* can't stat() file, so not really much to say about it */
	{
		fileInfoReturn->isDir = 0;
		fileInfoReturn->size = 0;
	}
	
	return (ent != NULL);
}


void SST_OS_CloseDirectory(SST_Dir dir)
{
	SST_Dir_POSIX* dh = (SST_Dir_POSIX*)dir;
	closedir(dh->dirp);
	free(dh->canonPath);
	free(dh);
}

int SST_OS_CreateDirectory(const char* dir)
{
	/* Make a directory for anyone to read/write. */
	if(mkdir(dir, 0777) == 0)
		return 0; /* Success */

	if(errno == EEXIST)
	{
		/* This could refer to a file by the same name, so check to
		see if it is really a directory. */
		struct stat statbuf;
	
		if(stat(dir, &statbuf) == 0)
		{
			/* It really is a directory. Return positive to signal
			that the directory already exists. */
			if(S_ISDIR(statbuf.st_mode))
				return 1;
		}
	}

	/* Other error -> failure */
	return -1;
}

/******************************************************************************/

int SST_OS_RemoveDirectory(const char* dir)
{
	return (rmdir(dir) == 0);
}

