/*====================================================================*
 *
 *   char const * codename (struct _code_ const list [], size_t size, code_t code, char const * name);
 *
 *   symbol.h  
 *
 *   return the name associated with a given code by searching a name
 *   list arranged in ascending order by code; return the codename if
 *   the code is found or the name argument if not;
 *
 *   typedef code_t and struct _code_ are defined in types.h; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef CODENAME_SOURCE
#define CODENAME_SOURCE

#include "../tools/symbol.h"

char const * codename (struct _code_ const list [], size_t size, code_t code, char const * name) 

{
	size_t lower = 0;
	size_t upper = size;
	while (lower < upper) 
	{
		size_t index = (lower + upper) >> 1;
		signed order = code - list [index].code;
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
		return (list [index].name);
	}
	return (name);
}


#endif

