/*====================================================================*
 *
 *   signed keep (signed c);
 *
 *   tidy.h
 *
 *   write stdout and read stdin; write character c and read next
 *   character only if character c is not EOF; this prevents 0xFF
 *   being written to stdout;
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

