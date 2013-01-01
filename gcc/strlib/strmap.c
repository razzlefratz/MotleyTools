/*====================================================================*
 *
 *   char *strmap(char string[], char const *charset1, char const charset2);
 *
 *   strlib.h
 *
 *   convert a string from one character set to another; character 
 *   sets are specified as NUL terminated strings of equal length; 
 *   characters in the first are replaced by corresponding ones in
 *   the second; nothing happens if either set is NULL or the sets
 *   have unequal length;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef STRMAP_SOURCE
#define STRMAP_SOURCE

#include <string.h>

#include "../strlib/strlib.h"

char *strmap (char string [], register char const *charset1, register char const *charset2) 

{
	if (string == (char *)(0));
	else if (charset1 == (char *)(0));
	else if (charset2 == (char *)(0));
	else if (strlen (charset1) != strlen (charset2));
	else 
	{
		char *sp;
		for (sp = string; *sp; ++sp) 
		{
			size_t index;
			for (index = 0; charset1 [index]; index++) 
			{
				if (charset1 [index] == *sp) 
				{
					*sp = charset2 [index];
					break;
				}
			}
		}
	}
	return (string);
}


#endif

