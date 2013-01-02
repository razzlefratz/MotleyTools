/*====================================================================*
 *
 *   regex.demo.c - 
 *
 *   
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#define _GETOPT_H

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <ctype.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/tools.h"
#include "../regex/regex.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#include "../regex/regexmake.c"
#include "../regex/regexspan.c"
#include "../regex/regexmax.c"
#include "../regex/regexcomp.c"
#include "../regex/regexfree.c"
#include "../regex/regexshow.c"
#include "../tools/emalloc.c"
#include "../chrlib/charset.c"
#include "../chrlib/chruesc.c"

/*====================================================================*
 *   main program;
 *--------------------------------------------------------------------*/

int main (int argc, char const *argv []) 

{
	regexp *pattern;
	char const *sp;
	if (*++argv != (char const *)(0)) 
	{
		pattern = regexmake (*argv);
		regexshow (pattern, *argv);
	}
	while (*++argv != (char const *)(0)) 
	{
		sp = regexspan (pattern, *argv);
		if (sp == (char *)(0)) 
		{
			printf ("no match: [%s]\n", *argv);
			continue;
		}
		if (*sp == (char)(0)) 
		{
			printf ("match: [%s]\n", *argv);
			continue;
		}
		printf ("no match: [%s]\n", *argv);
	}
	regexfree (pattern);
	return (0);
}

