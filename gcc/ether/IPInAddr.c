/*====================================================================*
 *
 *   unsigned IPInAddr(char const *address);
 *
 *   convert an IPV4 dotted decimal in-addr.arpa address string to 
 *   an unsigned integer; in-addr.arpa octets are in reverse order;  
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef IPINADDR_SOURCE
#define IPINADDR_SOURCE

#include <ctype.h>

#include "../ether/IPAddr.h"

unsigned IPInAddr (char const *address) 

{
	IPA addr = 
	{
		0
	};
	if (address != (char *) (0)) 
	{
		unsigned octet;
		for (octet = 0; octet < IP_ADDR_OCTETS; octet++) 
		{
			unsigned value = 0;
			while (isdigit (*address)) 
			{
				value *= 10;
				value += *address++ - '0';
			}
			if (*address == IP_ADDR_EXTENDER) 
			{
				address++;
			}
			if (value < 0x100) 
			{
				addr.octet [octet] = value;
			}
		}
	}
	return (addr.value);
}


#endif

