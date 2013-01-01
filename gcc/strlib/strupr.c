/*====================================================================*
 *
 *   char *strupr(char *string);
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

#ifndef STRUPR_SOURCE
#define STRUPR_SOURCE

#include <ctype.h>

#include "../strlib/strlib.h"

char *strupr (register char *string) 

{
	if (string != (char *) (0)) 
	{
		char *sp;
		for (sp = string; *sp != (char) (0); sp++) 
		{
			*sp = toupper (*sp);
		}
	}
	return (string);
}


#endif

