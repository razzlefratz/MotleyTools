/*====================================================================*
 *
 *   void scanreset (SCAN * content);
 *
 *   scan.h
 *
 *   begin the scan process at the start of the token string; this
 *   collapses the token to zero length and clears the token class;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SCANRESET_SOURCE
#define SCANRESET_SOURCE

#include "../scan/scan.h"

void scanreset (SCAN * content) 

{
	content->final = content->first;
	return;
}


#endif

