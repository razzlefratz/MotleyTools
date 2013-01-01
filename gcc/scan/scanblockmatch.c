/*====================================================================*
 *
 *   void scanblockmatch (SCAN * content);
 *
 *   scan characters until an inverted pair is detected; the pair
 *   must occur in the same order as the first two literal characters;
 *
 *   this method collects text between inverted delimiter pairs like:
 *   
 *   "{* ... *}" or "-- ... --"
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SCANBLOCKMATCH_SOURCE
#define SCANBLOCKMATCH_SOURCE

#include "../scan/scan.h"

void scanblockmatch (SCAN * content) 

{
	while ((content->final < content->limit) && (*content->final != *content->first)) 
	{
		content->first++;
		scanuntilmatch (content);
		scanbreakmatch (content);
		content->first--;
	}
	if (content->final < content->limit) 
	{
		content->final++;
	}
	return;
}


#endif

