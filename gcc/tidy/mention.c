/*====================================================================*
 *
 *   void mention (signed c);
 *   
 *   read from stdin and write to stdout; copy an sgml-style comment
 *   of the form "-- .... --" and align to the following character;
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef MENTION_SOURCE
#define MENTION_SOURCE

#include <stdio.h>

#include "../tidy/tidy.h"

signed mention (signed e) 

{
	signed c = getc (stdin);
	if (c == e) 
	{
		while (c == e) 
		{
			c = keep (c);
		}
		while ((c != e) && (c != EOF)) 
		{
			while ((c != e) && (c != EOF)) 
			{
				c = keep (c);
			}
			c = keep (c);
		}
		while (c == e) 
		{
			c = keep (c);
		}
	}
	return (c);
}


#endif

