/*====================================================================*
 *
 *   signed fgetlongline(char *buffer, size_t length, unsigned preserve, FILE *stream);
 *
 *   tools.h
 *
 *   read characters from the input stream into buffer until a newline is
 *   read, the file ends or the buffer is full; terminate the buffer with
 *   NUL and return the resulting line length or -1 on EOF;
 *
 *   this implementation returns -1 if buffer is NULL or the length is 0;
 *   it does not terminate the buffer when length is 0;
 *
 *   this implementation either ignores and discards escaped newlines, or
 *   ignores but preserves them, based on the preserve flag where 0 means
 *   means discard;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef FGETLONGLINE_SOURCE
#define FGETLONGLINE_SOURCE

#include <stdio.h>
#include "tools.h"

signed fgetlongline (register char *buffer, size_t length, unsigned preserve, FILE * stream) 

{
	register char *bp = buffer;
	register int c = EOF;
	register int o = EOF;
	if ((buffer != (char *)(0)) && (length > 0)) 
	{
		while ((--length > 0) && ((c = fgetc (stream)) != EOF) && (c != '\n')) 
		{
			if (c == '\\') 
			{
				if ((o = fgetc (stream)) != EOF) 
				{
					if (o != '\n') 
					{
						*bp++ = (char)(c);
						*bp++ = (char)(o);
					}
					else if (preserve) 
					{
						*bp++ = (char)(c);
						*bp++ = (char)(o);
					}
				}
				else 
				{
					*bp++ = (char)(c);
				}
			}
			else 
			{
				*bp++ = (char)(c);
			}
		}
		*bp = (char)(0);
	}
	return ((c == EOF) && (bp == buffer)? -1: bp - buffer);
}


#endif

