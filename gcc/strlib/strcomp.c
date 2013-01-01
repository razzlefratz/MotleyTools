/*====================================================================*
 *
 *   signed strcomp (char const *string1, char const *string2, unsigned char convert (unsigned));
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef STRCOMP_SOURCE
#define STRCOMP_SOURCE

#include "../strlib/strlib.h"

signed strcomp (char const * string1, char const * string2, unsigned char convert (unsigned)) 

{
	if (string1 == string2) 
	{
		return (0);
	}
	if (!string1) 
	{
		return (-1);
	}
	if (!string2) 
	{
		return (+1);
	}
	while (convert (*string1) == convert (*string2)) 
	{
		if (*string1 == (char) (0)) 
		{
			return (0);
		}
		string1++;
		string2++;
	}
	return (convert (*string1) < convert (*string2)? -1: +1);
}


#endif

