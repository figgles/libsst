/*
	SST_File_Win32.c
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 12/23/2011

	Purpose: 

	libsst-os file I/O for Win32 platforms (Windows 7 or later)

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#include "Win32Private.h"
#include <SST/SST_File.h>
#include <SST/SST_Assert.h>

/*************************************************************************/

SST_File SST_OS_OpenFile(const char* path, uint32_t mode)
{
	DWORD accessFlags;
	DWORD createFlags;
	DWORD otherFlags;
	DWORD shareFlags;
	HANDLE hFile;
	SST_File_Win32* file;

	SST_OS_DebugAssert(path != NULL, "File path may not be NULL");

	/* Async I/O is not yet suppported */
	/* see win32 flag FILE_FLAG_OVERLAPPED */
	if(mode & SST_OPEN_ASYNC)
		return NULL;
	
	/* Only one of SST_OPEN_HINTRAND or SST_OPEN_HINTSEQ may be set. */
	if((mode & (SST_OPEN_HINTRAND|SST_OPEN_HINTSEQ)) == (SST_OPEN_HINTRAND|SST_OPEN_HINTSEQ))
		return NULL;
	
	otherFlags = FILE_ATTRIBUTE_NORMAL;
	switch(mode & 0xF) /* Lower byte has the open mode, remaining 24 bits are flags */
	{
		/* In each of the three cases (r/w/a), we set the execute bit so that memory mapped
		I/O can specify 'execute' a permission too -- apparently the mapped view must be a
		subset of the permissions the file was originally opened with. */
		case SST_OPEN_READ:
			createFlags = OPEN_EXISTING;
			accessFlags = GENERIC_READ | GENERIC_EXECUTE;
			shareFlags = FILE_SHARE_READ;
			break;
			
		case SST_OPEN_WRITE:
			createFlags = CREATE_ALWAYS;
			accessFlags = GENERIC_READ | GENERIC_WRITE | GENERIC_EXECUTE;
			shareFlags = 0;
			break;
			
		case SST_OPEN_APPEND:
			createFlags = OPEN_ALWAYS;
			accessFlags = FILE_APPEND_DATA;
			shareFlags = 0;
			break;
	
		/* Invalid open mode */
		default:
			return NULL;
	}
	
	if(mode & SST_OPEN_HINTRAND)
		otherFlags |= FILE_FLAG_RANDOM_ACCESS;
	else if(mode & SST_OPEN_HINTSEQ)
		otherFlags |= FILE_FLAG_SEQUENTIAL_SCAN;
	
	
	hFile = CreateFileA(path, accessFlags, shareFlags, NULL, createFlags, otherFlags, NULL);
	if(hFile == INVALID_HANDLE_VALUE)
		return NULL;
	
	/* Append mode: start at end of file */
	if((mode & 0xF) == SST_OPEN_APPEND)
		SetFilePointer(hFile, 0, NULL, FILE_END);

	/* Can't use malloc(), so use the process heap */
	file = (SST_File_Win32*)HeapAlloc(GetProcessHeap(), 0, sizeof(SST_File_Win32));
	if(file == NULL)
	{
		CloseHandle(hFile);
		return NULL;
	}
	
	file->hFile = hFile;
	file->hMap = NULL;
	file->isAsync = (int)(mode & SST_OPEN_ASYNC); /* Not yet used */
	file->accessFlags = accessFlags;
#ifdef _DEBUG
	file->nrMmaps = 0;
#endif
	
	return (SST_File)file;
}

/*************************************************************************/

