/*====================================================================*
 *
 *   char * itosn (char buffer [], size_t length, unsigned long number, char const * digits);
 *
 *   number.h
 *
 *   encode an unsigned integer value as an ascii field of exact width;
 *   pad or truncate field on left as needed; terminate field with NUL;
 *   return the start address address; the radix is implied by a digit
 *   string that starts with "0" and includes all digits in the number
 *   base; the radix is the string length;
 *
 *   this implementation fills fields right to left, lsd to msd; a zero
 *   length or NULL digit string does not write the field; a one digit 
 *   string pads the field with that digit; an empty digit string pads 
 *   the field with NUL bytes;
 *
 *   this function is designed to encode characters in numeric format 
 *   but can be used to gnerate line numbers, serial numbers or other
 *   fixed width numeric strings; some common encoding schemes are:
 *
 *   decimal    itosn (buffer, length, number, "0123456789");
 *   hex        itosn (buffer, length, number, "0123456789ABCDEF");
 *   octal      itosn (buffer, length, number, "01234567");
 *   binary     itosn (buffer, length, number, "01");
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef ITOSN_SOURCE
#define ITOSN_SOURCE

#include "../tools/number.h"

char * itosn(char buffer[], size_t length, unsigned long number, char const * digits)

{
	unsigned short radix = 0;

#ifdef CMASSOC_SAFEMODE

	if (! string)
	{
		return (string);
	}
	if (! digits)
	{
		return (string);
	}

#endif

	if (length)
	{
		buffer [-- length] = (char)(0);
	}
	while (digits[radix])
	{
		radix++;
	}
	if (radix)
	{
		while (length)
		{
			buffer [-- length] = digits[number % radix];
			number /= radix;
		}
	}
	return (& buffer[length]);
}

/*====================================================================*
 *   test/demo program;
 *--------------------------------------------------------------------*/

#if 0
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const * argv[])

{
	char buffer[20];
	char * digits = "0123456789";
	unsigned long value = 10000000;
	printf ("%s\n", itosn(buffer, sizeof(buffer), value, digits));
	printf ("%s\n", itosn(buffer, sizeof(buffer), value, digits));
	printf ("%s\n", itosn(buffer, sizeof(buffer), value, digits));
	printf ("%s\n", itosn(buffer, sizeof(buffer), value, "01"));
	printf ("%s\n", itosn(buffer, sizeof(buffer), value, "0123456789ABCDEF"));
	exit (0);
}

#endif

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif



