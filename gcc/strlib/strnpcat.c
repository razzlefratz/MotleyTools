/*====================================================================*
 *
 *   char *strnpcat(char *buffer, char const *string, size_t count);
 *
 *   strlib.h
 *
 *   append no more than the specified number of characters of a string
 *   to a buffer; return the address of the last character copied to the
 *   buffer which will be the NUL terminator.
 *
 *   It implements the macro:
 *
 *   #define _strnpcat(bp,sp,n) (_strchr(_strncat((bp),(sp),(n)),NUL))
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef STRNPCAT_SOURCE
#define STRNPCAT_SOURCE

#include "../strlib/strlib.h"

char *strnpcat (register char * buffer, register char const * string, register size_t count) 

{
	if (buffer) 
	{
		while (*buffer) buffer++;
		if (string) 
		{
			while ((*string) && (count-- > 0)) 
			{
				*buffer++ = *string++;
			}
			*buffer = (char)(0);
		}
	}
	return (buffer);
}


#endif

