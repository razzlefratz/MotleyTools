/*====================================================================*
 *
 *   signed lookup (struct _code_ const list [], size_t size, char const * name);
 *
 *   symbol.h
 *   
 *   search a name list and return the associated name; return the
 *   corresponding code on success or -1 on failure; the search is
 *   case insensitive;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef LOOKUP_SOURCE
#define LOOKUP_SOURCE

#include <unistd.h>
#include <string.h>

#include "../tools/symbol.h"

signed lookup (struct _code_ const list [], size_t size, char const * name) 

{
	const struct _code_ * item = list;
	if ((name) && (*name)) while ((size_t)(item - list) < size) 
	{
		if (!strcasecmp (item->name, name)) 
		{
			return (item->code);
		}
		item++;
	}
	return (-1);
}


#endif

