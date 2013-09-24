/*====================================================================*
 *
 *   void typelist (struct _type_ const list [], size_t size, const char * group, char const * comma, FILE * fp);
 *
 *   symbol.h
 *   
 *   print a list of typelisted symbols on stderr;
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef TYPELIST_SOURCE
#define TYPELIST_SOURCE

#include <stdio.h>

#include "../tools/symbol.h"

void typelist(struct _type_ const list[], size_t size, char const * group, char const * comma, FILE * fp)

{
	struct _type_ const * item = list;
	if (list) while((size_t) (item - list) < size)
	{
		if (item > list)
		{
			fputs (comma, fp);
		}
		if ((group) && (* group))
		{
			fputc (* group++, stdout);
		}
		fprintf (fp, "%s", item->name);
		if ((group) && (* group))
		{
			fputc (* group++, stdout);
		}
		item++;
	}
	return;
}

#endif



