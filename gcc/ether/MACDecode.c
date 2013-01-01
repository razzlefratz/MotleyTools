/*====================================================================*
 *
 *   char const * MACDecode (const byte number[], size_t octets, char *string);
 *
 *   MACAddr.h
 *
 *   decode numeric MAC address as hexadecimal string; MAC addresses
 *   are 6 octets but the number is variable because one never knows; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef MACDECODE_SOURCE
#define MACDECODE_SOURCE

#include "../tools/error.h"
#include "../ether/MACAddr.h"

char * MACDecode (const byte number [], size_t octets, char *string) 

{
	extern char const hexdigits [];
	size_t octet;
	for (octet = 0; octet < octets; octet++) 
	{
		if (octet > 0) 
		{
			*string++ = hexdigits [0x10];
		}
		*string++ = hexdigits [(number [octet] >> 4) & 0x0F];
		*string++ = hexdigits [(number [octet] >> 0) & 0x0F];
	}
	*string = (char) (0);
	return (string);
}


#endif

