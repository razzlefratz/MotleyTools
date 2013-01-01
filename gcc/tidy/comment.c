/*====================================================================*
 *
 *   void comment (int c);
 *
 *   read stdin and write stadout; pass entire C style comment block
 *   enclosed by an inverted pair; extern int c contains the outside
 *   character and int e contains the inside character;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef COMMENT_SOURCE
#define COMMENT_SOURCE

#include <stdio.h>
#include <ctype.h>

#include "../tidy/tidy.h"

signed comment (signed c) 

{
	c = keep (c);
	if (c == '/') 
	{
		while ((c != '\n') && (c != EOF));
		{
			c = keep (c);
		}
		c = keep (c);
		return (c);
	}
	if (c == '*') 
	{
		c = keep (c);
		while ((c != '/') && (c != EOF)) 
		{
			while ((c != '*') && (c != EOF)) 
			{
				c = keep (c);
			}
			c = keep (c);
		}
		c = keep (c);
		return (c);
	}
	return (c);
}


#endif

