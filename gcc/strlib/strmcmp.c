/*====================================================================*
 *
 *   signed strmcmp (register char const *string1, register char const *string2, signed convert (signed));
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

#ifndef STMMCMP_SOURCE
#define STRMCMP_SOURCE

#include <ctype.h>
#include "../strlib/strlib.h"

static char const * advance (char const * string) 

{
	while (isspace (*string) || (*string == '_') || (*string == '-')) 
	{
		string++;
	}
	return (string);
}

signed strmcmp (register char const *string1, register char const *string2, signed convert (signed)) 

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
	string1 = advance (string1);
	string2 = advance (string2);
	while (convert (*string1) == convert (*string2)) 
	{
		if (*string1 == (char) (0)) 
		{
			return (0);
		}
		string1 = advance (++string1);
		string2 = advance (++string2);
	}
	return (convert (*string1) < convert (*string2)? -1: +1);
}


#endif

