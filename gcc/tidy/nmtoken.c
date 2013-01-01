/*====================================================================*
 *
 *   void nmtoken (int c);
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

#ifndef NMTOKEN_SOURCE
#define NMTOKEN_SOURCE

#include <stdio.h>
#include <ctype.h>

#include "../tidy/tidy.h"

signed nmtoken (signed c, signed e) 

{
	do 
	{
		c = keep (c);
	}
	while (isalnum (c) || (c == '_') || (c == '-') || (c == '.') || (c == ':'));
	return (c);
}


#endif

