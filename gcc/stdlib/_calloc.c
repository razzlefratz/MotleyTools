/*====================================================================*
 *
 *   void *_calloc(size_t count, size_t itemsize);
 *
 *   _malloc.h
 *
 *   This function allocates a memory region of sufficient size to
 *   receive 'count' items, each of a specified size in bytes, and
 *   returns the starting address. The region is 0 filled.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "../stdlib/_malloc.h"
#include "../stdlib/_stddef.h"

void *_calloc (size_t count, size_t itemsize) 

{
	unsigned short int *buffer;
	if ((buffer = (unsigned short int *)(_malloc (count *= itemsize))) != NULL) 
	{
		while (count > 0) buffer [--count] = 0;
	}
	return ((void *)(buffer));
}

