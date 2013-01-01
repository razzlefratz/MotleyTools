/*====================================================================*
 *
 *   char const * termname (struct _term_ const, list [], size_t size, char const * term);
 *
 *   symbol.h  
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef TERMNAME_SOURCE
#define TERMNAME_SOURCE

#include <string.h>

#include "../tools/symbol.h"

char const * termname (const struct _term_ const list [], size_t size, char const * term) 

{
	size_t lower = 0;
	size_t upper = size;
	while (lower < upper) 
	{
		size_t index = (lower + upper) >> 1;
		signed order = strcmp (term, list [index].term);
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
		return (list [index].text);
	}
	return (term);
}


#endif

