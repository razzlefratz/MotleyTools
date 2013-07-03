/*====================================================================*
 *
 *   signed span (signed c);
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

signed span (signed c) 

{
	while (c == '\\') 
	{
		signed o = getc (stdin);
		if (o == '\n') 
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

