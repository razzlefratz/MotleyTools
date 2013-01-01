/*====================================================================*
 *
 *   bool isbreak (SCAN * content, char const *charset);
 *
 *   scan.h
 *
 *   return true if the current input character is a member of the 
 *   specified character set; comparison is case sensitive;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef ISBREAK_SOURCE
#define ISBREAK_SOURCE

#include "../scan/scan.h"

bool isbreak (SCAN * content, char const *charset) 

{
	if (content->final < content->limit) while (*charset) 
	{
		if (*charset == *content->final) 
		{
			return (true);
		}
		charset++;
	}
	return (false);
}


#endif

