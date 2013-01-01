/*====================================================================*
 *
 *   int _strcasecmp(char const *string1, char const *string2);
 *
 *   _string.h
 *
 *   compare two strings and return a negative, zero or positive integer
 *   to indicate that the first string precedes, matches or follows the
 *   second; the posix standards specifie lower case comparison for this
 *   fucntion;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "../stdlib/_stddef.h"
#include "../string/_string.h"
#include "../string/_ctype.h"

int _strcasecmp (register char const *string1, register char const *string2) 

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
	while (_tolower (*string1) == _tolower (*string2)) 
	{
		if (*string1 == (char) (0)) 
		{
			return (0);
		}
		string1++;
		string2++;
	}
	return (_tolower (*string1) < _tolower (*string2)? -1: +1);
}

