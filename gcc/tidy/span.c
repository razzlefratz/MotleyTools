/*====================================================================*
 *
 *   signed span (signed c);
 *
 *   join continuation lines; return first character of next line;
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

