/*====================================================================*
 *
 *   signed find (signed c);
 *
 *   tidy.h
 *
 *   read stdin; write character c then return the next non-space
 *   character;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef FIND_SOURCE
#define FIND_SOURCE

#include <stdio.h>
#include <ctype.h>

#include "../tidy/tidy.h"

signed find (signed c) 

{
	do 
	{
		c = keep (c);
	}
	while (isspace (c));
	return (c);
}


#endif

