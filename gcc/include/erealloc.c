/*====================================================================*
 *
 *   void *erealloc(void *address, size_t nbytes)
 *
 *   tools.h
 *
 *   attempt to expand an allocated memory block using realloc(); 
 *   return the resulting memory address on success; print an error 
 *   message on stderr and terminate the program on failure;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef EREALLOC_SOURCE
#define EREALLOC_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>

#include "../tools/tools.h"

void *erealloc (void *address, size_t nbytes) 

{
	if ((address = realloc (address, nbytes)) == (void *) (0)) 
	{
		error (1, errno, "can't reallocate %d bytes", nbytes);
	}
	return (address);
}


#endif

