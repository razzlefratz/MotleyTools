/*====================================================================*
 *
 *   FILE *efopen(char const *filename, char const *openmode);
 *
 *   tools.h
 *
 *   attempt to open a file using fopen(); return a valid file pointer
 *   on success; print an error message to stderr and then return NULL
 *   on failure;
 *
 *   this function simplifies program logic because no error handling is
 *   needed; it simply does not return on error; also see efreopen();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef EFOPEN_SOURCE
#define EFOPEN_SOURCE

#include <stdio.h>
#include <errno.h>

#include "../tools/tools.h"
#include "../tools/error.h"

FILE *efopen (char const *filename, char const *openmode) 

{
	FILE *fp;
	if ((fp = fopen (filename, openmode)) == (FILE *)(0)) 
	{
		error (0, errno, "%s", filename);
	}
	return (fp);
}


#endif

