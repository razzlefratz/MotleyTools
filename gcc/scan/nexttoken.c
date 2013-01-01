/*====================================================================*
 *
 *   void nexttoken(SCAN * content);
 *
 *   scan.h
 *
 *   collect the next non-space token;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef NEXTTOKEN_SOURCE
#define NEXTTOKEN_SOURCE

#include "../scan/scan.h"

void nexttoken (SCAN * content) 

{
	scanspace (content);
	scanflush (content);
	scantoken (content);
	return;
}


#endif

