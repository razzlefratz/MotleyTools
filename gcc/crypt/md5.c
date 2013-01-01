/*====================================================================*
 *
 *    MD5C.C - RSA Data Security, Inc., MD5 message-digest algorithm
 *   
 *    Copyright (C) 1991-2, RSA Data Security, Inc. Created 1991. All
 *    rights reserved.
 *   
 *    License to copy and use this software is granted provided that it
 *    is identified as the "RSA Data Security, Inc. MD5 Message-Digest
 *    Algorithm" in all material mentioning or referencing this software
 *    or this function.
 *   
 *    License is also granted to make and use derivative works provided
 *    that such works are identified as "derived from the RSA Data
 *    Security, Inc. MD5 Message-Digest Algorithm" in all material
 *    mentioning or referencing the derived work.
 *   
 *    RSA Data Security, Inc. makes no representations concerning either
 *    the merchantability of this software or the suitability of this
 *    software for any particular purpose. It is provided "as is"
 *    without express or implied warranty of any kind.
 *   
 *    These notices must be retained in any copies of any part of this
 *    documentation and/or software.
 *--------------------------------------------------------------------*/

#ifndef MD5_SOURCE
#define MD5_SOURCE

#include "../crypt/MD5Reset.c"
#include "../crypt/MD5Write.c"
#include "../crypt/MD5Block.c"
#include "../crypt/MD5Fetch.c"

#include <stdio.h>

int main (int argc, char const * argv []) 

{
	struct md5 md5;
	unsigned char digest [16];
	unsigned n;
	while ((--argc) && (*++argv)) 
	{
		MD5Reset (&md5);
		MD5Write (&md5, (byte const *)(*argv), strlen (*argv));
		MD5Fetch (&md5, digest);
		for (n = 0; n < sizeof (digest); n++) 
		{
			putc ("0123456789ABCDEF"[(digest [n]>>4)&0x0F], stdout);
			putc ("0123456789ABCDEF"[(digest [n]>>0)&0x0F], stdout);
		}
		putc ('\n', stdout);
	}
	return (0);
}


#endif

