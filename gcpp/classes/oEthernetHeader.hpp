/*====================================================================*
 *
 *   oEthernetHeader.hpp - oEthernetHeader class definitions and declaration;
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

#ifndef oETHERNET_HEADER
#define oETHERNET_HEADER

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <stdint.h>
#include <net/ethernet.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"

/*====================================================================*
 *   class datatypes;
 *--------------------------------------------------------------------*/

typedef unsigned char byte;

/*====================================================================*
 *   class declaration;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) oEthernetHeader

{
public: 
	oEthernetHeader (void);
	oEthernetHeader (uint16_t protocol);
	virtual ~ oEthernetHeader (void);
	size_t HeaderLength (void) const;
	byte const * SourceAddress (void) const;
	byte const * TargetAddress (void) const;
	uint16_t Protocol (void) const;
	void * getHeader (void * memory) const;
	void * getTargetAddress (void * memory) const;
	void * getSourceAddress (void * memory) const;
	void * getProtocol (void * memory) const;
	void const * SetHeader (void const * memory);
	void const * SetTargetAddress (void const * memory);
	void const * SetSourceAddress (void const * memory);
	void const * SetProtocol (void const * memory);
	char const * SourceAddressString (void) const;
	char const * TargetAddressString (void) const;
	char const * ProtocolString (void) const;
	oEthernetHeader & SetProtocol (uint16_t);
	oEthernetHeader & Print ();
	static byte const BroadcastAddress [ETHER_ADDR_LEN];
private: 
	byte mpeeraddr [ETHER_ADDR_LEN];
	byte mhostaddr [ETHER_ADDR_LEN];
	uint16_t mprotocol;
};

/*====================================================================*
 *   end declaration;
 *--------------------------------------------------------------------*/

#endif



