/*====================================================================*
 *
 *   void scanalnum (SCAN * content);
 *
 *   scan.h
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SCANALNUM_SOURCE
#define SCANALNUM_SOURCE

#include <ctype.h>

#include "../scan/scan.h"

void scanalnum (SCAN * content) 

{
	while ((content->final < content->limit) && isalnum (*content->final)) 
	{
		content->final++;
	}
	return;
}


#endif

