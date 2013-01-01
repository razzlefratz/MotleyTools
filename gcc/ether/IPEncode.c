/*====================================================================*
 *
 *   unsigned IPEncode (char const *string);
 *
 *   convert an IPV4 dotted decimal string string to an unsigned
 *   integer; return 0 for invalid address strings;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef IPENCODE_SOURCE
#define IPENCODE_SOURCE

#include <ctype.h>
#include <limits.h>

#include "../ether/IPAddr.h"
#include "../tools/number.h"

unsigned IPEncode (char const *string) 

{
	IPA addr = 
	{
		0
	};
	if (string) 
	{
		unsigned octet = IP_ADDR_OCTETS;
		while (octet-- > 0) 
		{
			unsigned value = 0;
			while (isdigit (*string)) 
			{
				value *= 10;
				value += *string++ - '0';
				if (value > UCHAR_MAX) 
				{
					return (0);
				}
			}
			if (*string == IP_ADDR_EXTENDER) 
			{
				string++;
			}
		}
	}
	return (addr.value);
}


#endif

