/*====================================================================*
 *
 *   ether.h - Ethernet definitions and declarations;
 *
 *   include or exclude various ethernet related definitions based 
 *   platform and environment;
 *
 *.  Motley Tools by Charles Maier <cmaier@cmassoc.net>
 *:  Copyright (c) 1982-2006 by Charles Maier
 *;  Licensed under Internet Software Consortium License
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

#ifndef ETHER_HEADER
#define ETHER_HEADER

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <stdint.h>
#if defined (__linux__)
#	include <net/if.h>
#	include <net/ethernet.h>
#	include <arpa/inet.h>
#elif defined (__APPLE__)
#	include <sys/types.h>
#	include <sys/socket.h>
#	include <net/if.h>
#	include <net/ethernet.h>
#	include <arpa/inet.h>
#	include <net/bpf.h>
#elif defined (__OpenBSD__)
#	include <sys/ioctl.h>
#	include <sys/types.h>
#	include <sys/socket.h>
#	include <net/if.h>
#	include <netinet/in.h>
#	include <netinet/if_ether.h>
#	include <net/bpf.h>
#	include <fcntl.h>
#elif defined (WIN32)
#	if defined (WINPCAP)
#		include <pcap.h>
#		include <pcap/Packet32.h>
#		include <pcap/Ntddndis.h>
#	endif
#	include <net/ethernet.h>
#	include <net/if.h>
#else
#error "Unknown environment"
#endif

#ifndef ETH_CRC_LEN
#define ETH_CRC_LEN 4 /* normally defined in ethernet.h or if_ether.h */
#endif

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/types.h"

/*====================================================================*
 *   variables;
 *--------------------------------------------------------------------*/

struct nic 

{
	unsigned ifindex;
	byte ethernet [ETHER_ADDR_LEN];
	byte internet [4];
	char ifname [IF_NAMESIZE];
	char ifdesc [255];
}

NIC;

/*====================================================================*
 *   basic 802.2 Ethernet frame structure;
 *--------------------------------------------------------------------*/

#ifndef __GNUC__
#pragma pack (push, 1)
#endif

typedef struct ethernet_frame 

{
	byte frame_dhost [ETHER_ADDR_LEN];
	byte frame_shost [ETHER_ADDR_LEN];
	uint16_t frame_type;
	byte frame_body [ETHERMTU];
}

FRAME;

#ifndef __GNUC__
#pragma pack (pop)
#endif

/*====================================================================*
 *   functions;
 *--------------------------------------------------------------------*/

char * getifname (signed number);
signed gethwaddr (void * memory, char const * device);
signed anynic (char buffer [], unsigned length);
unsigned hostnics (struct nic list [], unsigned size);

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif

