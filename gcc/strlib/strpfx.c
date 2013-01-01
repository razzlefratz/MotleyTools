/*====================================================================*
 *
 *   char *strpfx(char const *string, char const *prefix);
 *
 *   strlib.h
 *
 *   compare two strings, left to right, to determine if the first string
 *   starts with the second; if so then return a pointer to the remainder
 *   of the first string; otherwise, return NULL;
 *
 *   this implementation treats NULL prefixes like NIL prefixes, returning
 *   a pointer to the start of the string;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef STRPFX_SOURCE
#define STRPFX_SOURCE

#include "../strlib/strlib.h"

char const *strpfx (register char const *string, register char const *prefix) 

{
	if (!string || !prefix) 
	{
		return (string);
	}
	while ((*string) && (*string == *prefix)) 
	{
		string++;
		prefix++;
	}
	return ((*prefix)? (char *) (0): string);
}


/*====================================================================*
 *  demo program;
 *--------------------------------------------------------------------*/

#if 0
#include <stdio.h>

int main (int argc, char const *argv []) 

{
	printf ("strpfx(%s, %s) = [%s]\n", argv [1], argv [2], strpfx (argv [1], argv [2]));
	return;
}


#endif

/*====================================================================*
 *  
 *--------------------------------------------------------------------*/

#endif

