/*====================================================================*
 *
 *   size_t decencode (void * memory, size_t extent, char const *string);
 *
 *   memory.h
 *
 *   encode a memory region with a dotted decimal string octet;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef DECENCODE_SOURCE
#define DECENCODE_SOURCE

#include <ctype.h>
#include <errno.h>

#include "../tools/memory.h"
#include "../tools/number.h"

size_t decencode(void * memory, register size_t extent, char const * string)

{
	register byte * origin = (byte *) (memory);
	register byte * offset = (byte *) (memory);
	unsigned radix = RADIX_DEC;
	unsigned digit = 0;
	while ((extent--) && (* string))
	{
		unsigned field = OCTETS_DEC;
		unsigned value = 0;
		if ((offset > origin) && (* string == DEC_EXTENDER))
		{
			string++;
		}
		while (field--)
		{
			if ((digit = todigit(* string)) < radix)
			{
				value *= radix;
				value += digit;
				if (value >> 8)
				{
					errno = ERANGE;
					return (- 1);
				}
				string++;
			}
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



