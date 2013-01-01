/*====================================================================*
 *
 *   char *_strpbrk(char const *string, char const *charset);
 *
 *   _string.h
 *
 *   find the first occurance in string of a charcter in charset; 
 *   return the character address or NULL if not found;
 *
 *   this function is similar to strchr() which looks for one character
 *   instead of a set of characters; in fact, this version of strpbrk()
 *   calls strchr().
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "../string/_string.h"

char *_strpbrk (register char const *string, register char const *charset) 

{

#ifdef CMASSOC_SAFEMODE

	if (string == (char *)(0)) 
	{
		return (string);
	}

#endif

	while (*string != (char)(0)) 
	{
		if (_strchr (charset, *string) != (char *)(0)) 
		{
			return ((char *)(string));
		}
		string++;
	}
	return ((char *)(0));
}

