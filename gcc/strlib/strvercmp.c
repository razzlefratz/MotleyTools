/*====================================================================*
 *
 *   signed strvercmp (char const * s1, char const * s2, signed c);
 *   
 *   compare two version strings; return -1 or +1 to indicate that 
 *   the first precedes or follows the second; return 0 to indicate
 *   that the strings are either equal or are different and cannot 
 *   be meaninglully compared as versions;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef STRVERCMP_SOURCE
#define STRVERCMP_SOURCE

#include <stdio.h>
#include <ctype.h>

#include "../strlib/strlib.h"

signed strvercmp (char const * s1, char const * s2, signed c) 

{

#ifdef CMASSOC_SAFEMODE

	if (s1 == s2) 
	{
		return (0);
	}
	if (s1 == (char *) (0)) 
	{
		return (-1);
	}
	if (s2 == (char *) (0)) 
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
			signed v1 = -1;
			signed v2 = -1;
			if (isdigit (*++s1)) 
			{
				v1 = 0;
			}
			if (isdigit (*++s2)) 
			{
				v2 = 0;
			}
			while (isdigit (*s1)) 
			{
				v1 *= 10;
				v1 += *s1++ - '0';
			}
			while (isdigit (*s2)) 
			{
				v2 *= 10;
				v2 += *s2++ - '0';
			}
			if (v1 < v2) 
			{
				return (-1);
			}
			if (v1 > v2) 
			{
				return (+1);
			}
			continue;
		}
		s1++;
		s2++;
	}
	if (*s1 == c) 
	{
		return (-1);
	}
	if (*s2 == c) 
	{
		return (+1);
	}
	if (*s1 < *s2) 
	{
		return (-1);
	}
	if (*s1 > *s2) 
	{
		return (+1);
	}
	return (0);
}


/*====================================================================*
 *   test/demo program
 *--------------------------------------------------------------------*/

#if 0             
#include <stdio.h>

int main (int argc, char const *argv []) 

{

#if 0

	printf ("%d = strvercmp('%s', '%s')\n", strvercmp (argv [1], argv [2], '.'), argv [1], argv [2]);

#else

	int argn;
	int argp;
	for (argn = 1; argn < argc; argn++) 
	{
		char const * temp = argv [argn];
		for (argp = argn; argp > 1; argp--) 
		{
			if (strvercmp (temp, argv [argp-1], '.') >= 0) 
			{
				break;
			}
			argv [argp] = argv [argp-1];
		}
		argv [argp] = temp;
	}
	for (argn = 1; argn < argc; argn++) 
	{
		printf ("%03d %s\n", argn, argv [argn]);
	}

#endif

	exit (0);
}


#endif

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif

