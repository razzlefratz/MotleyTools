/*====================================================================*
 *
 *   size_t chrcount (char const * string, signed c);
 *
 *   chrlib.h
 *
 *   scan string for the specified character; return the number of
 *   times that character occurs within string; return 0 if string
 *   is NULL or NIL or c is NUL; 
 *
 *   this function can be called to estimate how many fields exist
 *   within string when allocating memory for a string vector; see
 *   function strsplit() as one example where this might be useful;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef CHRCOUNT_SOURCE
#define CHRCOUNT_SOURCE

#include "../chrlib/chrlib.h"

size_t chrcount (register char const * string, register signed c) 

{
	size_t count = 0;

#ifdef CMASSOC_SAFEMODE

	if (!string) 
	{
		return (count);
	}

#endif

	while (*string) 
	{
		if (*string == (char) (c)) 
		{
			count++;
		}
		string++;
	}
	return (count);
}


#endif

