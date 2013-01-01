/*====================================================================*
 *
 *   bool fileinfolder (char const *pathname, char const *wildcard)
 *
 *   files.h  
 *
 *   return true if the named file is present in the named folder;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef FILEINFOLDER_SOURCE
#define FILEINFOLDER_SOURCE

#include <dirent.h>

#include "../files/files.h"
#include "../tools/types.h"

bool fileinfolder (char const *pathname, char const *wildcard) 

{
	DIR *dir;
	if ((dir = opendir (pathname))) 
	{
		struct dirent *dirent;
		while ((dirent = readdir (dir))) 
		{
			if (match (dirent->d_name, wildcard)) 
			{
				closedir (dir);
				return (true);
			}
		}
		closedir (dir);
	}
	return (false);
}


#endif

