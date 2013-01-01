/*====================================================================*
 *
 *   void SHA256Ident (int fd, void * memory, size_t extent, byte digest []);
 *
 *   SHA256.h
 *
 *   compute the SHA256 digest of file content; the digest becomes
 *   the fingerprint that can be used to identify the file despite 
 *   filename changes;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SHA256IDENT_SOURCE
#define SHA256IDENT_SOURCE

#include <unistd.h>

#include "../crypt/SHA256.h"

void SHA256Ident (int fd, void * memory, size_t extent, byte digest []) 

{
	struct sha256 sha256;
	signed length;
	SHA256Reset (&sha256);
	while ((length = read (fd, memory, extent)) > 0) 
	{
		SHA256Write (&sha256, memory, length);
	}
	SHA256Fetch (&sha256, digest);
	return;
}


#endif

