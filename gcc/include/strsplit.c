/*====================================================================*
 *
 *   void strsplit (char const *vector[], size_t length, char string[], unsigned c);
 *
 *   this helper function splits a string into fields; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef STRSPLIT_SOURCE
#define STRSPLIT_SOURCE

#include "../strlib/strlib.h"

size_t strsplit (char const * vector [], size_t length, char string [], signed c) 

{
	char const **vp = vector;

#ifdef STRLIB_SAFEMODE

	if (vector == (char const **) (0)) 
	{
		return (0);
	}
	if (string == (char *) (0)) 
	{
		return (0);
	}

#endif

	if (length-- > 1) 
	{
		for (*vector++ = string; *string != (char) (0); string++) 
		{
			if (*string == c) 
			{
				*vector++ = string + 1;
				*string = (char) (0);
			}
		}
		*vector = (char *) (0);
	}
	return (vector - vp);
}


#endif

