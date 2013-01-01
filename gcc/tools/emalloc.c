/*====================================================================*
 *
 *   void *emalloc(size_t extent)
 *
 *   tools.h
 *
 *   attempt to allocate memory using malloc(); return the memory address
 *   on success; print an error message on stderr and then terminate the
 *   program on failure;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef EMALLOC_SOURCE
#define EMALLOC_SOURCE

#include <stdint.h>
#include <stdlib.h>

#include "../tools/memory.h"
#include "../tools/error.h"

void *emalloc (size_t extent) 

{
	void * memory = malloc (extent);;
	if (!memory) 
	{
		error (1, errno, "Need %zu bytes", extent);
	}
	return (memory);
}


#endif

