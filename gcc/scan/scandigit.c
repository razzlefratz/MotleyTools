/*====================================================================*
 *
 *   void scandigit (SCAN * content);
 *
 *   scan.h
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SCANDIGIT_SOURCE
#define SCANDIGIT_SOURCE

#include <ctype.h>

#include "../scan/scan.h"

void scandigit (SCAN * content) 

{
	while ((content->final < content->limit) && isdigit (*content->final)) 
	{
		content->final++;
	}
	return;
}


#endif

