/*====================================================================*
 *
 *   void showfind (struct _find_ * find, FILE * file);
 *   
 *   find.h
 *   
 *   print the internals of struct _find_ on stdout;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *   
 *--------------------------------------------------------------------*/

#ifndef SHOWFIND_SOURCE
#define SHOWFIND_SOURCE

#include <stdio.h>

#include "../files/find.h"

void showfind (struct _find_ *find, FILE * fp) 

{
	fprintf (fp, "flagword=[%04X]\n", find->flagword);
	fprintf (fp, "fullpath=[%s]\n", find->fullpath);
	fprintf (fp, "pathname=[%s]\n", find->pathname);
	fprintf (fp, "basename=[%s]\n", find->basename);
	fprintf (fp, "filename=[%s]\n", find->filename);
	fprintf (fp, "extender=[%s]\n", find->extender);
	fprintf (fp, "wildcard=[%s]\n", find->wildcard);
	fprintf (fp, "\n");
	return;
}


#endif

