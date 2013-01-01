/*====================================================================*
 *
 *   void MD5Fetch (struct md5 * md5, uint8_t  digest [DIGEST_SIZE]);
 *   
 *--------------------------------------------------------------------*/

#ifndef MD5FETCH_SOURCE
#define MD5FETCH_SOURCE

#include <stdint.h>
#include <memory.h>
#include <limits.h>

#include "../crypt/MD5.h"

static void Encode (uint8_t output [], uint32_t input [], unsigned length) 

{
	for (length >>= 2; length--; input++) 
	{
		*output++ = (uint8_t)((*input >> 0) & UCHAR_MAX);
		*output++ = (uint8_t)((*input >> 8) & UCHAR_MAX);
		*output++ = (uint8_t)((*input >> 16) & UCHAR_MAX);
		*output++ = (uint8_t)((*input >> 24) & UCHAR_MAX);
	}
	return;
}

void MD5Fetch (struct md5 * md5, uint8_t digest [MD5_DIGEST_LENGTH]) 

{
	uint8_t bits [8];
	unsigned index = (unsigned)((md5->count [0] >> 3) & 0x3F);
	unsigned extra = (index < 56)? (56 - index): (120 - index);
	Encode (bits, md5->count, sizeof (bits));
	MD5Write (md5, md5->extra, extra);
	MD5Write (md5, bits, sizeof (bits));
	Encode (digest, md5->state, sizeof (digest));
	memset (md5, 0, sizeof (struct md5));
	return;
}


#endif

