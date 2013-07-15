/*====================================================================*
 *
 *   efru.c - 802.2 Ethernet Frame Data Capture
 *   
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

#define _GETOPT_H

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <fcntl.h>
#include <stdio.h>
#include <limits.h>
#include <ctype.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#ifdef __linux__
#include <net/if.h>
#include <net/if_arp.h>
#include <netpacket/packet.h>
#include <signal.h>
#endif

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/getoptv.h"
#include "../tools/putoptv.h"
#include "../tools/memory.h"
#include "../tools/number.h"
#include "../tools/types.h"
#include "../tools/flags.h"
#include "../tools/error.h"
#include "../ether/channel.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../tools/hexdump.c"
#include "../tools/hexdecode.c"
#include "../tools/hexstring.c"
#include "../tools/uintspec.c"
#include "../tools/basespec.c"
#include "../tools/todigit.c"
#include "../tools/error.c"
#endif

#ifndef MAKEFILE
#include "../ether/channel.c"
#include "../ether/openchannel.c"
#include "../ether/closechannel.c"
#include "../ether/sendpacket.c"
#include "../ether/readpacket.c"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define ETHDEVICE "ETH"

/*====================================================================*
 *   
 *   int main (int argc, char * argv[]);
 *   
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv []) 

{ 
	extern struct channel channel; 
	struct ethernet_frame frame; 
	static char const * optv [] = 
	{ 
		"i:qt:v", 
		PUTOPTV_S_DIVINE, 
		"802.3 Ethernet Frame Data Streamer", 
		"e x\tethertype is (x) [" LITERAL (ETH_P_802_2) "]", 
		"i n\tuse host interface n [" LITERAL (CHANNEL_ETHDEVICE) "]", 
		"q\tsuppress normal output", 
		"t n\tread timeout is (n) milliseconds [" LITERAL (CHANNEL_TIMEOUT) "]", 
		"v\tverbose messages on stdout", 
		(char const *) (0)
	}; 
	signed c; 
	if (getenv (ETHDEVICE)) 
	{ 
		channel.ifname = strdup (getenv (ETHDEVICE)); 
	} 
	channel.type = ETH_P_802_2; 
	channel.timer = - 1; 
	while ((c = getoptv (argc, argv, optv)) != - 1) 
	{ 
		switch (c) 
		{ 
		case 'e': 
			channel.type = (uint16_t)(basespec (optarg, 16, sizeof (channel.type))); 
			break; 
		case 'i': 
			channel.ifname = optarg; 
			break; 
		case 'q': 
			_setbits (channel.flags, CHANNEL_SILENCE); 
			break; 
		case 't': 
			channel.timer = (unsigned)(uintspec (optarg, 0, UINT_MAX)); 
			break; 
		case 'v': 
			_setbits (channel.flags, CHANNEL_VERBOSE); 
			break; 
		default: 
			break; 
		} 
	} 
	argc -= optind; 
	argv += optind; 
	if (geteuid ()) 
	{ 
		error (1, EPERM, ERROR_NOTROOT); 
	} 
	openchannel (& channel); 
	while (readpacket (& channel, & frame, sizeof (frame)) > 0) 
	{ 
		write (STDOUT_FILENO, frame.frame_body, ntohs (frame.frame_type)); 
	} 
	closechannel (& channel); 
	return (0); 
} 

