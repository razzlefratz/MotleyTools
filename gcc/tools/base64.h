/*====================================================================*
 *
 *   base64.h - base64 conversion definitions and declarations;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 2005 by Charles Maier Associates for internal use;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef BASE64_HEADER
#define BASE64_HEADER

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#include <unistd.h>

/*====================================================================*
 *   constants;
 *--------------------------------------------------------------------*/

#define BASE64_CHARSET "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
#define BASE64_BYTEMASK 0xFF
#define BASE64_CHARMASK 0x3F
#define BASE64_WORDSIZE 32
#define BASE64_BYTESIZE 8
#define BASE64_CHARSIZE 6

/*====================================================================*
 *   encode/decode functions;
 *--------------------------------------------------------------------*/

void b64dump (void const * memory, size_t extent, size_t column, FILE *fp);

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif

