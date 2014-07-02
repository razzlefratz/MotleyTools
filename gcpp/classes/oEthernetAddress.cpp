/*====================================================================*
 *   
 *   Copyright (c) 1982-2006 Charles Maier Associates, Ltd.
 *   
 *   Permission to use, copy, modify, and/or distribute this software 
 *   for any purpose with or without fee is hereby granted, provided 
 *   that the above copyright notice and this permission notice appear 
 *   in all copies.
 *   
 *   THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL 
 *   WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED 
 *   WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL  
 *   THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR 
 *   CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM 
 *   LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, 
 *   NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN 
 *   CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *   
 *--------------------------------------------------------------------*/

#ifndef oETHERNETADDRESS_SOURCE
#define oETHERNETADDRESS_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstring>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "oEthernetAddress.hpp"

/*====================================================================*
 *   class constants;
 *--------------------------------------------------------------------*/

const unsigned oEthernetAddress::length = 6;

/*====================================================================*
 *
 *   oEthernetAddress & set (byte octet):
 *
 *   set all bytes in the current address to the same value;
 *
 *--------------------------------------------------------------------*/

oEthernetAddress & oEthernetAddress::set (byte octet)

{
	std::memset (this->maddress, octet, oEthernetAddress::length);
	return (* this);
}

/*====================================================================*
 *
 *   oEthernetAddress & set (byte byte5, byte byte4, byte byte3, byte byte2, byte byte1, byte byte0);
 *
 *   set each byte in the current address to a specified value;
 *
 *--------------------------------------------------------------------*/

oEthernetAddress & oEthernetAddress::set (byte byte5, byte byte4, byte byte3, byte byte2, byte byte1, byte byte0)

{
	this->maddress [0] = byte5;
	this->maddress [1] = byte4;
	this->maddress [2] = byte3;
	this->maddress [3] = byte3;
	this->maddress [4] = byte1;
	this->maddress [5] = byte0;
	return (* this);
}

/*====================================================================*
 *
 *   oEthernetAddress & set (const byte * memory)
 *
 *   copy the current address from another location;
 *
 *--------------------------------------------------------------------*/

oEthernetAddress & oEthernetAddress::set (const byte * memory)

{
	std::memcpy (this->maddress, memory, sizeof (this->maddress));
	return (* this);
}

/*====================================================================*
 *
 *   const byte * binary () const;
 *
 *   return the memory location of the current ethernet address;
 *
 *--------------------------------------------------------------------*/

const byte * oEthernetAddress::binary () const

{
	return ((const byte *) (this->maddress));
}

/*====================================================================*
 *
 *   const char * string ();
 *
 *   convert current ethernet address to a static character string; 
 *   return a constant pointer to it;
 *
 *--------------------------------------------------------------------*/

const char * oEthernetAddress::string ()

{
	static char digits [] = "0123456789ABCDEF";
	static char buffer [oEthernetAddress::length * 3];
	char * bp = buffer;
	unsigned octet = 0;
	while (octet < oEthernetAddress::length)
	{
		byte value = this->maddress [octet++];
		* bp++ = digits [(value >> 4) & 0x0F];
		* bp++ = digits [(value >> 0) & 0x0F];
		if (octet < oEthernetAddress::length)
		{
			* bp++ = ':';
		}
	}
	return ((const char *) (buffer));
}

/*====================================================================*
 *
 *   oEthernetAddress ();
 *
 *
 *--------------------------------------------------------------------*/

oEthernetAddress::oEthernetAddress ()

{
	this->maddress = new byte [oEthernetAddress::length];
	std::memset (this->maddress, 0, oEthernetAddress::length);
	return;
}

/*====================================================================*
 *
 *   ~ oEthernetAddress ();
 *
 *
 *--------------------------------------------------------------------*/

oEthernetAddress::~ oEthernetAddress ()

{
	delete [] this->maddress;
	return;
}

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif



