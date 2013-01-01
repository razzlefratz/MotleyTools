/*====================================================================*
 *
 *   char *_filename (char const *filename);
 *
 *   linux.h
 *
 *   return filename less any pathname (directory) prefix; return
 *   an empty string 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef _FILENAME_SOURCE
#define _FILENAME_SOURCE

#include "../files/files.h"

char const *_filename (char const *string) 

{
	char const *sp = string;
	while (*string != (char) (0)) 
	{
		if (*string++ == PATH_C_EXTENDER) 
		{
			sp = string;
		}
	}
	return (sp);
}


#endif

