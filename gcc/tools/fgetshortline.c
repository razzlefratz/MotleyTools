/*====================================================================*
 *
 *   signed fgetshortline(char *buffer, size_t length, unsigned preserve, FILE *stream);
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
 *   this implementation continues to read until EOL or EOF even after
 *   buffer overflow; remaining characters are merely discarded;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef FGETSHORTLINE_SOURCE
#define FGETSHORTLINE_SOURCE

#include <stdio.h>

#include "../tools/tools.h"
#include "../tools/types.h"

signed fgetshortline (register char *buffer, size_t length, bool preserve, FILE * stream) 

{
	register size_t column = 0;
	register int c = EOF;
	register int o = EOF;
	if ((buffer != (char *) (0)) && (length > 0) && (column < length)) 
	{
		while (((c = fgetc (stream)) != EOF) && (c != '\n')) 
		{
			if (c == '\\') 
			{
				if ((o = fgetc (stream)) != EOF) 
				{
					if (o != '\n') 
					{
						if (column < length) 
						{
							buffer [column++] = (char) (c);
							length--;
						}
						if (column < length) 
						{
							buffer [column++] = (char) (o);
							length--;
						}
					}
					else if (preserve) 
					{
						if (column < length) 
						{
							buffer [column++] = (char) (c);
							length--;
						}
						if (column < length) 
						{
							buffer [column++] = (char) (o);
							length--;
						}
					}
				}
				else if (column < length) 
				{
					buffer [column++] = (char) (c);
					length--;
				}
			}
			else if (column < length) 
			{
				buffer [column++] = (char) (c);
				length--;
			}
		}
		if (length > 0) 
		{
			buffer [column] = (char) (0);
		}
	}
	return ((c == EOF) && (column == 0)? -1: (signed)(column));
}


#endif

