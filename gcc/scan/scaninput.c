/*====================================================================*
 *
 *   void scaninput (SCAN * content, char const buffer [], signed length);
 *
 *   scan.h
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SCANINPUT_SOURCE
#define SCANINPUT_SOURCE

#include <stdlib.h>

#include "../scan/scan.h"

void scaninput (SCAN * content, char const buffer [], signed length) 

{
	content->start = buffer;
	content->first = buffer;
	content->final = buffer;
	content->index = buffer;
	content->limit = buffer + length;
	content->class = TOKEN_EMPTY;
	content->block = TOKEN_WIDTH;
	content->width = TOKEN_WIDTH;
	content->token = malloc (content->width);
	return;
}


#endif

