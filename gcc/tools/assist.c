/*====================================================================*
 *
 *   void assist (struct _code_ const list [], size_t size, char const * name, char const * type, FILE * fp);
 *
 *   symbol.h
 *   
 *   print program name followed by an error message containing the
 *   type of name expected, the incorrect name and a list of correct
 *   name;
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef ASSIST_SOURCE
#define ASSIST_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "../tools/symbol.h"
#include "../tools/error.h"

void assist(struct _code_ const list[], size_t size, char const * name, char const * type, FILE * fp)

{
	extern char const * program_name;
	fprintf (fp, "%s: ", program_name);
	fprintf (fp, "%s: ", strerror(EINVAL));
	if (name)
	{
		fprintf (fp, "Have %s '%s' but need ", type, name);
	}
	else 
	{
		fprintf (fp, "Need %s ", type);
	}
	codelist (list, size, "''", ",", fp);
	fprintf (fp, ".\n");
	exit (1);
}

#endif



