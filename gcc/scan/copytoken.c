/*====================================================================*
 *
 *   void copytoken (SCAN * content, char buffer [], signed length);
 *
 *   scan.h
 *
 *   copy the current token to a user supplied buffer of specified 
 *   length; the token is NUL terminated and truncated when needed 
 *   to fit the buffer;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef COPYTOKEN_SOURCE
#define COPYTOKEN_SOURCE

# include "../scan/scan.h"

void copytoken (SCAN * content, char buffer [], signed length) 

{
	if (length-- > 0) 
	{
		content->index = content->first;
		while ((length-- > 0) && (content->index < content->final)) 
		{
			*buffer++ = *content->index++;
		}
		*buffer = (char) (0);
	}
	return;
}


#endif

