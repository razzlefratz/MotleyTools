/*====================================================================*
 *
 *   signed getargv (signed argc, char const * argv [])
 *
 *   symbol.h
 *
 *   read one line from stdin; fill argv [] with fields from that
 *   line; return the number of fields found; ignore blank lines 
 *   and script style comment lines; this implementation inserts
 *   a program name at argv [0] to emulate a true argv [];
 *
 *.  Motley Tools by Charles Maier <cmaier@cmassoc.net>
 *:  Copyright (c) 1982-2006 by Charles Maier
 *;  Licensed under Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef GETARGV_SOURCE
#define GETARGV_SOURCE

#include <stdio.h>
#include <ctype.h>
#include <memory.h>

#include "../tools/symbol.h"
#include "../tools/chars.h"

signed getargv (signed argc, char const * argv []) 

{
	static char string [4096];
	char const ** argp = argv;
	char * sp = string;
	signed c;
	memset (string, 0, sizeof (string));
	memset ((char **)(argv), 0, argc * sizeof (char const *));
	do 
	{
		c = getc (stdin);
		if (c == '#') 
		{
			do 
			{
				c = getc (stdin);
			}
			while (nobreak (c));
		}
	}
	while (isspace (c));
	*argp = sp;
	while (nobreak (c)) 
	{
		if (isblank (c)) 
		{
			do 
			{
				c = getc (stdin);
			}
			while (isblank (c));
			*sp++ = (char)(0);
			*++argp = sp;
		}
		else if (isquote (c)) 
		{
			signed o = c;
			for (c = getc (stdin); nobreak (c) && (c != o); c = getc (stdin)) 
			{
				*sp++ = (char) (c);
			}
			if (c == o) 
			{
				c = getc (stdin);
			}
			*sp++ = (char)(0);
		}
		else 
		{
			*sp++ = (char)(c);
			c = getc (stdin);
		}
	}
	*sp = (char)(0);
	if (*argp != sp) 
	{
		argp++;
	}
	*argp = (char const *)(0);
	return ((signed)(argp - argv));
}


#endif

