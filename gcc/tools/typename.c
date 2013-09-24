/*====================================================================*
 *
 *   char const * typename (struct _type_ const list [], size_t size, type_t type, char const * name);
 *
 *   tools.h  
 *
 *   return the name associated with a given type by searching a name
 *   table arranged in ascending order by type; return the table name
 *   if the type is found or argument name if not;
 *
 *   typedefs type_t and struct _type_ are defined in list.h; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef TYPENAME_SOURCE
#define TYPENAME_SOURCE

#include "../tools/symbol.h"

char const * typename(struct _type_ const list[], size_t size, type_t type, char const * name)

{
	size_t lower = 0;
	size_t upper = size;
	while (lower < upper)
	{
		size_t index = (lower +  upper) >> 1;
		signed order = type - list[index].type;
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
		return (list[index].name);
	}
	return (name);
}

#endif



