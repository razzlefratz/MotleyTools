/*====================================================================*
 *
 *   void scanwhile (SCAN * content, char const *charset);
 *
 *   scan.h
 * 
 *   append input characters to the current token while they are 
 *   members of the specified character set; stop on the first one
 *   that is not a member; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SCANWHILE_SOURCE
#define SCANWHILE_SOURCE

#include "../scan/scan.h"

void scanwhile (SCAN * content, char const *charset) 

{
	while ((content->final < content->limit) && isbreak (content, charset)) 
	{
		content->final++;
	}
	return;
}


#endif

