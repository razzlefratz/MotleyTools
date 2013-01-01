/*====================================================================*
 *
 *   SHA256.h - SHA256 encryption declarations and definitions;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SHA256_HEADER
#define SHA256_HEADER

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <stdint.h>
#include <string.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/types.h"

/*====================================================================*
 *   constants;
 *--------------------------------------------------------------------*/

#define SHA256_DIGEST_LENGTH 256/8

/*====================================================================*
 *   variables;
 *--------------------------------------------------------------------*/

typedef struct sha256 

{
	uint32_t count [2];
	uint32_t state [8];
	uint8_t block [64];
	uint8_t extra [64];
}

SHA256;

/*====================================================================*
 *   functions;
 *--------------------------------------------------------------------*/

void SHA256Reset (struct sha256 * sha256);
void SHA256Write (struct sha256 * sha256, void const * memory, size_t extent);
void SHA256Block (struct sha256 * sha256, void const * memory);
void SHA256Fetch (struct sha256 * sha256, byte digest []);
void SHA256Print (byte const digest [], char const * string);
void SHA256Ident (signed fd, void * memory, size_t extent, byte digest []);
bool SHA256Match (signed fd, byte const digest []);

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif 

