/*====================================================================*
 *
 *   int compact (int c, int e);
 *
 *   read stdin and write stdout; replace spaces and tabs with c
 *   unless terminated with e; 
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

