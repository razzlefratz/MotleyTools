/*====================================================================*
 *
 *   void fprintv(FILE *fp, char const *list[], size_t size);
 *
 *   tools.h
 *
 *   print a string vector to the specified output stream;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef FPRINTV_SOURCE
#define FPRINTV_SOURCE

#include <stdio.h>

#include "tools.h"

int fprintv(FILE * fp, char const * list[], size_t size)

{
	size_t item = 0;
	size_t length = 0;
	while (item < size)
	{
		length += fprintf(fp, "%3zd [%s]\n", item, list[item]);
		item++;
	}
	length += fprintf(fp, "\n");
	return (length);
}

#endif



