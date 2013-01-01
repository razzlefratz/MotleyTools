/*====================================================================*
 *
 *   char *strsfx(char *string, char const *suffix);
 *
 *   strlib.h
 *
 *   compare two strings, right to left, to determine if the first string
 *   ends with the second; if so then return a pointer to the start of the
 *   second string within the first; otherwise, return NULL; 
 *
 *   this implementation treats NULL suffixes like NIL suffixes, returning 
 *   a pointer to the string terminator;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef STRSFX_SOURCE
#define STRSFX_SOURCE

#include "../strlib/strlib.h"

char const *strsfx (char const *string, char const *suffix) 

{
	char const *stringp = string;
	char const *suffixp = suffix;
	if (stringp) 
	{
		while (*stringp) 
		{
			stringp++;
		}
	}
	if (suffix) 
	{
		while (*suffixp) 
		{
			suffixp++;
		}
	}
	while ((stringp > string) && (suffixp > suffix)) 
	{
		if (*--stringp != *--suffixp) 
		{
			return ((char const *)(0));
		}
	}
	return (stringp);
}


/*====================================================================*
 *   demo program;
 *--------------------------------------------------------------------*/

#if 0
#include <stdio.h>

int main (int argc, char const *argv []) 

{
	printf ("strsfx(%s, %s) = [%s]\n", argv [1], argv [2], strsfx (argv [1], argv [2]));
	return;
}


#endif

/*====================================================================*
 *   
 *--------------------------------------------------------------------*/

#endif

