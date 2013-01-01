/*====================================================================*
 *
 *   void scanbreakmatch (SCAN * content);
 *
 *   scan.h
 * 
 *   append the next input character to the current token if it is
 *   the same as the first token character;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SCANBREAKMATCH_SOURCE
#define SCANBREAKMATCH_SOURCE

#include "../scan/scan.h"

void scanbreakmatch (SCAN * content) 

{
	if ((content->final < content->limit) && (*content->final != *content->first)) 
	{
		content->final++;
	}
	return;
}


#endif

