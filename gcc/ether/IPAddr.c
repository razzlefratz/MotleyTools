/*====================================================================*
 *
 *   IPAddress.c - basic IP address conversion functions;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef IPADDRESS_SOURCE
#define IPADDRESS_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <ctype.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../ether/IPAddr.h"

/*====================================================================*
 *   declared static for speed;
 *--------------------------------------------------------------------*/

static char string [4 * IP_ADDR_OCTETS];
static char digits [12] = "0123456789.";

/*====================================================================*
 *
 *   unsigned IPEncode (char const *string);
 *
 *   convert an IPV4 dotted decimal string string to an unsigned
 *   integer;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

unsigned IPEncode (char const *string) 

{
	IPA addr = 
	{
		0
	};
	if (string != (char *) (0)) 
	{
		unsigned octet = IP_ADDR_OCTETS;
		while (octet-- > 0) 
		{
			unsigned value = 0;
			while (isdigit (*string)) 
			{
				value *= 10;
				value += *string++ - digits [0];
			}
			if (*string == digits [10]) 
			{
				string++;
			}
			if (value < 0x100) 
			{
				addr.octet [octet] = value;
			}
		}
	}
	return (addr.value);
}


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
				value += *address++ - digits [0];
			}
			if (*address == digits [10]) 
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

char const *IPDecode (unsigned address) 

{
	IPA addr = 
	{
		address
	};
	unsigned octet;
	unsigned digit = sizeof (string);
	string [--digit] = (char) (0);
	for (octet = 0; octet < IP_ADDR_OCTETS; octet++) 
	{
		unsigned value;
		unsigned width;
		if (octet > 0) 
		{
			string [--digit] = digits [10];
		}
		value = addr.octet [octet];
		for (width = 0; width < 3; width++) 
		{
			string [--digit] = digits [0] + (char) (value % 10);
			value /= 10;
		}
	}
	return (&string [digit]);
}


/*====================================================================*
 *
 *   char *IPString(unsigned address);
 *
 *   convert an unsigned integer IPv4 address to an interger string;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const *IPString (unsigned address) 

{
	IPA addr = 
	{
		address
	};
	unsigned octet;
	unsigned digit = sizeof (string);
	string [--digit] = (char) (0);
	for (octet = 0; octet < IP_ADDR_OCTETS; octet++) 
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


/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif

