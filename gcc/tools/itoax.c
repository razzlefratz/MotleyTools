/*====================================================================*
 *
 *   char * itoax (unsigned long value, char buffer [], size_t length, char const * digits);
 *
 *   number.h
 *
 *   encode an unsigned integer value as an ascii field of exact width;
 *   left pad with zero or left truncate as needed; terminate the field
 *   with NUL; return the terminator address; the radix is specified by
 *   a digit string that starts with "0" and includes all digits for the
 *   number base; the radix is the length of this string;
 *
 *   this implementation fills fields right to left, lsd to msd; a zero
 *   width or NULL digit string does not write the field; one character
 *   character digit strings pad the field with the character; an empty
 *   digit string pads the field with NUL bytes;
 *
 *   this function is designed to encode characters as fixed length octal
 *   or hexidecimal fields but it has other uses, such as indexing lines;
 *   typical encoding schemes are:
 *
 *   decimal    itoax (value, buffer,  3, "0123456789");
 *   hex        itoax (value, buffer,  2, "0123456789ABCDEF");
 *   octal      itoax (value, buffer,  3, "01234567");
 *   binary     itoax (value, buffer, 32, "01");
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef ITOAX_SOURCE
#define ITOAX_SOURCE

#include "../tools/number.h"

char * itoax(unsigned long value, char buffer[], size_t length, char const * digits)

{
	unsigned short radix;

#ifdef CMASSOC_SAFEMODE

	if (! buffer)
	{
		return (buffer);
	}
	if (! digits)
	{
		return (buffer);
	}

#endif

	for (radix = 0; digits[radix]; radix++);
	if (length)
	{
		buffer [-- length] = (char)(0);
	}
	while (length)
	{
		if (radix > 1)
		{
			buffer [-- length] = digits[value % radix];
			value /= radix;
		}
		else 
		{
			buffer [-- length] = digits[0];
		}
	}
	return (& buffer[length]);
}

#endif



