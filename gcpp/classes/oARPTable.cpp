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

#ifndef oARPTABLE_SOURCE
#define oARPTABLE_SOURCE

/*====================================================================*
 *   system header fileds;
 *--------------------------------------------------------------------*/

#include <cstdio>

/*====================================================================*
 *   custome header files;
 *--------------------------------------------------------------------*/

#include "oARPTable.hpp"
#include "../classes/oEthernetAddress.hpp"
#include "../classes/oInternetAddress.hpp"
#include "memory.h"

/*====================================================================*
 *   class constants;
 *--------------------------------------------------------------------*/

#define ARP_REQUEST 1
#define ARP_REPLY   2
#define ARP_HWTYPE_ETH 1
#define ARP_TIMER 120

/*====================================================================*
 *   class variables;
 *--------------------------------------------------------------------*/

extern oInternetAddress internet;
extern oEthernetAddress ethernet;
extern uint16_t uip_len;
extern uint8_t uip_buf [];
static unsigned arptimer = 0;
static unsigned arpindex = 0;
static struct arpentry * arpentry;
static struct arpentry

{
	byte internet_address [4];
	byte ethernet_address [6];
	byte timer;
}

arptable [8];

/*====================================================================*
 *
 *   boot empty (void * memory, unsigned extent, byte value);
 *
 *   return true of the specified memory region contains all zero
 *   bytes;
 *
 *--------------------------------------------------------------------*/

bool ARP::empty (void * memory, unsigned extent)

{
	byte * offset = (byte *) (memory);
	while (extent--)
	{
		if (* offset++)
		{
			return (false);
		}
	}
	return (true);
}

/*====================================================================*
 *
 *   Periodic ARP processing function.
 *
 *   This function performs periodic timer processing in the ARP module
 *   and should be called at regular intervals. The recommended interval
 *   is 10 seconds between the calls.
 *
 *--------------------------------------------------------------------*/

void ARP::timer (void)

{
	for (arpindex = 0; arpindex < SIZEOF (arptable); ++ arpindex)
	{
		arpentry = & arptable [arpindex];
		if (! empty (arpentry->internet_address, sizeof (arpentry->internet_address)) && (arptimer - arpentry->timer) >= ARP_TIMER)
		{
			std::cerr << "Delete old ARP table entry." << std::endl;
			std::memset (arpentry, 0, sizeof (arpentry));
		}
	}
	arptimer++;
	return;
}

/*====================================================================*
 *
 *   void ARP::update (byte internet_address *, byte ethernet_address *);
 *
 *--------------------------------------------------------------------*/

void ARP::update (byte * internet_address, byte * ethernet_address)

{
	for (arpindex = 0; arpindex < SIZEOF (arptable); ++ arpindex)
	{
		arpentry = & arptable [arpindex];
		if (! empty (arpentry, sizeof (* arpentry)))
		{
			if (! std::memcmp (arpentry->internet_address, internet_address, sizeof (arpentry->ethernet_address)))
			{
				std::cerr << "Update old ARP table entry." << std::endl;
				std::memcpy (arpentry->ethernet_address, ethernet_address, sizeof (arpentry->ethernet_address));
				arpentry->timer = arptimer;
				return;
			}
		}
	}
	for (arpindex = 0; arpindex < SIZEOF (arptable); ++ arpindex)
	{
		arpentry = & arptable [arpindex];
		if (empty (arpentry, sizeof (* arpentry)))
		{
			std::cerr << "Create new ARP table entry." << std::endl;
			break;
		}
	}
	if (arpindex == SIZEOF (arptable))
	{
		unsigned tmpage = 0;
		unsigned oldest = 0;
		for (arpindex = 0; arpindex < SIZEOF (arptable); ++ arpindex)
		{
			arpentry = & arptable [arpindex];
			if ((arptimer - arpentry->timer) > tmpage)
			{
				tmpage = arptimer - arpentry->timer;
				oldest = arpindex;
			}
		}
		arpentry = & arptable [oldest];
		Serial.println ("Delete old ARP table entry.");
	}
	std::memcpy (arpentry->internet_address, internet_address, sizeof (arpentry->ethernet_address));
	std::memcpy (arpentry->ethernet_address, ethernet_address, sizeof (arpentry->internet_address));
	arpentry->timer = arptimer;
	return;
}

/*--------------------------------------------------------------------*/

/*
 * ARP processing for incoming IP packets
 *
 * This function should be called by the device driver when an IP
 * packet has been received. The function will check if the address is
 * in the ARP cache, and if so the ARP cache entry will be
 * refreshed. If no ARP cache entry was found, a new one is created.
 *
 * This function expects an IP packet with a prepended Ethernet header
 * in the uip_buf[] buffer, and the length of the packet in the global
 * variable uip_len.
 */

/* Only insert/update an entry if the source IP address of the
 * incoming IP packet comes from a host on the local network.
 */

/*--------------------------------------------------------------------*/

void ARP::ipin (void)

