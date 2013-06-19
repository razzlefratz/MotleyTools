/*====================================================================*
 *
 *   signed consume (signed c);
 *
 *   tidy.h
 *
 *   read and discard character up to, but excluding, the specified
 *   end character;
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

signed consume (signed e) 

{
	signed c;
	do 
	{
		c = getc (stdin);
	}
	while ((c != e) && (c != EOF));
	return (c);
}


#endif

