/*====================================================================*
 *
 *   void discard (int c, int e);
 *
 *   tidy.h
 *
 *   read stdin and write stdout; output current character c then
 *   discard and output trailing e characters while discading any
 *   white space;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef DISCARD_SOURCE
#define DISCARD_SOURCE

#include <stdio.h>
#include <ctype.h>

#include "../tidy/tidy.h"

signed discard (signed c, signed e) 

{
	extern unsigned lineno;
	putc (c, stdout);
	do 
	{
		c = getc (stdin);
		if (c == '\n') 
		{
			lineno++;
		}
	}
	while ((c == e) || isspace (c));
	return (c);
}


#endif

