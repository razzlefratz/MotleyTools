/*====================================================================*
 *
 *   void escaped (signed c);
 *
 *   tidy.h
 *
 *   if output character is '\\' then output that one and the next 
 *   one then return the one after that;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef ESCAPED_SOURCE
#define ESCAPED_SOURCE

#include <stdio.h>

#include "../tidy/tidy.h"

signed escaped (signed c) 

{
	if (c == '\\') 
	{
		c = keep (c);
	}
	c = keep (c);
	return (c);
}


#endif

