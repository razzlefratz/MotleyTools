/*====================================================================*
 *
 *   char *strfield(char buffer[], char const *string, char const *charset)
 *
 *   strlib.h
 *
 *   copy string to buffer until some character in charset is found 
 *   but do not copy that character; terminate buffer with NUL and 
 *   return the address the following string character;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef STRFIELD_SOURCE
#define STRFIELD_SOURCE

#include <string.h>

#include "../strlib/strlib.h"

char *strfield (register char buffer [], register char const *string, char const *charset) 

{
	if ((buffer != (char *) (0)) && (string != (char *) (0))) 
	{
		while (strchr (charset, *string) != (char *) (0)) 
		{
			*buffer++ = *string++;
		}
		if (*string != (char) (0)) 
		{
			string++;
		}
		*buffer = (char) (0);
	}
	return ((char *) (string));
}


#endif

