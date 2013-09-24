/*====================================================================*
 *
 *   char const * termspec (char const * term, char const * type, struct _term_ const list [], size_t size);
 *
 *   tools.h   
 *
 *   search list for term and return text; exit program on failure;
 *   this function combines functions synonym and synonyms;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef TERMSPEC_SOURCE
#define TERMSPEC_SOURCE

#include <string.h>
#include <stdlib.h>

#include "../tools/tools.h"
#include "../tools/types.h"

char const * termspec(char const * term, char const * type, struct _term_ const list[], size_t size)

{
	extern char const * program_name;
	const struct _term_ * item = list;
	size_t lower = 0;
	size_t upper = size;
	while (lower < upper)
	{
		size_t index = (lower +  upper) >> 1;
		signed order = strcmp(term, list[index].term);
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
		return (list[index].text);
	}
	if ((program_name) && (* program_name))
	{
		fprintf (stderr, "%s: ", program_name);
	}
	fprintf (stderr, "Have '%s' but need %s ", term, type);
	while ((size_t) (item - list) < size)
	{
		if (item > list)
		{
			fputc ('|', stderr);
		}
		fprintf (stderr, "'%s'", item->term);
		item++;
	}
	fputc ('\n', stderr);
	exit (1);
}

#endif



