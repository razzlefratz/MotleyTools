/*====================================================================*
 *
 *   void scanspace (SCAN * content);
 *
 *   scan.h
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SCANSPACE_SOURCE
#define SCANSPACE_SOURCE

#include <ctype.h>

#include "../scan/scan.h"

void scanspace (SCAN * content) 

{
	while ((content->final < content->limit) && isspace (*content->final)) 
	{
		content->final++;
	}
	return;
}


#endif

