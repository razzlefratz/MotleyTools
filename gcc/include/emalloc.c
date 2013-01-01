/*====================================================================*
 *
 *   void *emalloc (signed length);
 *
 *   allocate a buffer having the spefied length in bytes; return
 *   the buffer address; log system error and exit the program on 
 *   failure;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef EMALLOC_SOURCE
#define EMALLOC_SOURCE

#include <stdlib.h>
#include <error.h>
#include <errno.h>

#include "../tools/tools.h"

void *emalloc (size_t length) 

{
	void *buffer;
	if ((buffer = malloc (length)) == (void *) (0)) 
	{
		error (1, errno, "can't continue");
	}
	return (buffer);
}


#endif

