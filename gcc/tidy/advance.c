/*====================================================================*
 *
 *   void advance (int c);
 *
 *   read stdin and write stdout; output current character c then
 *   advance and output trailing e characters while discading any
 *   white space;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef ADVANCE_SOURCE
#define ADVANCE_SOURCE

#include <stdio.h>
#include <ctype.h>

#include "../tidy/tidy.h"

signed advance (signed c) 

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
	while (isspace (c));
	return (c);
}


#endif

