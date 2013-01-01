/*====================================================================*
 *
 *   bool isready (SCAN * content);
 *
 *   scan.h
 *
 *   return true unless the input buffer has been scanned;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef ISREADY_SOURCE
#define ISREADY_SOURCE

#include <string.h>

#include "../scan/scan.h"

bool isready (SCAN * content) 

{
	return (content->first < content->limit);
}


#endif

