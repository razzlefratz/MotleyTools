/*====================================================================*
 *
 *   void scanalpha (SCAN * content);
 *
 *   scan.h
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SCANALPHA_SOURCE
#define SCANALPHA_SOURCE

#include <ctype.h>

#include "../scan/scan.h"

void scanalpha (SCAN * content) 

{
	while ((content->final < content->limit) && isalpha (*content->final)) 
	{
		content->final++;
	}
	return;
}


#endif

