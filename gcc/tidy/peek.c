/*=*
 *
 *   signed peek (signed c);
 *
 *-*/

#ifndef PEEK_SOURCE
#define PEEK_SOURCE

#include <stdio.h>

#include "../tidy/tidy.h"

signed peek (signed c) 

{
	while (c == '\\') 
	{
		signed o = getc (stdin);
		if (o != '\n')
		{
			putc (c, stdout);
			putc (o, stdout);
		}
		c = getc (stdin);
	}
	return (c);
}

#endif

