/*====================================================================*
 *
 *   char *makepath (char fullpath[], char const * absolute, char const *relative)
 *
 *   split the absolute pathname and relative pathname string arguments
 *   into constituent components; sort through the constituents and make
 *   one clean pathname string;
 *
 *   pathname is split into constituent filenames; filename is then split
 *   split into constituent filenames that are appended to the ones from
 *   pathname; if filename starts with a slash then its filenames replace 
 *   those from pathname; the result is a vector of strings "", ".", ".." 
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

#if 0

static void showstack (size_t limit, char const *stack []) 

{
	size_t count;
	for (count = 0; count < limit; count++) 
	{
		printf ("%d [%s]\n", count, stack [count]);
	}
	printf ("\n");
	return;
}


#endif

char *makepath (char fullpath [], char const *absolute, char const *relative) 

{
	char const *stack [FILE_DIR_MAX] = 
	{
		(char *)(0)
	};
	char buffer1 [FILENAME_MAX];
	char buffer2 [FILENAME_MAX];
	size_t limit = sizeof (stack);
	size_t level = 0;

#ifdef CMASSOC_SAFEMODE

	if (fullpath == (char *) (0)) 
	{
		return (fullpath);
	}
	if (absolute == (char *) (0)) 
	{
		return (fullpath);
	}
	if (relative == (char *) (0)) 
	{
		return (fullpath);
	}

#endif

	level = splitpath (level, limit, stack, strcpy (buffer1, absolute));
	level = splitpath (level, limit, stack, strcpy (buffer2, relative));
	limit = mergepath (level, limit, stack);
	strcpy (fullpath, stack [0]);
	for (level = 1; level < limit; level++) 
	{
		strcat (fullpath, PATH_S_EXTENDER);
		strcat (fullpath, stack [level]);
	}
	return (fullpath);
}


#endif

