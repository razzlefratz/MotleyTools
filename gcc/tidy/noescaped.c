/*====================================================================*
 *
 *   void noescaped (signed c);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef NOESCAPED_SOURCE
#define NOESCAPED_SOURCE

#include <stdio.h>

#include "../tidy/tidy.h"

signed noescaped (signed c) 

{
	if (c == '\\') 
	{
		c = getc (stdin);
	}
	c = getc (stdin);
	return (c);
}


#endif

