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

#ifndef oINTERNET_SOURCE
#define oINTERNET_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <Arduino.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "ethernet.h"
#include "oInternet.h"
#include "ipaddress.h"
#include "memory.h"

/*====================================================================*
 *  define class variables;
 *--------------------------------------------------------------------*/

#if oINTERNET_TABLE

static struct

{
	byte number;
	char const * acronym;
	char const * name;
}

protocols [] =

{
	{
		1,
		"icmp",
		"Internet Control Message Protocol"
	},
	{
		2,
		"igmp",
		"Internet Group Management Protocol"
	},
	{
		6,
		"tcp",
		"Transmission Control Protocol"
	},
	{
		17,
		"udp",
		"User Datagram Protocol"
	}
};

#endif

/*====================================================================*
 *   public constants;
 *--------------------------------------------------------------------*/

const unsigned oInternet::header_length = sizeof (struct oInternet_header);

/*====================================================================*
 *
 *   bool onsubnet (const byte * address1, const byte * address2, const byte * netmask)
 *
 *   return true if addres argument matches current address;
 *
 *--------------------------------------------------------------------*/

bool oInternet::onsubnet (const byte * address1, const byte * address2, const byte * netmask)

{
	unsigned octet = ipaddress::length;
        while (octet--)
	{
		if ((address1 [octet] & netmask [octet]) != (address2 [octet] & netmask [octet]))
		{
			return (false);
		}
	}
	return (true);
	return (true);
}

/*====================================================================*
 *
 *   void PrintHeader (void * memory, unsigned extent);
 *
 *   print Internet protocol name;
 *   print Internet protocol header as decimal and hex fields;
 *   print Internet protocol address as dotted decimal fields;
 *
 *--------------------------------------------------------------------*/

#if oINTERNET_TABLE

void oInternet::PrintHeader (void * memory, unsigned extent)

{
	struct oInternet_packet * packet = (struct oInternet_packet *) (memory);
	packet->header.total_length = ntohs (packet->header.total_length);
	Serial.println (oInternet::ProtocolName (packet->header.protocol));

#if 0

	Serial.print ("Protocol=");
	Serial.println (packet->header.protocol);
	Serial.print ("Length=");
	Serial.println (packet->header.total_length);

#endif

	Serial.print ("[");
	memory::decOctets (& packet->header.src_addr, sizeof (packet->header.src_addr));
	Serial.print ("] [");
	memory::decOctets (& packet->header.dst_addr, sizeof (packet->header.dst_addr));
	Serial.println ("]");
	return;
}

#endif

/*====================================================================*
 *
 *   char const * ProtocolName (byte protocol);
 *
 *   convert an Internet protocol number to a human readable string; 
 *   use a binary search for speed;
 *
 *--------------------------------------------------------------------*/

#if oINTERNET_TABLE

char const * oInternet::ProtocolName (byte protocol)

{
	size_t lower = 0;
	size_t upper = SIZEOF (protocols);
	while (lower < upper)
	{
		size_t index = (lower +  upper) >> 1;
		signed order = protocol - protocols [index].number;
		if (order < 0)
		{
			upper = index - 0;
			continue;
		}
		if (order > 0)
		{
			lower = index +  1;
			continue;
		}
		return (protocols [index].name);
	}
	return ("unknown inTERNET protocol");
}

#endif

/*====================================================================*
 *
 *   oInternet ();
 *
 *
 *--------------------------------------------------------------------*/

oInternet::oInternet ()

{
	oInternet::broadcast.set (255);
	oInternet::address.set (192, 168, 1, 10);
	oInternet::netmask.set (255, 255, 255, 0);
	oInternet::gateway.set (192, 168, 1, 5);
	return;
}

/*====================================================================*
 *
 *   ~ oInternet ();
 *
 *
 *--------------------------------------------------------------------*/

oInternet:: ~ oInternet ()

{
	return;
}

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif



