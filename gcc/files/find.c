/*====================================================================*
 *
 *   struct _find_ find; 
 *
 *   find.h
 *
 *   generic struct _find_ used for recursive searching; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef FIND_SOURCE
#define FIND_SOURCE
#include <time.h>
#include "../tools/types.h"
#include "../files/files.h"
#include "../files/find.h"

struct _find_ find = 

{
	{
		
	},
	"",
	FILE_S_EXTENDER,
	FILE_S_EXTENDER,
	"",
	"",
	FILE_S_WILDCARD,
	(flag_t)(0),
	(mode_t)(0),
	(time_t)(0),
	(size_t)(0),
	(file_t)(-1)
};


#endif

