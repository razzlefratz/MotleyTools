/*====================================================================*
 *   
 *   void MD5Print (const byte digest [], char const * string);
 *
 *   HPAVKey.h
 *
 *   print a digest in hexadecimal on stdout followed by string if
 *   string is non-empty;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef MD5PRINT_SOURCE
#define MD5PRINT_SOURCE

#include <stdio.h>

#include "../crypt/MD5.h"
#include "../tools/number.h"
#include "../tools/types.h"

void MD5Print (const byte digest [], char const * string) 

{
	unsigned length = MD5_DIGEST_LENGTH;
	while (length--) 
	{
		putc (DIGITS_HEX [(*digest >> 4) & 0x0F], stdout);
		putc (DIGITS_HEX [(*digest >> 0) & 0x0F], stdout);
		digest++;
	}
	if (string) for (putc (' ', stdout); *string; string++) 
	{
		putc (*string, stdout);
	}
	printf ("\n");
	return;
}


#endif

