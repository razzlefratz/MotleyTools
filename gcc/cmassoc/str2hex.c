/*====================================================================*
 *
 *   str2hex.c - convert string arguments to hex strings;
 *
 *   print ASCII argument strings as hexadecimal character strings;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

#include <stdio.h>

#define DIGITS_HEX "0123456789ABCDEF"

int main(int argc, char const * argv[])

{
	char const * sp;
	while ((-- argc) && (* ++ argv))
	{
		for (sp = * argv; * sp; ++ sp)
		{
			putc (DIGITS_HEX[(* sp >> 4) & 0x0F], stdout);
			putc (DIGITS_HEX[(* sp >> 0) & 0x0F], stdout);
		}
		putc ('\n', stdout);
	}
	return (0);
}

