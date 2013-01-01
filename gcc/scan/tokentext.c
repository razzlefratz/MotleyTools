/*====================================================================*
 *
 *   char * tokentext (SCAN * content);
 *
 *   scan.h
 *
 *   return the address of a constant string containing a copy of 
 *   the current token; calling applications may duplicate it, if 
 *   needed; the string content will, and the address may, change 
 *   with each call to tokentext;
 *
 *   the token buffer size expands, as needed, using a fibonacci 
 *   expansion; don't ask; it's magic;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef TOKENTEXT_SOURCE
#define TOKENTEXT_SOURCE

#include <stdlib.h>
#include <memory.h>

#include "../scan/scan.h"

char * tokentext (SCAN * content) 

{
	while (content->width <= (content->final - content->first)) 
	{
		free (content->token);
		content->width = content->width + content->block;
		content->block = content->width - content->block;
		content->token = malloc (content->width);
	}
	memcpy (content->token, content->first, content->final - content->first);
	content->token [content->final - content->first] = (char) (0);
	return (content->token);
}


#endif

