/*====================================================================*
 *
 *   size_t _strcspn(char const *string, char const *charset);
 *
 *   _string.h
 *
 *   search a string for the first occurance of any character in a character
 *   set; return the relative position if found. return the string length if
 *   not found; return 0 if either the string address or the character set
 *   address is NULL.
 *
 *   this function is similar to strchr() but returns the character position
 *   within the string instead of the character address;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "../string/_string.h"

size_t _strcspn (register char const *string, register char const *charset) 

{
	char const *sp = string;

#ifdef CMASSOC_SAFEMODE

	if (string == (char *)(0)) 
	{
		return (0);
	}
	if (charset == (char *)(0)) 
	{
		return (0);
	}

#endif

	while ((*sp != (char)(0)) && (_strchr (charset, *sp) != (char *)(0))) 
	{
		sp++;
	}
	return ((size_t) (sp - string));
}

