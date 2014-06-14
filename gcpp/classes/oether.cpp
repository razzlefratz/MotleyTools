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

#ifndef oETHER_SOURCE
#define oETHER_SOURCE

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "ether.h"

/*====================================================================*
 *  define class variables;
 *--------------------------------------------------------------------*/

static struct

{
	uint16_t type;
	char const * name;
}

ethertypes [] =

{
	{
		0x0800,
		"Internet Protocol version 4 (IPv4)"
	},
	{
		0x0806,
		"Address Resolution Protocol (ARP)"
	},
	{
		0x0842,
		"Wake-on-LAN[3]"
	},
	{
		0x22F3,
		"IETF TRILL Protocol"
	},
	{
		0x6003,
		"DECnet Phase IV"
	},
	{
		0x8035,
		"Reverse Address Resolution Protocol"
	},
	{
		0x809B,
		"AppleTalk (Ethertalk)"
	},
	{
		0x80F3,
		"AppleTalk Address Resolution Protocol (AARP)"
	},
	{
		0x8100,
		"VLAN-tagged frame (IEEE 802.1Q) & Shortest Path Bridging IEEE 802.1aq[4]"
	},
	{
		0x8137,
		"IPX"
	},
	{
		0x8138,
		"IPX"
	},
	{
		0x8204,
		"QNX Qnet"
	},
	{
		0x86DD,
		"Internet Protocol Version 6 (IPv6)"
	},
	{
		0x8808,
		"Ethernet flow control"
	},
	{
		0x8809,
		"Slow Protocols (IEEE 802.3)"
	},
	{
		0x8819,
		"CobraNet"
	},
	{
		0x884,
		"MPLS unicast"
	},
	{
		0x8848,
		"MPLS multicast"
	},
	{
		0x8863,
		"PPPoE Discovery Stage"
	},
	{
		0x8864,
		"PPPoE Session Stage"
	},
	{
		0x8870,
		"Jumbo Frames[2]"
	},
	{
		0x887B,
		"HomePlug 1.0 MME"
	},
	{
		0x888E,
		"EAP over LAN (IEEE 802.1X)"
	},
	{
		0x8892,
		"PROFINET Protocol"
	},
	{
		0x889A,
		"HyperSCSI (SCSI over Ethernet)"
	},
	{
		0x88A2,
		"ATA over Ethernet"
	},
	{
		0x88A4,
		"EtherCAT Protocol"
	},
	{
		0x88A8,
		"Provider Bridging (IEEE 802.1ad) & Shortest Path Bridging IEEE 802.1aq[5]"
	},
	{
		0x88AB,
		"Ethernet Powerlink[citation needed]"
	},
	{
		0x88CC,
		"Link Layer Discovery Protocol (LLDP)"
	},
	{
		0x88CD,
		"SERCOS III"
	},
	{
		0x88E1,
		"HomePlug AV"
	},
	{
		0x88E3,
		"Media Redundancy Protocol (IEC62439-2)"
	},
	{
		0x88E5,
		"MAC security (IEEE 802.1AE)"
	},
	{
		0x88F7,
		"Precision Time Protocol (IEEE 1588)"
	},
	{
		0x8902,
		"IEEE 802.1ag Connectivity Fault Management (CFM) Protocol / ITU-T Recommendation Y.1731 (OAM)"
	},
	{
		0x8906,
		"Fibre Channel over Ethernet (FCoE)"
	},
	{
		0x8914,
		"FCoE Initialization Protocol"
	},
	{
		0x8915,
		"RDMA over Converged Ethernet (RoCE)"
	},
	{
		0x892F,
		"High-availability Seamless Redundancy (HSR)"
	},
	{
		0x9000,
		"Ethernet Configuration Testing Protocol[6]"
	},
	{
		0x9100,
		"Q-in-Q"
	},
	{
		0xCAFE,
		"Veritas Low Latency Transport (LLT)[7] for Veritas Cluster Server"
	}
};


/*====================================================================*
 *
 *   void showFrame (byte memory, unsigned extent);
 *
 *--------------------------------------------------------------------*/

void oether::showFrame (byte * memory, unsigned extent)

{
	if (extent)
	{
		struct ether * frame = (struct ether *) (memory);
//                PRINTLN (etherProtocol(frame->header.type));
		PRINT ("[");
		MemoryClass::hexstring (frame->header.oda, sizeof (frame->header.oda));
		PRINT ("] [");
		MemoryClass::hexstring (frame->header.osa, sizeof (frame->header.osa));
		PRINT ("] [");
		MemoryClass::hexstring ((byte *)(&frame->header.type), sizeof (frame->header.type));
		PRINT ("] [");
		MemoryClass::hexstring (frame->body, extent - sizeof (frame->header));
		PRINT ("]");
		PRINTLN ();
	}
	return;
}

/*====================================================================*
 *
 *   char const * protocolname (uint16_t ethertype);
 *
 *   convert an Ethernet protocol number (Ethertype) to a human
 *   readable string; use a binary search to located the string
 *   for speed reasons;
 *
 *--------------------------------------------------------------------*/

char const * oether::protocolname (uint16_t ethertype)

{
	size_t lower = 0; 
	size_t upper = SIZEOF (ethertypes); 
	ethertype = ntohs (ethertype); 
	while (lower < upper) 
	{ 
		size_t index = (lower +  upper) >> 1; 
		signed order = ethertype - ethertypes [index].type; 
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
		return (ethertypes [index].name);
	} 
	return ("unknown protocol");
} 

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif



