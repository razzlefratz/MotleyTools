/*====================================================================*
 *
 *   signed nocontext (signed c, signed e) 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef NOCONTEXT_SOURCE
#define NOCONTEXT_SOURCE

#include <stdio.h>

#include "../tools/chars.h"
#include "../tidy/tidy.h"

signed nocontext (signed c, signed e) 

{
	c = getc (stdin);
	while ((c != e) && (c != EOF)) 
	{
		if (c == '{') 
		{
			c = nocontext (c, '}');
			continue;
		}
		if (c == '(') 
		{
			c = nocontext (c, ')');
			continue;
		}
		if (c == '[') 
		{
			c = nocontext (c, ']');
			continue;
		}
		if (isquote (c)) 
		{
			c = noliteral (c);
			continue;
		}
		c = getc (stdin);
	}
	c = getc (stdin);
	return (c);
}


#endif

