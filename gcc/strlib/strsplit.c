/*====================================================================*
 *
 *   size_t strsplit (char const * vector[], size_t length, char buffer[], unsigned c);
 *
 *   convert a buffered string to a vector of sub-strings and return
 *   the substring count; sub-strings are separated by character c;
 *
 *   this function modifes buffer by replacing each occurance of the
 *   character c with ASCII NUL;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef STRSPLIT_SOURCE
#define STRSPLIT_SOURCE

#include "../strlib/strlib.h"

size_t strsplit (char const * vector [], size_t length, char buffer [], signed c) 

{
	char const ** string = vector;

#ifdef CMASSOC_SAFEMODE

	if (!string) 
	{
		return (0);
	}
	if (!buffer) 
	{
		return (0);
	}

#endif

	if (length-- > 1) 
	{
		for (*string++ = buffer; *buffer; buffer++) 
		{
			if (*buffer == c) 
			{
				if (length-- > 1) 
				{
					*string++ = buffer + 1;
					*buffer = (char) (0);
				}
			}
		}
	}
	*string = (char *) (0);
	return (string - vector);
}


#endif

