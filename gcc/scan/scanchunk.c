/*====================================================================*
 *
 *   void scanchunk (SCAN * content, char const *literal);
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

#ifndef SCANCHUNK_SOURCE
#define SCANCHUNK_SOURCE

#include "../scan/scan.h"

void scanchunk (SCAN * content) 

{
	while ((content->final < content->limit) && (*content->final != '\n')) 
	{
		while ((content->final < content->limit) && (*content->final != '\r')) 
		{
			content->final++;
		}
		content->final++;
	}
	if (content->final < content->limit) 
	{
		content->final++;
	}
	return;
}


#endif

