/*====================================================================*
 *   
 *   signed content (signed c);
 *
 *   tidy.h
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *   
 *--------------------------------------------------------------------*/

#ifndef CONTENT_SOURCE
#define CONTENT_SOURCE

#include "../tidy/tidy.h"

signed content (signed c) 

{
	if (c == '/') 
	{
		c = comment (c);
	}
	else if (isquote (c)) 
	{
		c = literal (c, c);
	}
	else if (c == '{') 
	{
		c = context ('{', '}');
	}
	else if (c == '(') 
	{
		c = context ('(', ')');
	}
	else if (c == '[') 
	{
		c = context ('[', ']');
	}
	else 
	{
		c = keep (c);
	}
	return (c);
}


#endif

