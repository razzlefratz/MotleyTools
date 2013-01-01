/*====================================================================*
 *
 *   signed equate (struct _code_ const list [], size_t size, char const * name, signed fail);
 *
 *   symbol.h
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef EQUATE_SOURCE
#define EQUATE_SOURCE

#include <string.h>

#include "../tools/symbol.h"

signed equate (struct _code_ const list [], size_t size, char const * name, signed fail) 

{
	size_t lower = 0;
	size_t upper = size;

#ifdef CMASSOC_SAFEMODE

	if (!name) 
	{
		return (fail);
	}
	if (!list) 
	{
		return (fail);
	}

#endif

	while (lower < upper) 
	{
		size_t index = (lower + upper) >> 1;
		signed order = strcmp (name, list [index].name);
		if (order < 0) 
		{
			upper = index - 0;
			continue;
		}
		if (order > 0) 
		{
			lower = index + 1;
			continue;
		}
		return (list [index].code);
	}
	return (fail);
}


#endif

