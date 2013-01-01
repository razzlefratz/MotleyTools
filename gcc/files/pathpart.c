/*====================================================================*
 *
 *   char *pathpart (char const *filename);
 *
 *   files.h
 *
 *   return pathname (directory) portion of a file specification
 *   filename as a new filename;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef PATHPART_SOURCE
#define PATHPART_SOURCE

#include <string.h>

#include "../files/files.h"

char const *pathpart (char const *filename) 

{
	static char buffer [FILENAME_MAX];
	char *anchor = strcpy (buffer, filename);
	for (filename = (char const *)(buffer); *filename != (char) (0); filename++) 
	{
		if (*filename == PATH_C_EXTENDER) 
		{
			anchor = (char *) (filename);
		}
	}
	*anchor = (char) (0);
	return (buffer);
}


#endif

