/*====================================================================*
 *
 *   char * decstring (char buffer [], size_t length, const byte memory [], size_t extent);
 *
 *   memory.h
 *
 *   decode a memory block of given length in bytes as a string of
 *   separated hexadecimal bytes; terminate once the string fills
 *   or the memory ends; terminate the string and return the actual
 *   string bytes;
 *
 *   allow three string characters for each memory byte; this means
 *   that the buffer must have at least three characters or nothing
 *   will be decoded; the maximum number of bytes is the lesser of
 *   chars/3 and bytes;; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef DECSTRING_SOURCE
#define DECSTRING_SOURCE

#include "../tools/memory.h"
#include "../tools/number.h"

char * decstring (char buffer [], size_t length, const byte memory [], size_t extent) 

{
	char * string = buffer;
	length /= 4;
	while ((length--) && (extent--)) 
	{
		unsigned number = *memory++;
		unsigned digit = 3;
		while (digit--) 
		{
			string [digit] = '0' + number % 10;
			number /= 10;
		}
		string += 3;
		if ((length) && (extent)) 
		{
			*string++ = DEC_EXTENDER;
		}
	}
	*string = (char) (0);
	return (buffer);
}


/*====================================================================*
 * test program;
 *--------------------------------------------------------------------*/

#if 0
#include <stdio.h>

int main (int argc, char const * argv []) 

{
	byte memory [] = 
	{
		0x01,
		0x02,
		0x03,
		0x04
	};
	char string [100]="$";
	printf ("string=[%s]\n", netstring (string, sizeof (string), memory, sizeof (memory)));
	return (0);
}


#endif

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif

