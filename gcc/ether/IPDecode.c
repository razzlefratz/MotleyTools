/*====================================================================*
 *
 *   char *IPDecode (unsigned address);
 *
 *   convert an unsigned integer to an IPV4 dotted decimal string; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef IPDECODE_SOURCE
#define IPDECODE_SOURCE

#include "../ether/IPAddr.h"

char const *IPDecode (unsigned address) 

{
	static char string [4 * IP_ADDR_OCTETS];
	IPA addr = 
	{
		address
	};
	unsigned octet = IP_ADDR_OCTETS;
	unsigned digit = sizeof (string);
	string [--digit] = (char) (0);
	while (octet-- > 0) 
	{
		unsigned value = addr.octet [octet];
		unsigned width = 3;
		while (width-- > 0) 
		{
			string [--digit] = '0' + (char) (value % 10);
			value /= 10;
		}
		if (octet > 0) 
		{
			string [--digit] = IP_ADDR_EXTENDER;
		}
	}
	return (&string [digit]);
}


#endif

