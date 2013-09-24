/*====================================================================*
 *
 *   void *erealloc(void * memory, size_t extent)
 *
 *   tools.h
 *
 *   attempt to expand an allocated memory block using realloc(); 
 *   return the resulting memory memory on success; print an error 
 *   message on stderr and terminate the program on failure;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef EREALLOC_SOURCE
#define EREALLOC_SOURCE

#include <stdint.h>
#include <stdlib.h>

#include "../tools/memory.h"
#include "../tools/error.h"

void * erealloc(void * memory, size_t extent)

{
	memory = realloc(memory, extent);
	if (! memory)
	{
		error (1, errno, "Need %zu bytes", extent);
	}
	return (memory);
}

#endif



