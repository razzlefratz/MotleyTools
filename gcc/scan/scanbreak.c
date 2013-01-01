/*====================================================================*
 *
 *   void scanbreak (SCAN * content, char const *charset);
 *
 *   scan.h
 * 
 *   append the next input character to the current token if it is
 *   in charaset;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SCANBREAK_SOURCE
#define SCANBREAK_SOURCE

#include "../scan/scan.h"

void scanbreak (SCAN * content, char const *charset) 

{
	if ((content->final < content->limit) && isbreak (content, charset)) 
	{
		content->final++;
	}
	return;
}


#endif

