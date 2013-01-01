/*====================================================================*
 *
 *   int strccmp (char const *s1, char const *s2, unsigned char c);
 *   
 *   compare two strings up to the first occurance of terminator c; 
 *   return -1, 0 or 1 to indicate that the first string precedes, 
 *   equals or follows the second; 
 *
 *   this function can be used to compare strings ending in equals
 *   or any other character without having to isolate the prefix;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef STRVCMP_SOURCE
#define STRVCMP_SOURCE

#include <ctype.h>

#include "../strlib/strlib.h"

int strccmp (char const *s1, char const *s2, unsigned char c) 

{

#ifdef CMASSOC_SAFEMODE

	if (s1 == s2) 
	{
		return (0);
	}
	if (s1 == (char *)(0)) 
	{
		return (-1);
	}
	if (s2 == (char *)(0)) 
	{
		return (+1);
	}

#endif

	while (*s1 == *s2) 
	{
		if (*s1 == (char) (0)) 
		{
			return (0);
		}
		if (*s1 == (char) (c)) 
		{
			return (0);
		}
		s1++;
		s2++;
	}
	if ((*s1 == (char)(0)) || (*s1 == (char)(c))) 
	{
		return (-1);
	}
	if ((*s2 == (char)(0)) || (*s2 == (char)(c))) 
	{
		return (+1);
	}
	return (0);
}


/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#define K9J3C0X2
#ifndef K9J3C0X2
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char const *argv []) 

{
	printf ("%d = strccmp('%s', '%s')\n", strccmp (argv [1], argv [2], '.'), argv [1], argv [2]);
	exit (0);
}


#endif
#endif

