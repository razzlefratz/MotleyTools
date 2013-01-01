/*====================================================================*
 *
 *   regexp *regexfree(regexp *pattern);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef REGEXFREE_SOURCE
#define REGEXFREE_SOURCE

#include <stdlib.h>

#include "../regex/regex.h"

regexp *regexfree (regexp * pattern) 

{
	while (pattern) 
	{
		regexp *discard = pattern;
		pattern = pattern->next;
		discard->next = (regexp *) (0);
		free (discard->charset);
		free (discard);
	}
	return ((regexp *) (0));
}


#endif

