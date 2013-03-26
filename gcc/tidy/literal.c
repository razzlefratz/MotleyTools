/*====================================================================*
 *
 *   void literal (signed c, signed e);
 *
 *   read stdin and write stdout; copy literal string allowing for
 *   escaped characters;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef LITERAL_SOURCE
#define LITERAL_SOURCE

#include <stdio.h>

#include "../tidy/tidy.h"

signed literal (signed c) 

{
	signed e = c;
	c = keep (e);
	while ((c != e) && (c != EOF)) 
	{
		c = escaped (c);
	}
	c = keep (e);
	return (c);
}


#endif

