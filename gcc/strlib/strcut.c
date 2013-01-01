/*====================================================================*
 *
 *   char *strcut(char *string, unsigned c);
 *
 *   strlib.h
 *
 *   search a string for the first occurance of a character and replace it
 *   with NUL; return a pointer to the next character, if one exists.
 *
 *   string1 = "ab(cd,ef)gh";
 *   string2 = strcut(string1,'(');
 *
 *      string1 :== "ab"
 *      string2 :== "cd,ef)gh"
 *
 *   string3 = strcut(string2,')');
 *
 *      string2 :== "cd,ef"
 *      string3 :== "gh"
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef STRCUT_SOURCE
#define STRCUT_SOURCE

#include "../strlib/strlib.h"

char *strcut (register char *string, register unsigned c) 

{
	if (string != (char *)(0)) 
	{
		while (*string != (char)(0)) 
		{
			if (*string == (char)(c)) 
			{
				*string++ = (char)(0);
				break;
			}
			else 
			{
				string++;
			}
		}
	}
	return (string);
}


#endif

