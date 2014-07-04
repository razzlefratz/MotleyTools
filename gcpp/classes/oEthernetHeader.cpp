/*====================================================================*
 *
 *   oEthernetHeader.cpp - oEthernetHeader class definition;
 *
 *   implement a standard Ethernet header consisting of peer address,
 *   host address and ethertype; provide methods to encode and decode
 *   external memory;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oETHERNET_SOURCE
#define oETHERNET_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstring>
#include <iostream>

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <net/ethernet.h>
#include <netinet/in.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/oEthernetHeader.hpp"
#include "../classes/omemory.hpp"

/*====================================================================*
 *   class constants;
 *--------------------------------------------------------------------*/

byte const oEthernetHeader::BroadcastAddress [ETHER_ADDR_LEN] =

{
	0xFF,
	0xFF,
	0xFF,
	0xFF,
	0xFF,
	0xFF
};

/*====================================================================*
 *
 *   size_t HeaderLength (void) const;
 *
 *   return the length of an encoded Ethernet header in bytes;
 *
 *--------------------------------------------------------------------*/

size_t oEthernetHeader::HeaderLength (void) const

{
	return (sizeof (this->mpeeraddr) +  sizeof (this->mhostaddr) +  sizeof (this->mprotocol));
}

/*====================================================================*
 *
 *   void * getHeader (void * memory) const;
 *
 *   encode external memory with an Ethernet header and return the
 *   address of the next unencoded memory byte;
 *
 *--------------------------------------------------------------------*/

void * oEthernetHeader::getHeader (void * memory) const

{
	memory = oEthernetHeader::getTargetAddress (memory);
	memory = oEthernetHeader::getSourceAddress (memory);
	memory = oEthernetHeader::getProtocol (memory);
	return (memory);
}

/*====================================================================*
 *
 *   void const * SetHeader (void * memory);
 *
 *   decode external memory containing an Ethernet header and return
 *   the address of the next undecoded memory byte;
 *
 *--------------------------------------------------------------------*/

void const * oEthernetHeader::SetHeader (void const * memory)

{
	memory = oEthernetHeader::SetTargetAddress (memory);
	memory = oEthernetHeader::SetSourceAddress (memory);
	memory = oEthernetHeader::SetProtocol (memory);
	return (memory);
}

/*====================================================================*
 *
 *   void * getTargetAddress (void * memory) const;
 *
 *   encode external memory with the peer hardware address and return
 *   the address of the next unencoded memory byte;
 *
 *--------------------------------------------------------------------*/

void * oEthernetHeader::getTargetAddress (void * memory) const

{
	memory = omemory::encode (memory, this->mpeeraddr, sizeof (this->mpeeraddr));
	return (memory);
}

/*====================================================================*
 *
 *   void * getSourceAddress (void * memory) const;
 *
 *   encode external memory with the host hardware address and return
 *   the address of the next unencoded memory byte;
 *
 *--------------------------------------------------------------------*/

void * oEthernetHeader::getSourceAddress (void * memory) const

{
	memory = omemory::encode (memory, this->mhostaddr, sizeof (this->mhostaddr));
	return (memory);
}

/*====================================================================*
 *
 *   void * oEthernetHeader::getProtocol (void * memory) const;
 *
 *   encode external memory with the Ethernet protocol and return
 *   the address of the next unencoded memory byte;
 *
 *--------------------------------------------------------------------*/

void * oEthernetHeader::getProtocol (void * memory) const

{
	memory = omemory::encode (memory, & this->mprotocol, sizeof (this->mprotocol));
	return (memory);
}

/*====================================================================*
 *
 *   void const * SetTargetAddress (void const * memory);
 *
 *   decode external memory containing the peer hardware address and
 *   return the address of the next undecoded byte;
 *
 *--------------------------------------------------------------------*/

void const * oEthernetHeader::SetTargetAddress (void const * memory)

{
	memory = omemory::decode (memory, this->mpeeraddr, sizeof (this->mpeeraddr));
	return (memory);
}

/*====================================================================*
 *
 *   void const * SetSourceAddress (void const * memory);
 *
 *   decode external memory containing the host hardware address and
 *   return the address of the next undecoded byte;
 *
 *--------------------------------------------------------------------*/

void const * oEthernetHeader::SetSourceAddress (void const * memory)

{
	memory = omemory::decode (memory, this->mhostaddr, sizeof (this->mhostaddr));
	return (memory);
}

/*====================================================================*
 *
 *   void const * SetProtocol (void const * memory);
 *
 *   decode external memory containing the Ethernet protocol and
 *   return the address of the next undecoded byte;
 *
 *--------------------------------------------------------------------*/

void const * oEthernetHeader::SetProtocol (void const * memory)

{
	memory = omemory::decode (memory, & this->mprotocol, sizeof (this->mprotocol));
	return (memory);
}

/*====================================================================*
 *
 *   byte const * TargetAddress (void) const;
 *
 *   return the binary peer address location;
 *
 *--------------------------------------------------------------------*/

byte const * oEthernetHeader::TargetAddress (void) const

{
	return (this->mpeeraddr);
}

/*====================================================================*
 *
 *   byte const * SourceAddress (void) const;
 *
 *   return the binary host address location;
 *
 *--------------------------------------------------------------------*/

byte const * oEthernetHeader::SourceAddress (void) const

{
	return (this->mhostaddr);
}

/*====================================================================*
 *
 *   uint16_t oEthernetHeader::Protocol (void) const;
 *
 *   return the Ethernet protocol as an integer in host byte order;
 *
 *   the Ethernet protocol is stored internally in network byte order
 *   so that it can be encoded/decoded and imported/exported directly
 *   without modification;
 *
 *--------------------------------------------------------------------*/

uint16_t oEthernetHeader::Protocol (void) const

{
	return (ntohs (this->mprotocol));
}

/*====================================================================*
 *
 *   oEthernetHeader & SetProtocol (uint16_t protocol);
 *
 *   accept a new Ethernet protocol specified as an integer in host
 *   byte order;
 *
 *   the Ethernet protocol is stored internally in network byte order
 *   so that it may be encoded/decoded and imported/exported directly
 *   without modification;
 *
 *--------------------------------------------------------------------*/

oEthernetHeader & oEthernetHeader::SetProtocol (uint16_t protocol)

{
	this->mprotocol = htons (protocol);
	return (* this);
}

/*====================================================================*
 *
 *   char const * TargetAddressString (void) const;
 *
 *   return the peer address string location;
 *
 *--------------------------------------------------------------------*/

char const * oEthernetHeader::TargetAddressString (void) const

{
	static char buffer [sizeof (this->mpeeraddr) * 3];
	omemory::hexdecode (this->mpeeraddr, sizeof (this->mpeeraddr), buffer, sizeof (buffer));
	return (buffer);
}

/*====================================================================*
 *
 *   char const * SourceAddressString (void) const;
 *
 *   return the host address string location;
 *
 *--------------------------------------------------------------------*/

char const * oEthernetHeader::SourceAddressString (void) const

{
	static char buffer [sizeof (this->mhostaddr) * 3];
	omemory::hexdecode (this->mhostaddr, sizeof (this->mhostaddr), buffer, sizeof (buffer));
	return (buffer);
}

/*====================================================================*
 *
 *   char const * ProtocolString (void) const;
 *
 *   return the protocol string location;
 *
 *--------------------------------------------------------------------*/

char const * oEthernetHeader::ProtocolString (void) const

{
	static char buffer [sizeof (this->mprotocol) * 3];
	omemory::hexdecode (& this->mprotocol, sizeof (this->mprotocol), buffer, sizeof (buffer));
	return (buffer);
}

/*====================================================================*
 *
 *   oEthernetHeader & Print ();
 *
 *   print peer address, host address and ethertype on stdout in hex
 *   format; return the object instance address;
 *
 *--------------------------------------------------------------------*/

oEthernetHeader & oEthernetHeader::Print ()

{
	std::cerr << oEthernetHeader::TargetAddressString () << " ";
	std::cerr << oEthernetHeader::SourceAddressString () << " ";
	std::cerr << oEthernetHeader::ProtocolString () << std::endl;
	return (* this);
}

/*====================================================================*
 *
 *   oEthernetHeader (uint16_t protocol);
 *
 *   clear peer and host hardware addresses; set protocol to default
 *   in network byte order;
 *
 *--------------------------------------------------------------------*/

oEthernetHeader::oEthernetHeader (uint16_t protocol)

{
	std::memset (this->mpeeraddr, 0, sizeof (this->mpeeraddr));
	std::memset (this->mhostaddr, 0, sizeof (this->mhostaddr));
	this->mprotocol = htons (protocol);
	return;
}

/*====================================================================*
 *
 *   oEthernetHeader (void);
 *
 *   clear peer and host hardware addresses; set protocol to default
 *   value in network byte order;
 *
 *--------------------------------------------------------------------*/

oEthernetHeader::oEthernetHeader (void)

{
	std::memset (this->mpeeraddr, 0, sizeof (this->mpeeraddr));
	std::memset (this->mhostaddr, 0, sizeof (this->mhostaddr));
	this->mprotocol = 0;
	return;
}

/*====================================================================*
 *
 *   ~oEthernetHeader (void);
 *
 *--------------------------------------------------------------------*/

oEthernetHeader::~ oEthernetHeader (void)

{
	return;
}

/*====================================================================*
 *   end definition;
 *--------------------------------------------------------------------*/

#endif



