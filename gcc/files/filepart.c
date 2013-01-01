/*====================================================================*
 *
 *   char const *filepart (char const * pathname);
 *
 *   files.h
 *
 *   return the address of the filename portion of pathname;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef FILEPART_SOURCE
#define FILEPART_SOURCE

#include "../files/files.h"

char const * filepart (char const * pathname) 

{
	char const *filename = pathname;
	while (*pathname) 
	{

#if 1

		if (*pathname++ == PATH_C_EXTENDER) 
		{
			filename = pathname;
		}

#else

		if ((*pathname == '/') || (*pathname == '\\')) 
		{
			filename = pathname + 1;
		}
		pathname++;

#endif

	}
	return (filename);
}


#endif

