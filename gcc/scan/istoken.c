/*====================================================================*
 *
 *   bool istoken (SCAN * content, char const *literal);
 *
 *   scan.h
 *
 *   return true if the current token substring matches the given literal
 *   string; comparison is case sensitive;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef ISTOKEN_SOURCE
#define ISTOKEN_SOURCE

#include <ctype.h>

#include "../scan/scan.h"

bool istoken (SCAN * content, char const *literal) 

{
	char const * current = content->first;
	while ((current < content->final) && (*current == *literal)) 
	{
		current++;
		literal++;
	}
	return (*literal == (char) (0));
}


#endif

