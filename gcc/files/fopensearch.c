/*====================================================================*
 *
 *   FILE *fopensearch(char const *filename, char const *openmode, char const *pathlist);
 *
 *   files.h
 *
 *   attempt to open the named file in each path named in pathlist 
 *   until one of them opens or pathlist is exhausted; return the 
 *   open file pointer on success or (FILE *)(0) on failure;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef FOPENSEARCH_SOURCE
#define FOPENSEARCH_SOURCE

#include <stdio.h>
#include <string.h>

#include "../files/files.h"

FILE *fopensearch (char const *filename, char const *openmode, char const *pathlist) 

{
	char nextpath [FILENAME_MAX];
	char *pathname;
	FILE *fp;

#ifdef CMASSOC_SAFEMODE

	if (filename == (char const *) (0)) 
	{
		return ((FILE *) (0));
	}
	if (pathlist == (char const *) (0)) 
	{
		return ((FILE *) (0));
	}

#endif

	while (*pathlist != (char) (0)) 
	{
		for (pathname = nextpath; *pathlist != (char) (0); *pathname++ = *pathlist++) 
		{
			if (*pathlist == PATH_C_SEPARATOR) 
			{
				pathlist++;
				break;
			}
		}
		*pathname++ = PATH_C_EXTENDER;
		strcpy (pathname, filename);
		if ((fp = fopen (nextpath, openmode)) != (FILE *) (0)) 
		{
			return (fp);
		}
	}
	return ((FILE *) (0));
}


#endif

