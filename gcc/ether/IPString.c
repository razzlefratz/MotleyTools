/*====================================================================*
 *
 *   char *IPString(unsigned address);
 *
 *   convert an unsigned integer IPv4 address to an integer string;
 *   use IPDecode to obtain a dotted decimal string;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef IPSTRING_SOURCE
#define IPSTRING_SOURCE

#include "../ether/IPAddr.h"

static char string [4 * IP_ADDR_OCTETS];
static char digits [] = "0123456789.";
char const *IPString (unsigned address) 

{
	IPA addr = 
	{
		address
	};
	unsigned octet;
	unsigned digit = sizeof (string);
	string [--digit] = (char) (0);
	for (octet = 0; octet < sizeof (addr.octet); octet++) 
	{
		unsigned value;
		if (octet > 0) 
		{
			string [--digit] = digits [10];
		}
		value = addr.octet [octet];
		do 
		{
			string [--digit] = digits [0] + (char) (value % 10);
		}
		while (value /= 10);
	}
	return (&string [digit]);
}


#endif

