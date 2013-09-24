/*====================================================================*
 *
 *   size_t fgetv (char * vector[], size_t size, char buffer [], size_t length, FILE * ifp);
 *
 *   tools.h
 *
 *   read the specified number of lines from the input stream and return
 *   them in the NULL terminated string vector; the caller allocates the
 *   the input buffer;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef FGETV_SOURCE
#define FGETV_SOURCE

#include <stdio.h>
#include <string.h>

#include "tools.h"

size_t fgetv(char * vector[], size_t size, char buffer[], size_t length, FILE * ifp)

{
	size_t index = 0;
	while ((index < size) && (fgetline(buffer, length, ifp) != - 1))
	{
		vector [index++] = strdup(buffer);
	}
	vector [index] = (char *) (0);
	return (index);
}

#endif



