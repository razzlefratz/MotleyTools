/*====================================================================*
 *   
 *   size_t str2argv (char string [], char const * vector [], size_t length);
 *  
 *   strlib.h;
 *
 *.  Motley Tools by Charles Maier; cmaier@cmassoc.net;
 *:  Released 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef STR2ARGV_SOURCE
#define STR2ARGV_SOURCE

#include "../strlib/strlib.h"
#include "../tools/chars.h"

size_t str2argv (char string [], char const * vector [], size_t length) 

{
	char const ** vp = vector;
	char * sp = string;
	for (*vp = sp; (*sp) && ((vp - vector) < length); ++sp) 
	{
		if (isquote (*sp)) 
		{
			char * cp = sp++;
			for (*vp++ = sp; (*sp) && (*sp != *cp); ++sp);
			*cp = *sp = (char)(0);
			*vp = (char const *)(0);
			continue;
		}
		if (isblank (*sp)) 
		{
			*sp = (char)(0);
			*vp = sp + 1;
			continue;
		}
		if (*vp == sp) 
		{
			*++vp = (char const *)(0);
			continue;
		}
	}
	*vp = (char const *)(0);
	*sp = (char)(0);
	return ((size_t)(vp - vector));
}


/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#if 0

#include <stdio.h>
#include <string.h>

int main (int argc, char const * argv []) 

{
	char const * vector [100];
	char string [100];
	signed length;
	signed count;
	while ((argc) && (*argv)) 
	{
		strcpy (string, *argv);
		length = sizeof (vector) / sizeof (vector [0]);
		length = str2argv (string, vector, length);
		for (count = 0; count < length; count++) 
		{
			printf ("%d [%s]\n", count, vector [count]);
		}
		printf ("%d [%d]\n", count, (signed)(vector [count]));
		argc--;
		argv++;
	}
	return (0);
}


#endif

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif

