/*====================================================================*
 *
 *   char *_pathname (char const *string);
 *
 *   linux.h
 *
 *   return pathname (directory) portion of a file specification
 *   string as a new string;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef _PATHNAME_SOURCE
#define _PATHNAME_SOURCE

#include <string.h>

#include "../files/files.h"

char const *_pathname (char const *string) 

{
	static char buffer [FILENAME_MAX];
	char *sp = strcpy (buffer, string);
	for (string = (char const *)(buffer); *string != (char) (0); string++) 
	{
		if (*string == PATH_C_EXTENDER) 
		{
			sp = (char *) (string);
		}
	}
	if (*sp != PATH_C_EXTENDER) 
	{
		*sp++ = FILE_C_EXTENDER;
	}
	*sp = (char) (0);
	return (buffer);
}


#endif

