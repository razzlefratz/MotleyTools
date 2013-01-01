/*====================================================================*
 *
 *   char *makepath (char pathname[], char const *basename, char const *filename)
 *
 *   split the absolute pathname and relative pathname string arguments
 *   into constituent filenames; sort through the constituents and make
 *   one clean pathname string;
 *
 *   absolute is split into constituent filenames; relative is then split
 *   split into constituent filenames that are appended to the ones from
 *   absolute; if relative starts with a slash then its filenames replace 
 *   those from absolute; the result is a vector of strings "", ".", ".." 
 *   and filenames;
 *
 *   we preserve leading "" strings then collect remaining strings except
 *   for "", "." and ".." strings; each "" and "." is discarded and ".." 
 *   discarded after decrementing the accumulation counter; the resulting
 *   string vector is copied to the baseline string argument with slashes
 *   to separate each strings;
 *  
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef MAKEPATH_SOURCE
#define MAKEPATH_SOURCE

#include <string.h>

#include "../files/files.h"

char *makepath (char fullpath [], char const *pathname, char const *filename) 

{
	char const *stack [FILE_DIR_MAX] = 
	{
		FILE_S_EXTENDER
	};
	char buffer1 [FILENAME_MAX];
	char buffer2 [FILENAME_MAX];
	size_t count = 1;
	size_t limit = sizeof (stack);

#ifdef FILE_SAFEMODE

	if (fullpath == (char *) (0)) 
	{
		return (fullpath);
	}
	if (pathname == (char *) (0)) 
	{
		return (fullpath);
	}
	if (filename == (char *) (0)) 
	{
		return (fullpath);
	}

#endif

	count = splitpath (count, limit, stack, strcpy (buffer1, pathname));
	count = splitpath (count, limit, stack, strcpy (buffer2, filename));
	limit = mergepath (count, limit, stack);
	strcpy (fullpath, stack [0]);
	for (count = 1; count < limit; count++) 
	{
		strcat (fullpath, PATH_S_EXTENDER);
		strcat (fullpath, stack [count]);
	}
	return (fullpath);
}


#endif

