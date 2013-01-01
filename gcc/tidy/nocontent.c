/*====================================================================*
 *
 *   signed nocontent (signed c, signed e) 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef NOCONTENT_SOURCE
#define NOCONTENT_SOURCE

#include <stdio.h>

#include "../tools/chars.h"
#include "../tidy/tidy.h"

signed nocontent (signed c, signed e) 

{
	c = getc (stdin);
	while ((c != e) && (c != EOF)) 
	{
		c = getc (stdin);
	}
	c = getc (stdin);
	return (c);
}


#endif

