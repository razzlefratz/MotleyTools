/*====================================================================*
 *
 *   MD5.H - header file for MD5C.C
 *   
 *   Copyright (C) 1991-2, RSA Data Security, Inc. Created 1991. All
 *   rights reserved.
 *   
 *   License to copy and use this software is granted provided that it
 *   is identified as the "RSA Data Security, Inc. MD5 Message-Digest
 *   Algorithm" in all material mentioning or referencing this software
 *   or this function.
 *   
 *   License is also granted to make and use derivative works provided
 *   that such works are identified as "derived from the RSA Data
 *   Security, Inc. MD5 Message-Digest Algorithm" in all material
 *   mentioning or referencing the derived work.
 *   
 *   RSA Data Security, Inc. makes no representations concerning either
 *   the merchantability of this software or the suitability of this
 *   software for any particular purpose. It is provided "as is"
 *   without express or implied warranty of any kind.
 *   These notices must be retained in any copies of any part of this
 *   documentation and/or software.
 *   
 *--------------------------------------------------------------------*/

#ifndef MD5_HEADER
#define MD5_HEADER

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <stdint.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/types.h"

/*====================================================================*
 *   md5 constants;
 *--------------------------------------------------------------------*/

#define MD5_DIGEST_LENGTH 16

/*====================================================================*
 *   md5 variables;
 *--------------------------------------------------------------------*/

typedef struct md5 

{
	uint32_t count [2];
	uint32_t state [4];
	uint8_t block [64];
	uint8_t extra [64];
}

MD5;

/*====================================================================*
 *   md5 functions;
 *--------------------------------------------------------------------*/

void MD5Reset (struct md5 *);
void MD5Write (struct md5 *, byte const [], unsigned);
void MD5Block (struct md5 *, byte const []);
void MD5Fetch (struct md5 *, byte []);

/*====================================================================*
 *   
 *--------------------------------------------------------------------*/

#endif

