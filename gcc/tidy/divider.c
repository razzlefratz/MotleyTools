/*====================================================================*
 *
 *   void divider (int c, unsigned width);
 *
 *   tidy.h
 *
 *   read stdin and write stdout; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef DIVIDER_SOURCE
#define DIVIDER_SOURCE

#include <stdio.h>
#include <ctype.h>

#include "../tidy/tidy.h"
#include "../tools/chars.h"

signed divider (signed c, unsigned width) 

{
	putc (c, stdout);
	c = getc (stdin);
	if ((char) (c) == ' ') 
	{
		putc (c, stdout);
		c = getc (stdin);
		if (((char) (c) == '=') || ((char) (c) == '-')) 
		{
			signed o;
			do 
			{
				o = getc (stdin);
			}
			while (o == c);
			for (putc (c, stdout); width-- > 0; putc (c, stdout));
		}
		else 
		{
			while (nobreak (c)) 
			{
				putc (c, stdout);
				c = getc (stdin);
			}
		}
	}
	return (c);
}


#endif

