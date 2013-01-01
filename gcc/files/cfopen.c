/*====================================================================*
 *
 *   bool cfopen(char const *pathname, char const *extender);
 *
 *   open the named file as stdout; rename it by appending the given  
 *   extender;  
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef CFOPEN_SOURCE
#define CFOPEN_SOURCE

#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "../files/files.h"
#include "../tools/error.h"

bool cfopen (char const *filename, char const *extender) 

{
	struct stat statinfo;
	char loadname [FILENAME_MAX];
	char savename [FILENAME_MAX];
	char const *sp = filename;
	char *cp = (char *)(sp);;
	makepath (loadname, getenv ("PWD"), filename);
	makepath (savename, getenv ("PWD"), filename);
	while (*sp) 
	{
		if (*sp == FILE_C_EXTENDER) 
		{
			cp = (char *) (sp);
		}
		sp++;
	}
	if (*cp != FILE_C_EXTENDER) 
	{
		cp = (char *)(sp);
	}
	while ((*cp++ = *extender++));
	if (lstat (loadname, &statinfo)) 
	{
		error (0, errno, "Can't open %s", loadname);
		return (false);
	}
	if (S_ISDIR (statinfo.st_mode)) 
	{
		error (0, ECANCELED, "Won't open %s: file is a directory.", loadname);
		return (false);
	}
	if (!freopen (loadname, "rb", stdin)) 
	{
		error (0, errno, "Can't open %s for input", loadname);
		return (false);
	}
	if (!freopen (savename, "wb", stdout)) 
	{
		error (0, errno, "Can't open %s for output", savename);
		return (false);
	}
	return (true);
}


#endif

