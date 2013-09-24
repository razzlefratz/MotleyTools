/*====================================================================*
 *
 *   signed totruth (char const * string, signed fail);
 *
 *   number.h
 *
 *   convert boolean name to the equivalent numeric value; valid   
 *   names return 0 or 1; invalid names return -1; boolean names 
 *   are "true", "false", "on", "off", "yes", "no", "0", "1" and
 *   so on; others may be added; conversion is case insensitive;
 *
 *.  Motley Tools by Charles Maier
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef TOTRUTH_SOURCE
#define TOTRUTH_SOURCE

#include <string.h>
#include <ctype.h>

#include "../tools/number.h"
#include "../tools/types.h"

signed totruth(char const * string)

{
	static struct item
	{
		char const * name;
		char code;
	}
	list [] = 
	{
		{
			"0",
			0
		},
		{
			"1",
			1
		},
		{
			"false",
			0
		},
		{
			"no",
			0
		},
		{
			"off",
			0
		},
		{
			"on",
			1
		},
		{
			"true",
			1
		},
		{
			"yes",
			1
		}
	};
	if ((string) && (* string))
	{
		size_t lower = 0;
		size_t upper = sizeof(list) / sizeof(struct item);
		while (lower < upper)
		{
			size_t index = (lower +  upper) >> 1;
			signed order = strcasecmp(string, list[index].name);
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
			return (list[index].code);
		}
	}
	return (- 1);
}

#endif



