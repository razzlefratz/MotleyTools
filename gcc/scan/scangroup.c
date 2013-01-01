/*====================================================================*
 *
 *   void scangroup (SCAN * content, char const *charset);
 *
 *   scan.h
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SCANGROUP_SOURCE
#define SCANGROUP_SOURCE

#include "../scan/scan.h"

void scangroup (SCAN * content, char const *charset) 

{
	while ((content->final < content->limit) && !isbreak (content, charset)) 
	{
		switch (*content->final++) 
		{
		case '{':
			scangroup (content, "}");
			nextbreak (content);
			break;
		case '(':
			scangroup (content, ")");
			nextbreak (content);
			break;
		case '[':
			scangroup (content, "]");
			nextbreak (content);
			break;
		case '\"':
			scanquote (content, "\"");
			nextbreak (content);
			break;
		case '\'':
			scanquote (content, "\'");
			nextbreak (content);
			break;
		case '\\':
			nextbreak (content);
			break;
		default:
			break;
		}
	}
	return;
}


#endif

