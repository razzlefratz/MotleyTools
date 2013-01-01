/*====================================================================*
 *
 *   char *_strtok(char const *string, char const *charset);
 *
 *   _string.h
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "../string/_string.h"

char *_strtok (register char *string, register char const *charset) 

{
	static char *sp = (char *)(0);
	if (string != (char *)(0)) 
	{
		sp = string;
	}
	else 
	{
		string = sp;
	}
	if ((sp = _strpbrk (string, charset))) 
	{
		*sp++ = (char)(0);
	}
	return (string);
}

