/*====================================================================*
 *
 *   void collect (int c, int e);
 *
 *   read stdin and write stdout; output current character c then
 *   collect and output trailing e characters while discading any
 *   white space;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef COLLECT_SOURCE
#define COLLECT_SOURCE

#include <stdio.h>
#include <ctype.h>

#include "../tidy/tidy.h"

signed collect (signed c, signed e) 

{
	do 
	{
		c = advance (c);
	}
	while (c == e);
	return (c);
}


#endif

