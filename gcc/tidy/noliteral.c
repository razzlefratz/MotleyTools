/*====================================================================*
 *
 *   signed noliteral (signed c) 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef NOLITERAL_SOURCE
#define NOLITERAL_SOURCE

#include <stdio.h>

#include "../tidy/tidy.h"

signed noliteral (signed c) 

{
	signed e = c;
	c = getc (stdin);
	while ((c != e) && (c != EOF)) 
	{
		c = noescaped (c);
	}
	c = getc (stdin);
	return (c);
}


#endif

