/*====================================================================*
 *
 *   size_t strfbits (char buffer[], size_t length, char const *operands[], char const *operator, flag_t flagword);
 *
 *   tools.h
 *
 *   format buffer with an enumerated list of the bits in a flagword; 
 *   each flagword bit position corresponds to a string in operands[]
 *   and operator is the string separating formatted operands;
 *
 *   enumeration continues until all bits are enumerated or operands
 *   are exhausted or the buffer fills;
 *
 *   for example, the following formats buffer with the literal string
 *   "one, three, five, six" since those bits are set;
 *
 *   char buffer[100];
 *   char const operator = ", ";
 *   char const *operands[] = 
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
 *   flag_t flags = 0x006C;
 *
 *   strfbits (buffer, sizeof(buffer), operator, operands, flags);
 *
 *   we decrement length before starting to reserve room for the NUL
 *   terminator; not room ... no write; we then add length to buffer
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
#include "../tools/types.h"
#include "../tools/flags.h"

size_t strfbits (char buffer [], size_t length, char const *operands [], char const *operator, flag_t flagword) 

{
	char *string = buffer;
	char const *separator = "";

#ifdef CMASSOC_SAFEMODE

	if (buffer == (char *) (0)) 
	{
		return (0);
	}
	if (operands == (char const **) (0)) 
	{
		return (0);
	}
	if (operand == (char *) (0)) 
	{
		operand = "";
	}

#endif

	if (length-- > 0) 
	{
		buffer += length;
		while ((flagword != (flag_t) (0)) && (*operands != (char const *) (0))) 
		{
			if (flagword & 1) 
			{
				char const *symbol;
				for (symbol = separator; (*symbol != (char) (0)) && (string < buffer); symbol++) 
				{
					*string++ = *symbol;
				}
				for (symbol = *operands; (*symbol != (char) (0)) && (string < buffer); symbol++) 
				{
					*string++ = *symbol;
				}
				separator = operator;
			}
			flagword >>= 1;
			operands++;
		}
		*string = (char) (0);
		buffer -= length;
	}
	return (string - buffer);
}


#endif

