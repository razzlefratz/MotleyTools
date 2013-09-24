/*====================================================================*
 *
 *   char *serial (char buffer[], size_t length, char c, unsigned number);
 *
 *   number.h
 *
 *   encode a buffer of given length with the ASCII representation of
 *   an unsigned integer number and return the buffer address; 
 *
 *   the buffer is filled with digits and NUL terminated; the encoded
 *   number may be truncated on the left or paddded with zeros on the  
 *   the left; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SERIAL_SOURCE
#define SERIAL_SOURCE

#include <stdint.h>

#include "../tools/number.h"

char * serial(char buffer[], size_t length, char c, unsigned number)

{
	if ((buffer) && (length))
	{
		buffer [-- length] = c;
		while (length)
		{
			buffer [-- length] = '0' +  number % 10;
			number /= 10;
		}
	}
	return (buffer);
}

#endif



