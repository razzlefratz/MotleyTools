/*====================================================================*
 *
 *   type_t nametype (struct _type_ const list[], size_t size, char const * name, type_t type);
 *
 *   symbol.h  
 *
 *   return the type associated with a given name by searching a list
 *   of list arranged in ascending order by name; typedef type_t and
 *   struct _type_ are defined in list.h; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef NAMETYPE_SOURCE
#define NAMETYPE_SOURCE

#include <string.h>

#include "../tools/symbol.h"

type_t nametype(struct _type_ const list[], size_t size, char const * name, type_t type)

{
	size_t lower = 0;
	size_t upper = size;
	while (lower < upper)
	{
		size_t index = (lower +  upper) >> 1;
		signed order = strcmp(name, list[index].name);
		if (order < 0)
		{
			upper = index - 0;
			continue;
		}
		if (order > 0)
		{
			lower = index +  1;
			continue;
		}
		return (list[index].type);
	}
	return (type);
}

#endif



