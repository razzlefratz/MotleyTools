/*====================================================================*
 *
 *   void scanuntil (SCAN * content);
 *
 *   scan.h
 *
 *   append input buffer characters to the current token substring while
 *   they are not member of the specified character set; stop on the first
 *   one that is a member; it marks the start of another scan;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SCANUNTILMATCH_SOURCE
#define SCANUNTILMATCH_SOURCE

#include "../scan/scan.h"

void scanuntilmatch (SCAN * content) 

{
	while ((content->final < content->limit) && (*content->final != *content->first)) 
	{
		content->final++;
	}
	return;
}


#endif

