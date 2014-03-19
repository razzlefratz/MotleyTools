/*====================================================================*
 *
 *   signed fgetline(char *buffer, size_t length, FILE *stream);
 *
 *   tools.h
 *
 *   read characters from the input stream into buffer until a newline 
 *   is read or the file ends; NUL terminate the buffer and return the
 *   resulting line length or -1 on EOF;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef FGETLINE_SOURCE
#define FGETLINE_SOURCE

#include <stdio.h>

#include "../tools/tools.h"

signed fgetline(register char * buffer, size_t length, FILE * fp)

{
	register char * bp = buffer;
	register int c = EOF;

#ifdef CMASSOC_SAFEMODE

	if (!buffer)
	{
		return (- 1);
	}

#endif

	if (length > 0)
	{
		while ((-- length > 0) && ((c = fgetc(fp)) != EOF) && (c != '\n'))
		{
			* bp++ = (char) (c);
		}
		* bp = (char) (0);
	}
	return ((c == EOF) && (bp == buffer)? (- 1): (bp - buffer));
}

#endif



