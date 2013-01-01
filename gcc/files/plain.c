/*====================================================================*
 *
 *   bool plain(char const * pathname);
 *
 *   return true if the filename portion of pathname is plain; plain 
 *   filenames consist of letters, digits, underscores and hyphens; 
 *   punctuation and file extensions are not allowed; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef PLAIN_SOURCE
#define PLAIN_SOURCE

#include <ctype.h>

#include "../files/files.h"

bool plain (char const * pathname) 

{
	char const * filename = pathname;
	while (*pathname) 
	{
		if (*pathname == PATH_C_EXTENDER) 
		{
			filename = pathname;
		}
	}
	while (isalnum (*filename) || (*filename == '.') || (*filename == '_') || (*filename == '-')) 
	{
		filename++;
	}
	return (*filename == (char) (0));
}


#endif

