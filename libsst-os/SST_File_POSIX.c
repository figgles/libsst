/*
	SST_File_POSIX.c
	Author: Patrick Baggett <ptb1@762studios.com>
	Created: 12/23/2011

	Purpose: 

	libsst-os file I/O for POSIX platforms

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#include "POSIXPrivate.h"
#include <SST/SST_File.h>
#include <SST/SST_Assert.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/******************************************************************************/

SST_File SST_OS_OpenFile(const char* path, uint32_t mode)
{
	int flags;
	int fd;
	SST_File_POSIX* file;
	mode_t openMode = 0;

	SST_OS_DebugAssert(path != NULL, "File path may not be NULL");

	/* Async I/O is not yet suppported */
	if(mode & SST_OPEN_ASYNC)
		return NULL;
	
	/* Only one of SST_OPEN_HINTRAND or SST_OPEN_HINTSEQ may be set. */
	if((mode & (SST_OPEN_HINTRAND|SST_OPEN_HINTSEQ)) == (SST_OPEN_HINTRAND|SST_OPEN_HINTSEQ))
		return NULL;

	switch(mode & 0xF) /* Lower byte has the open mode, remaining 24 bits are flags */
	{
		/* In each of the three cases (r/w/a), we set the execute bit so that memory mapped
		I/O can specify 'execute' a permission too -- apparently the mapped view must be a
		subset of the permissions the file was originally opened with. */
		case SST_OPEN_READ:
			flags = O_RDONLY;
			break;
			
		case SST_OPEN_WRITE:
			flags = O_WRONLY | O_CREAT | O_TRUNC;
			openMode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH; /* User/Group: RW, Other: R */
			break;
			
		case SST_OPEN_APPEND:
			flags = O_WRONLY | O_APPEND;
			break;
	
		/* Invalid open mode */
		default:
			return NULL;
	}
	
	fd = open(path, flags, openMode);
	if(fd < 0)
		return NULL;
	#if _XOPEN_SOURCE >= 600 || _POSIX_C_SOURCE >= 200112L
	if(mode & SST_OPEN_HINTRAND)
		posix_fadvise(fd, 0, 0, POSIX_FADV_RANDOM);
	else if(mode & SST_OPEN_HINTSEQ)
		posix_fadvise(fd, 0, 0, POSIX_FADV_SEQUENTIAL);
	#endif

	file = (SST_File_POSIX*)malloc(sizeof(SST_File_POSIX));
	if(file == NULL)
	{
		close(fd);
		return NULL;
	}
	
	file->fd = fd;
	file->isAsync = (int)(mode & SST_OPEN_ASYNC); /* Not yet used */
#ifdef _DEBUG
	file->nrMmaps = 0;
#endif
	
	return (SST_File)file;
}

/******************************************************************************/

uint64_t SST_OS_WriteFile(SST_File file, const void* buf, uint64_t bytes)
{
	SST_File_POSIX* fp = (SST_File_POSIX*)file;
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
		size_t nrBytesToWrite;
		ssize_t nrWritten;
		
		/* Determine how many bytes to write */
		if(bytesLeft > SIZE_MAX)
			nrBytesToWrite = SIZE_MAX;
		else
			nrBytesToWrite = (size_t)bytesLeft;
		
		/* Actually write data to the file */
		nrWritten = write(fp->fd, writePtr, nrBytesToWrite);

		if(nrWritten < 0) /* error */
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

/******************************************************************************/

uint64_t SST_OS_ReadFile(SST_File file, void* buf, uint64_t bytes)
{
	SST_File_POSIX* fp = (SST_File_POSIX*)file;
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
		size_t nrBytesToRead;
		ssize_t nrRead;
		
		/* Determine how many bytes to read */
		if(bytesLeft > SIZE_MAX)
			nrBytesToRead = SIZE_MAX;
		else
			nrBytesToRead = (size_t)bytesLeft;
		
		
		nrRead = read(fp->fd, readPtr, nrBytesToRead);
		if(nrRead <= 0)
		{
			/* Error or EOF, but some of the reads could have succeeded, so return how much
			was read */
			break;
		}
		
		/* Advance pointers and counters */
		readPtr += nrRead;
		totalRead += (uint64_t)nrRead;
		bytesLeft -= (uint64_t)nrRead;
		
	} while(bytesLeft > 0);

	return totalRead; 
}

/******************************************************************************/
int SST_OS_GetFilePointer(SST_File file, uint64_t* fpReturn)
{
	SST_File_POSIX* fp = (SST_File_POSIX*)file;
	off_t off;
	
	SST_OS_DebugAssert(file != NULL, "File handle may not be NULL");
	SST_OS_DebugAssert(fpReturn != NULL, "File pointer return may not be NULL");
#ifdef _DEBUG
	SST_OS_DebugAssert(fp->nrMmaps == 0, "Cannot use synchronous file I/O while memory maps exist!");
#endif

	off = lseek(fp->fd, 0, SEEK_CUR);
	
	if(off == (off_t)-1)
		return 0;
	
	*fpReturn = (uint64_t)off;
	return 1;
}

/******************************************************************************/

int SST_OS_SetFilePointer(SST_File file, uint64_t ptr)
{
	SST_File_POSIX* fp = (SST_File_POSIX*)file;
	off_t off;
	SST_OS_DebugAssert(file != NULL, "File handle may not be NULL");
#ifdef _DEBUG
	SST_OS_DebugAssert(fp->nrMmaps == 0, "Cannot use synchronous file I/O while memory maps exist!");
#endif

	/* Trying to seek > 4GB but underlying OS doesn't support it -> error */
	if(sizeof(off_t) == sizeof(uint32_t) && ptr > UINT32_MAX)
		return 0;
	
	off = (off_t)ptr;
		
	if(lseek(fp->fd, off, SEEK_SET) != (off_t)-1)
		return 0;
	
	return 1;
}

/******************************************************************************/

int SST_OS_FileEOF(SST_File file)
{
	SST_File_POSIX* fp = (SST_File_POSIX*)file;
	off_t here, eof;
	SST_OS_DebugAssert(file != NULL, "File handle may not be NULL");
#ifdef _DEBUG
	SST_OS_DebugAssert(fp->nrMmaps == 0, "Cannot use synchronous file I/O while memory maps exist!");
#endif

	/* Step 1: Get current file position */
	here = lseek(fp->fd, 0, SEEK_CUR);
	if(here == (off_t)-1)
		return -1;
	
	/* Step 2: Seek to EOF */
	eof = lseek(fp->fd, 0, SEEK_END);
	if(eof == (off_t)-1)
		return -2;

	/* Step 3: Put it back! */
	lseek(fp->fd, here, SEEK_SET);

	/* Step 4: Compare and return */
	return (here == eof);
}

/******************************************************************************/

void SST_OS_FlushFile(SST_File file)
{
	SST_File_POSIX* fp = (SST_File_POSIX*)file;
	
	SST_OS_DebugAssert(file != NULL, "File handle may not be NULL");

	(void)fsync(fp->fd);
}

/******************************************************************************/

void SST_OS_CloseFile(SST_File file)
{
	SST_File_POSIX* fp = (SST_File_POSIX*)file;

	SST_OS_DebugAssert(file != NULL, "File handle may not be NULL");

	if(fp->fd > 0)
	{
		close(fp->fd);
		#ifdef _DEBUG
		fp->fd = 0;
		#endif
	}
	
	#ifdef _DEBUG
	SST_OS_DebugAssert(fp->nrMmaps == 0, "Closing file with open memory maps means leaked OS resources");
	#endif

	free(fp);
}

/******************************************************************************/

int SST_OS_SeekFile(SST_File file, int64_t offset, int fromWhere)
{
	SST_File_POSIX* fp = (SST_File_POSIX*)file;
	int method;
	off_t off;

	SST_OS_DebugAssert(file != NULL, "File handle may not be NULL");
#ifdef _DEBUG
	SST_OS_DebugAssert(fp->nrMmaps == 0, "Cannot use synchronous file I/O while memory maps exist!");
#endif
	
	off = (off_t)offset;
	
	/* Map SST to POSIX constants (pretty sure they are isomorphic) */
	switch(fromWhere)
	{
		case SST_SEEK_START: method = SEEK_SET; break;
		case SST_SEEK_CUR: method = SEEK_CUR; break;
		case SST_SEEK_END: method = SEEK_END; break;

		/* Invalid parameter */
		default: return 0; 
	}
	
	if(lseek(fp->fd, off, method) == (off_t)-1)
		return 0;

	return 1;

}

/******************************************************************************/

uint64_t SST_OS_GetFileSize(SST_File file)
{
	SST_File_POSIX* fp = (SST_File_POSIX*)file;
	struct stat info;

	if(fstat(fp->fd, &info) == 0) /* i.e. success */
		return (uint64_t)info.st_size;
	
	/* Failure */
	return UINT64_MAX;
}

/******************************************************************************/

