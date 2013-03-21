/*====================================================================*
 *
 *   int compact (int c, int e);
 *
 *   tidy.h
 *
 *   read stdin and write stdout; replace white space and character
 *   c unless the whitespace is terminated by character e; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef COMPACT_SOURCE
#define COMPACT_SOURCE

#include <stdio.h>
#include <ctype.h>

#include "../tidy/tidy.h"

signed compact (signed c, signed e) 

{
	signed o;
	do 
	{
		o = getc (stdin);
	}
	while (isspace (o));
	if ((o != e) && (o != EOF)) 
	{
		putc (c, stdout);
	}
	return (o);
}


#endif

