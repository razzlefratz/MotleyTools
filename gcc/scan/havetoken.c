/*====================================================================*
 *
 *   bool havetoken(SCAN * content, char const *literal);
 *
 *   scan.h
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef HAVETOKEN_SOURCE
#define HAVETOKEN_SOURCE

#include "../scan/scan.h"

bool havetoken (SCAN * content, char const *literal) 

{
	if (istoken (content, literal)) 
	{
		nexttoken (content);
		return (true);
	}
	return (false);
}


#endif

