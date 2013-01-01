/*====================================================================*
 *
 *   int strpkgcmp (char const *s1, char const *s2, unsigned c);
 *
 *   compare two filenames for matching package names, ignoring any
 *   version numbers; the package name is everything upto the first
 *   occurance of character c; 
 * 
 *   return 0 if the filenames match; return 1 if the package names
 *   match; return -1 otherwise; 
 * 
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef STRPKGCMP_SOURCE
#define STRPKGCMP_SOURCE

#include "../strlib/strlib.h"

int strpkgcmp (char const *s1, char const *s2, unsigned c) 

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
		return (-1);
	}

#endif

	while (*s1 == *s2) 
	{
		if (*s1 == (char) (0)) 
		{
			return (0);
		}
		if (*s1 == (char)(c)) 
		{
			while (*s1 == *s2) 
			{
				if (*s1 == (char) (0)) 
				{
					return (0);
				}
				s1++;
				s2++;
			}
			return (1);
		}
		s1++;
		s2++;
	}
	return (-1);
}


/*====================================================================*
 *   demo/test program;
 *--------------------------------------------------------------------*/

#if 0
#include <stdio.h>

int main (int argc, char const *argv []) 

{
	printf ("%d = strpkgcmp('%s', '%s')\n", strpkgcmp (argv [1], argv [2], '.'), argv [1], argv [2]);
	exit (0);
}


#endif

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif

