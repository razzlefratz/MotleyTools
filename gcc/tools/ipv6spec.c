/*====================================================================*
 *
 *   size_t ipv6spec (char const * string, byte memory []);
 *
 *   memory.h
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

#ifndef IPV6SPEC_SOURCE
#define IPV6SPEC_SOURCE

#include <memory.h>
#include <ctype.h>
#include <errno.h>

#include "../tools/memory.h"
#include "../tools/number.h"
#include "../tools/error.h"

size_t ipv6spec (char const * string, byte memory []) 

{
	char const * number = string;
	unsigned extent = IPv6_LEN;
	unsigned marker = IPv6_LEN;
	unsigned offset = 0;
	unsigned radix = 16;
	unsigned digit = 0;
	while ((*number) && (offset < extent)) 
	{
		uint32_t value = 0;
		if (offset) 
		{
			if (*number == HEX_EXTENDER) 
			{
				number++;
			}
			if (*number == HEX_EXTENDER) 
			{
				marker = offset;
			}
		}
		while ((digit = todigit (*number)) < radix) 
		{
			value *= radix;
			value += digit;
			if (value > 0xFFFF) 
			{
				error (1, ERANGE, "IPv6 '%s' field %d exceeds 16 bits", string, 1 + (offset >> 1));
			}
			number++;
		}
		memory [offset++] = (byte)(value >> 8);
		memory [offset++] = (byte)(value >> 0);
	}

#if defined (WIN32)

	while (isspace (*number)) 
	{
		number++;
	}

#endif

	if (*number) 
	{
		error (1, EINVAL, "IPv6 '%s' includes trash '%s'", string, number);
	}
	if (offset < extent) 
	{
		while (offset > marker) 
		{
			memory [--extent] = memory [--offset];
		}
		while (extent > offset) 
		{
			memory [--extent] = 0;
		}
	}
	if (offset < marker) 
	{
		error (1, EINVAL, "IPv6 '%s' has only %d fields", string, offset >> 1);
	}
	return (offset);
}


/*====================================================================*
 *   demo/test program;
 *--------------------------------------------------------------------*/

#if 0
#include <stdio.h>
#include "../tools/hexdecode.c"
#include "../tools/todigit.c"
#include "../tools/error.c"

char const * program_name = "ipv6spec";
int main (int argc, char const * argv []) 

{
	byte memory [IPv6_LEN];
	char string [IPv6_LEN * 3];
	while (*++argv) 
	{
		ipv6spec (*argv, memory);
		hexdecode (memory, sizeof (memory), string, sizeof (string));
		printf ("%s %s\n", string, *argv);
	}
	return (0);
}


#endif

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif

