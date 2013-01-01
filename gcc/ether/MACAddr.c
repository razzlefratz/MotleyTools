/*====================================================================*
 *
 *   MACAddr.c - MAC Address encode and decode functions;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef MACADDR_SOURCE
#define MACADDR_SOURCE

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../ether/MACAddr.h"

/*====================================================================*
 *   functions; 
 *--------------------------------------------------------------------*/

#include "../ether/MACEncode.c"
#include "../ether/MACDecode.c"
#include "../ether/MACSpec.c"

/*====================================================================*
 *   
 *   int main (int argc, char *argv[]);
 *
 *   a siple test/demo program for MACEncode/Decode functions;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#if 0

int main (int argc, char *argv []) 

{
	char string [ETH_ALEN * 3];
	unsigned char MAC [ETH_ALEN] = 
	{
		0x00,
		0xB0,
		0x52,
		0x0B,
		0x20,
		0x18
	};
	if (*++argv) 
	{
		MACSpec (MAC, sizeof (MAC), *argv);
	}
	MACDecode (MAC, sizeof (MAC), string);
	printf ("%s\n", string);
	exit (0);
}


#endif

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif

