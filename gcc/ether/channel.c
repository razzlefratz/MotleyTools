/*====================================================================*
 *
 *   channel.c - global channel structure;
 *
 *   channel.h
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef CHANNEL_SOURCE
#define CHANNEL_SOURCE

#include "../ether/channel.h"
#include "../ether/ether.h"

struct channel channel = 

{
	(file_t)(-1),
	0,
	CHANNEL_ETHNUMBER,
	CHANNEL_ETHDEVICE,
	{
		0x00,
		0xB0,
		0x52,
		0x00,
		0x00,
		0x01
	},
	{
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00
	},
	ETH_P_802_2,

#if defined (__linux__)

#elif defined (__APPLE__) || defined (__OpenBSD__)

	0,
	0,
	0,
	0,

#elif defined (WINPCAP) || defined (LIBPCAP)

	(pcap_t *)(0),
	{
		0
	},

#else
#error "Unknown Environment"
#endif

	CHANNEL_TIMEOUT,
	CHANNEL_TIMER,
	CHANNEL_OPTIONS
};


#endif

