/*====================================================================*
 *
 *   size_t numencode (void * memory, unsigned extent, char const * string, unsigned radix, unsigned comma);
 *
 *   memory.h
 *
 *   encode a octet-separated string into a byte array; return the
 *   number of bytes encoded on success or -1 on error; permit the 
 *   use of delimiters to specify empty octets;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef MEMENCODE_SOURCE
#define MEMENCODE_SOURCE

#include <memory.h>    
#include <errno.h>

#include "../tools/memory.h"
#include "../tools/number.h"
#include "../tools/types.h"

size_t numencode (void * memory, register size_t extent, register char const * string, unsigned radix, unsigned comma) 

{
	register byte * origin = (byte *)(memory);
	register byte * offset = (byte *)(memory);
	while ((extent--) && (*string)) 
	{
		unsigned digit = 0;
		unsigned octet = 0;
		if ((offset > origin) && (*string == comma)) 
		{
			string++;
		}
		while ((digit = todigit (*string)) < radix) 
		{
			octet *= radix;
			octet += digit;
			if (octet > 255) 
			{
				errno = EINVAL;
				return (-1);
			}
			string++;
		}
		* offset = octet;
		offset++;
	}

#if defined (WIN32)

	while (isspace (*string)) 
	{
		string++;
	}

#endif

	if ((*string) || (extent)) 
	{
		errno = EINVAL;
		return (-1);
	}
	return ((size_t)(offset - origin));
}


/*====================================================================*
 *    test/demo program;
 *--------------------------------------------------------------------*/

#if 0
#include <stdio.h>

#include "../tools/hexdecode.c"
#include "../tools/todigit.c"

int main (int argc, char const * argv []) 

{
	byte memory [16];
	char buffer [100];
	while (*++argv) 
	{
		memset (memory, 0, sizeof (memory));
		numencode (memory, sizeof (memory), *argv, 10, '.');
		hexdecode (memory, sizeof (memory), buffer, sizeof (buffer));
		printf ("%s=[%s]\n", *argv, buffer);
	}
	return (0);
}


#endif

/*====================================================================*
 * 
 *--------------------------------------------------------------------*/

#endif

