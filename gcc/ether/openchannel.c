/*====================================================================*
 *
 *   signed openchannel (struct channel * channel);
 *
 *   channel.h
 *
 *   open a raw ethernet channel;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under GNU General Public License Version 2 Only;
 *
 *--------------------------------------------------------------------*/

#ifndef OPENCHANNEL_SOURCE
#define OPENCHANNEL_SOURCE

#include <unistd.h>
#include <memory.h>
#include <errno.h>

#if defined (__linux__)
#	include <net/if_arp.h>
#	include <netpacket/packet.h>
#	include <sys/ioctl.h>
#elif defined (__APPLE__)
#	include <sys/ioctl.h>
#	include <fcntl.h>
#	include <stdlib.h>
#elif defined (__OpenBSD__)
#	include <sys/ioctl.h>
#	include <stdlib.h>
#elif defined (WINPCAP) 
#	include <string.h>
#else
#error "Unknown environment"
#endif

#include "../ether/channel.h"
#include "../tools/memory.h"
#include "../tools/flags.h"
#include "../tools/error.h"

#if defined (__APPLE__) || defined (__OpenBSD__)
#include "../ether/gethwaddr.c"
#endif

signed openchannel (struct channel * channel) 

{

#if defined (__linux__) 

	struct ifreq ifreq;
	struct sockaddr_ll sockaddr_ll = 
	{
		PF_PACKET,
		0x0000,
		0x0000,
		ARPHRD_ETHER,
		PACKET_HOST,
		ETHER_ADDR_LEN,
		{
			0x00,
			0x00,
			0x00,
			0x00,
			0x00,
			0x00,
			0x00,
			0x00
		}
	};
	memset (&ifreq, 0, sizeof (ifreq));
	sockaddr_ll.sll_protocol = htons (channel->type);
	if ((channel->fd = socket (sockaddr_ll.sll_family, SOCK_RAW, sockaddr_ll.sll_protocol)) == -1) 
	{
		error (1, errno, "%s can't open %s", __func__, channel->ifname);
	}
	memcpy (ifreq.ifr_name, channel->ifname, sizeof (ifreq.ifr_name));
	if (ioctl (channel->fd, SIOCGIFINDEX, &ifreq) == -1) 
	{
		error (1, errno, "%s can't read index: %s", __func__, ifreq.ifr_name);
	}
	channel->ifindex = sockaddr_ll.sll_ifindex = ifreq.ifr_ifindex;
	if (ioctl (channel->fd, SIOCGIFHWADDR, &ifreq) == -1) 
	{
		error (1, errno, "%s can't read %s address", __func__, ifreq.ifr_name);
	}
	memcpy (sockaddr_ll.sll_addr, ifreq.ifr_ifru.ifru_hwaddr.sa_data, sizeof (sockaddr_ll.sll_addr));
	if (bind (channel->fd, (struct sockaddr *) (&sockaddr_ll), sizeof (sockaddr_ll)) == -1) 
	{
		error (1, errno, "%s can't bind %s socket", __func__, ifreq.ifr_name);
	}
	memcpy (channel->host, sockaddr_ll.sll_addr, sizeof (channel->host));
	if (ioctl (channel->fd, SIOCGIFFLAGS, &ifreq) == -1) 
	{
		error (1, errno, "%s can't read %s state", __func__, ifreq.ifr_name);
	}
	channel->ifstate = ifreq.ifr_flags;
	_setbits (ifreq.ifr_flags, (IFF_UP | IFF_BROADCAST | IFF_MULTICAST));
	_clrbits (ifreq.ifr_flags, (IFF_ALLMULTI | IFF_PROMISC));
	if (ioctl (channel->fd, SIOCSIFFLAGS, &ifreq) == -1) 
	{
		error (1, errno, "%s can't save %s state", __func__, ifreq.ifr_name);
	}

#else

	struct bpf_program bpf_program;
	static struct bpf_insn bpf_insn [] = 
	{
		{
			BPF_LD + BPF_H + BPF_ABS,
			0,
			0,
			12
		},
		{
			BPF_JMP + BPF_JEQ + BPF_K,
			0,
			18,
			0
		},
		{
			BPF_LD + BPF_B + BPF_ABS,
			0,
			0,
			0
		},
		{
			BPF_JMP + BPF_JEQ + BPF_K,
			0,
			10,
			0
		},
		{
			BPF_LD + BPF_B + BPF_ABS,
			0,
			0,
			1
		},
		{
			BPF_JMP + BPF_JEQ + BPF_K,
			0,
			8,
			0
		},
		{
			BPF_LD + BPF_B + BPF_ABS,
			0,
			0,
			2
		},
		{
			BPF_JMP + BPF_JEQ + BPF_K,
			0,
			6,
			0
		},
		{
			BPF_LD + BPF_B + BPF_ABS,
			0,
			0,
			3
		},
		{
			BPF_JMP + BPF_JEQ + BPF_K,
			0,
			4,
			0
		},
		{
			BPF_LD + BPF_B + BPF_ABS,
			0,
			0,
			4
		},
		{
			BPF_JMP + BPF_JEQ + BPF_K,
			0,
			2,
			0
		},
		{
			BPF_LD + BPF_B + BPF_ABS,
			0,
			0,
			5
		},
		{
			BPF_JMP + BPF_JEQ + BPF_K,
			4,
			0,
			0
		},
		{
			BPF_LD + BPF_W + BPF_ABS,
			0,
			0,
			0
		},
		{
			BPF_JMP + BPF_JEQ + BPF_K,
			0,
			4,
			0xFFFFFFFF
		},
		{
			BPF_LD + BPF_H + BPF_ABS,
			0,
			0,
			4
		},
		{
			BPF_JMP + BPF_JEQ + BPF_K,
			0,
			2,
			0xFFFF
		},
		{
			BPF_LD + BPF_W + BPF_LEN,
			0,
			0,
			0
		},
		{
			BPF_RET + BPF_A,
			0,
			0,
			0
		},
		{
			BPF_RET + BPF_K,
			0,
			0,
			0
		}
	};

#if defined (__APPLE__) || defined (__OpenBSD__)

	struct ifreq ifreq;
	struct timeval timeout = 
	{
		0,
		0
	};
	char filename [sizeof (CHANNEL_BPFDEVICE) + 1];
	unsigned count;
	unsigned state;
	for (count = 0; count < 100; count++) 
	{
		snprintf (filename, sizeof (filename), CHANNEL_BPFDEVICE, count);
		if ((channel->fd = open (filename, O_RDWR)) != -1) 
		{
			break;
		}
	}
	if (channel->fd == -1) 
	{
		error (1, ECANCELED, "No free bpf devices");
	}
	memcpy (ifreq.ifr_name, channel->ifname, sizeof (ifreq.ifr_name));
	if (ioctl (channel->fd, BIOCSETIF, &ifreq) == -1) 
	{
		error (1, errno, "%s", ifreq.ifr_name);
	}
	if (ioctl (channel->fd, BIOCGBLEN, &channel->bpf_length) == -1) 
	{
		error (1, errno, "Can't determine %s buffer length", ifreq.ifr_name);
	}
	channel->bpf_buffer = malloc (channel->bpf_length);
	if (channel->bpf_buffer == NULL) 
	{
		error (1, errno, "Can't allocate %s receive buffer", ifreq.ifr_name);
	}
	channel->bpf_bp = channel->bpf_buffer;

#if defined (__APPLE__)

	state = 0;
	if (ioctl (channel->fd, BIOCSSEESENT, &state) == -1) 
	{
		error (1, errno, "%s can't hide outgoing %s frames", __func__, ifreq.ifr_name);
	}

#elif defined (__OpenBSD__)

	state = BPF_DIRECTION_OUT;
	if (ioctl (channel->fd, BIOCSDIRFILT, &state) == -1) 
	{
		error (0, errno, "Can't hide outgoing frames");
	}

#else
#error "Abandon all hope"
#endif

#if defined (__MAC_10_6)

/*
 *	accommodate known bug in BPF on MAC OS X 10.6; shorter times cause socket read
 *	operations to block indefinitely if no frames are waiting because tv_usec gets
 *      clobbered;
 */

	timeout.tv_sec = 1;

#else

	timeout.tv_usec = channel->timeout * 1000;

#endif

	if (ioctl (channel->fd, BIOCSRTIMEOUT, &timeout) == -1) 
	{
		error (1, errno, "%s can't set %s channel timeout", __func__, ifreq.ifr_name);
	}
	state = 1;
	if (ioctl (channel->fd, BIOCIMMEDIATE, &state) == -1) 
	{
		error (1, errno, "%s can't set %s immediate mode", __func__, ifreq.ifr_name);
	}

#if 1

	gethwaddr (channel->host, channel->ifname);

#else

	if (ioctl (channel->fd, SIOCGIFADDR, &ifreq) > 0) 
	{
		error (1, errno, "%s", ifreq.ifr_name);
	}
	memcpy (channel->host, LLADDR (ifreq.ifr_ifru.ifru_addr), sizeof (channel->host));

#endif

	bpf_program.bf_len = sizeof (bpf_insn) / sizeof (struct bpf_insn);
	bpf_program.bf_insns = bpf_insn;
	if (channel->type == ETH_P_802_2) 
	{
		bpf_insn [1].code = BPF_JMP + BPF_JGT + BPF_K;
		bpf_insn [1].jt = 18;
		bpf_insn [1].jf = 0;
		bpf_insn [1].k = ETHERMTU;
	}
	else 
	{
		bpf_insn [1].code = BPF_JMP + BPF_JEQ + BPF_K;
		bpf_insn [1].jt = 0;
		bpf_insn [1].jf = 18;
		bpf_insn [1].k = channel->type;
	}
	bpf_insn [3].k = channel->host [0];
	bpf_insn [5].k = channel->host [1];
	bpf_insn [7].k = channel->host [2];
	bpf_insn [9].k = channel->host [3];
	bpf_insn [11].k = channel->host [4];
	bpf_insn [13].k = channel->host [5];
	if (ioctl (channel->fd, BIOCSETF, &bpf_program) == -1) 
	{
		error (1, errno, "%s can't store %s filter", __func__, channel->ifname);
	}

#elif defined (WINPCAP) || defined (LIBPCAP)

	channel->ifname = getifname (channel->ifindex);
	gethwaddr (channel->host, channel->ifname);
	channel->socket = pcap_open_live (channel->ifname, 65536, 0, channel->timeout, channel->errbuf);
	snprintf ((char *)(channel->ifname), strlen (channel->ifname), "nic%d", channel->ifindex);
	if (!channel->socket) 
	{
		error (1, errno, "%s can't open %s interface", __func__, channel->ifname);
	}
	bpf_program.bf_len = sizeof (bpf_insn)/sizeof (struct bpf_insn);
	bpf_program.bf_insns = bpf_insn;
	if (channel->type == ETH_P_802_2) 
	{
		bpf_insn [1].code = BPF_JMP + BPF_JGT + BPF_K;
		bpf_insn [1].jt = 18;
		bpf_insn [1].jf = 0;
		bpf_insn [1].k = ETHERMTU;
	}
	else 
	{
		bpf_insn [1].code = BPF_JMP + BPF_JEQ + BPF_K;
		bpf_insn [1].jt = 0;
		bpf_insn [1].jf = 18;
		bpf_insn [1].k = channel->type;
	}
	bpf_insn [3].k = channel->host [0];
	bpf_insn [5].k = channel->host [1];
	bpf_insn [7].k = channel->host [2];
	bpf_insn [9].k = channel->host [3];
	bpf_insn [11].k = channel->host [4];
	bpf_insn [13].k = channel->host [5];
	if (pcap_setfilter (channel->socket, &bpf_program) < 0) 
	{
		error (1, errno, "%s can't store %s filter", __func__, channel->ifname);
	}
	if (pcap_setmintocopy (channel->socket, ETHER_MIN_LEN) < 0) 
	{
		error (1, errno, "%s can't set %s pcap mintocopy", __func__, channel->ifname);
	}

#else
#error "Unknown Environment"
#endif
#endif

	return (0);
}


#endif