{
	uip_len -= sizeof (struct ethernet_header);
	struct ethernet_header * ethernet_header = (struct ethernet_header *) (& uip_buf [0]);
	struct internet_packet * internet_packet = (struct internet_packet *) (& uip_buf [0]);
	struct internet_header * internet_header = (struct internet_header *) (& internet_packet->internet_header);
	if (internet.onsubnet (internet_header->source_address, internet.address.get (), internet.netmask.get ()))
	{
		ARP::update (internet_header->source_address, ethernet_header->osa);
	}
	return;
}


/*=*
 * ARP processing for incoming ARP packets.
 *
 * This function should be called by the device driver when an ARP
 * packet has been received. The function will act differently
 * depending on the ARP packet type: if it is a reply for a request
 * that we previously sent out, the ARP cache will be filled in with
 * the values from the ARP reply. If the incoming ARP packet is an ARP
 * request for our IP address, an ARP reply packet is created and put
 * into the uip_buf[] buffer.
 *
 * When the function returns, the value of the global variable uip_len
 * indicates whether the device driver should send out a packet or
 * not. If uip_len is zero, no packet should be sent. If uip_len is
 * non-zero, it contains the length of the outbound packet that is
 * present in the uip_buf[] buffer.
 *
 * This function expects an ARP packet with a prepended Ethernet
 * header in the uip_buf[] buffer, and the length of the packet in the
 * global variable uip_len.
 *
 *-*/

void ARP::in (void)

{
	extern byte uip_hostaddr [4];
	extern byte uip_ethaddr [6];
	struct ethernet_header * ethernet_header = (struct ethernet_header *) (& uip_buf);
	struct arp_packet * arp_packet = (struct arp_packet *) (& uip_buf);
	struct arp_header * arp_header = (struct arp_header *) (& arp_packet->arp_header);
	if (uip_len < sizeof (* arp_packet))
	{
		Serial.println ("ARP packet too short");
		uip_len = 0;
		return;
	}
	uip_len = 0;
	switch (arp_header->opcode)
	{
	case htons (ARP_REQUEST):
		Serial.println ("ARP_REQUEST");

/* ARP request. If it asked for our address, we send out a
 * reply.
 */

		if (! std::memcmp (arp_header->target_ipaddr, internet.address.get (), sizeof (arp_header->target_ipaddr)))
		{
			Serial.println ("Register host");

/* First, we register the one who made the request in our ARP
 * table, since it is likely that we will do more communication
 * with this host in the future.
 */

			ARP::update (arp_header->source_ipaddr, arp_header->source_hwaddr);
			arp_header->opcode = htons (2);
			std::memcpy (arp_header->target_hwaddr, arp_header->source_hwaddr, sizeof (arp_header->source_hwaddr));
			std::memcpy (arp_header->source_hwaddr, uip_ethaddr, sizeof (arp_header->source_hwaddr));
			std::memcpy (ethernet_header->osa, uip_ethaddr, sizeof (ethernet_header->osa));
			std::memcpy (ethernet_header->oda, arp_header->target_hwaddr, sizeof (ethernet_header->oda));
			std::memcpy (arp_header->target_ipaddr, arp_header->source_ipaddr, sizeof (arp_header->target_ipaddr));
			std::memcpy (arp_header->source_ipaddr, uip_hostaddr, sizeof (arp_header->source_ipaddr));
			ethernet_header->protocol = htons (ETHERTYPE_ARP);
			uip_len = sizeof (struct arp_packet);
		}
		break;
	case htons (ARP_REPLY):
		Serial.println ("ARP_REPLY");

/* ARP reply. We insert or update the ARP table if it was meant
 * for us.
 */

		if (! std::memcmp (arp_header->target_ipaddr, uip_hostaddr, sizeof (arp_header->target_ipaddr)))
		{
			ARP::update (arp_header->source_ipaddr, arp_header->source_hwaddr);
		}
		break;
	default: 
		Serial.println ("ARP_ERROR");
		break;
	}
	return;
}

/*--------------------------------------------------------------------*/

/*
 * Prepend Ethernet header to an outbound IP packet and see if we need
 * to send out an ARP request.
 *
 * This function should be called before sending out an IP packet. The
 * function checks the destination IP address of the IP packet to see
 * what Ethernet MAC address that should be used as a destination MAC
 * address on the Ethernet.
 *
 * If the destination IP address is in the local network (determined
 * by logical ANDing of netmask and our IP address), the function
 * checks the ARP cache to see if an entry for the destination IP
 * address is found. If so, an Ethernet header is prepended and the
 * function returns. If no ARP cache entry is found for the
 * destination IP address, the packet in the uip_buf[] is replaced by
 * an ARP request packet for the IP address. The IP packet is dropped
 * and it is assumed that they higher level protocols (e.g., TCP)
 * eventually will retransmit the dropped packet.
 *
 * If the destination IP address is not on the local network, the IP
 * address of the default router is used instead.
 *
 * When the function returns, a packet is present in the uip_buf[]
 * buffer, and the length of the packet is in the global variable
 * uip_len.
 */

/*--------------------------------------------------------------------*/

