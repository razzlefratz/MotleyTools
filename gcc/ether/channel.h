/*====================================================================*
 *
 *   channel.h - raw packet channel definitions and declarations;
 *
 *   the channel structure contains information needed to perform
 *   raw packet I/O on specific platforms;
 *
 *.  Motley Tools by Charles Maier <cmaier@cmassoc.net>
 *:  Copyright (c) 1982-2006 by Charles Maier
 *;  Licensed under Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef CHANNEL_HEADER
#define CHANNEL_HEADER

/*====================================================================*
 *  system header files;
 *--------------------------------------------------------------------*/

#include <stdint.h>

/*====================================================================*
 *  custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/types.h"
#include "../ether/ether.h"

/*====================================================================*
 *   channel flagword bitmasks;
 *--------------------------------------------------------------------*/

#define CHANNEL_VERBOSE (1 << 0)
#define CHANNEL_SILENCE (1 << 1)
#define CHANNEL_WARNING (1 << 2)
#define CHANNEL_SUCCESS (1 << 3)
#define CHANNEL_FAILURE (1 << 4)

#define CHANNEL_UPDATE_TARGET (1 << 5) /* used by efsu only */
#define CHANNEL_UPDATE_SOURCE (1 << 6) /* used by efsu only */
#define CHANNEL_LISTEN (1 << 7)	       /* used by efsu only */

#define CHANNEL_ETHNUMBER 2
#if defined (__linux__)
#	define CHANNEL_ETHDEVICE "eth1"
#elif defined (__APPLE__)
#	define CHANNEL_ETHDEVICE "en0"
#	define CHANNEL_BPFDEVICE "/dev/bpf%d"
#elif defined (__OpenBSD__)
#	define CHANNEL_ETHDEVICE "bce0"
#	define CHANNEL_BPFDEVICE "/dev/bpf%d"
#else
#error "Unknown environment"
#endif

#define CHANNEL_LONGTIME (unsigned)(~0)
#define CHANNEL_TIMEOUT 15 
#define CHANNEL_TIMER 50 
#define CHANNEL_BAILOUT 0
#define CHANNEL_OPTIONS 0

/*====================================================================*
 *   common channel error messages;
 *--------------------------------------------------------------------*/

#define CHANNEL_CANTSEND "Send timeout or network error"    
#define CHANNEL_CANTREAD "Read timeout or network error"

/*====================================================================*
 *   channel ethertype definitions;
 *--------------------------------------------------------------------*/

#ifndef ETH_P_802_2
#define ETH_P_802_2 1
#endif

/*====================================================================*
 *   communication channel structure;
 *--------------------------------------------------------------------*/

typedef struct channel 

{
	signed fd;
	signed ifstate;
	signed ifindex;
	char const * ifname;
	uint8_t peer [ETHER_ADDR_LEN];
	uint8_t host [ETHER_ADDR_LEN];
	uint16_t type;

#if defined (__linux__)

#elif defined (__APPLE__) || defined (__OpenBSD__)

	signed bpf_length;
	uint8_t * bpf_buffer;
	uint8_t * bpf_bp;
	signed bpf_bufused;

#elif defined (WINPCAP) 

	pcap_t * socket;
	char errbuf [PCAP_ERRBUF_SIZE];

#else
#error "Unknown Environment"
#endif

	signed timeout;
	signed timer;
	flag_t flags;
}

CHANNEL;

/*====================================================================*
 *   channel functions;
 *--------------------------------------------------------------------*/

signed openchannel (struct channel *);
signed sendpacket (struct channel *, void * memory, size_t extent);
signed readpacket (struct channel *, void * memory, size_t extent);
signed closechannel (struct channel *);

/*====================================================================*
 *   
 *--------------------------------------------------------------------*/

#endif

