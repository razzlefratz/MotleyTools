/*====================================================================*
 *
 *   void scanuntil (char const *charsetm SCAN * content);
 *
 *   scan.h
 * 
 *   append input characters to the current token while they are not 
 *   members of the specified character set; stop on the first one 
 *   that is a member; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SCANUNTIL_SOURCE
#define SCANUNTIL_SOURCE

#include "../scan/scan.h"

void scanuntil (SCAN * content, char const *charset) 

{
	while ((content->final < content->limit) && !isbreak (content, charset)) 
	{
		content->final++;
	}
	return;
}


#endif

