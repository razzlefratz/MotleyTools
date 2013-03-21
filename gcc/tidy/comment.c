/*====================================================================*
 *
 *   void comment (int c);
 *
 *   tidy.h
 *
 *   read stdin and write stdout; pass C style comment block;
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

