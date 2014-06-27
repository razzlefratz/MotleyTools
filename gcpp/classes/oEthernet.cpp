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

#ifndef oETHERNET_SOURCE
#define oETHERNET_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/


/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "oEthernet.hpp"
#include "omemory.hpp"

/*====================================================================*
 *  define class variables;
 *--------------------------------------------------------------------*/

#define oETHERNET_TABLE 0
#if oETHERNET_TABLE

static struct

{
	uint16_t number;
	char const * acronymn;
	char const * name;
}

protocols [] =

{
	{
		0x0800,
		"ipv4",
		"Internet Protocol version 4"
	},
	{
		0x0806,
		"arp",
		"Address Resolution Protocol"
	},
	{
		0x0842,
		"WoL",
		"Wake-on-LAN[3]"
	},
	{
		0x22F3,
		"",
		"IETF TRILL Protocol"
	},
	{
		0x6003,
		"",
		"DECnet Phase IV"
	},
	{
		0x8035,
		"rarp",
		"Reverse Address Resolution Protocol"
	},
	{
		0x809B,
		"",
		"AppleTalk (Ethertalk)"
	},
	{
		0x80F3,
		"aarp",
		"AppleTalk Address Resolution Protocol (AARP)"
	},
	{
		0x8100,
		"",
		"VLAN-tagged frame (IEEE 802.1Q) & Shortest Path Bridging IEEE 802.1aq[4]"
	},
	{
		0x8137,
		"ipx",
		"IPX"
	},
	{
		0x8138,
		"ipx",
		"IPX"
	},
	{
		0x8204,
		"qnx",
		"QNX Qnet"
	},
	{
		0x86DD,
		"ipv6",
		"Internet Protocol Version 6 (IPv6)"
	},
	{
		0x8808,
		"",
		"Ethernet flow control"
	},
	{
		0x8809,
		"",
		"Slow Protocols (IEEE 802.3)"
	},
	{
		0x8819,
		"",
		"CobraNet"
	},
	{
		0x884,
		"",
		"MPLS unicast"
	},
	{
		0x8848,
		"",
		"MPLS multicast"
	},
	{
		0x8863,
		"ppoe",
		"PPPoE Discovery Stage"
	},
	{
		0x8864,
		"ppoe",
		"PPPoE Session Stage"
	},
	{
		0x8870,
		"",
		"Jumbo Frames[2]"
	},
	{
		0x887B,
		"hp1",
		"HomePlug 1.0 MME"
	},
	{
		0x888E,
		"",
		"EAP over LAN (IEEE 802.1X)"
	},
	{
		0x8892,
		"",
		"PROFINET Protocol"
	},
	{
		0x889A,
		"",
		"HyperSCSI (SCSI over Ethernet)"
	},
	{
		0x88A2,
		"",
		"ATA over Ethernet"
	},
	{
		0x88A4,
		"",
		"EtherCAT Protocol"
	},
	{
		0x88A8,
		"",
		"Provider Bridging (IEEE 802.1ad) & Shortest Path Bridging IEEE 802.1aq[5]"
	},
	{
		0x88AB,
		"",
		"Ethernet Powerlink[citation needed]"
	},
	{
		0x88CC,
		"lldp",
		"Link Layer Discovery Protocol (LLDP)"
	},
	{
		0x88CD,
		"",
		"SERCOS III"
	},
	{
		0x88E1,
		"hpav",
		"HomePlug AV"
	},
	{
		0x88E3,
		"",
		"Media Redundancy Protocol (IEC62439-2)"
	},
	{
		0x88E5,
		"",
		"MAC security (IEEE 802.1AE)"
	},
	{
		0x88F7,
		"",
		"Precision Time Protocol (IEEE 1588)"
	},
	{
		0x8902,
		"",
		"IEEE 802.1ag Connectivity Fault Management (CFM) Protocol / ITU-T Recommendation Y.1731 (OAM)"
	},
	{
		0x8906,
		"FCoE",
		"Fibre Channel over Ethernet (FCoE)"
	},
	{
		0x8914,
		"FCoE",
		"FCoE Initialization Protocol"
	},
	{
		0x8915,
		"RoCE",
		"RDMA over Converged Ethernet (RoCE)"
	},
	{
		0x892F,
		"",
		"High-availability Seamless Redundancy (HSR)"
	},
	{
		0x9000,
		"",
		"Ethernet Configuration Testing Protocol[6]"
	},
	{
		0x9100,
		"",
		"Q-in-Q"
	},
	{
		0xCAFE,
		"",
		"Veritas Low Latency Transport (LLT)[7] for Veritas Cluster Server"
	}
};

#endif

/*====================================================================*
 *   public constants;
 *--------------------------------------------------------------------*/

const unsigned oEthernet::header_length = sizeof (struct ethernet_header);

/*====================================================================*
 *
 *   void PrintEthernetFrame (byte * memory, unsigned extent);
 *
 *--------------------------------------------------------------------*/

#if oETHERNET_TABLE

void oEthernet::PrintFrame (void * memory, unsigned extent)

{
	if (extent)
	{
		struct oEthernet_frame * frame = (struct oEthernet_frame *) (memory);

#if 0

		if (ntohs (frame->header.protocol) == 0x0800)
		{
			oEthernet::PrintHeader (& frame->header, sizeof (frame->header));
			internet::PrintHeader (& frame->body, sizeof (frame->body));
		}

#endif

	}
	return;
}

#endif

/*====================================================================*
 *
 *   void PrintHeader (void * memory, unsigned extent);
 *
 *   print Ethernet protocol name;
 *   print Ethernet frame header as multi-byte hex fields; 
 *
 *--------------------------------------------------------------------*/

#if oETHERNET_TABLE

void oEthernet::PrintHeader (void * memory, unsigned extent)

{
	struct oEthernet_header * oEthernet = (struct oEthernet_header *) (memory);
	Serial.println (oEthernet::ProtocolName (oEthernet->protocol));
	Serial.print ("[");
	memory::hexOctets (oEthernet->oda, sizeof (oEthernet->oda));
	Serial.print ("] [");
	memory::hexOctets (oEthernet->osa, sizeof (oEthernet->osa));
	Serial.print ("] [");
	memory::hexString (& oEthernet->protocol, sizeof (oEthernet->protocol));
	Serial.println ("]");
	return;
}

#endif

/*====================================================================*
 *
 *   char const * ProtocolName (uint16_t protocol);
 *
 *   convert an Ethernet protocol number to a string; 
 *
 *--------------------------------------------------------------------*/

#if oETHERNET_TABLE

char const * oEthernet::ProtocolName (uint16_t protocol)

{
	size_t lower = 0;
	size_t upper = SIZEOF (protocols);
	protocol = ntohs (protocol);
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
	return ("unknown oEthernet protocol");
}

#endif

/*====================================================================*
 *
 *   oEthernet ();
 *
 *
 *--------------------------------------------------------------------*/

oEthernet::oEthernet ()

{
	oEthernet::broadcast.set (0xFF);
	oEthernet::address.set (0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF);
	return;
}

/*====================================================================*
 *
 *   ~ oEthernet ();
 *
 *
 *--------------------------------------------------------------------*/

oEthernet:: ~ oEthernet ()

{
	return;
}

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif



