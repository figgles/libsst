/*
        SST_FileSys_Win32.c
        Author: Patrick Baggett <ptbaggett@762studios.com>
        Created: 3/29/2012

        Purpose: 

        libsst-os file system querying for Win32

        License:

        This program is free software. It comes without any warranty, to
        the extent permitted by applicable law. You can redistribute it
        and/or modify it under the terms of the Do What The Fuck You Want
        To Public License, Version 2, as published by Sam Hocevar. See
        http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#include <SST/SST_FileSys.h>

#include <windows.h>
#include <string.h>

/*************************************************************************/

typedef struct SST_Dir_Win32
{
	HANDLE hFind;
	WIN32_FIND_DATAA data;
	int once;
} SST_Dir_Win32;

/*************************************************************************/

/* Copy data from WIN32_FILE_DATAA structure to SST_FileInfo structure */
static void copyWin32FindData(SST_FileInfo* info, const WIN32_FIND_DATAA* data)
{
	size_t len = strlen(data->cFileName);
		
	if(len >= SST_FILENAME_MAX)
		len = SST_FILENAME_MAX-1;
	
	memcpy(info->name, data->cFileName, len);
	info->name[len] = '\0';
	info->size = (((uint64_t)data->nFileSizeHigh) << (8*sizeof(uint32_t))) | ((uint64_t)data->nFileSizeLow);
	info->nameLen = len;
	info->isDir = (data->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY);
}

/*************************************************************************/

SST_Dir SST_OS_OpenDirectory(const char* path)
{
	char findPath[MAX_PATH];
	size_t len = strlen(path);
	SST_Dir_Win32* win32dir;
	
	/* Don't allow paths to end with a trailing slash */
	if(path[len-1] == '/' || path[len-1] == '\\')
		return NULL;

	if(len > MAX_PATH-3)
		len = MAX_PATH-3;
	
	/* Append "/" and "*" to the end */
	memcpy(findPath, path, len);
	findPath[len] = '/';
	findPath[len+1] = '*';
	findPath[len+2] = '\0';
	
	/* Allocate structure to use */
	win32dir = (SST_Dir_Win32*)HeapAlloc(GetProcessHeap(), 0, sizeof(SST_Dir_Win32));
	if(win32dir == NULL)
		return (SST_Dir)NULL;

	/* Attempt to find the first file */
	win32dir->hFind = FindFirstFileA(findPath, &win32dir->data);
	win32dir->once = 1;
	
	/* Failed? */
	if(win32dir->hFind == INVALID_HANDLE_VALUE)
	{
		/* FindFirstFile() returns ERROR_FILE_NOT_FOUND when no files are found.
		If we didn't get that, then return NULL */
		if(GetLastError() !=  ERROR_FILE_NOT_FOUND)
		{
			HeapFree(GetProcessHeap(), 0, (void*)win32dir);
			return NULL;
		}
	}
	
	return (SST_Dir)win32dir;
}

/*************************************************************************/

int SST_OS_ReadNextDirectoryEntry(SST_Dir dir, SST_FileInfo* fileInfoReturn)
{
	SST_Dir_Win32* win32dir = (SST_Dir_Win32*)dir;
	int result = 0;
	
	/* Check if call to FindFirstFileA() returned 0 files found */
	if(win32dir->hFind != INVALID_HANDLE_VALUE)
	{		
		/* FindFirstFileA() copies the first file data automatically, so use the first time */
		if(win32dir->once)
		{
			/* NOTE: data already copied to win32dir->data when FindFirstFileA() was called */
			win32dir->once = 0;
			result = 1;
		}
		else
			result = FindNextFileA(win32dir->hFind, &win32dir->data);
	
		/* If we have file data to copy, then do so now */
		if(result)
		{
			if(strcmp(win32dir->data.cFileName, ".") == 0 || strcmp(win32dir->data.cFileName, "..") == 0)
				return SST_OS_ReadNextDirectoryEntry(dir, fileInfoReturn);
			else
				copyWin32FindData(fileInfoReturn, &win32dir->data);
		}
	}
	
	return result;
}

/*************************************************************************/

void SST_OS_CloseDirectory(SST_Dir dir)
{
	SST_Dir_Win32* win32dir = (SST_Dir_Win32*)dir;
	
	/* Close the handle if not invalid */
	if(win32dir->hFind != INVALID_HANDLE_VALUE)
		FindClose(win32dir->hFind);
	
	/* Return heap memory */
	HeapFree(GetProcessHeap(), 0, (void*)win32dir);
}

/*************************************************************************/

int SST_OS_CreateDirectory(const char* dir)
{
	if(CreateDirectoryA(dir, NULL) == FALSE)
	{
		if(GetLastError() == ERROR_ALREADY_EXISTS)
			return 1; /* positive == already exists */
		else
			return -1; /* negative == error */
	}

	return 0; /* zero == success */
}

/*************************************************************************/

int SST_OS_RemoveDirectory(const char* dir)
{
	return (int)RemoveDirectory(dir);
}

