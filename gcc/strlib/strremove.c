/*====================================================================*
 *
 *   char *strremove(char *string, char const *charset);
 *
 *   strlib.h
 *
 *   remove all characters from a string that are members of a charset
 *   string thus leaving those that are not members behind; return the
 *   number of characters that were discarded;
 *
 *   the original string is modified and may become shorter;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef STRREMOVE_SOURCE
#define STRREMOVE_SOURCE

#include <string.h>

#include "../strlib/strlib.h"

size_t strremove (register char *string, register char const *charset) 

{
	char *sp = string;

#ifdef CMASSOC_SAFEMODE

	if (string == (char *) (0)) 
	{
		return (0);
	}
	if (string == (char const *) (0)) 
	{
		return (0);
	}

#endif

	while ((*string = *sp) != (char) (0)) 
	{
		if (strchr (charset, *sp++) == (char *) (0)) 
		{
			string++;
		}
	}
	return ((size_t) (sp - string));
}


#endif

