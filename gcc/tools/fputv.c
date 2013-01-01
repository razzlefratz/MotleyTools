/*====================================================================*
 *
 *   void fputv(char *string[], size_t size, FILE *fp);
 *
 *   write a string vector to an output stream one string per line;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef FPUTV_SOURCE
#define FPUTV_SOURCE

#include <stdio.h>
#include "tools.h"

void fputv (char const *string [], size_t size, FILE *fp) 

{
	size_t item;
	for (item = 0; item < size; ++item) 
	{
		fputs (string [item], fp);
		fputc ('\n', fp);
	}
	return;
}


#endif

