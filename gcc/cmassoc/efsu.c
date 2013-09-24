/*====================================================================*
 *
 *   efsu.c - Ethernet Frame Send Utility;
 *
 *   convert hexadecimal text files to ethernet frames and transmit
 *   them over the network; basically, it is a 'send your own frame'
 *   utility; 
 *
 *   the program works like cat, sending file after file to a given
 *   interface; as each file is read, all hexadecimal octets in the
 *   file are converted to bytes and buffered; a semicolon causes a
 *   buffer transmit as does the end of file; script-style comments
 *   starting with hash (#) and c-language-style comments starting
 *   with slash-slash or slash-asterisk are consumed and discard as
 *   the file is read; the errors that can occur are non-hex digits
 *   and odd number of hex digits;
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
#include <string.h>
#include <limits.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/getoptv.h"
#include "../tools/putoptv.h"
#include "../tools/error.h"
#include "../tools/memory.h"
#include "../tools/number.h"
#include "../tools/symbol.h"
#include "../tools/flags.h"
#include "../ether/channel.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../tools/error.c"
#include "../tools/hexencode.c"
#include "../tools/hexload.c"
#include "../tools/hexdump.c"
#include "../tools/todigit.c"
#include "../tools/uintspec.c"
#include "../tools/basespec.c"
#endif

#ifndef MAKEFILE
#include "../ether/openchannel.c"
#include "../ether/closechannel.c"
#include "../ether/readpacket.c"
#include "../ether/sendpacket.c"
#include "../ether/channel.c"
#endif

/*====================================================================*
 *   program contants;
 *--------------------------------------------------------------------*/

#define ETHDEVICE "ETH"
#define EFSU_PAUSE 0
#define EFSU_DELAY 0
#define EFSU_COUNT 1

/*====================================================================*
 *   
 *   void function (struct channel * channel, void * memory, ssize_t extent);
 *
 *   read Ethernet frame descriptions from stdin and transmit them 
 *   as raw ethernet frames; wait for a response if CHANNEL_LISTEN
 *   flagword bit is set;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void function (struct channel * channel, void * memory, ssize_t extent)

{
	struct ether_header * frame = (struct ether_header *)(memory);
	unsigned length;
	while ((length = (unsigned)(hexload (memory, extent, stdin))) > 0)
	{
		if (length < (ETHER_MIN_LEN - ETHER_CRC_LEN))
		{
			error (1, ENOTSUP, "Frame size of %d is less than %d bytes", length, (ETHER_MIN_LEN - ETHER_CRC_LEN));
		}
		if (length > (ETHER_MAX_LEN - ETHER_CRC_LEN))
		{
			error (1, ENOTSUP, "Frame size of %d is more than %d bytes", length, (ETHER_MAX_LEN - ETHER_CRC_LEN));
		}
		if (_anyset (channel->flags, CHANNEL_UPDATE_TARGET))
		{
			memcpy (frame->ether_dhost, channel->peer, sizeof (frame->ether_dhost));
		}
		if (_anyset (channel->flags, CHANNEL_UPDATE_SOURCE))
		{
			memcpy (frame->ether_shost, channel->host, sizeof (frame->ether_shost));
		}
		sendpacket (channel, memory, length);
		if (_anyset (channel->flags, CHANNEL_LISTEN))
		{
			while (readpacket (channel, memory, extent) > 0);
		}
	}
	return;
}

/*====================================================================*
 *   
 *   void iterate (int argc, char const * argv [], void * memory, ssize_t extent, unsigned pause);
 *
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void iterate (int argc, char const * argv [], struct channel * channel, unsigned pause)

{
	byte buffer [ETHER_MAX_LEN];
	if (! argc)
	{
		function (channel, buffer, sizeof (buffer));
	}
	while ((argc) && (* argv))
	{
		if (! freopen (* argv, "rb", stdin))
		{
			error (1, errno, "Can't open %s", * argv);
		}
		function (channel, buffer, sizeof (buffer));
		argc--;
		argv++;
		if ((argc) && (* argv))
		{
			sleep (pause);
		}
	}
	return;
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

int main (int argc, char const * argv [])

{
	extern struct channel channel;
	static char const * optv [] = 
	{
		"d:hi:l:p:t:vw:",
		PUTOPTV_S_FUNNEL,
		"Ethernet Frame Send Utility",
		"d x\treplace destination address with (x)",
		"h\treplace source address with host address",
		"i s\tuse host interface (s) [" LITERAL (CHANNEL_ETHDEVICE) "]",
		"l n\trepeat file sequence (n) times [" LITERAL (EFSU_COUNT) "]",
		"p n\twait (n) seconds between files [" LITERAL (EFSU_PAUSE) "]",
		"t n\tread timeout is (n) milliseconds [" LITERAL (CHANNEL_TIMEOUT) "]",
		"v\tverbose messages",
		"w n\twait (n) seconds between counts [" LITERAL (EFSU_DELAY) "]",
		(char const *) (0)
	};
	unsigned pause = EFSU_PAUSE;
	unsigned delay = EFSU_DELAY;
	unsigned count = EFSU_COUNT;
	signed c;
	if (getenv (ETHDEVICE))
	{
		channel.ifname = strdup (getenv (ETHDEVICE));
	}
	while (~ (c = getoptv (argc, argv, optv)))
	{
		switch (c)
		{
		case 'd':
			_setbits (channel.flags, CHANNEL_UPDATE_TARGET);
			if (! hexencode (channel.peer, sizeof (channel.peer), optarg))
			{
				error (1, errno, "%s", optarg);
			}
			break;
		case 'h':
			_setbits (channel.flags, CHANNEL_UPDATE_SOURCE);
			break;
		case 'i':
			channel.ifname = optarg;
			break;
		case 'l':
			count = (unsigned)(uintspec (optarg, 0, UINT_MAX));
			break;
		case 'p':
			pause = (unsigned)(uintspec (optarg, 0, 1200));
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
		case 'w':
			delay = (unsigned)(uintspec (optarg, 0, 1200));
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
	while (count--)
	{
		iterate (argc, argv, & channel, pause);
		if (count)
		{
			sleep (delay);
		}
	}
	closechannel (& channel);
	return (0);
}

