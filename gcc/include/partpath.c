/*====================================================================*
 *
 *   void partpath (char const *filespec, char pathname[], char basename[]);
 *
 *   files.h
 *
 *   scan filespec and copy the path component into the pathname
 *   buffer and file component into the filename buffer; missing
 *   components are not expanded; expand missing components with
 *   aother function; see makefind() for one example;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef PARTPATH_SOURCE
#define PARTPATH_SOURCE

#include "../files/files.h"

void partpath (char const *filespec, char *pathname, char *basename) 

{
	char const *sp;

#ifdef FILE_SAFEMODE

	if (filespec == (char const *) (0)) 
	{
		return;
	}
	if (pathname == (char *) (0)) 
	{
		return;
	}
	if (basename == (char *) (0)) 
	{
		return;
	}

#endif

	if (*filespec == PATH_C_EXTENDER) 
	{
		*pathname++ = *filespec++;
	}
	for (sp = filespec; *sp != (char) (0); sp++) 
	{
		if (*sp == PATH_C_EXTENDER) 
		{
			while (filespec < sp) 
			{
				*pathname++ = *filespec++;
			}
		}
	}
	if (*filespec == PATH_C_EXTENDER) 
	{
		filespec++;
	}
	while (filespec < sp) 
	{
		*basename++ = *filespec++;
	}
	*pathname++ = (char) (0);
	*basename++ = (char) (0);
	return;
}


#endif

