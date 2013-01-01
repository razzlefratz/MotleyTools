/*====================================================================*
 *
 *   signed find (signed c);
 *
 *   tidy.h
 *
 *   write (c) then return next non-blank character;
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

