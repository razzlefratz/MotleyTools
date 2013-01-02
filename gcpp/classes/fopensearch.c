/*====================================================================*
 *
 *   FILE *fopensearch(char const *filename, char const *openmode, char const *pathlist);
 *
 *   file.h
 *
 *   attempt to open the named file in each path named in pathlist 
 *   until one of them opens or pathlist is exhausted; return the 
 *   open file pointer on success or (FILE *)(0) on failure;
 *
 *.  published 2003 by charles maier associates limited for internal use;
 *:  modified sun 07 sep 03 by user root on host zeus;
 *;  compiled for debian gnu/linux using gcc compiler;
 *
 *--------------------------------------------------------------------*/

#ifndef FOPENSEARCH_SOURCE
#define FOPENSEARCH_SOURCE

#include <stdio.h>
#include <string.h>

#include "files.h"
 
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


