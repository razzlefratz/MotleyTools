/*====================================================================*
 *
 *   int ccollect (LIST * files, char const * paths []);
 *
 *   clang.h
 *
 *   fill list with included filenames;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef CCOLLECT_SOURCE
#define CCOLLECT_SOURCE

#include "../clang/clang.h"
#include "../list/list.h"

int ccollect (LIST * files, char const * paths []) 

{
	files->error = 0;
	for (files->lower = files->start; files->lower < files->count; files->lower++) 
	{
		cinclude (files, paths);
	}
	return (files->error);
}


#endif

