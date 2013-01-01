/*====================================================================*
 *
 *   size_t strpart (char const *vector[], char string[], signed c);
 *
 *   split a string into vectored substrings at each occurance of c;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef STRPART_SOURCE
#define STRPART_SOURCE

#include "../strlib/strlib.h"

size_t strpart (char const *vector [], char string [], signed c) 

{
	char const **vp = vector;

#ifdef CMASSOC_SAFEMODE

	if (vector == (char const **) (0)) 
	{
		return (0);
	}
	if (string == (char *) (0)) 
	{
		return (0);
	}

#endif

	for (*vector++ = string; *string != (char) (0); string++) 
	{
		if (*string == c) 
		{
			*vector++ = string + 1;
			*string = (char) (0);
		}
	}
	*vector = (char *) (0);
	return (vector - vp);
}


#endif

