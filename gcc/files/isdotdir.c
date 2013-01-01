/*====================================================================*
 *
 *   bool isdotdir (char const *filename);
 *
 *   files.h
 *
 *   return true if the filename argument is NULL, NIL, "." or "..";
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef ISDOTDIR_SOURCE
#define ISDOTDIR_SOURCE

#include "../tools/types.h"
#include "../files/files.h"

bool isdotdir (char const *filename) 

{
	if (filename != (char *) (0)) 
	{
		if (*filename == '.') 
		{
			filename++;
		}
		if (*filename == '.') 
		{
			filename++;
		}
		if (*filename == (char) (0)) 
		{
			return (true);
		}
	}
	return (false);
}


#endif

