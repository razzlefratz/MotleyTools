/*====================================================================*
 *
 *   void synonyms (struct _term_ const list [], size_t size, char const * term, char const * type);
 *  
 *   symbol.h
 *
 *   print program name followed by an error message containing the
 *   offending term, type of term and a list of valid terms;
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SYNONYMS_SOURCE
#define SYNONYMS_SOURCE

#include <stdio.h>
#include <stdlib.h>

#include "../tools/symbol.h"

void synonyms (struct _term_ const list [], size_t size, char const * term, char const * type) 

{
	extern char const * program_name;
	const struct _term_ * item = list;
	if ((program_name) && (*program_name)) 
	{
		fprintf (stderr, "%s: ", program_name);
	}
	fprintf (stderr, "Have '%s' but need %s ", term, type);
	while ((size_t)(item - list) < size) 
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

