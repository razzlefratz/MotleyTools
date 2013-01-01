/*====================================================================*
 *
 *   size_t bindecode (const byte memory [], size_t extent, char buffer [], size_t length);
 *
 *   memory.h
 *
 *   decode a memory region as a string of binary digits;
 *
 *   allow 9 characters per byte when allocating the buffer;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef BINDECODE_SOURCE
#define BINDECODE_SOURCE

#include "../tools/memory.h"
#include "../tools/number.h"
#include "../tools/types.h"

size_t bindecode (void const * memory, size_t extent, char buffer [], size_t length) 

{
	register char * string = (char *)(buffer);
	register byte * offset = (byte *)(memory);
	if (length) 
	{
		length /= OCTETS_BIN + 1;
		while ((length--) && (extent--)) 
		{
			unsigned digit = OCTETS_BIN;
			unsigned value = *offset++;
			while (digit--) 
			{
				string [digit] = DIGITS_BIN [value % RADIX_BIN];
				value /= RADIX_BIN;
			}
			string += OCTETS_BIN;
			if ((length) && (extent)) 
			{
				*string++ = BIN_EXTENDER;
			}
		}
		*string = (char) (0);
	}
	return ((size_t)(string - buffer));
}


#endif

