/*====================================================================*
 *
 *   _memory.h - memory allocation definitions and declarations;
 *
 *.  Motley Tools by Charles Maier
 *:  modified sun 07 sep 03 by user root on host zeus;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef _MEMORY_HEADER
#define _MEMORY_HEADER

/*====================================================================*
 *   external header files;
 *--------------------------------------------------------------------*/

#include <stddef.h>

/*====================================================================*
 *   memory allocation constants;
 *--------------------------------------------------------------------*/

#define _MEMPAGE 512     /* size of physical memory page (bytes) */
#define _NALLOC 1024     /* minimum memory allocation in bytes */

/*====================================================================*
 *   memory allocation function prototypes;
 *--------------------------------------------------------------------*/

void *_calloc (unsigned count, size_t itemsize);
void *_malloc (size_t itemsize);
void *_realloc (void *pp, size_t itemsize);
void _free (void *pp);
void _cfree (void *pp);

/*====================================================================*
 *   memory manipulation function prototypes;
 *--------------------------------------------------------------------*/

void * _memset (void * memory, const int c, unsigned long count);
void * _memchr (void * memory, const int c, unsigned long count);
void * _memcpy  (void * target, const void * source, unsigned long count);
void * _memccpy (void * target, const void * source, const int c, unsigned long count);
int _memicmp (const void * target, const void * source, unsigned long count);
int _memcmp (const void * target, const void * source, unsigned long count);

/*====================================================================*
 *   end definitions;
 *--------------------------------------------------------------------*/

#endif

