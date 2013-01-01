/*====================================================================*
 *
 *   signed fortran (signed c);
 *
 *   read stdin and write stdout; copy consecutive lines starting
 *   which character c as one block; include the trailing newline;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef FORTRAN_SOURCE
#define FORTRAN_SOURCE

#include <stdio.h>

#include "../tidy/tidy.h"
#include "../tools/chars.h"

signed fortran (signed c) 

{
	c = keep (c);
	while ((c != '\n') && (c != EOF)) 
	{
		if (c == '/') 
		{
			c = comment (c);
			continue;
		}
		c = escaped (c);
	}
	c = keep (c);
	return (c);
}


#endif

