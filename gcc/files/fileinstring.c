/*====================================================================*
 *
 *   bool fileinstring (char const *pathnames, char const *filename)
 *
 *   files.h  
 *
 *   return true if wildcard filespec matches any file found in any
 *   folder named in NUL terminated pathname string;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef FILEINSTRING_SOURCE
#define FILEINSTRING_SOURCE

#include <sys/stat.h>

#include "../files/files.h"

bool fileinstring (char const *pathnames, char const *filename) 

{
	struct stat statinfo;
	char fullname [FILENAME_MAX+1];
	char pathname [FILENAME_MAX+1];

#ifdef CMASSOC_SAFEMODE

	if (pathnames == (char const *)(0)) 
	{
		return (false);
	}
	if (filename == (char const *)(0)) 
	{
		return (false);
	}

#endif

	while (*pathnames != (char) (0)) 
	{
		char *path;
		for (path = pathname; *pathnames != (char) (0); *path++ = *pathnames++) 
		{
			if (*pathnames == PATH_C_SEPARATOR) 
			{
				pathnames++;
				break;
			}
		}
		*path = (char) (0);
		makepath (fullname, pathname, filename);
		if (!lstat (fullname, &statinfo)) 
		{
			return (true);
		}
	}
	return (false);
}


#endif

