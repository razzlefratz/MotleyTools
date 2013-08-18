/*====================================================================*
 *
 *   signed connect (signed c, signed o, signed e);
 *
 *   tidy.h
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef CONNECT_SOURCE
#define CONNECT_SOURCE

#include <stdio.h>

#include "../tidy/tidy.h"

signed connect (signed c, signed o, signed e) 

{
	while (c == o)
	{
		signed o = getc (stdin);
		if (o == e)
		{
			c = getc (stdin);
			continue;
		}
		ungetc (o, stdin);
		break;
	}
	return (c);
}


#endif

