/*====================================================================*
 *
 *   size_t strfbits (char buffer[], size_t length, char const *vector[], char const *operator, unsigned flagword);
 *
 *   basic.h
 *
 *   format buffer with an enumerated list of the bits in a flagword; 
 *   each flagword bit position corresponds to a string in string[]
 *   and operator is the string separating formatted string;
 *
 *   enumeration continues until all bits are enumerated or string
 *   are exhausted or the buffer fills;
 *
 *   for example, the following formats buffer with the literal string
 *   "one, three, five, six" since those bits are set in flagword;
 *
 *   char buffer[100];
 *   char const operator = ", ";
 *   char const *vector[] = 
 *   { 
 *      "zero", 
 *      "one", 
 *      "two", 
 *      "three", 
 *      "four", 
 *      "five", 
 *      "six", 
 *      "seven", 
 *      "eight",
 *      "nine",
 *      "ten",
 *      (char *)(0) 
 *   };
 *   unsigned flagword = 0x006C;
 *
 *   strfbits (buffer, sizeof(buffer), string, operator, flagword);
 *
 *   we decrement length before starting to reserve room for the NUL
 *   terminator; no room, ... no write; we then add length to buffer
 *   before to compute the terminator address then subtract it after
 *   to compute the buffer start; this minimizes indexing and offset 
 *   calculations within the loop; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef STRFBITS_SOURCE
#define STRFBITS_SOURCE

#include <unistd.h>

#include "../strlib/strlib.h"

size_t strfbits (char buffer [], size_t length, char const *vector [], char const *operator, unsigned flagword) 

{
	char *string = buffer;
	char const *separator = "";

#ifdef CMASSOC_SAFEMODE

	if (!buffer) 
	{
		return (0);
	}
	if (!vector) 
	{
		return (0);
	}
	if (!operand) 
	{
		operand = "";
	}

#endif

	if (length-- > 0) 
	{
		buffer += length;
		while ((flagword != (unsigned)(0)) || (*vector != (char const *)(0))) 
		{
			if ((flagword & 1) && (**vector != (char)(0))) 
			{
				char const *symbol;
				for (symbol = separator; (*symbol != (char)(0)) && (string < buffer); symbol++) 
				{
					*string++ = *symbol;
				}
				for (symbol = *vector; (*symbol != (char)(0)) && (string < buffer); symbol++) 
				{
					*string++ = *symbol;
				}
				separator = operator;
			}
			flagword >>= 1;
			vector++;
		}
		*string = (char) (0);
		buffer -= length;
	}
	return (string - buffer);
}


#endif

