/*====================================================================*
 *
 *   bool fileexists (char const *filename)
 *
 *   files.h  
 *
 *   return true if filename exists;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef FILEEXISTS_SOURCE
#define FILEEXISTS_SOURCE

#include <sys/stat.h>

#include "../files/files.h"

bool fileexists (char const *filename) 

{
	struct stat statinfo;
	return (!lstat (filename, &statinfo));
}


#endif

