/*====================================================================*
 *
 *   crypt.h - encryption/decryption definitions and declarations; 
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 2005 by Charles Maier Associates for internal use;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef CRYPT_HEADER
#define CRYPT_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/types.h"

/*====================================================================*
 *   function;
 *--------------------------------------------------------------------*/

void fingerprint (int fd, byte digest []);
void passwords (unsigned seed, unsigned start, unsigned count, unsigned limit, unsigned block, char space);

/*====================================================================*
 *   
 *--------------------------------------------------------------------*/

#endif

