/*====================================================================*
 *
 *   void scanflush(SCAN * content);
 *
 *   scan.h
 * 
 *   flush the current token by aligning the first character pointer 
 *   to the input character pointer, creating in a zero-length token 
 *   string;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SCANFLUSH_SOURCE
#define SCANFLUSH_SOURCE

#include "../scan/scan.h"

void scanflush (SCAN * content) 

{
	content->first = content->final;
	return;
}


#endif

