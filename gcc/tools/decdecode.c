/*====================================================================*
 *
 *   size_t decdecode (void const * memory, size_t extent, char buffer [], size_t length);
 *
 *   memory.h
 *
 *   decode a memory block of given length in bytes as a string of
 *   separated hexadecimal bytes; terminate once the string fills
 *   or the memory ends; terminate the string and return the actual
 *   string bytes;
 *
 *   allow three string characters for each memory byte; this means
 *   that the buffer must have at least three characters or nothing
 *   will be decoded; the maximum number of bytes is the lesser of
 *   chars/3 and bytes;; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef DECDECODE_SOURCE
#define DECDECODE_SOURCE

#include "../tools/memory.h"
#include "../tools/number.h"

size_t decdecode(void const * memory, size_t extent, char buffer[], size_t length)

{
	char * string = (char *) (buffer);
	byte * offset = (byte *) (memory);
	if (length)
	{
		length /= 4;
		while ((length--) && (extent--))
		{
			unsigned digit = 3;
			unsigned value = * offset;
			while (digit-- > 0)
			{
				string [digit] = DIGITS_DEC[value % 10];
				value /= 10;
			}
			string += 3;
			if ((length) && (extent))
			{
				* string++ = DEC_EXTENDER;
			}
			offset++;
		}
		* string = (char)(0);
	}
	return ((size_t) (string - buffer));
}

#endif



