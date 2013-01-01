/*====================================================================*
 *
 *   char const *_basename (char const *filespec);
 *
 *   _libgen.h
 *
 *   return filename less the directory prefix; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef _BASENAME_SOURCE
#define _BASENAME_SOURCE

#include "../libgen/_libgen.h"
#include "../files/files.h"

char const *_basename (char const *filespec) 

{
	char const *filename = filespec;
	while (*filespec != (char) (0)) 
	{
		if (*filespec++ == PATH_C_EXTENDER) 
		{
			filename = filespec;
		}
	}
	return (filename);
}


#endif

