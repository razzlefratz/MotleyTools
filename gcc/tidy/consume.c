/*====================================================================*
 *
 *   signed consume (signed c);
 *
 *   tidy.h
 *
 *   consume and discard the current character up to, but
 *   excluding, the next newline or EOF;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef EATME_SOURCE
#define EATME_SOURCE

#include <stdio.h>

#include "../tidy/tidy.h"

signed consume (signed c) 

{
	do 
	{
		c = getc (stdin);
	}
	while (nobreak (c));
	return (c);
}


#endif

