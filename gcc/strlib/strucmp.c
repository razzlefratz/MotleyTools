/*====================================================================*
 *
 *   int strucmp(char const *string1, char const *string2);
 *
 *   strlib.h
 *
 *   compare two strings and return a negative, zero or positive integer
 *   to indicate that the first string lexographically precedes, matches
 *   or follows the second using uppercase comparison;
 *
 *   this implementation always returns either -1, 0 or 1;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef STRUCMP_SOURCE
#define STRUCMP_SOURCE

#include <ctype.h>
#include "../strlib/strlib.h"

int strucmp (register char const *string1, register char const *string2) 

{
	if (string1 == string2) 
	{
		return (0);
	}
	else if (string1 == (char *) (0)) 
	{
		return (-1);
	}
	else if (string2 == (char *) (0)) 
	{
		return (+1);
	}
	else 
	{
		while (toupper (*string1) == toupper (*string2)) 
		{
			if (*string1 == (char) (0)) 
			{
				return (0);
			}
			string1++;
			string2++;
		}
		return (toupper (*string1) < toupper (*string2)? -1: +1);
	}
}


#endif

