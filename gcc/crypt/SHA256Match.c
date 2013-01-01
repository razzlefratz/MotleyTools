/*====================================================================*
 *
 *   bool SHA256Match (int fd, const byte digest[]);
 *
 *   SHA256.h
 *
 *   search a fingerprint file for the given digest; return true 
 *   on success and false on failure; digests in the fingerprint
 *   file must be upper case because comparison is binary;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SHA256MATCH_SOURCE
#define SHA256MATCH_SOURCE

#include <unistd.h>
#include <errno.h>

#include "../tools/number.h"
#include "../crypt/SHA256.h"

bool SHA256Match (int fd, const byte digest []) 

{
	char string [SHA256_DIGEST_LENGTH << 1];
	char buffer [SHA256_DIGEST_LENGTH << 1];
	size_t length = 0;
	while (length < sizeof (string)) 
	{
		string [length++] = DIGITS_HEX [(*digest >> 4) & 0x0F];
		string [length++] = DIGITS_HEX [(*digest >> 0) & 0x0F];
		digest++;
	}
	while (read (fd, buffer, sizeof (buffer)) == sizeof (buffer)) 
	{
		signed char c;
		if (!memcmp (string, buffer, sizeof (string))) 
		{
			return (true);
		}
		while (read (fd, &c, sizeof (c)) == sizeof (c)) 
		{
			if (c == '\n') 
			{
				break;
			}
		}
	}
	return (false);
}


#endif

