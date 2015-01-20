/*====================================================================*
 *
 *   onumber.cpp - onumber class definition;
 *
 *   convert common specification strings to numeric values; these
 *   methods are designed for command line argument parsing an may
 *   not return on conversion failure;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oNUMBER_SOURCE
#define oNUMBER_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <stdint.h>
#include <cctype>
#include <cerrno>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/onumber.hpp"
#include "../classes/oerror.hpp"

/*====================================================================*
 *
 *   huge_t uintspec (char const *number, huge_t minimum, huge_t maximum) const;
 *
 *   convert a numeric string to an unsigned integer; confirm that
 *   the result does not exceed the specified range; report errors
 *   and terminate the program on error;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

huge_t onumber::uintspec (char const * string, huge_t minimum, huge_t maximum)

{
	char const * number = string;
	unsigned radix = DEC_RADIX;
	unsigned digit;
	huge_t value = 0;
	if (* number == '0')
	{
		number++;
		if ((* number == 'b') || (* number == 'B'))
		{
			radix = BIN_RADIX;
			number++;
		}
		else if ((* number == 'x') || (* number == 'X'))
		{
			radix = HEX_RADIX;
			number++;
		}
	}
	while ((digit = onumber::todigit (* number)) < radix)
	{
		value *= radix;
		value += digit;
		number++;
	}
	if (* number)
	{
		oerror::error (1, EINVAL, "Have '%s' but want an unsigned integer", string);
	}
	if ((value < minimum) || (value > maximum))
	{
		oerror::error (1, ERANGE, "Have '%s' but want %llu thru %llu", string, minimum, maximum);
	}
	return (value);
}

/*====================================================================*
 *
 *   huge_t basespec (char const * string, unsigned base, unsigned size) const;
 *
 *   convert a character string to an equivalent unsigned integer and
 *   return the result; terminate the program on failure;
 *
 *   the base argument is the number base to be used for conversion;
 *   base 0 permits the number base to be determined by the string
 *   string prefix; 0b, 0d or 0x for binary, deciaml or hex;
 *
 *   the size argument is the maximum number of bits permitted in the
 *   resulting string;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

huge_t onumber::basespec (char const * string, unsigned base, unsigned size)

{
	char const * number = string;
	unsigned radix = DEC_RADIX;
	unsigned digit = 0;
	huge_t limit = ~ 0;
	huge_t value = 0;
	if (size < sizeof (limit))
	{
		limit <<= size << 3;
		limit = ~ limit;
	}
	if (base)
	{
		radix = base;
	}
	if (* number == '0')
	{
		number++;
		if ((* number == 'b') || (* number == 'B'))
		{
			radix = BIN_RADIX;
			number++;
		}
		else if ((* number == 'd') || (* number == 'D'))
		{
			radix = DEC_RADIX;
			number++;
		}
		else if ((* number == 'x') || (* number == 'X'))
		{
			radix = HEX_RADIX;
			number++;
		}
	}
	if ((base) && (base != radix))
	{
		oerror::error (1, EINVAL, "%s is not base %d notation", string, base);
	}
	while ((digit = onumber::todigit (* number)) < radix)
	{
		value *= radix;
		value += digit;
		if (value > limit)
		{
			oerror::error (1, ERANGE, "%s exceeds %d bits", string, (size << 3));
		}
		number++;
	}

#ifdef WIN32

	while (std::isspace (* number))
	{
		number++;
	}

#endif

	if (* number)
	{
		oerror::error (1, EINVAL, "%s is not base %d notation", string, radix);
	}
	return (value);
}

/*====================================================================*
 *
 *   size_t ipv4spec (char const * string, void   * memory) const;
 *
 *   encode a 4-byte memory region with the equivalent of an IPv4
 *   dotted decimal string; all field delimiters must be present
 *   but individual fields may be empty or have leading zeros;
 *
 *      0.0.0.0		 0x00, 0x00, 0x00, 0x00
 *      127...1		 0x7F, 0x00, 0x00, 0x01
 *      192.168.099.000  0xC0, 0xA8, 0x63, 0x00
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

size_t onumber::ipv4spec (char const * string, void * memory)

{
	char const * number = string;
	byte * origin = (byte *) (memory);
	byte * offset = (byte *) (memory);
	byte * extent = offset + IPv4_SIZE;
	unsigned radix = DEC_RADIX;
	unsigned digit = 0;
	while ((* number) && (offset < extent))
	{
		unsigned value = 0;
		if (offset > origin)
		{
			if (* number == DEC_EXTENDER)
			{
				number++;
			}
		}
		while ((digit = onumber::todigit (* number)) < radix)
		{
			value *= radix;
			value += digit;
			if (value >> 8)
			{
				oerror::error (1, ERANGE, "IPv4 '%s' octet %d exceeds 8 bits", string, ((offset - origin) >> 1) + 1);
			}
			number++;
		}
		* offset++ = value;
	}

#if defined (WIN32)

	while (std::isspace (* number))
	{
		number++;
	}

#endif

	if (offset < extent)
	{
		oerror::error (1, EINVAL, "IPv4 '%s' has only %d octets", string, offset - origin);
	}
	if (* number)
	{
		oerror::error (1, EINVAL, "IPv4 '%s' contains trash '%s'", string, number);
	}
	return (offset - origin);
}

/*====================================================================*
 *
 *   size_t ipv6spec (char const * string, void   * memory) const;
 *
 *   encode a 16-byte memory region with the binary equivalent of an
 *   ipv6 address string; ipv6 addresses are defined as 8 16-bit hex
 *   numbers separated with colons; two consecutive colons represent
 *   one or more 0000 fields;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

size_t onumber::ipv6spec (char const * string, void * memory)

{
	char const * number = string;
	byte * origin = (byte *) (memory);
	byte * offset = (byte *) (memory);
	byte * extent = offset + IPv6_SIZE;
	byte * marker = offset + IPv6_SIZE;
	unsigned radix = HEX_RADIX;
	unsigned digit = 0;
	while ((* number) && (offset < extent))
	{
		uint32_t value = 0;
		if (offset > origin)
		{
			if (* number == HEX_EXTENDER)
			{
				number++;
			}
			if (* number == HEX_EXTENDER)
			{
				marker = offset;
			}
		}
		while ((digit = onumber::todigit (* number)) < radix)
		{
			value *= radix;
			value += digit;
			if (value >> 16)
			{
				oerror::error (1, ERANGE, "IPv6 '%s' field %d exceeds 16 bits", string, ((offset - origin) >> 1) + 1);
			}
			number++;
		}
		* offset++ = (byte) (value >> 8);
		* offset++ = (byte) (value >> 0);
	}

#if defined (WIN32)

	while (std::isspace (* number))
	{
		number++;
	}

#endif

	if (* number)
	{
		oerror::error (1, EINVAL, "IPv6 '%s' includes trash '%s'", string, number);
	}
	if (offset < extent)
	{
		while (offset > marker)
		{
			* -- extent = * -- offset;
		}
		while (extent > offset)
		{
			* -- extent = 0;
		}
	}
	if (offset < marker)
	{
		oerror::error (1, EINVAL, "IPv6 '%s' has only %d fields", string, (offset - origin) >> 1);
	}
	return (offset - origin);
}

/*====================================================================*
 *
 *   void * ipv4encode (char const * string, void * memory)
 *
 *   encode external memory with the binary equivalent of an IPv4
 *   dotted-decimal string and return the address of the next
 *   unencoded memory byte;
 *
 *   all field delimiters must be present but individual fields may
 *   be empty or have any number of leading zeros;
 *
 *      0.0.0.0		 0x00, 0x00, 0x00, 0x00
 *      127...1		 0x7F, 0x00, 0x00, 0x01
 *      192.168.099.000  0xC0, 0xA8, 0x63, 0x00
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

void * onumber::ipv4encode (char const * string, void * memory)

{
	char const * number = string;
	byte * origin = (byte *) (memory);
	byte * offset = (byte *) (memory);
	byte * extent = offset + IPv4_SIZE;
	unsigned radix = DEC_RADIX;
	unsigned digit = 0;
	while ((* number) && (offset < extent))
	{
		unsigned value = 0;
		if (offset > origin)
		{
			if (* number == DEC_EXTENDER)
			{
				number++;
			}
		}
		while ((digit = onumber::todigit (* number)) < radix)
		{
			value *= radix;
			value += digit;
			if (value >> 8)
			{
				oerror::error (1, ERANGE, "IPv4 '%s' octet %d exceeds 8 bits", string, ((offset - origin) >> 1) + 1);
			}
			number++;
		}
		* offset++ = value;
	}

#if defined (WIN32)

	while (std::isspace (* number))
	{
		number++;
	}

#endif

	if (offset < extent)
	{
		oerror::error (1, EINVAL, "IPv4 '%s' has only %d octets", string, offset - origin);
	}
	if (* number)
	{
		oerror::error (1, EINVAL, "IPv4 '%s' contains trash '%s'", string, number);
	}
	return ((void *) (offset));
}

/*====================================================================*
 *
 *   size_t ipv6encode (char const * string, void   * memory);
 *
 *   encode a 16-byte memory region with the binary equivalent of an
 *   ipv6 address string; ipv6 addresses are defined as 8 16-bit hex
 *   numbers separated with colons; two consecutive colons represent
 *   one or more 0000 fields;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

void * onumber::ipv6encode (char const * string, void * memory)

{
	char const * number = string;
	byte * origin = (byte *) (memory);
	byte * offset = (byte *) (memory);
	byte * extent = offset + IPv6_SIZE;
	byte * marker = offset + IPv6_SIZE;
	unsigned radix = HEX_RADIX;
	unsigned digit = 0;
	while ((* number) && (offset < extent))
	{
		uint32_t value = 0;
		if (offset > origin)
		{
			if (* number == HEX_EXTENDER)
			{
				number++;
			}
			if (* number == HEX_EXTENDER)
			{
				marker = offset;
			}
		}
		while ((digit = onumber::todigit (* number)) < radix)
		{
			value *= radix;
			value += digit;
			if (value >> 16)
			{
				oerror::error (1, ERANGE, "IPv6 '%s' field %d exceeds 16 bits", string, ((offset - origin) >> 1) + 1);
			}
			number++;
		}
		* offset++ = (byte) (value >> 8);
		* offset++ = (byte) (value >> 0);
	}

#if defined (WIN32)

	while (std::isspace (* number))
	{
		number++;
	}

#endif

	if (* number)
	{
		oerror::error (1, EINVAL, "IPv6 '%s' includes trash '%s'", string, number);
	}
	if (offset < extent)
	{
		while (offset > marker)
		{
			* -- extent = * -- offset;
		}
		while (extent > offset)
		{
			* -- extent = 0;
		}
	}
	if (offset < marker)
	{
		oerror::error (1, EINVAL, "IPv6 '%s' has only %d fields", string, (offset - origin) >> 1);
	}
	return ((void *) (offset));
}

/*====================================================================*
 *
 *   signed todigit (signed c);
 *
 *   convert an SCII character digit to an integer;
 *
 *--------------------------------------------------------------------*/

signed onumber::todigit (signed c)

{
	if ((c >= '0') && (c <= '9'))
	{
		return (c - '0');
	}
	if ((c >= 'A') && (c <= 'Z'))
	{
		return (c - 'A' + 10);
	}
	if ((c >= 'a') && (c <= 'z'))
	{
		return (c - 'a' + 10);
	}
	return (-1);
}

/*====================================================================*
 *
 *   onumber::onumber ();
 *
 *--------------------------------------------------------------------*/

onumber::onumber ()

{
	return;
}

/*====================================================================*
 *
 *   ~onumber();
 *
 *--------------------------------------------------------------------*/

onumber::~ onumber ()

{
	return;
}

/*====================================================================*
 *   end definition;
 *--------------------------------------------------------------------*/

#endif



