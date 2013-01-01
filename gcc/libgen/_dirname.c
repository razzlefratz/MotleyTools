/*====================================================================*
 *
 *   char const *_dirname (char const *filespec);
 *
 *   _libgen.h
 *
 *   return directory portion of filespec; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef _DIRNAME_SOURCE
#define _DIRNAME_SOURCE

#include <string.h>

#include "../libgen/_libgen.h"
#include "../files/files.h"
#include "../tools/sizes.h"

char const *_dirname (char const *filespec) 

{
	static char buffer [FILENAME_MAX];
	char *pathname = strcpy (buffer, filespec);
	for (filespec = (char const *)(buffer); *filespec != (char) (0); filespec++) 
	{
		if (*filespec == PATH_C_EXTENDER) 
		{
			pathname = (char *) (filespec);
		}
	}
	if (*pathname != PATH_C_EXTENDER) 
	{
		*pathname++ = FILE_C_EXTENDER;
	}
	*pathname = (char) (0);
	return (buffer);
}


#endif

