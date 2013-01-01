/*====================================================================*
 *
 *   char *strvis(char *string, char const c);
 *
 *   strlib.h
 *
 *   replace control characters in a string with the specified character;
 *   return the string address;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef STRVIS_SOURCE
#define STRVIS_SOURCE

#include "../strlib/strlib.h"

char *strvis (register char *string, register char const c) 

{
	if (string) while (*string) 
	{
		if (*string < 0x0020) *string = (char)(c);
	}
	return (string);
}


#endif

