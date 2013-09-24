/*====================================================================*
 *
 *   size_t binencode (void * memory, size_t extent, char const * string);
 *
 *   memory.h
 *
 *   encode a binary string into a byte array; return the number of 
 *   bytes encoded on success or -1 on error; permit an optional
 *   BIN_EXTENDER between successive octets;
 *
 *   constant BIN_EXTENDER is defined in number.h as a hyphen;
 *
 *   string must contain an even multiple of 8 binary digits; bytes
 *   are fixed width fields; leading zeros are required or an error
 *   will occur; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef BINENCODE_SOURCE
#define BINENCODE_SOURCE

#include <errno.h>

#include "../tools/memory.h"
#include "../tools/number.h"

size_t binencode(void * memory, register size_t extent, register char const * string)

{
	register byte * origin = (byte *) (memory);
	register byte * offset = (byte *) (memory);
	register unsigned radix = RADIX_BIN;
	register unsigned digit = 0;
	while ((extent--) && (* string))
	{
		register unsigned field = OCTETS_BIN;
		register unsigned value = 0;
		if ((offset > origin) && (* string == BIN_EXTENDER))
		{
			string++;
		}
		while (field--)
		{
			if ((digit = todigit(* string)) < radix)
			{
				value *= radix;
				value += digit;
				string++;
				continue;
			}
			errno = EINVAL;
			return (- 1);
		}
		* offset = value;
		offset++;
	}

#if defined (WIN32)

	while (isspace(* string))
	{
		string++;
	}

#endif

	if ((extent) || (* string))
	{
		errno = EINVAL;
		return (- 1);
	}
	return ((size_t) (offset - origin));
}

#endif



