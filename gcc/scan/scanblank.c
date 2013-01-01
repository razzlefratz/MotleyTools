/*====================================================================*
 *
 *   void scanblank (SCAN * content);
 *
 *   scan.h
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SCANBLANK_SOURCE
#define SCANBLANK_SOURCE

#include <ctype.h>

#include "../scan/scan.h"

void scanblank (SCAN * content) 

{
	while ((content->final < content->limit) && (isblank (*content->final))) 
	{
		content->final++;
	}
	return;
}


#endif

