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

#ifndef oINTERNETADDRESS_SOURCE
#define oINTERNETADDRESS_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstring>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "oInternetAddress.hpp"

/*====================================================================*
 *   class constants;
 *--------------------------------------------------------------------*/

const unsigned oInternetAddress::length = 4;

/*====================================================================*
 *
 *   oInternetAddress & set (byte byte):
 *
 *   set all bytes in the current address to the same value;
 *
 *--------------------------------------------------------------------*/

oInternetAddress & oInternetAddress::set (byte byte)

{
	std::memset (this->maddress, byte, oInternetAddress::length);
	return (* this);
}

/*====================================================================*
 *
 *   oInternetAddress & set (byte byte3, byte byte2, byte byte1, byte byte0)
 *
 *   set each byte in the current address to a specified value;
 *
 *--------------------------------------------------------------------*/

oInternetAddress & oInternetAddress::set (byte byte3, byte byte2, byte byte1, byte byte0)

{
	this->maddress [0] = byte3;
	this->maddress [1] = byte2;
	this->maddress [2] = byte1;
	this->maddress [3] = byte0;
	return (* this);
}

/*====================================================================*
 *
 *   oInternetAddress & set (const byte * memory)
 *
 *   copy the current address from another location;
 *
 *--------------------------------------------------------------------*/

oInternetAddress & oInternetAddress::set (const byte * memory)

{
	memcpy (this->maddress, memory, oInternetAddress::length);
	return (* this);
}

/*====================================================================*
 *
 *   const byte * binary () const;
 *
 *   return the memory location of the current internet address;
 *
 *--------------------------------------------------------------------*/

const byte * oInternetAddress::binary () const

{
	return ((const byte *) (this->maddress));
}

/*====================================================================*
 *
 *   const char * string ();
 *
 *   convert current internet address to a static character string;
 *   return a constant pointer to it;
 *
 *--------------------------------------------------------------------*/

const char * oInternetAddress::string ()

{
	static char buffer [oInternetAddress::length * 4];
	char * character = buffer + sizeof (buffer);
	unsigned octet = oInternetAddress::length;
	* -- character = (char) (0);
	while (octet--)
	{
		byte value = this->maddress [octet];
		do 
		{
			* -- character = '0' + (value % 10);
		}
		while (value /=  10);
		if (octet)
		{
			* -- character = '.';
		}
	}
	return ((const char *) (character));
}

/*====================================================================*
 *
 *   oInternetAddress ();
 *
 *   allocate and initialize internet address buffer;
 *
 *--------------------------------------------------------------------*/

oInternetAddress::oInternetAddress ()

{
	this->maddress = new byte [oInternetAddress::length];
	std::memset (this->maddress, 0, oInternetAddress::length);
	return;
}

/*====================================================================*
 *
 *   ~ oInternetAddress ();
 *
 *   deallocate internet address buffer;
 *
 *--------------------------------------------------------------------*/

oInternetAddress::~ oInternetAddress ()

{
	delete [] this->maddress;
	return;
}

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif



