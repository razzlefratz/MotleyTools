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
#include "../tools/types.h"

void showfind (struct _find_ *find, FILE * fp) 

{
	fprintf (fp, "fullname=[%s]\n", find->fullname);
	fprintf (fp, "pathname=[%s]\n", find->pathname);
	fprintf (fp, "filename=[%s]\n", find->filename);
	fprintf (fp, "basename=[%s]\n", find->basename);
	fprintf (fp, "extender=[%s]\n", find->extender);
	fprintf (fp, "wildcard=[%s]\n", find->wildcard);
	fprintf (fp, "flagword=[0x%08X]\n", find->flagword);

// fprintf (fp, "filetime=[%u]\n", find->filetime);

	fprintf (fp, "filesize=[%zu]\n", find->filesize);
	fprintf (fp, "\n");
	return;
}


#endif

