/*====================================================================*
 *
 *   signed join (signed c);
 *
 *   tidy.h
 *
 *   discard consecutive escaped newline characters and return the next character;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef JOIN_SOURCE
#define JOIN_SOURCE

#include <stdio.h>

#include "../tidy/tidy.h"

signed join (signed c) 

{
	while (c == '\\') 
	{
		signed o = getc (stdin);
		if ((o != '\r') && (o != '\n'))
		{
			putc (c, stdout);
			putc (o, stdout);
		}
		c = getc (stdin);
	} 
	return (c);
}


#endif

