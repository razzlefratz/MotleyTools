/*====================================================================*
 *   
 *   bool checkfilename (char const * pathname);
 *
 *   files.h
 *   
 *   confirm that the filename portion of a pathname string contains
 *   only letters, digits, periods, underscores and hyphens; 
 *
 *   this prevents users from entering an Ethernet address where a 
 *   filename should appear on the command line; Ethernet addresses 
 *   are also valid filenames;
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef CHECKFILENAME_SOURCE
#define CHECKFILENAME_SOURCE

#include <string.h>
#include <ctype.h>

#include "../files/files.h"

bool checkfilename (char const * pathname) 

{
	char const * filename;
	for (filename = pathname; *pathname; pathname++) 
	{
		if ((*pathname == '/') || (*pathname == '\\')) 
		{
			filename = pathname + 1;
		}
	}
	while (isalnum (*filename) || (*filename == '.') || (*filename == '_') || (*filename == '-')) 
	{
		filename++;
	}
	return (*filename == (char) (0));
}


#endif

