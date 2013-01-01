/*====================================================================*
 *
 *   char *fullpath (char pathname[], char const *filename);
 *
 *   files.h
 *
 *   convert filename to an absolute pathname; use the current working 
 *   directory ${PWD} as the reference; return the result in the user
 *   specified buffer;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef FULLPATH_SOURCE
#define FULLPATH_SOURCE

#include <stdlib.h>

#include "../files/files.h"

char *fullpath (char pathname [], char const *filename) 

{
	return (makepath (pathname, getenv ("PWD"), filename));
}


#endif

