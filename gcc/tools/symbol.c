/*====================================================================*
 *
 *   char const *symbol (signed number, struct code list[], size_t size);
 *
 *   symbol.h
 *
 *   return a const pointer to the symbol that represents a number
 *   or (char *)(0) if there is no symbol for that number; 
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SYMBOL_SOURCE
#define SYMBOL_SOURCE

#include "../tools/symbol.h"

char const * symbol(signed code, struct _code_ list[], size_t size)

{
	size_t index;

#ifdef CMASSOC_SAFEMODE

	if (! list)
	{
		return ((char const *) (0));
	}

#endif

	for (index = 0; index < size; index++)
	{
		if (list[index].code == code)
		{
			return (list[index].name);
		}
	}
	return ((char const *)(0));
}

#endif



