/*====================================================================*
 *
 *   signed nocomment (signed c) 
 *   
 *   read stdin and discard comment; character c contains the 
 *   slash character value;
 * 
 *   if the next character is slash then read and discard characters
 *   until a newline or EOF is read;
 *
 *   if the next character is asterisk the read and discard characters
 *   until closing inverted pair is read; 
 *
 *   otherwise, unget the next character and write the slash;
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef NOCOMMENT_SOURCE
#define NOCOMMENT_SOURCE

#include <stdio.h>
#include <stdlib.h>

#include "../tidy/tidy.h"

signed nocomment (signed c) 

{
	c = getc (stdin);
	if (c == '/') 
	{
		do 
		{
			c = getc (stdin);
		}
		while ((c != '\n') && (c != EOF));
		return (c);
	}
	if (c == '*') 
	{
		c = getc (stdin);
		while ((c != '/') && (c != EOF)) 
		{
			while ((c != '*') && (c != EOF)) 
			{
				c = getc (stdin);
			}
			c = getc (stdin);
		}
		c = getc (stdin);
		return (c);
	}
	putc ('/', stdout);
	return (c);
}


#endif

