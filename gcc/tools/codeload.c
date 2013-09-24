/*====================================================================*
 *
 *   size_t codeload (struct _code_ list [], size_t size);
 *
 *   symbol.h
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef CODELOAD_SOURCE
#define CODELOAD_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/symbol.h"
#include "../tools/number.h"
#include "../tools/error.h"

/*====================================================================*
 *   functions;
 *--------------------------------------------------------------------*/

size_t codeload(struct _code_ list[], size_t size)

{
	size_t item = 0;
	char string[100];
	signed c;
	while ((c = getc(stdin)) != EOF)
	{
		size_t lower = 0;
		size_t upper = item;
		unsigned radix = 10;
		unsigned digit = 0;
		unsigned value = 0;
		char * sp = string;
		while (isblank(c))
		{
			c = getc(stdin);
		}
		if ((char) (c) == '0')
		{
			c = getc(stdin);
			switch ((char) (c))
			{
			case 'x':
			case 'X':
				radix = 16;
				c = getc(stdin);
				break;
			case 'b':
			case 'B':
				radix = 2;
				c = getc(stdin);
				break;
			default: 
				radix = 8;
				break;
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
		if (isalpha(c) || ((char) (c) == '_'))
		{
			do 
			{
				if ((size_t) (sp - string) < (sizeof(string) - 1))
				{
					* sp++ = (char) (c);
				}
				c = getc(stdin);
			}
			while (isalnum(c) || ((char) (c) == '_'));
		}
		* sp = (char) (0);
		while (isblank(c))
		{
			c = getc(stdin);
		}
		if ((sp == string) || ((char) (c) != '\n'))
		{
			error (1, EINVAL, "Bailing out");
		}
		while (lower < upper)
		{
			size_t index = (lower +  upper) >> 1;
			signed order = value - list[index].code;
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
			error (1, EINVAL, "Duplicate 0x%04x \"%s\"", value, string);
		}
		if (item < size)
		{
			for (upper = item++; upper > lower; upper--)
			{
				list [upper].code = list[upper - 1].code;
				list [upper].name = list[upper - 1].name;
			}
			list [upper].code = value;
			list [upper].name = (char const *) (strdup(string));
			continue;
		}
		error (1, EOVERFLOW, "Bailing Out");
	}
	return (item);
}

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif



