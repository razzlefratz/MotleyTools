/*====================================================================*
 *
 *   signed getfields (char const * fields [], signed limit, char buffer [], size_t length);
 *
 *   symbol.h
 *
 *   read one line from stdin and fill vector [] with fields from that
 *   line; return the number of fields found up to the limit of argc; 
 *   if the line has more than argc fields then the last field holds
 *   all fields in the trailing portion of that line; vector vector is
 *   always NULL termianted; ignore script-style comments and empty
 *   lines;
 *
 *   fields are separated by spaces and/or tabs; use single or double
 *   quotes to include white space in a field;
 *
 *   we assume one argument since empty lines are ignored; this means 
 *   that no arguments indicates EOF; 
 *
 *.  Motley Tools by Charles Maier <cmaier@cmassoc.net>
 *:  Copyright (c) 1982-2006 by Charles Maier
 *;  Licensed under Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef GETFIELDS_SOURCE
#define GETFIELDS_SOURCE

#include <stdio.h>
#include <ctype.h>
#include <memory.h>

#include "../tools/symbol.h"
#include "../tools/chars.h"
#include "../tools/sizes.h"

signed getfields (char const * fields [], signed limit, char buffer [], size_t length) 

{
	signed count = 0;
	signed c;
	limit --;
	memset (fields, 0, limit * sizeof (* fields));
	memset (buffer, 0, length);
	fields [count++] = buffer;
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
			if (count < limit) 
			{
				if (length) 
				{
					buffer++;
					length--;
					fields [count++] = buffer;
				}
			}
			else 
			{
				if (length) 
				{
					*buffer = ' ';
					buffer++;
					length--;
				}
			}
			continue;
		}
		if (isquote (c)) 
		{
			signed quote = c;

#if 0

			if (length) 
			{
				*buffer = (char)(quote);
				buffer++;
				length--;
			}

#endif

			while (((c = getc (stdin)) != quote) && nobreak (c)) 
			{
				if (c == '\\') 
				{
					if ((c = getc (stdin)) == EOF) 
					{
						break;
					}
				}
				if (length) 
				{
					*buffer = (char) (c);
					buffer++;
					length--;
				}
			}

#if 0

			if (length) 
			{
				*buffer = (char)(quote);
				buffer++;
				length--;
			}

#endif

			if (c == quote) 
			{
				c = getc (stdin);
			}
			continue;
		}
		if (length) 
		{
			*buffer = (char)(c);
			buffer++;
			length--;
		}
		c = getc (stdin);
	}
	if (--count)
	{
		++count;
	}
	return (count);
}

#endif

