/*====================================================================*
 *
 *   ethcat.c - 
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

#include <stdlib.h>
#include <limits.h>
#include <memory.h>
#include <signal.h>
#include <termios.h>
#include <unistd.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/getoptv.h"
#include "../tools/putoptv.h"
#include "../tools/memory.h"
#include "../tools/number.h"
#include "../tools/error.h"
#include "../tools/flags.h"
#include "../ether/ether.h"
#include "../ether/channel.h"
#include "../files/files.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../tools/efreopen.c"
#include "../tools/uintspec.c"
#include "../tools/todigit.c"
#include "../tools/hexdump.c"
#include "../tools/hexencode.c"
#include "../tools/error.c"
#endif

#ifndef MAKEFILE
#include "../ether/channel.c"
#include "../ether/openchannel.c"
#include "../ether/closechannel.c"
#include "../ether/readpacket.c"
#include "../ether/sendpacket.c"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define ETHDEVICE "ETH"

/*====================================================================*
 *
 *   signed function (struct channel * channel, signed fd);
 *
 *   copy fd to channel as a series of IEEE 802.3 Ethernet frames;
 *   struct ethernet_frame is defined in ether/ether.h; 
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

signed function(struct channel * channel, signed fd)

{
	struct ethernet_frame frame;
	signed bytes;
	memcpy (frame.frame_dhost, channel->peer, sizeof(frame.frame_dhost));
	memcpy (frame.frame_shost, channel->host, sizeof(frame.frame_shost));
	while ((bytes = read(fd, frame.frame_body, sizeof(frame.frame_body))) > 0)
	{
		frame.frame_type = htons(bytes);
		if (bytes < ETHERMIN)
		{
			bytes = ETHERMIN;
		}
		bytes += ETHER_HDR_LEN;
		if (sendpacket(channel, & frame, bytes) != bytes)
		{
			error (1, errno, CHANNEL_CANTSEND);
		}
		sleep (1);
	}
	return (0);
}

/*====================================================================*
 *
 *   int main (int argc, char const * argv []);
 *
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

int main(int argc, char const * argv[])

{
	extern struct channel channel;
	static char const * optv[] = 
	{
		"d:i:qt:v",
		PUTOPTV_S_FUNNEL,
		"copy one or more files to a serial device",
		"d x\tdestination address is (x) [00:B0:52:00:00:01]",
		"i s\tuse host interface (s) [" LITERAL(CHANNEL_ETHDEVICE) "]",
		"t n\tread timeout is (n) milliseconds [" LITERAL(CHANNEL_TIMEOUT) "]",
		"q\tquiet mode",
		"v\tverbose mode",
		(char const *) (0)
	};
	signed c;
	if (getenv(ETHDEVICE))
	{
		channel.ifname = getenv(ETHDEVICE);
	}
	while (~ (c = getoptv(argc, argv, optv)))
	{
		switch (c)
		{
		case 'd':
			hexencode (channel.peer, sizeof(channel.peer), optarg);
			break;
		case 'i':
			channel.ifname = optarg;
			break;
		case 'q':
			_setbits (channel.flags, CHANNEL_SILENCE);
			break;
		case 't':
			channel [.] timer = (unsigned) (uintspec(optarg, 0, UINT_MAX));
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
	openchannel (& channel);
	if (! argc)
	{
		function (& channel, STDIN_FILENO);
	}
	while ((argc) && (* argv))
	{
		if (efreopen(* argv, "rb", stdin))
		{
			function (& channel, STDIN_FILENO);
		}
		argc--;
		argv++;
	}
	closechannel (& channel);
	exit (0);
}

