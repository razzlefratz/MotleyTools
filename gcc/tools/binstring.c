/*====================================================================*
 *
 *   char binstring (char buffer [], size_t length, const byte memory [], size_t extent);
 *
 *   memory.h
 *
 *   decode a memory block as a string of binary digits;
 *
 *   allow 9 characters per byte when allocating the buffer;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef BINSTRING_SOURCE
#define BINSTRING_SOURCE

#include "../tools/memory.h"
#include "../tools/number.h"

char * binstring(char buffer[], size_t length, const byte memory[], size_t extent)

{
	char * string = buffer;
	length /= 9;
	while ((length--) && (extent--))
	{
		unsigned number = * memory++;
		unsigned bits = 8;
		while (bits--)
		{
			string [bits] = DIGITS_BIN[number & 1];
			number >>= 1;
		}
		string += 8;
		if ((length) && (extent))
		{
			* string++ = BIN_EXTENDER;
		}
	}
	* string = (char)(0);
	return (buffer);
}

/*====================================================================*
 * test program;
 *--------------------------------------------------------------------*/

#if 0
#include <stdio.h>

int main(int argc, char const * argv[])

{
	byte memory[] = 
	{
		0x01,
		0x02,
		0x03,
		0x04
	};
	char string[100] = "$";
	printf ("string=[%s]\n", binstring(string, sizeof(string), memory, sizeof(memory)));
	return (0);
}

#endif

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif



