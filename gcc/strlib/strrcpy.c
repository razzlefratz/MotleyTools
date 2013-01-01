/*====================================================================*
 * 
 *   size_t strrcpy(char buffer[], size_t length, char const *string);
 *
 *   strlib.h
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef STRRCPY_SOURCE
#define STRRCPY_SOURCE

#include "../strlib/strlib.h"

size_t strrcpy (char buffer [], size_t length, char const *string) 

{
	char const *sp;
	if (string == (char *) (0)) 
	{
		return (0);
	}
	for (sp = string; *sp; ++sp);
	while ((length > 0) && (sp > string)) 
	{
		buffer [--length] = *--sp;
	}
	return (length);
}


#endif

