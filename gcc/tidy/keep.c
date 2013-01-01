/*====================================================================*
 *
 *   signed keep (signed c);
 *
 *   tidy.h
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef KEEP_SOURCE
#define KEEP_SOURCE

#include <stdio.h>

#include "../tidy/tidy.h"

signed keep (signed c) 

{
	if (c != EOF) 
	{
		putc (c, stdout);
		c = getc (stdin);
	}
	return (c);
}


#endif

