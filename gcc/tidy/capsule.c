/*====================================================================*
 *   
 *   signed capsule (signed c);
 *
 *   tidy.h
 *
 *   read stdin and write stdout; 
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *   
 *--------------------------------------------------------------------*/

#ifndef CAPSULE_SOURCE
#define CAPSULE_SOURCE

#include "../tidy/tidy.h"

signed capsule (signed c) 

{
	if (c == '/') 
	{
		c = comment (c);
	}
	else if (isquote (c)) 
	{
		c = literal (c);
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

