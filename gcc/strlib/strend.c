/*====================================================================*
 *
 *   char *strend(char const *string);
 *
 *   strlib.h
 *
 *   return a pointer to the NUL terminator, or end, of a string;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef STREND_SOURCE
#define STREND_SOURCE

#include "../strlib/strlib.h"

char *strend (register char const *string) 

{
	if (string) while (*string) string++;
	return ((char *)(string));
}


#endif

