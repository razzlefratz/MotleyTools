/*====================================================================*
 *
 *   size_t typeload (struct _type_ list [], size_t size);
 *
 *   symbol.h
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef TYPELOAD_SOURCE
#define TYPELOAD_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/symbol.h"
#include "../tools/number.h"
#include "../tools/error.h"
#include "../tools/sizes.h"

/*====================================================================*
 *   functions;
 *--------------------------------------------------------------------*/

size_t typeload(struct _type_ list[], size_t size)

{
	size_t item = 0;
	size_t line = 0;
	char string[_NAMESIZE];
	signed c = getc(stdin);
	while (c != EOF)
	{
		size_t lower = 0;
		size_t upper = item;
		unsigned radix = 10;
		unsigned value = 0;
		unsigned digit = 0;
		char * sp = string;
		if (c == '\n')
		{
			line++;
		}
		if (isspace(c))
		{
			c = getc(stdin);
			continue;
		}
		if ((c == '#') || (c == ';'))
		{
			do 
			{
				c = getc(stdin);
			}
			while ((c != '\n') && (c != EOF));
			continue;
		}
		if (c == '0')
		{
			c = getc(stdin);
			if ((c == 'x') || (c == 'X'))
			{
				c = getc(stdin);
				radix = 16;
			}
			else if((c == 'b') || (c == 'B'))
			{
				c = getc(stdin);
				radix = 2;
			}
			else 
			{
				radix = 8;
			}
		}
		while ((digit = todigit(c)) < radix)
		{
			value *= radix;
			value += digit;
			c = getc(stdin);
		}
		while (isblank(c))
		{
			c = getc(stdin);
		}
		if (isalpha(c) || (c == '_'))
		{
			do 
			{
				if ((size_t) (sp - string) < (sizeof(string) - 1))
				{
					* sp++ = (char) (c);
				}
				c = getc(stdin);
			}
			while (isalnum(c) || (c == '_'));
		}
		* sp = (char) (0);
		if (sp == string)
		{
			error (1, EINVAL, "No name on line %zd", line);
		}
		while (isblank(c))
		{
			c = getc(stdin);
		}
		if ((c != '#') && (c != ';') && (c != '\n') && (c != EOF))
		{
			error (1, EINVAL, "Trash on line %zd after %s", line, string);
		}
		while (lower < upper)
		{
			size_t index = (lower +  upper) >> 1;
			signed order = value - list[index].type;
			if (order < 0)
			{
				upper = index - 0;
				continue;
			}
			if (order > 0)
			{
				lower = index +  1;
				continue;
			}
			error (1, EINVAL, "Duplicate value %d for %s/%s on line %zd", value, string, list[index].name, line);
		}
		if (item < size)
		{
			for (upper = item++; upper > lower; upper--)
			{
				list [upper].type = list[upper - 1].type;
				list [upper].name = list[upper - 1].name;
			}
			list [upper].type = value;
			list [upper].name = (char const *) (strdup(string));
			continue;
		}
		error (1, EOVERFLOW, "Bailing Out");
	}
	return (item);
}

#endif



