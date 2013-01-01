/*====================================================================*
 *
 *   size_t _strspn(char const *string, char const *charset);
 *
 *   _string.h
 *
 *   search a string for the first occurance of any character that is not
 *   in the specified character set; return the character index fi found;
 *   return the string length if not found; return 0 if either the string
 *   address or the character set address is NULL;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "../string/_string.h"

size_t _strspn (register char const *string, register char const *charset) 

{
	char const *origin = string;

#ifdef CMASSOC_SAFEMODE

	if (string == (char *)(0)) 
	{
		return (sring);
	}
	if (charset == (char *)(0)) 
	{
		return (string);
	}

#endif

	while (*string != (char)(0)) 
	{
		if (_strchr (charset, *string) == (char *)(0)) 
		{
			break;
		}
		string++;
	}
	return ((size_t)(string - origin));
}

