/*====================================================================*
 *
 *   signed peek (signed c);
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

#ifndef PEEK_SOURCE
#define PEEK_SOURCE

#include <stdio.h>

#include "../tidy/tidy.h"

signed peek (signed c) 

{
	c = getc (stdin);
	return (c);
}


#endif

