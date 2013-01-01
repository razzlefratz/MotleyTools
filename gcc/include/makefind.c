/*====================================================================*
 *
 *   void makefind (struct _find_ *search, char const *filespec);
 *
 *   find.h
 *
 *   initialize _find_ struct with pathname and filename components
 *   from filespec; expand components to make fullpath and wildcard;
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
#include <error.h>
#include <errno.h>

#include "../files/files.h"
#include "../files/find.h"

void makefind (struct _find_ *find, char const *filespec, code_t mode) 

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

	makepath (find->fullpath, getenv ("PWD"), filespec);
	partpath (find->fullpath, find->pathname, find->basename);
	partfile (find->basename, find->filename, find->extender);
	if (find->pathname [0] == (char) (0)) 
	{
		find->pathname [0] = FILE_C_EXTENDER;
		find->pathname [1] = (char) (0);
	}
	if (find->basename [0] == (char) (0)) 
	{
		find->basename [0] = FILE_C_EXTENDER;
		find->basename [1] = (char) (0);
	}
	strcpy (find->fullpath, find->pathname);
	strcat (find->fullpath, PATH_S_EXTENDER);
	strcat (find->fullpath, find->basename);
	switch (mode) 
	{
	case FIND_M_NORMAL:
		strcpy (find->wildcard, find->basename);
		break;
	case FIND_M_SEARCH:
		strcpy (find->fullpath, find->pathname);
		strcpy (find->wildcard, find->basename);
		break;
	default:
		error (1, EINVAL, "makefind (..., code_t mode)");
	}
	if (find->wildcard [0] == FILE_C_EXTENDER) 
	{
		find->wildcard [0] = FILE_C_WILDCARD;
		find->wildcard [1] = (char) (0);
	}
	return;
}


#endif

