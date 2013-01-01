/*====================================================================*
 *
 *   int openpath (char const *file, int oflag, char const *pathstring);
 *
 *   files.h
 *
 *   try to open the named file using open(); if the file does not open
 *   then try to open a file of the same name in each successive parent
 *   folder until the file opens or the root folder has been tried;
 *
 *   if that fails then repeat the process for each path listed in the
 *   pathstring; calling this function with a NULL or empty pathstring
 *   is equivalent to calling open1();
 *
 *   return a valid file descriptor on success or -1 on failure;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef OPENPATH_SOURCE
#define OPENPATH_SOURCE

#ifdef _WIN32
#include <fcntl.h>
#include <io.h>
#else
#include <unistd.h>
#endif

#include <sys/types.h>
#include <string.h>

#include "../files/files.h"

int openpath (char const *filename, int oflag, char const *folders) 

{
	char pathname [FILENAME_MAX];
	int fd;
	if ((fd = open (filename, oflag)) != -1) 
	{
		return (fd);
	}
	if (folders) while (*folders) 
	{
		char * sp = pathname;
		while ((*sp = *folders) && (*sp != PATH_C_SEPARATOR)) 
		{
			folders++;
			sp++;
		}
		*sp++ = PATH_C_EXTENDER;
		strcpy (sp, filename);
		if ((fd = open (pathname, oflag)) != -1) 
		{
			return (fd);
		}
		if (*folders) 
		{
			folders++;
		}
	}
	return (-1);
}


/*====================================================================*
 *   demo/test program;
 *--------------------------------------------------------------------*/

#if 0

#include <stdio.h>

#include "../tools/error.h"
#include "../tools/error.c"

char const * program_name = "openpath";
int main (int argc, char const * argv []) 

{
	char * pathlist;
	int fd;
	if (*++argv) 
	{
		pathlist = *argv;
	}
	while (*++argv) 
	{
		if ((fd = openpath (*argv, O_RDONLY, pathlist)) == -1) 
		{
			error (0, 0, "can't open %s", *argv);
			continue;
		}
		error (0, 0, "opened %s", *argv);
		close (fd);
	}
	return (0);
}


#endif

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif

