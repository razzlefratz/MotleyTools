/*====================================================================*
 *
 *   size_t cursor (signed c)
 *
 *   chrlib.h
 *
 *   update page, line row, col and byte count based on the value
 *   of character c; return c or, in some cases, another value;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef CURSOR_SOURCE
#define CURSOR_SOURCE

#include "../chrlib/chrlib.h"

size_t chr = 0;
size_t page = 0;
size_t line = 0;
size_t col = 0;
size_t row = 0;
size_t cursor (signed c) 

{
	switch (c) 
	{
	case '\f':
		chr++;
		page++;
		line = 0;
		row = 0;
		col = 0;
		break;
	case '\n':
		chr++;
		line++;
		row++;
		col = 0;
		break;
	case '\t':
		chr++;
		col++;
		break;
	default:
		chr++;
		break;
	}
	return (c);
}


#endif

