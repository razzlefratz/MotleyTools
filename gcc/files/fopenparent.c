/*====================================================================*
 *
 *   FILE * fopenparent (char const * file, char const * openmode);
 *
 *   files.h
 *
 *   open the named file with fopen(); if the file does not open then
 *   search  each parent folder; ultimately return a valid file pointer
 *   or NULL; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef FOPENPARENT_SOURCE
#define FOPENPARENT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../files/files.h"

FILE * fopenparent (char const * filename, char const * openmode) 

{
	char fullpath [FILENAME_MAX];
	char * cp;
	char * sp;
	strcpy (fullpath, filename);
	for (sp = cp = fullpath; *cp; ++cp) 
	{
		if (*cp == PATH_C_EXTENDER) 
		{
			sp = cp;
		}
	}
	while (cp > fullpath) 
	{
		if (*--cp == PATH_C_EXTENDER) 
		{
			sp = strcpy (cp, sp);

#if 1

			printf ("%s\n", fullpath);

#else

			if ((fp = fopen (filename, openmode))) 
			{
				return (fp);
			}

#endif

		}
	}
	return ((FILE *) (0));
}


/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#if 0

int main (int argc, char *argv []) 

{
	while (--argc) 
	{
		fopenparent (*++argv, "r");
	}
	return;
}


#endif

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif

