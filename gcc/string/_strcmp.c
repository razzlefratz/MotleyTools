/*====================================================================*
 *
 *   int _strcmp(char const *string1, char const *string2);
 *
 *   _string.h
 *
 *   Compare two strings and return a negative, zero or positive integer
 *   to indicate that the first string lexographically precedes, matches
 *   or follows the second.
 *
 *   This particular implementation always returns either -1, 0 or +1;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "../string/_string.h"

int _strcmp (register char const *string1, register char const *string2) 

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
	return (*string1 < *string2? -1: +1);
}

