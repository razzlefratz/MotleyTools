/*====================================================================*
 *
 *   int _strncmp(char const *string1, char const *string2, size_t count);
 *
 *   _string.h
 *
 *   Compare the first count characters of two strings and return a
 *   negative, zero, or positive integer to indicate that the first string
 *   lexographically precedes, matches or follows the second based on the
 *   collating sequence of the host system.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "../string/_string.h"
#include "../stdlib/_stddef.h"

int _strncmp (register char const *string1, register char const *string2, register size_t count) 

{
	if (string1 == (char *)(0)) 
	{
		return ((string2 == (char *)(0))? (0):(-1));
	}
	if (string2 == (char *)(0)) 
	{
		return ((string1 == (char *)(0))? (0):(+1));
	}
	while ((count-- > 0) && (*string1 == *string2)) 
	{
		if (*string1 == (char)(0)) 
		{
			return (0);
		}
		string1++,
		string2++;
	}
	if (*string1 < *string2) 
	{
		return (-1);
	}
	if (*string1 > *string2) 
	{
		return (+1);
	}
	return (0);
}

