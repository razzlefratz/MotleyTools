/*====================================================================*
 *
 *   void scanblock (SCAN * content, char const *literal);
 *
 *   collect input characters until an inverted pair is detected; the 
 *   pair is specified in reverse order;
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

#ifndef SCANBLOCK_SOURCE
#define SCANBLOCK_SOURCE

#include "../scan/scan.h"

void scanblock (SCAN * content, char const *literal) 

{
	while ((content->final < content->limit) && (*content->final != *literal)) 
	{
		literal++;
		scanuntil (content, literal);
		scanbreak (content, literal);
		literal--;
	}
	nextbreak (content);
	return;
}


#endif

