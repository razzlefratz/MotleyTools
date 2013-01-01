/*====================================================================*
 *
 *   void nextbreak(SCAN * content);
 *
 *   scan.h
 *
 *   append the current input buffer character to the current token 
 *   by incrementing the input character pointer but do not advance
 *   past the end of the input buffer;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef NEXTBREAK_SOURCE
#define NEXTBREAK_SOURCE

#include "../scan/scan.h"

void nextbreak (SCAN * content) 

{
	if (content->final < content->limit) 
	{
		content->final++;
	}
	return;
}


#endif

