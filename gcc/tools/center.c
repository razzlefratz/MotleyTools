/*====================================================================*
 *
 *   void center (char const buffer [], unsigned length, unsigned margin);
 *
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef CENTER_SOURCE
#define CENTER_SOURCE

#include <stdio.h>

void center(char const buffer[], unsigned length, unsigned margin)

{
	if (length < margin)
	{
		margin -= length;
		margin /= 2;
	}
	else 
	{
		length = margin;
		margin = 0;
	}
	while (margin-- > 0)
	{
		putc (' ', stdout);
	}
	while (length-- > 0)
	{
		putc (* buffer++, stdout);
	}
	return;
}

#endif



