/*====================================================================*
 *
 *   char *strpcpy(char *target, char const *source)
 *
 *   strlib.h
 *
 *   copy the source string to the target string; return the address of the
 *   NUL terminator in the target string; this function speeds successive
 *   string concatenations;
 *
 *   this function is similar to strcpy() but returns the end of the target
 *   source instead of the start. It is similar to strpcat() but it does not
 *   search for the end of the target source before copying.
 *
 *   this function can be implemented by the following macro ...
 *
 *   #define _strpcpy(bp,sp) strchr(strcpy((bp),(sp)),NUL)
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef STRPCPY_SOURCE
#define STRPCPY_SOURCE

#include "../strlib/strlib.h"

char *strpcpy (register char *target, register char const *source) 

{
	if (target != (char *) (0)) 
	{
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

