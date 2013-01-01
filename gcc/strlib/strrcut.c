/*====================================================================*
 *
 *   char *strrcut(char *string, const unsigned c)
 *
 *   strlib.h
 *
 *   search a buffer for the final occurance of a character and replace
 *   it with NUL; return the address of the next character, if present,
 *   or the address of the NUL terminator;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef STRRCUT_SOURCE
#define STRRCUT_SOURCE

#include "../strlib/strlib.h"

char *strrcut (register char *string, register const unsigned c) 

{
	if (string != (char *)(0)) 
	{
		register char *sp;
		for (sp = (char *)(0); *string != (char)(0); string++) 
		{
			if (*string == (char)(c)) 
			{
				sp = string;
			}
		}
		if (sp != (char *)(0)) 
		{
			*sp++ = (char)(0);
			string = sp;
		}
	}
	return (string);
}


#endif

