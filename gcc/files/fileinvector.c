/*====================================================================*
 *
 *   bool fileinvector (char const *pathnames[], char const *filename)
 *
 *   files.h  
 *
 *   return true if wildcard filespec matches any file found in any
 *   folder named in NULL termnated pathname string vector; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef FILEINVECTOR_SOURCE
#define FILEINVECTOR_SOURCE

#include <sys/stat.h>
#include "../files/files.h"

bool fileinvector (char const *pathnames [], char const *filename) 

{
	struct stat statinfo;
	char fullname [FILENAME_MAX+1];

#ifdef CMASSOC_SAFEMODE

	if (pathnames == (char const **) (0)) 
	{
		return (false);
	}
	if (filename == (char const *) (0)) 
	{
		return (false);
	}

#endif

	while (*pathnames != (char const *) (0)) 
	{
		makepath (fullname, *pathnames++, filename);
		if (!lstat (fullname, &statinfo)) 
		{
			return (true);
		}
	}
	return (false);
}


#endif

