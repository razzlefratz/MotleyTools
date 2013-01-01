/*====================================================================*
 *
 *   void makefind (struct _find_ *search, char const *filespec);
 *
 *   find.h
 *
 *   initialize _find_ struct with pathname and filename components
 *   from filespec; expand components to make fullname and wildcard;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef FINDPATH_SOURCE
#define FINDPATH_SOURCE

#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

#include "../tools/error.h"
#include "../files/files.h"
#include "../files/find.h"

void makefind (struct _find_ *find, char const *filespec) 

{

#ifdef CMASSOC_SAFEMODE

	if (find == (struct _find_ *) (0)) 
	{
		return;
	}
	if (filespec == (char const *) (0)) 
	{
		return;
	}

#endif

	makepath (find->fullname, getenv ("PWD"), filespec);
	partpath (find->fullname, find->pathname, find->filename);
	partfile (find->filename, find->basename, find->extender);
	strcpy (find->wildcard, find->filename);
	if (find->pathname [0] == (char) (0)) 
	{
		find->pathname [0] = FILE_C_EXTENDER;
		find->pathname [1] = (char) (0);
	}
	if (find->filename [0] == (char) (0)) 
	{
		find->filename [0] = FILE_C_EXTENDER;
		find->filename [1] = (char) (0);
	}
	for (filespec = find->filename; *filespec != (char)(0); filespec++) 
	{
		if (strchr ("\\[]!?*&|=;", *filespec) != (char *)(0)) 
		{
			strcpy (find->fullname, find->pathname);
			strcpy (find->wildcard, find->filename);
			find->filename [0] = FILE_C_WILDCARD;
			find->filename [1] = (char) (0);
			find->basename [0] = FILE_C_WILDCARD;
			find->basename [1] = (char) (0);
		}
	}
	if (find->wildcard [0] == FILE_C_EXTENDER) 
	{
		find->wildcard [0] = FILE_C_WILDCARD;
		find->wildcard [1] = (char) (0);
	}
	return;
}


#endif

