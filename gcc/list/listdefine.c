/*====================================================================*
 *
 *   bool listdefine (LIST * list, char const * item, char const c)
 *
 *   list.h
 *
 *   split a copy of the string argument into substrings at each occurance 
 *   of character c; add each substring to the list using listappend();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef LISTDEFINE_SOURCE
#define LISTDEFINE_SOURCE

#include <string.h>

#include "../list/list.h"

bool listdefine (LIST * list, char const * item, char const c) 

{
	char * sp;

#ifdef CMASSOC_SAFEMODE

	if (!list) 
	{
		return (false);
	}
	if (!item) 
	{
		return (false);
	}

#endif

	for (item = sp = strdup (item); *sp; sp++) 
	{
		if (*sp == c) 
		{
			*sp = (char) (0);
			listappend (list, item);
			item = sp + 1;
		}
	}
	if (item < sp) 
	{
		listappend (list, item);
	}
	return (true);
}


#endif

