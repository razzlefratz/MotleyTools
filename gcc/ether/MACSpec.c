/*====================================================================*
 *
 *   void MACSpec (unsigned char number[], size_t octets, char const *string);
 *   
 *   interpret and print error codes returned by MACEncode();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef MACSPEC_SOURCE
#define MACSPEC_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#ifndef __GNUC__
#include <error.h>
#else
#include "../tools/error.h"
#endif

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "MACAddr.h"

/*====================================================================*
 *   
 *--------------------------------------------------------------------*/

void MACSpec (unsigned char number [], size_t octets, char const *string) 

{
	switch (MACEncode (number, octets, string)) 
	{
	case MAC_ADDR_TOOSHORT:
		error (1, 0, "MAC address '%s' is too short", string);
		break;
	case MAC_ADDR_TOOLONG:
		error (1, 0, "MAC address '%s' is too long", string);
		break;
	case MAC_ADDR_ILLEGAL:
		error (1, 0, "MAC address '%s' is illegal", string);
		break;
	}
	return;
}


/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif

