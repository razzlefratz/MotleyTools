/*====================================================================*
 *
 *   bool havematch(SCAN * content);
 *
 *   scan.h
 *
 *   return true if the input token character matches the first and
 *   advance to the next character; otherwise, return false and do
 *   nothing;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef HAVEMATCH_SOURCE
#define HAVEMATCH_SOURCE

#include "../scan/scan.h"

bool havematch (SCAN * content) 

{
	if (ismatch (content)) 
	{
		nextbreak (content);
		return (true);
	}
	return (false);
}


#endif