void ARP::out (void)

{
	static byte ipaddr [4];
	struct arp_packet * arp_packet = (struct arp_packet *) (& uip_buf);
	struct arp_header * arp_header = (struct arp_header *) (& arp_packet->arp_header);
	struct internet_packet * internet_packet = (struct internet_packet *) (& uip_buf);
	struct internet_header * internet_header = (struct internet_header *) (& internet_packet->internet_header);
	struct ethernet_header * ethernet_header = (struct ethernet_header *) (& uip_buf);

/* Find the destination IP address in the ARP table and construct
 * the Ethernet header. If the destination IP addres isn't on the
 * local network, we use the default router's IP address instead.
 *
 * If not ARP table entry is found, we overwrite the original IP
 * packet with an ARP request for the IP address.
 */

/* First check if destination is a local broadcast. */

	if (! std::memcmp (& internet_header->target_address, internet.broadcast.get (), sizeof (internet_header->target_address)))
	{
		std::memcpy (ethernet_header->oda, ethernet.broadcast.get (), sizeof (ethernet_header->oda));
	}
	else 
	{
		if (internet.onsubnet ((byte *) (& internet_header->target_address), internet.address.get (), internet.netmask.get ()))
		{
			std::memcpy (ipaddr, & internet_header->target_address, sizeof (ipaddr));
		}
		else 
		{
			std::memcpy (ipaddr, internet.gateway.get (), sizeof (ipaddr));
		}
		for (arpindex = 0; arpindex < SIZEOF (arptable); ++ arpindex)
		{
			arpentry = & arptable [arpindex];
			if (! std::memcmp (arpentry->internet_address, ipaddr, sizeof (arpentry->internet_address)))
			{
				break;
			}
		}
		if (arpindex == SIZEOF (arptable))
		{

/* The destination address was not in our ARP table, so we
 * overwrite the IP packet with an ARP request.
 */

			std::memset (ethernet_header->oda, 0xff, sizeof (ethernet_header->oda));
			std::memcpy (ethernet_header->osa, ethernet.address.get (), sizeof (ethernet_header->osa));
			ethernet_header->protocol = htons (ETHERTYPE_ARP);
			std::memset (arp_header->target_hwaddr, 0x00, sizeof (arp_header->target_hwaddr));
			std::memcpy (arp_header->source_hwaddr, ethernet.address.get (), sizeof (arp_header->source_hwaddr));
			std::memcpy (arp_header->target_ipaddr, ipaddr, sizeof (arp_header->target_ipaddr));
			std::memcpy (arp_header->source_ipaddr, internet.address.get (), sizeof (arp_header->source_ipaddr));
			arp_header->opcode = htons (ARP_REQUEST);
			arp_header->hardware_type = htons (ARP_HWTYPE_ETH);
			arp_header->protocol_type = htons (ETHERTYPE_IP);
			arp_header->hwaddrlen = ethernet.address.length;
			arp_header->ipaddrlen = internet.address.length;

// uip_appdata = & uip_buf [UIP_TCPIP_HLEN + UIP_LLH_LEN];

			uip_len = sizeof (struct arp_packet);
			return;
		}

/* Build an ethernet header. */

		std::memcpy (ethernet_header->oda, arpentry->ethernet_address, sizeof (ethernet_header->oda));
	}
	std::memcpy (ethernet_header->osa, ethernet.address.get (), sizeof (ethernet_header->osa));
	ethernet_header->protocol = htons (ETHERTYPE_IP);
	uip_len += sizeof (struct ethernet_header);
	return;
}

/*====================================================================*
 *
 *   static void PrintARPHeader (void * memory, unsigned extent);
 *
 *
 *--------------------------------------------------------------------*/

static void PrintARPHeader (void * header, unsigned extent)

{
	struct arp_header * arp_header = (struct arp_header *) (header);
	std::cerr << "hardware type " << ntohs (arp_header->hardware_type) << std::endl;
	std::cerr << "protocol type " << ntohs (arp_header->protocol_type) << std::endl;
	std::cerr << "hardware address length " << arp_header->hwaddrlen << std::endl;
	std::cerr << "protocol address length " << arp_header->ipaddrlen << std::endl;
	std::cerr << "opcode" << ntohs (arp_header->opcode) << std::endl;
	std::cerr << "sender hardware address " << ethernet.address.get (arp_header->source_hwaddr).string () << std::endl;
	std::cerr << "sender protocol address " << internet.address.get (arp_header->source_ipaddr).string () << std::endl; 
	std::cerr << "target hardware address " << ethernet.address.get (arp_header->target_hwaddr).string () << std::endl;
	std::cerr << "target protocol address " << internet.address.get (arp_header->target_ipaddr).string () << std::endl;
	return;
}

/*====================================================================*
 *
 *   ARP ();
 *
 *--------------------------------------------------------------------*/

ARP::ARP ()

{
	std::memset (arptable, 0, sizeof (arptable));
	return;
}

/*====================================================================*
 *
 *   ARP ();
 *
 *--------------------------------------------------------------------*/

#endif
