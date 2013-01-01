/*====================================================================*
 *
 *   size_t filelist(char const *pathname, char const *wildcard, char const *list[], size_t size);
 *
 *   fill a string vector with filenames from the specified folder 
 *   pathname;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef FILELIST_SOURCE
#define FILELIST_SOURCE

#include <dirent.h>
#include <stddef.h>
#include <string.h>

#include "../strlib/strlib.h"
#include "../files/files.h"
#include "../list/list.h"

size_t filelist (char const *pathname, char const *wildcard, char const *list [], size_t size) 

{
	DIR *dir;
	struct dirent *file;
	size_t count = 0;
	if ((dir = opendir (pathname))) 
	{
		while ((count < size) && (file = readdir (dir))) 
		{
			if (match (file->d_name, wildcard)) 
			{
				size_t index;
				for (index = count++; index > 0; index--) 
				{
					if (strcmp (file->d_name, list [index - 1]) >= 0) 
					{
						break;
					}
					list [index] = list [index - 1];
				}
				list [index] = strdup (file->d_name);
				list [count] = (char *) (0);
			}
		}
		closedir (dir);
	}
	return (count);
}


#endif

