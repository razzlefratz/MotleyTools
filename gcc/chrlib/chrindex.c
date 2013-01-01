/*====================================================================*
 *
 *   size_t chrindex (register char const * string, register signed c);
 *
 *   chrlib.h
 *
 *   return the position of a given character within a string; 
 *   return the  the string length if the search fails;
 *
 *   this function is similar to strcspn() but searches for one
 *   character instead of several; it is identical to function 
 *   cindex() declared in strlib.h;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef CHRINDEX_SOURCE
#define CHRINDEX_SOURCE

#include "../chrlib/chrlib.h"

size_t chrindex (register char const * string, register signed c) 

{
	char const * sp;

#ifdef CMASSOC_SAFEMODE

	if (!string) 
	{
		return (0);
	}

#endif

	for (sp = string; (*sp) && (*sp != (char)(c)); sp++);
	return ((size_t) (sp - string));
}


#endif

