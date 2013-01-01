/*====================================================================*
 *
 *   void MD5Reset (struct md5 * md5);
 *
 *   initialize the MD5 hash state;
 *
 *--------------------------------------------------------------------*/

#ifndef MD5RESET_SOURCE
#define MD5RESET_SOURCE

#include <stdint.h>
#include <memory.h>

#include "../crypt/MD5.h"

void MD5Reset (struct md5 * md5) 

{
	memset (md5, 0, sizeof (struct md5));
	md5->state [0] = 0x67452301;
	md5->state [1] = 0xefcdab89;
	md5->state [2] = 0x98badcfe;
	md5->state [3] = 0x10325476;
	md5->extra [0] = 0x80;
	return;
}


#endif

