/*====================================================================*
 *
 *   signed nokeep (signed c);
 *
 *   tidy.h
 *
 *   read next character from stdin;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef NOKEEP_SOURCE
#define NOKEEP_SOURCE

#include <stdio.h>

#include "../tidy/tidy.h"

signed nokeep (signed c) 

{
	c = getc (stdin);
	return (c);
}


#endif

