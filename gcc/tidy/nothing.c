/*====================================================================*
 *
 *   signed nothing (signed c);
 *
 *   tidy.h
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <ctype.h>

#include "../tidy/tidy.h"

signed nothing (signed c) 

{
	while (isspace (c)) 
	{
		c = keep (c);
		if (c == '#') 
		{
			c = fortran (c);
			continue;
		}
		if (c == '/') 
		{
			c = comment (c);
			continue;
		}
	}
	return (c);
}

