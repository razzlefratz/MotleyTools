/*====================================================================*
 *
 *   size_t hexdecode (void const * memory, size_t extent,  char buffer [], size_t length);
 *
 *   memory.h
 *
 *   decode a memory region as a string of hex octets separated with 
 *   character HEX_EXTENDER;
 *
 *   allow three string characters for each memory byte; this means
 *   that the buffer must hold at least three characters or nothing
 *   will be decoded; the maximum number of bytes is the lesser of
 *   chars/3 and bytes; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef HEXDECODE_SOURCE
#define HEXDECODE_SOURCE

#include "../tools/memory.h"
#include "../tools/number.h"
#include "../tools/types.h"

size_t hexdecode(void const * memory, register size_t extent, char buffer[], register size_t length)

{
	register char * string = (char *) (buffer);
	register byte * offset = (byte *) (memory);
	if (length)
	{
		length /= OCTETS_HEX +  1;
		while ((length--) && (extent--))
		{
			* string++ = DIGITS_HEX[(* offset >> 4) & 0x0F];
			* string++ = DIGITS_HEX[(* offset >> 0) & 0x0F];
			if ((length) && (extent))
			{
				* string++ = HEX_EXTENDER;
			}
			offset++;
		}
		* string = (char)(0);
	}
	return (string - buffer);
}

#endif



