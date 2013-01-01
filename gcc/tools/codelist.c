/*====================================================================*
 *
 *   void codelist (struct _code_ const list [], size_t size, const char * group, char const * comma, FILE * fp);
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

#ifndef CODELIST_SOURCE
#define CODELIST_SOURCE

#include <stdio.h>

#include "../tools/symbol.h"

void codelist (struct _code_ const list [], size_t size, char const * group, char const * comma, FILE * fp) 

{
	struct _code_ const * item = list;
	if (list) while ((size_t)(item - list) < size) 
	{
		if (item > list) 
		{
			fputs (comma, fp);
		}
		if ((group) && (*group)) 
		{
			fputc (*group++, fp);
		}
		fprintf (fp, "%s", item->name);
		if ((group) && (*group)) 
		{
			fputc (*group++, fp);
		}
		item++;
	}
	return;
}


#endif

