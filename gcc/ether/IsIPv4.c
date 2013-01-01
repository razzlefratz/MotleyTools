/*====================================================================*
 *
 *   bool isIPv4 (char const *string);
 *
 *   IPAddr.h
 *
 *   return true if string is a syntactically valid dotted decimal
 *   IPv4 address;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef ISIPV4_SOURCE
#define ISIPV4_SOURCE

#include <ctype.h>

#include "../tools/types.h"
#include "../ether/IPAddr.h"

bool isIPv4 (char const *string) 

{
	int digits = 0;
	int octets = 0;
	int length = 0;
	while (isdigit (*string)) 
	{
		digits++;
		length++;
		string++;
		if (*string == IP_ADDR_EXTENDER) 
		{
			if (digits > 3) 
			{
				return (false);
			}
			digits = 0;
			octets++;
			length++;
			string++;
		}
	}
	if (*string) 
	{
		return (false);
	}
	if ((length < IP_ADDR_MINLENGTH) || (length > IP_ADDR_MAXLENGTH)) 
	{
		return (false);
	}
	if (octets != (IP_ADDR_OCTETS - 1)) 
	{
		return (false);
	}
	return (true);
}


#endif

