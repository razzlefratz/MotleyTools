/*====================================================================*
 *
 *   signed span (signed c, signed o, signed e) 
 *
 *   tidy.h
 *
 *   join continuation lines; return first character of next line;
 *
 *.  Motley Tools by Charles Maier <cmaier@cmassoc.net>
 *:  Copyright (c) 1982-2006 by Charles Maier.
 *;  Published under Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SPAN_SOURCE
#define SPAN_SOURCE

#include <stdio.h>

#include "../tidy/tidy.h"

signed span (signed c, signed o, signed e) 

{
	while (c == o) 
	{
		c = getc (stdin);
		if (c == e) 
		{
			c = getc (stdin);
			continue;
		}
		ungetc (c, stdin);
		return (o);
	}
	return (c);
}

#endif

