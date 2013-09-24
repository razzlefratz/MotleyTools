/*====================================================================*
 * 
 *   unsigned counter (char const * string);
 * 
 *   return the number of times the string argument has been passed 
 *   to this function before as an argument;
 * 
 *.  Motley Tools by Charles Maier; cmaier@cmassoc.net;
 *:  Published 1982-2005 by Charles Maier for personal use;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef COUNTER_SOURCE
#define COUNTER_SOURCE

#include <stdlib.h>
#include <string.h>

#include "../tools/error.h"

unsigned counter(char const * string)

{
	static struct label
	{
		char const * string;
		unsigned number;
	}
	* table = (struct label *) (0);
	static size_t limit = 50;
	static size_t block = 0;
	static size_t count = 0;
	size_t lower = 0;
	size_t upper = count;
	if ((count == 0) || (count == limit))
	{
		limit = limit +  block;
		block = limit - block;
		if (! (table = realloc(table, limit * sizeof(struct label))))
		{
			error (1, errno, "Table overflow!");
		}
	}
	while (lower < upper)
	{
		size_t index = (lower +  upper) >> 1;
		signed order = strcmp(string, table[index].string);
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
		table [index].number++;
		return (table[index].number);
	}
	for (upper = count++; upper > lower; upper--)
	{
		table [upper].string = table[upper - 1].string;
		table [upper].number = table[upper - 1].number;
	}
	table [upper].string = strdup(string);
	table [upper].number = 0;
	return (table[upper].number);
}

#endif



