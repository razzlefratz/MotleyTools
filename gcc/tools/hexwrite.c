/*====================================================================*
 *
 *   void hexwrite (signed fd, void const * memory, size_t extent, size_t column);
 *
 *   memory.h
 *
 *   write memory as a series of hexadecimal octets seperated by a
 *   a carrage return every (column) octets;
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef HEXWRITE_SOURCE
#define HEXWRITE_SOURCE

#include <unistd.h>
#include <stdint.h>

#include "../tools/number.h"
#include "../tools/memory.h"

void hexwrite(signed fd, void const * memory, size_t extent, size_t column)

{
	byte * origin = (uint8_t *) (memory);
	byte * offset = (uint8_t *) (memory);
	while (extent--)
	{
		byte byte = * offset;
		write (fd, & DIGITS_HEX[(byte >> 4) & 0x0F], sizeof(char));
		write (fd, & DIGITS_HEX[(byte >> 0) & 0x0F], sizeof(char));
		offset++;
		if ((extent) && (column))
		{
			write (fd, (offset - origin) % column? " ": "\n", sizeof(char));
		}
	}
	write (fd, "\n", sizeof(char));
	return;
}

#endif



