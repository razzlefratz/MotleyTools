/*====================================================================*
 *
 *   int openroot (char const *file, char const *oflag);
 *
 *   files.h 
 *
 *   try to open the named file using open(); if the file does not open
 *   then try to open a file of the same name in each successive parent
 *   folder until the file opens or the root folder has been tried;
 *
 *   return a valid file descriptor on success or -1 on failure;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef OPENROOT_SOURCE
#define OPENROOT_SOURCE

#ifdef WIN32
#include <fcntl.h>
#include <i.h>
#else
#include <unistd.h>
#endif

#include <string.h>

#include "../files/files.h"

int openroot (char const * filename, int oflag) 

{
	char pathname [FILENAME_MAX];
	char * root [FILE_DIR_MAX];
	char * cp;
	int node = 0;
	int fd;
	root [0] = pathname;
	for (cp = pathname; (*cp = *filename); filename++) 
	{
		if (*cp++ == PATH_C_EXTENDER) 
		{
			if (node < FILE_DIR_MAX) 
			{
				root [node++] = cp;
			}
		}
	}
	while (((fd = open (pathname, oflag)) == -1) && (node-- > 1)) 
	{
		strcpy (root [node-1], root [node]);
	}
	return (fd);
}


/*====================================================================*
 *   test/demo program;
 *--------------------------------------------------------------------*/

#if 0

#include <stdio.h>

#include "../tools/error.c"
#include "../tools/error.h"

char const * program_name = "open1";
int main (int argc, char const * argv []) 

{
	int fd;
	while (*++argv) 
	{
		if ((fd = openroot (*argv, O_RDONLY)) == -1) 
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

