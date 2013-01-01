/*====================================================================*
 *
 *   malloc.h - direct memory allocation and manipulation;
 *
 *.  Motley Tools by Charles Maier
 *:  modified sun 07 sep 03 by user root on host zeus;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef MALLOC_HEADER
#define MALLOC_HEADER

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#include "_stddef.h"

/*====================================================================*
 *   prototype memory allocation functions;
 *--------------------------------------------------------------------*/

#define _MEMPAGE 512     /* size of physical memory page in bytes */
#define _NALLOC 1024     /* minimum memory allocation in bytes */

typedef struct _alloc_t 

{
	unsigned _cnt;
	struct _alloc_t *_ptr;
}

Pool;
extern Pool base;
extern Pool * head;
void * _emalloc (size_t itemsize);
void * _calloc (size_t count, size_t itemsize);
void * _malloc (size_t itemsize);
void * _realloc (void *memory, size_t itemsize);
void _free (void *memory);
void _cfree (void *memory);

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#ifdef _never_ever

HGLOBAL GlobalAlloc (UINT uFlags, DWORD dwBytes);
HGLOBAL GlobalReAlloc (HGLOBAL hMemory, DWORD dwBytes, UINT uFlags);
HGLOBAL GlobalFree (HGLOBAL hMemory);

#endif

void *_sbrk (size_t nbytes);

/*====================================================================*
 *   end definitions;
 *--------------------------------------------------------------------*/

#endif

