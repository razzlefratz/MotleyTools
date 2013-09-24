/*====================================================================*
 *
 *   size_t ipv4spec (char const *string, byte memory []);
 *
 *   encode a 4-byte memory region with the equivalent of an IPv4 
 *   dotted decimal string; all field delimiters must be present 
 *   but individual fields may have leading zeros or be empty;
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

#ifndef IPV4SPEC_SOURCE
#define IPV4SPEC_SOURCE

#include <ctype.h>

#include "../tools/memory.h"
#include "../tools/number.h"
#include "../tools/error.h"

size_t ipv4spec(char const * string, byte memory[])

{
	char const * number = string;
	unsigned extent = IPv4_LEN;
	unsigned offset = 0;
	unsigned radix = 10;
	unsigned digit = 0;
	while ((* number) && (offset < extent))
	{
		unsigned value = 0;
		if (offset)
		{
			if (* number == DEC_EXTENDER)
			{
				number++;
			}
		}
		while ((digit = todigit(* number)) < radix)
		{
			value *= radix;
			value += digit;
			if (value > 0xFF)
			{
				error (1, ERANGE, "IPv4 '%s' octet %d exceeds 8 bits", string, offset + 1);
			}
			number++;
		}
		memory [offset++] = value;
	}

#if defined (WIN32)

	while (isspace(* number))
	{
		number++;
	}

#endif

	if (offset < extent)
	{
		error (1, EINVAL, "IPv4 '%s' has only %d octets", string, offset);
	}
	if (* number)
	{
		error (1, EINVAL, "IPv4 '%s' contains trash '%s'", string, number);
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

char const * program_name = "ipv4spec";
int main(int argc, char const * argv[])

{
	byte memory[IPv4_LEN];
	char string[IPv4_LEN * 4];
	while (* ++ argv)
	{
		ipv4spec (* argv, memory);
		hexdecode (memory, sizeof(memory), string, sizeof(string));
		printf ("%s %s\n", string, * argv);
	}
	return (0);
}

#endif

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif



