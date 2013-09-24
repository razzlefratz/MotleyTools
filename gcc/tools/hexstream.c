/*====================================================================*
 *
 *   char * hexstream (char buffer [], size_t length, const byte memory [], size_t extent);
 *
 *   memory.h
 *
 *   encode a buffer with the hexadecimal ASCII equivalent of a    
 *   memory region and return the buffer address;
 *
 *   allow two string characters for each memory byte; this means
 *   that the buffer must hold at least two characters or nothing
 *   will be encoded; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef HEXSTREAM_SOURCE
#define HEXSTREAM_SOURCE

#include "../tools/memory.h"
#include "../tools/number.h"

char * hexstream(char buffer[], size_t length, const byte memory[], size_t extent)

{
	char * string = buffer;
	if (length)
	{
		length >>= 1;
		while ((length--) && (extent--))
		{
			* string++ = DIGITS_HEX[(* memory >> 4) & 0x0F];
			* string++ = DIGITS_HEX[(* memory >> 0) & 0x0F];
			memory++;
		}
		* string = (char)(0);
	}
	return (buffer);
}

#endif



