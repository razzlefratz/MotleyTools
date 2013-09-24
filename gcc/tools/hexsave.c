/*====================================================================*
 *
 *   void hexsave (void const * memory, size_t column, size_t column, FILE *fp);
 *
 *   memory.h
 *
 *   print memory as a series of hexadecimal octets seperated by a 
 *   space or a carriage return every (column) octets;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef HEXSAVE_SOURCE
#define HEXSAVE_SOURCE

#include <stdio.h>
#include <ctype.h>

#include "../tools/memory.h"
#include "../tools/number.h"

void hexsave(void const * memory, size_t extent, size_t column, FILE * fp)

{
	byte * origin = (uint8_t *) (memory);
	byte * offset = (uint8_t *) (memory);
	while (extent--)
	{
		putc (DIGITS_HEX[(* offset >> 4) & 0x0F], fp);
		putc (DIGITS_HEX[(* offset >> 0) & 0x0F], fp);
		offset++;
		if ((extent) && (column))
		{
			putc ((offset - origin) % column? ' ': '\n', fp);
		}
	}
	putc ('\n', fp);
	return;
}

#endif