uint64_t SST_OS_WriteFile(SST_File file, const void* buf, uint64_t bytes)
{
	SST_File_Win32* fp = (SST_File_Win32*)file;
	uint64_t bytesLeft = bytes;
	uint64_t totalWritten;
	const char* writePtr = (const char*)buf;

	SST_OS_DebugAssert(file != NULL, "File handle may not be NULL");
	SST_OS_DebugAssert(buf != NULL, "Buffer may not be NULL");
	SST_OS_DebugAssert(!fp->isAsync, "Files opened for asynchronous I/O may not use the synchronous file I/O functions");
#ifdef _DEBUG
	SST_OS_DebugAssert(fp->nrMmaps == 0, "Cannot use synchronous file I/O while memory maps exist!");
#endif
	/* Do nothing? */
	if(bytes == 0)
		return 0;
		
	totalWritten = 0;
	do
	{
		DWORD nrBytesToWrite, nrWritten;
		
		/* Determine how many bytes to write (at most 4GB per WriteFile() call) */
		if(bytesLeft > (uint64_t)0xFFFFFFFF)
			nrBytesToWrite = 0xFFFFFFFF;
		else
			nrBytesToWrite = (DWORD)bytesLeft;
		
		/* Ensure invalid 'nrWritten' before calling WriteFile() */
		nrWritten = 0;
		
		/* Actually write data to the file */
		if(WriteFile(fp->hFile, writePtr, nrBytesToWrite, &nrWritten, NULL) == FALSE)
		{
			/* OK, but some of the data may have been written, so stop now but return how far we did get */
			break;
		}
		
		/* Advance pointers and counters */
		writePtr += nrWritten;
		totalWritten += (uint64_t)nrWritten;
		bytesLeft -= (uint64_t)nrWritten;
	} while(bytesLeft > 0);

	return totalWritten;
}

/*************************************************************************/

uint64_t SST_OS_ReadFile(SST_File file, void* buf, uint64_t bytes)
{
	SST_File_Win32* fp = (SST_File_Win32*)file;
	uint64_t bytesLeft = bytes;
	uint64_t totalRead;
	char* readPtr = (char*)buf;
	
	SST_OS_DebugAssert(file != NULL, "File handle may not be NULL");
	SST_OS_DebugAssert(buf != NULL, "Buffer may not be NULL");
	SST_OS_DebugAssert(!fp->isAsync, "Files opened for asynchronous I/O may not use the synchronous file I/O functions");
#ifdef _DEBUG
	SST_OS_DebugAssert(fp->nrMmaps == 0, "Cannot use synchronous file I/O while memory maps exist!");
#endif
	/* Do nothing? */
	if(bytes == 0)
		return 0;
		
	totalRead = 0;	
	do
	{
		DWORD nrBytesToRead, nrRead;
		
		/* Determine how many bytes to read (at most 4GB per ReadFile() call) */
		if(bytesLeft > (uint64_t)0xFFFFFFFF)
			nrBytesToRead = 0xFFFFFFFF;
		else
			nrBytesToRead = (DWORD)bytesLeft;
		
		/* Ensure invalid 'nrRead' before calling ReadFile() */
		nrRead = 0;
		
		if(ReadFile(fp->hFile, readPtr, nrBytesToRead, &nrRead, NULL) == FALSE)
		{
			/* Error, but some of the reads could have succeeded, so return how much
			was read */
			break;
		}
		
		/* When nrRead is 0 but ReadFile() returns true, then the EOF is hit */
		if(nrRead == 0)
			break;

		/* Advance pointers and counters */
		readPtr += (size_t)nrRead;
		totalRead += (uint64_t)nrRead;
		bytesLeft -= (uint64_t)nrRead;
	} while(bytesLeft > 0);

	return totalRead; 
}

/*************************************************************************/

int SST_OS_GetFilePointer(SST_File file, uint64_t* fpReturn)
{
	SST_File_Win32* fp = (SST_File_Win32*)file;
	LARGE_INTEGER zeroPos, newPos;
	
	SST_OS_DebugAssert(file != NULL, "File handle may not be NULL");
	SST_OS_DebugAssert(fpReturn != NULL, "File pointer return may not be NULL");
#ifdef _DEBUG
	SST_OS_DebugAssert(fp->nrMmaps == 0, "Cannot use synchronous file I/O while memory maps exist!");
#endif

	/* Zero bytes from 'current' = just get the position */
	zeroPos.QuadPart = 0;
	
	if(SetFilePointerEx(fp->hFile, zeroPos, &newPos, FILE_CURRENT) == FALSE)
		return 0;
	
	*fpReturn = (uint64_t)newPos.QuadPart;
	return 1;
}

/*************************************************************************/

