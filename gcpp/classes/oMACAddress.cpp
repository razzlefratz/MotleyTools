/*====================================================================*
 *
 *   oMACAddress.cpp - implementation of the oMACAddress class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oMACADDRESS_SOURCE
#define oMACADDRESS_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cctype>
#include <cstring>
#include <iostream>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "oMACAddress.hpp"

/*====================================================================*
 *   constant definitions;
 *--------------------------------------------------------------------*/

char const oMACAddress::digit[] = "0123456789ABCDEF";

/*====================================================================*
 *   
 *   errno_t error () const;
 *   
 *   
 *--------------------------------------------------------------------*/

errno_t oMACAddress::error() const

{
	return (this->merror);
}

/*====================================================================*
 *   
 *   unsigned char const * number () const
 *   
 *   
 *--------------------------------------------------------------------*/

unsigned char const * oMACAddress::number() const

{
	return ((const unsigned char *) (this->mnumber));
}

/*====================================================================*
 *   
 *   char const * string () const
 *   
 *   
 *--------------------------------------------------------------------*/

unsigned char const * oMACAddress::string() const

{
	return ((char const *) (this->mstring));
}

/*====================================================================*
 *
 *   void spec (unsigned char number [], size_t octets, char const * string);
 *   
 *--------------------------------------------------------------------*/

oMACAddress & oMACAddress::spec(char const * string)

{
	switch (this->encode(string).error())
	{
	case oMACADDRESS_TOOSHORT:
		std::cerr << "MAC address '" << string << "' is too short.\n";
		break;
	case oMACADDRESS_TOOLONG:
		std::cerr << "MAC address '" << string << "' is too long.\n";
		break;
	case oMACADDRESS_ILLEGAL:
		std::cerr << "MAC address '" << string << "' is illegal.\n";
		break;
	}
	return (* this);
}

/*====================================================================*
 *
 *   oMACAddress & encode (char const *string) 
 *
 *   convert a hexadecimal MAC address string to the equivalent six
 *   octet value; return 0 on success or non-zero on failure;
 *
 *--------------------------------------------------------------------*/

oMACAddress & oMACAddress::encode(char const * string)

{
	size_t octet;
	size_t upper;
	size_t lower;
	string = std::strncpy(this->mstring, string, ETHER_ADDR_LEN * 3);
	for (octet = 0; octet < ETHER_ADDR_LEN; octet++)
	{
		for (upper = 0; (oMACAddress::digit[upper] != std::toupper(* string)) && (oMACAddress::digit[upper] != (char)(0)); upper++);
		if (* string++ == (char)(0))
		{
			this->merror = oMACADDRESS_TOOSHORT;
			return (* this);
		}
		if (upper == (sizeof(oMACAddress::digit) - 1))
		{
			this->merror = oMACADDRESS_ILLEGAL;
			return (* this);
		}
		for (lower = 0; (oMACAddress::digit[lower] != std::toupper(* string)) && (oMACAddress::digit[lower] != (char)(0)); lower++);
		if (* string++ == (char)(0))
		{
			this->merror = oMACADDRESS_TOOSHORT;
			return (* this);
		}
		if (lower == (sizeof(oMACAddress::digit) - 1))
		{
			this->merror = oMACADDRESS_ILLEGAL;
			return (* this);
		}
		this->mnumber[octet] = ((upper & 0x0f) << 4) | (lower & 0x0f);
		if (* string == oMACADDRESS_EXTENDER)
		{
			string++;
		}
	}
	if (* string)
	{
		this->merror = oMACADDRESS_TOOLONG;
		return (* this);
	}
	return (* this);
}

/*====================================================================*
 *
 *   char const * MACDecode (const unsigned char number[], size_t octets, char *string);
 *
 *   decode numeric MAC address as hexadecimal string; MAC addresses
 *   are 6 octets but the number of octets is variable; 
 *
 *--------------------------------------------------------------------*/

oMACAddress & oMACAddress::decode(const unsigned char number[])

{
	char * string = this->mstring;
	std::memcpy(this->mnumber, number, ETHER_ADDR_LEN);
	for (size_t octet = 0; octet < ETHER_ADDR_LEN; octet++)
	{
		if (octet)
		{
			* string++ = oMACADDRESS_EXTENDER;
		}
		* string++ = oMACAddress::digit[(this->mnumber[octet] >> 4) & 0x0F];
		* string++ = oMACAddress::digit[(this->mnumber[octet] >> 0) & 0x0F];
	}
	* string = (char) (0);
	return (* this);
}

/*====================================================================*
 *
 *   oMACAddress()
 *
 *   
 *--------------------------------------------------------------------*/

oMACAddress::oMACAddress()

{
	this->mnumber = new unsigned char[ETHER_ADDR_LEN];
	this->mstring = new char[ETHER_ADDR_LEN * 3];
	std::memcpy(this->mnumber, 0, sizeof(this->mnumber));
	this->decode(this->mnumber);
	this->merror = (errno_t) (0);
	return;
}

/*====================================================================*
 *   
 *   ~oMACAddress()
 *
 *   
 *--------------------------------------------------------------------*/

oMACAddress::~ oMACAddress()

{
	return;
}

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif



