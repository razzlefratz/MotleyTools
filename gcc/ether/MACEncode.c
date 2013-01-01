/*====================================================================*
 *
 *   errno_t MACEncode (byte buffer [], size_t octets, char const *string);
 *
 *   buffer.h
 *
 *   convert a hexadecimal MAC address string to an equvalent six byte 
 *   value; return 0 on success or MAC_ADDR_TOOSHORT, MAC_ADDR_TOOLONG
 *   or MAC_ADDR_ILLEGAL on failure;
 *
 *   hexdigits is an external string containing 16 hex characters plus
 *   one extenders character; hex letters may be either upper or lower
 *   case; the extender is the last character and may be any character 
 *   except NUL; the string must be NUL terminated;
 *
 *   character pairs are converted to bytes in nibbles by looking for
 *   each character in hexdigits [] and using the string index is the 
 *   nibble value; the search is case in sensitive; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef MACENCODE_SOURCE
#define MACENCODE_SOURCE

#include <ctype.h>

#include "MACAddr.h"

static size_t cindex (char c, char const *string) 

{
	char const *offset;
	for (offset = string; *offset != (char) (0); offset++) 
	{
		if (toupper (c) == *offset) 
		{
			break;
		}
		if (tolower (c) == *offset) 
		{
			break;
		}
	}
	return (offset - string);
}

errno_t MACEncode (byte buffer [], size_t length, char const *string) 

{
	extern char const hexdigits [];
	size_t upper;
	size_t lower;
	while (length-- > 0) 
	{
		upper = cindex (*string, hexdigits);
		if (*string++ == (char) (0)) 
		{
			return (MAC_ADDR_TOOSHORT);
		}
		if (upper > 0x0f) 
		{
			return (MAC_ADDR_ILLEGAL);
		}
		lower = cindex (*string, hexdigits);
		if (*string++ == (char) (0)) 
		{
			return (MAC_ADDR_TOOSHORT);
		}
		if (lower > 0x0f) 
		{
			return (MAC_ADDR_ILLEGAL);
		}
		*buffer++ = ((upper & 0x0f) << 4) | ((lower & 0x0f) << 0);
		if (*string == hexdigits [0x10]) 
		{
			string++;
		}
	}
	if (*string != (char) (0)) 
	{
		return (MAC_ADDR_TOOLONG);
	}
	return (0);
}


#endif

