/*====================================================================*
 *
 *   void partfile (char const *filespec, char filename[], char extender[]);
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

#ifndef PARTFILE_SOURCE
#define PARTFILE_SOURCE

#include "../files/files.h"

void partfile (char const *filespec, char filename [], char extender []) 

{
	char const *sp;

#ifdef FILE_SAFEMODE

	if (filespec == (char const *) (0)) 
	{
		return;
	}
	if (filename == (char *) (0)) 
	{
		return;
	}
	if (extender == (char *) (0)) 
	{
		return;
	}

#endif

	for (sp = filespec; *sp != (char) (0); sp++) 
	{
		if ((*sp == PATH_C_EXTENDER) || (*sp == FILE_C_EXTENDER)) 
		{
			while (filespec < sp) 
			{
				*filename++ = *filespec++;
			}
		}
	}
	if (*filespec == FILE_C_EXTENDER) 
	{
		filespec++;
		while (filespec < sp) 
		{
			*extender++ = *filespec++;
		}
	}
	else 
	{
		while (filespec < sp) 
		{
			*filename++ = *filespec++;
		}
	}
	*filename++ = (char) (0);
	*extender++ = (char) (0);
	return;
}


#endif

