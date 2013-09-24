/*====================================================================*
 *
 *   oIPAddress.cpp - IP address conversion functions; 
 *
 *   convert numeric IP address to normal or padded string format; normal
 *   format has four octet fields having one to three digits each; padded
 *   format has four octet fields having three digits each; normal format
 *   strings do not sort properly but padded format strings do;
 *
 *   when sorting normal IP addresses 100.0.0.0 precedes 4.0.0.0; however, 
 *   we can convert the addresses to 100.000.000.000 and 004.000.000.000         
 *   so they sort as expected, like so:
 *    
 *   address = ip.padded(ip.number(address));
 *   
 *   convert IP address strings to unsigned integers; address strings can 
 *   be in normal msd-to-lsd format or in inaddr-arpa format, which is in 
 *   reverse order; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oIPADDRESS_SOURCE
#define oIPADDRESS_SOURCE

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include <ctype.h>

#include "../network/oIPAddress.hpp"

/*====================================================================*
 *   declared static for speed;
 *--------------------------------------------------------------------*/

union oIPAddress::bits oIPAddress::bitmap;
char oIPAddress::buffer[OCTETS * 4];
char oIPAddress::digits[12] = "0123456789.";
unsigned oIPAddress::digit;
unsigned oIPAddress::octet;
unsigned oIPAddress::value;
unsigned oIPAddress::width;

/*====================================================================*
 *
 *   char const *oIPAddress::string (unsigned number);
 *
 *   convert an IPV4 unsigned integer address to an equivalent dotted  
 *   dotted decimal string; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const * oIPAddress::string(unsigned number)

{
	oIPAddress::bitmap.value = number;
	oIPAddress::digit = sizeof(oIPAddress::buffer);
	buffer [-- oIPAddress::digit] = (char)(0);
	for (oIPAddress::octet = 0; oIPAddress::octet < OCTETS; oIPAddress::octet++)
	{
		if (oIPAddress::octet)
		{
			oIPAddress::buffer[-- oIPAddress::digit] = oIPAddress::digits[10];
		}
		oIPAddress::value = oIPAddress::bitmap.field[octet];
		do 
		{
			oIPAddress::buffer[-- oIPAddress::digit] = oIPAddress::digits[0] + (char)(oIPAddress::value % 10);
		}
		while (oIPAddress::value /= 10);
	}
	return (& oIPAddress::buffer[oIPAddress::digit]);
}

/*====================================================================*
 *
 *   char const *oIPAddress::padded (unsigned number);
 *
 *   convert an IPV4 unsigned integer address to an equivalent dotted  
 *   dotted decimal string; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const * oIPAddress::padded(unsigned number)

{
	oIPAddress::bitmap.value = number;
	oIPAddress::digit = sizeof(oIPAddress::buffer);
	buffer [-- oIPAddress::digit] = (char)(0);
	for (oIPAddress::octet = 0; oIPAddress::octet < OCTETS; oIPAddress::octet++)
	{
		if (oIPAddress::octet)
		{
			oIPAddress::buffer[-- oIPAddress::digit] = oIPAddress::digits[10];
		}
		oIPAddress::value = oIPAddress::bitmap.field[oIPAddress::octet];
		for (oIPAddress::width = 0; oIPAddress::width < 3; oIPAddress::width++)
		{
			oIPAddress::buffer[-- oIPAddress::digit] = oIPAddress::digits[0] + (char)(oIPAddress::value % 10);
			oIPAddress::value /= 10;
		}
	}
	return (& oIPAddress::buffer[oIPAddress::digit]);
}

/*====================================================================*
 *
 *   unsigned oIPAddress::number (char const *string);
 *
 *   convert an IPV4 dotted decimal string address to an unsigned    
 *   integer;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

unsigned oIPAddress::number(char const * string)

{
	oIPAddress::bitmap.value = 0;
	if (string != (char *)(0))
	{
		oIPAddress::octet = OCTETS;
		while (oIPAddress::octet-- > 0)
		{
			oIPAddress::value = 0;
			while (isdigit(* string))
			{
				oIPAddress::value *= 10;
				oIPAddress::value += * string++ - oIPAddress::digits[0];
			}
			if (* string == oIPAddress::digits[10])
			{
				string++;
			}
			if (oIPAddress::value < 0x100)
			{
				oIPAddress::bitmap.field[oIPAddress::octet] = oIPAddress::value;
			}
		}
	}
	return (oIPAddress::bitmap.value);
}

/*====================================================================*
 *
 *   unsigned oIPAddress::inaddr (char const *string);
 *
 *   convert an IPV4 dotted decimal in-addr.arpa string address to 
 *   an unsigned integer; in-addr.arpa octets are in reverse order; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

unsigned oIPAddress::inaddr(char const * string)

{
	oIPAddress::bitmap.value = 0;
	if (string != (char *)(0))
	{
		for (oIPAddress::octet = 0; oIPAddress::octet < OCTETS; oIPAddress::octet++)
		{
			oIPAddress::value = 0;
			while (isdigit(* string))
			{
				oIPAddress::value *= 10;
				oIPAddress::value += * string++ - oIPAddress::digits[0];
			}
			if (* string == oIPAddress::digits[10])
			{
				string++;
			}
			if (oIPAddress::value < 0x100)
			{
				oIPAddress::bitmap.field[oIPAddress::octet] = oIPAddress::value;
			}
		}
	}
	return (oIPAddress::bitmap.value);
}

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

oIPAddress::oIPAddress()

{
	return;
};

oIPAddress::~ oIPAddress()

{
	return;
}

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif



