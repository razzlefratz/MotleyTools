/*====================================================================*
 *
 *   char *strpcat(char *target, char const *source)
 *
 *   strlib.h
 *
 *   append the source string to the target string;  return the address of 
 *   NUL terminator in the target string; this functions speeds successive
 *   string concatenations;
 *
 *   this function is similar to strcat() but returns the end of the target
 *   source instead of the start; it is similar to strpcpy() but it searches
 *   for the end of the target source before copying.
 *
 *   This function can be implemented by the following macro ...
 *
 *   #define _strpcat(bp,sp) _strchr(_strcat((bp),(sp)),NUL)
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef STRPCAT_SOURCE
#define STRPCAT_SOURCE

#include "../strlib/strlib.h"

char *strpcat (register char *target, register char const *source) 

{
	if (target != (char *) (0)) 
	{
		while (*target != (char) (0)) 
		{
			target++;
		}
		if (source != (char *) (0)) 
		{
			while (*source != (char) (0)) 
			{
				*target++ = *source++;
			}
			*target = (char) (0);
		}
	}
	return (target);
}


#endif

