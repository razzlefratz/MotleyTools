/*====================================================================*
 *
 *   char *strlwr(char *string);
 *
 *   strlib.h
 *
 *   convert string letters to lower case and return string address;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef STRLWR_SOURCE
#define STRLWR_SOURCE

#include <ctype.h>

#include "../strlib/strlib.h"

char *strlwr (register char *string) 

{
	if (string != (char *) (0)) 
	{
		char *sp;
		for (sp = string; *sp != (char) (0); sp++) 
		{
			*sp = tolower (*sp);
		}
	}
	return (string);
}


#endif

