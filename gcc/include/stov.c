/*====================================================================*
 *
 *   char const **stov (char const *string, unsigned c);
 *
 *   strlib.h
 *
 *   allocate and return a string vector containing string fields  
 *   that are separted by character c;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef STRLIST_SOURCE
#define STRLIST_SOURCE

#include <string.h>
#include <stdlib.h>

#include "../strlib/strlib.h"
#include "../tools/tools.h"

char const **stov (char const *string, unsigned c) 

{
	size_t size = 2;
	char **argv = (char **) (0);
	char const *sp;
	for (sp = string; *sp != (char) (0); sp++) 
	{
		if (*sp == (char)(c)) 
		{
			size++;
		}
	}
	argv = LST (char *, size);
	size = 0;
	if (argv != (char **) (0)) 
	{
		while (*string != (char) (0)) 
		{
			for (sp = string; *sp != (char) (0); sp++) 
			{
				if (*sp == (char)(c)) 
				{
					break;
				}
			}
			if (sp > string) 
			{
				char *args = STR (sp - string);
				if (args != (char *) (0)) 
				{
					for (argv [size++] = args; string < sp; *args++ = *string++);
					*args = (char) (0);
				}
				string = sp;
			}
			if (*string != (char)(0)) 
			{
				string++;
			}
		}
		argv [size] = (char *) (0);
	}
	return ((char const **)(argv));
}


#endif

