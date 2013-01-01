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

void *_calloc (size_t count, size_t itemsize);
void *_malloc (size_t itemsize);
void *_realloc (void *pp, size_t itemsize);
void _free (void *pp);
void _cfree (void *pp);

/*====================================================================*
 *   memory manipulation function prototypes;
 *--------------------------------------------------------------------*/

void *memset (void *target, const int c, size_t count);
void *memcpy (void *target, void const *source, size_t count);
void *_memccpy (void *target, void const *source, const int c, unsigned int count);
int _memicmp (void const *target, void const *source, size_t count);
int memcmp (void const *target, void const *source, size_t count);
char *memchr (char const *buffer, const int c, size_t count);

/*====================================================================*
 *   end definitions;
 *--------------------------------------------------------------------*/

#endif