int SST_OS_SetFilePointer(SST_File file, uint64_t ptr)
{
	SST_File_Win32* fp = (SST_File_Win32*)file;
	LARGE_INTEGER pos;
	
	SST_OS_DebugAssert(file != NULL, "File handle may not be NULL");
#ifdef _DEBUG
	SST_OS_DebugAssert(fp->nrMmaps == 0, "Cannot use synchronous file I/O while memory maps exist!");
#endif
	
	/* Set it */
	pos.QuadPart = (LONGLONG)ptr;
	if(SetFilePointerEx(fp->hFile, pos, NULL, FILE_BEGIN) == FALSE)
		return 0;
		
	return 1;
}

/*************************************************************************/

int SST_OS_FileEOF(SST_File file)
{
	SST_File_Win32* fp = (SST_File_Win32*)file;
	LARGE_INTEGER ptr, end, zero;
	
	SST_OS_DebugAssert(file != NULL, "File handle may not be NULL");
#ifdef _DEBUG
	SST_OS_DebugAssert(fp->nrMmaps == 0, "Cannot use synchronous file I/O while memory maps exist!");
#endif
	
	zero.QuadPart = 0;
	
	/* Step 1: Get current file position */
	if(SetFilePointerEx(fp->hFile, zero, &ptr, FILE_CURRENT) == FALSE)
		return -2;
		
	/* Step 2: Get end of file position */
	if(GetFileSizeEx(fp->hFile, &end) == FALSE)
		return -3;
		
	/* Step 3: Compare */
	return (ptr.QuadPart == end.QuadPart);
}

/*************************************************************************/

void SST_OS_FlushFile(SST_File file)
{
	SST_File_Win32* fp = (SST_File_Win32*)file;
	
	SST_OS_DebugAssert(file != NULL, "File handle may not be NULL");
	
	(void)FlushFileBuffers(fp->hFile);
}

/*************************************************************************/

void SST_OS_CloseFile(SST_File file)
{
	SST_File_Win32* fp = (SST_File_Win32*)file;

	SST_OS_DebugAssert(file != NULL, "File handle may not be NULL");

	if(fp->hFile != NULL)
	{
		CloseHandle(fp->hFile);
		#ifdef _DEBUG
		fp->hFile = NULL;
		#endif
	}
	
	if(fp->hMap != NULL)
	{
		CloseHandle(fp->hMap);
		#ifdef _DEBUG
		fp->hMap = NULL;
		#endif
	}

	#ifdef _DEBUG
	SST_OS_DebugAssert(fp->nrMmaps == 0, "Closing file with open memory maps means leaked OS resources");
	#endif

	
	HeapFree(GetProcessHeap(), 0, fp);
}

/*************************************************************************/

int SST_OS_SeekFile(SST_File file, int64_t offset, int fromWhere)
{
	SST_File_Win32* fp = (SST_File_Win32*)file;
	LARGE_INTEGER pos;
	DWORD method;

	SST_OS_DebugAssert(file != NULL, "File handle may not be NULL");
#ifdef _DEBUG
	SST_OS_DebugAssert(fp->nrMmaps == 0, "Cannot use synchronous file I/O while memory maps exist!");
#endif
	
	/* Map SST to Win32 constants (pretty sure they are isomorphic) */
	switch(fromWhere)
	{
		case SST_SEEK_START: method = FILE_BEGIN; break;
		case SST_SEEK_CUR: method = FILE_CURRENT; break;
		case SST_SEEK_END: method = FILE_END; break;

		/* Invalid parameter */
		default: return 0; 
	}

	/* Save the offset, then do it */
	pos.QuadPart = (LONGLONG)offset;
	if(SetFilePointerEx(fp->hFile, pos, NULL, method) == FALSE)
		return 0;
		
	return 1;

}

/*************************************************************************/

uint64_t SST_OS_GetFileSize(SST_File file)
{
	SST_File_Win32* fp = (SST_File_Win32*)file;
	LARGE_INTEGER size;

	if(GetFileSizeEx(fp->hFile, &size))
		return (uint64_t)size.QuadPart;
		
	/* Failure */
	return UINT64_MAX;
}

/*************************************************************************/

