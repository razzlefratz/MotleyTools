/*====================================================================*
 *
 *   int strdictcmp(char const *string1, char const *string2);
 *
 *   strlib.h
 *
 *   compare two strings and return a negative, zero or positive result
 *   to indicate that the first string precedes, matches or follows the
 *   the second using dictionary collating sequence;
 *
 *   in a 'dictionary' collating sequence, a lower case letter precedes
 *   the upper case counterpart.
 *
 *   ... a < A < b < B ... < z < Z ...
 *
 *   this implementation always returns either -1, 0 or 1;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef STRDCMP_SOURCE
#define STRDCMP_SOURCE

#include <ctype.h>

#include "../strlib/strlib.h"

int strdictcmp (register char const *string1, register char const *string2) 

{
	if (string1 == string2) 
	{
		return (0);
	}
	if (string1 == (char *) (0)) 
	{
		return (-1);
	}
	if (string2 == (char *) (0)) 
	{
		return (+1);
	}
	while (*string1 == *string2) 
	{
		if (*string1 == (char) (0)) 
		{
			return (0);
		}
		string1++;
		string2++;
	}
	if (toupper (*string1) != toupper (*string2)) 
	{
		return (toupper (*string1) < toupper (*string2)? -1: +1);
	}
	return (*string1 > *string2? -1: +1);
}


#endif

