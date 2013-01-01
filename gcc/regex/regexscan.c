/*====================================================================*
 *
 *   char const *regexscan(const regexp * pattern, char const *literal);
 *   
 *   regex.h
 *
 *   search literal for the first substring that matches the regular 
 *   expression in pattern and return the substring start address if
 *   found or NULL if not found; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef REGEXSCAN_SOURCE
#define REGEXSCAN_SOURCE

#include "../regex/regex.h"

char const *regexscan (const regexp * pattern, char const *literal) 

{
	if (!pattern) 
	{
		return (literal);
	}
	if (!literal) 
	{
		return (literal);
	}
	while (*literal) 
	{
		if (regexspan (pattern, literal)) 
		{
			return (literal);
		}
	}
	return ((char *) (0));
}


#endif

