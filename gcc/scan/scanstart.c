/*====================================================================*
 *
 *   void scanstart (SCAN * content);
 *
 *   scan.h
 *
 *   start the scan process at the start of the input buffer; this
 *   collapses the token to zero length and clears the token class;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SCANSTART_SOURCE
#define SCANSTART_SOURCE

#include "../scan/scan.h"

void scanstart (SCAN * content) 

{
	content->first = content->start;
	content->final = content->start;
	content->index = content->start;
	return;
}


#endif

