/*====================================================================*
 *
 *   void regexshow (const regexp * pattern);
 *
 *   display a prose description of a regular expression on stdout;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef REGEXSHOW_SOURCE
#define REGEXSHOW_SOURCE

#include <stdio.h>

#include "../regex/regex.h"

void regexshow (const regexp * pattern) 

{
	while (pattern) 
	{
		if (pattern->minimum == pattern->maximum) 
		{
			printf (" %zu", pattern->minimum);
		}
		else 
		{
			printf (" %zu thru %zu", pattern->minimum, pattern->maximum);
		}
		printf (" %s", pattern->exclude? "not from": "from");
		printf (" %c%s%c\n", REGEX_C_SRT, pattern->charset, REGEX_C_END);
		pattern = pattern->next;
	}
	return;
}


#endif

