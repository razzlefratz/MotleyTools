/*====================================================================*
 *
 *   char *itosm(char buffer [], size_t length, unsigned long number, char const * digits, unsigned group, char comma);
 *   
 *
 *   number.h
 *
 *   encode an unsigned integer as variable-length, left-truncated,
 *   NUL-terminated numeric string with periodic delimiters; return 
 *   the string address;
 *
 *   this implementation fills the buffer right-to-left, lsd to msd; 
 *   the digits string specifies the radix; 
 *
 *   decimal    itosm (buffer, length, number, 3, "0123456789", ',');
 *   hex        itosm (buffer, length, number, 2, "0123456789ABCDEF", ':');
 *   octal      itosm (buffer, length, number, 3, "01234567", '.');
 *   binary     itosm (buffer, length, number, 8, "01", '-');
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef ITOSM_SOURCE
#define ITOSM_SOURCE

#include "../tools/number.h"

char * itosm (char buffer [], size_t length, unsigned long number, char const * digits, unsigned group, char comma) 

{
	unsigned short radix;
	size_t count;

#ifdef CMASSOC_SAFEMODE

	if (!buffer) 
	{
		return (buffer);
	}
	if (!digits) 
	{
		return (buffer);
	}

#endif

	for (radix = 0; digits [radix]; radix++);
	if (length && radix) 
	{
		buffer [--length] = (char) (0);
		for (count = 1; length && number; count++) 
		{
			buffer [--length] = digits [number % radix];
			number /= radix;
			if (length && number && group && comma && !(count%group)) 
			{
				buffer [--length] = comma;
			}
		}
	}
	return (buffer + length);
}


/*====================================================================*
 *   test/demo program;
 *--------------------------------------------------------------------*/

#if 0
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char const * argv []) 

{
	char buffer [100];
	char * digits = "0123456789";
	unsigned long value = 10000000;
	printf ("%s\n", itosm (buffer, sizeof (buffer), value, digits, 3, ','));
	printf ("%s\n", itosm (buffer, sizeof (buffer), value, digits, 0, ','));
	printf ("%s\n", itosm (buffer, sizeof (buffer), value, digits, 3, 0));
	printf ("%s\n", itosm (buffer, sizeof (buffer), value, "01", 8, '-'));
	printf ("%s\n", itosm (buffer, sizeof (buffer), value, "0123456789ABCDEF", 2, ':'));
	exit (0);
}


#endif

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif

