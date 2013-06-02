/*====================================================================*
 *
 *   signed getargv (char const * argv [], signed argc)
 *
 *   symbol.h
 *
 *   read one line from stdin and fill argv [] with fields from that
 *   line; return the number of fields found up to the limit of argc; 
 *   if the line has more than argc fields then the last field holds
 *   all fields in the trailing portion of that line; vector argv is
 *   always NULL termianted; ignore script-style comments and empty
 *   lines;
 *
 *   fields are separated by spaces and/or tabs; use single or double
 *   quotes to include white space in a field;
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
#include "../tools/sizes.h"

signed getargv (signed argc, char const * argv []) 

{
	static char string [_LINESIZE];
	char * sp = string;
	signed argn = 0;
	signed c;
	memset (string, 0, sizeof (string));
	memset (argv, 0, argc * sizeof (*argv));
	argv [argn++] = sp;
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
	while (nobreak (c)) 
	{
		if (isblank (c)) 
		{
			do 
			{
				c = getc (stdin);
			}
			while (isblank (c));
			if (argn < argc) 
			{
				*sp++ = (char)(0);
				argv [argn++] = sp;
			}
			else 
			{
				*sp++ = ' ';
			}
		}
		else if (isquote (c)) 
		{
			signed quote = c;
			while (((c = getc (stdin)) != quote) && nobreak (c)) 
			{
				if (c == '\\') 
				{
					if ((c = getc (stdin)) == EOF)
					{
						break;
					}
				}
				*sp++ = (char) (c);
			}
			if (c == quote) 
			{
				c = getc (stdin);
			}
		}
		else 
		{
			*sp++ = (char)(c);
			c = getc (stdin);
		}
	}
	*sp = (char)(0);
	argn--;
	if (sp != argv [argn]) 
	{
		argn++;
	}
	return (argn);
}


#endif

