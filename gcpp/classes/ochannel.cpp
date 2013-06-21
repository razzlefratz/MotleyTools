/*====================================================================*
 *
 *   ochannel.cpp - ochannel class definition;
 *
 *   raw Ethernet packet I/O channel managment;
 *
 *   This software and documentation is the property of Intellon 
 *   Corporation, Ocala, Florida. It is provided 'as is' without 
 *   expressed or implied warranty of any kind to anyone for any 
 *   reason. Intellon assumes no responsibility or liability for 
 *   errors or omissions in the software or documentation and 
 *   reserves the right to make changes without notification. 
 *   
 *   Intellon customers may modify and distribute the software 
 *   without obligation to Intellon. Since use of this software 
 *   is optional, users shall bear sole responsibility and 
 *   liability for any consequences of it's use. 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *   Contributor(s): 
 *	    Charles Maier <charles.maier@intellon.com>
 *
 *--------------------------------------------------------------------*/

#ifndef oCHANNEL_SOURCE
#define oCHANNEL_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <iostream>
#if defined (WIN32)
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#else
#include <cstring>
#include <cstdlib>
#include <cerrno>
#endif

#include <net/ethernet.h>
#if defined (__linux__)
#	include <net/if_arp.h>
#	include <sys/socket.h>
#	include <sys/ioctl.h>
#	include <sys/poll.h>
#	include <linux/if_packet.h>
#	include <arpa/inet.h>
#elif defined (__APPLE__)
#	include <sys/types.h>
#	include <sys/socket.h>
#	include <net/if_dl.h>
#	include <ifaddrs.h>
#	include <sys/ioctl.h>
#	include <fcntl.h>
#elif defined (__OpenBSD__)
#	include <net/if_dl.h>
#	include <sys/poll.h>
#elif defined (LIBPCAP)
#	include <sys/poll.h>
#elif defined (WINPCAP)
#	include <netinet/in.h>
#else
#error "Unknown environment."
#endif

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/ochannel.hpp"
#include "../classes/omemory.hpp"
#include "../classes/oerror.hpp"

/*====================================================================*
 *
 *   signed Descriptor () const;
 *
 *   return the channel socket file descriptor;
 *
 *--------------------------------------------------------------------*/

signed ochannel::Descriptor () const 

{
	return (this->mfd);
}


/*====================================================================*
 *
 *   unsigned Timer () const;
 *
 *   return the channel timeout; 
 *
 *--------------------------------------------------------------------*/

unsigned ochannel::Timer () const 

{
	return (this->mtimer);
}


/*====================================================================*
 *
 *   ochannel & SetTimer (unsigned timer)
 *
 *   set the channel timeout in milliseconds;  
 *
 *--------------------------------------------------------------------*/

ochannel & ochannel::SetTimer (unsigned timer) 

{
	this->mtimer = timer;
	return (* this);
}


/*====================================================================*
 *
 *   ochannel & Open (ointerface & interface) 
 *
 *--------------------------------------------------------------------*/

ochannel & ochannel::Open (unsigned index) 

{
	ointerface::SetIndex (index);
	return (ochannel::Open ());
}


ochannel & ochannel::Open (char const * device) 

{
	ointerface::SetName (device);
	return (ochannel::Open ());
}


/*====================================================================*
 *
 *   ochannel & Open () 
 *
 *--------------------------------------------------------------------*/

ochannel & ochannel::Open () 

{

#if defined (__linux__) 

	struct ifreq ifreq;
	struct sockaddr_ll sockaddr_ll = 
	{
		PF_PACKET,
		0x0000,
		0x0000,
		ARPHRD_ETHER,
		PACKET_OTHERHOST,
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
	std::memset (& ifreq, 0, sizeof (ifreq));
	std::memcpy (ifreq.ifr_name, ointerface::Name (), sizeof (ifreq.ifr_name));
	if ((this->mfd = socket (sockaddr_ll.sll_family, SOCK_RAW, oethernet::Protocol ())) == -1) 
	{
		oerror::error (1, errno, "%s", ointerface::Name ());
	}
	if (bind (this->mfd, (struct sockaddr *) (& sockaddr_ll), sizeof (sockaddr_ll)) == -1) 
	{
		oerror::error (1, errno, "Can't bind socket to %s", ifreq.ifr_name);
	}
#if 1

	if (ioctl (this->mfd, SIOCGIFFLAGS, & ifreq) == -1) 
	{
		oerror::error (1, errno, "%s", ifreq.ifr_name);
	}
	ifreq.ifr_flags |= (IFF_UP | IFF_BROADCAST | IFF_MULTICAST);
	ifreq.ifr_flags &= ~IFF_ALLMULTI;
	if (ioctl (this->mfd, SIOCSIFFLAGS, & ifreq) == -1) 
	{
		oerror::error (1, errno, "%s", ifreq.ifr_name);
	}
#endif

#elif defined (__APPLE__)

	struct ifreq ifreq;
	struct timeval timer = 
	{
		0,
		0
	};
	static struct bpf_insn bpf_insn [] = 
	{
		{
			BPF_LD+ BPF_H + BPF_ABS,
			0,
			0,
			12
		},
		{
			BPF_JMP+ BPF_JEQ + BPF_K,
			0,
			13,
			ntohs (oCHANNEL_ETHERTYPE)
		},
		{
			BPF_LD+ BPF_B+BPF_ABS,
			0,
			0,
			0
		},
		{
			BPF_JMP+ BPF_JEQ+BPF_K,
			0,
			11,
			0
		},
		{
			BPF_LD+ BPF_B+BPF_ABS,
			0,
			0,
			1
		},
		{
			BPF_JMP+ BPF_JEQ+BPF_K,
			0,
			9,
			0
		},
		{
			BPF_LD+ BPF_B+BPF_ABS,
			0,
			0,
			2
		},
		{
			BPF_JMP+ BPF_JEQ+BPF_K,
			0,
			7,
			0
		},
		{
			BPF_LD+ BPF_B+BPF_ABS,
			0,
			0,
			3
		},
		{
			BPF_JMP+ BPF_JEQ+BPF_K,
			0,
			5,
			0
		},
		{
			BPF_LD+ BPF_B+BPF_ABS,
			0,
			0,
			4
		},
		{
			BPF_JMP+ BPF_JEQ+BPF_K,
			0,
			3,
			0
		},
		{
			BPF_LD+ BPF_B+BPF_ABS,
			0,
			0,
			5
		},
		{
			BPF_JMP+ BPF_JEQ+BPF_K,
			0,
			1,
			0
		},
		{
			BPF_RET+ BPF_K,
			0,
			0,
			4096
		},
		{
			BPF_RET+ BPF_K,
			0,
			0,
			0
		}
	};
	struct bpf_program bpf_program;
	char filename [sizeof (oCHANNEL_BPFDEVICE)];
	const uint8_t * hostaddr = ointerface::HostAddress ();
	unsigned count;
	unsigned state;
	for (count = 0; count < 100; count++) 
	{
		std::snprintf (filename, sizeof (filename), oCHANNEL_BPFDEVICE, count);
		if ((this->mfd =::open (filename, O_RDWR)) != -1) 
		{
			break;
		}
	}
	if (this->mfd == -1) 
	{
		oerror::error (1, ECANCELED, "No bpf counts available");
	}
	std::memcpy (ifreq.ifr_name, this->mname, sizeof (ifreq.ifr_name));
	if (ioctl (this->mfd, BIOCSETIF, & ifreq) == -1) 
	{
		oerror::error (1, errno, "%s", ifreq.ifr_name);
	}
	if (ioctl (this->mfd, BIOCGBLEN, & this->bpf_length) == -1) 
	{
		oerror::error (1, errno, "Can't determine buffer length");
	}
	state = true;
	if (ioctl (this->mfd, BIOCIMMEDIATE, & state) == -1) 
	{
		oerror::error (1, errno, "Can't activate immediate mode");
	}
	state = false;
	if (ioctl (this->mfd, BIOCSSEESENT, & state) == -1) 
	{
		oerror::error (1, errno, "Can't hide outgoing frames");
	}
	timer.tv_usec = this->mtimer * 1000;
	if (ioctl (this->mfd, BIOCSRTIMEOUT, & timer) == -1) 
	{
		oerror::error (1, errno, "Can't set timeout");
	}
	bpf_insn [3].k = hostaddr [0];
	bpf_insn [5].k = hostaddr [1];
	bpf_insn [7].k = hostaddr [2];
	bpf_insn [9].k = hostaddr [3];
	bpf_insn [11].k = hostaddr [4];
	bpf_insn [13].k = hostaddr [5];
	bpf_program.bf_len = sizeof (bpf_program)/sizeof (struct bpf_insn);
	bpf_program.bf_insns = bpf_insn;
	if (ioctl (this->mfd, BIOCSETF, & bpf_program) == -1) 
	{
		oerror::error (1, errno, "Can't use filter program");
	}
#elif defined (__OpenBSD__)

	struct ifreq ifreq;
	std::memset (& ifreq, 0, sizeof (ifreq));
	if ((this->mfd = std::socket (sockaddr->sdl_family, SOCK_RAW, oethernet::Protocol ())) == -1) 
	{
		oerror::error (1, errno, "%s", ointerface::Name ());
	}
	std::memcpy (ifreq.ifr_name, interface, sizeof (ifreq.ifr_name));

#if 0

	if (ioctl (this->mfd, SIOCGIFINDEX, & ifreq) == -1) 
	{
		oerror::error (1, errno, "%s", ifreq.ifr_name);
	}
	sockaddr->sdl_ifindex = ifreq.ifr_ifindex;
	if (ioctl (this->mfd, OSIOCGIFADDR, & ifreq) == -1) 
	{
		oerror::error (1, errno, "%s", ifreq.ifr_name);
	}
	std::memcpy (sockaddr->sdl_data, ifreq.ifr_ifru.ifru_addr.sa_data, sizeof (sockaddr->sdl_data));
	if (std::bind (this->mfd, (struct sockaddr *) (sockaddr), sizeof (struct sockaddr_dl)) == -1) 
	{
		oerror::error (1, errno, "Can't bind socket to %s", interface);
	}
#endif

	if (ioctl (this->mfd, SIOCGIFFLAGS, & ifreq) == -1) 
	{
		oerror::error (1, errno, "Can't read state of %s", ifreq.ifr_name);
	}
	if (!(ifreq.ifr_flags & IFF_UP)) 
	{
		ifreq.ifr_flags |= IFF_UP;
		ifreq.ifr_flags |= IFF_BROADCAST;
		ifreq.ifr_flags |= IFF_MULTICAST;
		ifreq.ifr_flags &= ~IFF_ALLMULTI;
		if (ioctl (this->mfd, SIOCSIFFLAGS, & ifreq) == -1) 
		{
			oerror::error (1, errno, "Can't save state of %s", ifreq.ifr_name);
		}
	}
#elif defined (WINPCAP)

	struct bpf_program bpf_program;
	this->msocket = pcap_open_live (ointerface::Name (), 65536, 0, this->mtimer, this->merrbuf);
	if (!this->msocket) 
	{
		oerror::error (1, errno, "can't open adaptor: %s", ointerface::Name ());
	}
	_snprintf (this->mfilter, sizeof (this->mfilter), "ether proto 0x%04x and not ether src %s", oethernet::Protocol (), ointerface::HardwareAddressString ());
	if (pcap_compile (this->msocket, & bpf_program, this->mfilter, 1, 0xffffff) < 0) 
	{
		oerror::error (1, errno, "Can't compile pcap filter: %s", ointerface::Name);
	}
	if (pcap_setfilter (this->msocket, & bpf_program) < 0) 
	{
		oerror::error (1, errno, "Can't install pcap filter: %s", ointerface::Name ());
	}
	if (pcap_setmintocopy (this->msocket, ETHER_MAX_LEN)) 
	{
		oerror::error (1, errno, "Can't set minimum data: %s", ointerface::Name ());
	}
#if 0

	if (pcap_setdirection (this->msocket, PCAP_D_IN)) 
	{
		oerror::error (1, errno, "Can't set packet direction: %s", ointerface::Name ());
	}
#endif

#else
#error "Unknown Environment."
#endif

	return (* this);
}


/*====================================================================*
 *
 *   signed SendPacket (void const * packet, signed length);
 *
 *--------------------------------------------------------------------*/

signed ochannel::SendPacket (void const * memory, signed extent) 

{
	if (this->anyset (oCHANNEL_FLAG_VERBOSE)) 
	{
		omemory::hexdump (memory, 0, extent, & std::cout);
	}
#if defined (__linux__)

	extent =::sendto (this->mfd, memory, extent, 0, (struct sockaddr *) (0), (socklen_t) (0));

#elif defined (__APPLE__)

	extent =::write (this->mfd, memory, extent);

#elif defined (__OpenBSD__)

	extent =::sendto (this->mfd, memory, extent, 0, (struct sockaddr *) (0), (socklen_t) (0));

#elif defined (WINPCAP) 

	if (pcap_sendpacket (this->msocket, (const u_char *)(memory), extent)) 
	{
		extent = -1;
	}
#else
#error "Unknown Environment."
#endif

	return (extent);
}


/*====================================================================*
 *
 *   signed ReadPacket (void * memory, signed extent);
 *
 *   encode external memory with an incoming Ethernet frame; return
 *   frame length on success, 0 on timeout or -1 on error;
 *
 *   on linux/osx, this method returns as soon as a frame arrives or
 *   once the timeout has expired; consequently, long timeout values
 *   do not affect performance;
 *
 *   on winpcap/libpcap, this method does not return until the timeout
 *   expires; consequenty, long timeout values do affect performance; 
 *
 *--------------------------------------------------------------------*/

signed ochannel::ReadPacket (void * memory, signed extent) 

{

#if defined (__linux__) 

	struct pollfd pollfd = 
	{
		this->mfd,
		POLLIN,
		0
	};
	int status =::poll (& pollfd, 1, this->mtimer);
	std::memset (memory, 0, extent);
	if (status < 0) 
	{
		oerror::error (0, errno, "poll");
		return (-1);
	}
	if (status > 0) 
	{
		extent =::recvfrom (this->mfd, memory, extent, 0, (struct sockaddr *) (0), (socklen_t *)(0));
		if (extent == -1) 
		{
			oerror::error (0, errno, "recvfrom");
			return (-1);
		}
		if (this->anyset (oCHANNEL_FLAG_VERBOSE)) 
		{
			omemory::hexdump (memory, 0, extent, & std::cout);
		}
		return (extent);
	}
#elif defined (__APPLE__) 

	uint8_t buffer [this->bpf_length];
	struct bpf_hdr * bpf_packet = (struct bpf_hdr *)(buffer);
	std::memset (memory, 0, extent);
	std::memset (buffer, 0, sizeof (buffer));
	extent = read (this->mfd, buffer, sizeof (buffer));
	if (extent < 0) 
	{
		oerror::error (0, errno, "bpf");
		return (-1);
	}
	if (extent > 0) 
	{
		extent = bpf_packet->bh_caplen;
		std::memcpy (memory, buffer + bpf_packet->bh_hdrlen, bpf_packet->bh_caplen);
		if (this->anyset (oCHANNEL_FLAG_VERBOSE)) 
		{
			omemory::hexdump (memory, 0, extent, & std::cout);
		}
		return (extent);
	}
#elif defined (__OpenBSD__) 

	struct::pollfd pollfd = 
	{
		this->mfd,
		POLLIN,
		0
	};
	int status =::poll (& pollfd, 1, this->timer);
	std::memset (memory, 0, extent);
	if (status < 0) 
	{
		oerror::error (0, errno, "poll");
		return (-1);
	}
	if (status > 0) 
	{
		extent =::recvfrom (this->mfd, memory, extent, 0, (struct sockaddr *) (0), (socklen_t *)(0));
		if (extent == -1) 
		{
			oerror::error (0, errno, "recvfrom");
			return (-1);
		}
		if (this->anyset (oCHANNEL_FLAG_VERBOSE)) 
		{
			omemory::hexdump (memory, 0, extent, & std::cout);
		}
		return (extent);
	}
#elif defined (WINPCAP)

	struct pcap_pkthdr * header;
	const uint8_t * data;
	unsigned elapsed = 0;
	do 
	{
		signed status = pcap_next_ex (this->msocket, & header, & data);
		std::memset (memory, 0, extent);
		if (status < 0) 
		{
			oerror::error (0, errno, "pcap_next_ex");
			return (-1);
		}
		if (status > 0) 
		{
			std::memcpy (memory, data, header->caplen);
			extent = header->caplen;
			if (this->anyset (oCHANNEL_FLAG_VERBOSE)) 
			{
				omemory::hexdump (memory, 0, extent, & std::cout);
			}
			return (extent);
		}
		elapsed+= oCHANNEL_TIMEOUT;
	}
	while (elapsed < this->mtimer);

#elif defined (LIBPCAP)

	struct pcap_pkthdr * header;
	const uint8_t * data;
	struct pollfd pollfd = 
	{
		this->mfd,
		POLLIN,
		0
	};
	signed status = poll (& pollfd, 1, this->timer);
	std::memset (memory, 0, extent);
	if (status < 0) 
	{
		oerror::error (0, errno, "poll");
		return (-1);
	}
	if (status > 0) 
	{
		status = pcap_next_ex (this->msocket, & header, & data);
		if (status != 1) 
		{
			oerror::error (0, errno, "pcap_next_ext");
			return (-1);
		}
		std::memcpy (memory, data, header->caplen);
		extent = header->caplen;
		if (this->anyset (oCHANNEL_FLAG_VERBOSE)) 
		{
			omemory::hexdump (memory, 0, extent, & std::cout);
		}
		return (extent);
	}
#else
#error "Unknown environment."
#endif

	return (0);
}


/*====================================================================*
 *
 *   ochannel & Close () ;
 *
 *--------------------------------------------------------------------*/

ochannel & ochannel::Close () 

{

#if defined (WINPCAP) 

	pcap_close (this->msocket);

#else
::
	close (this->mfd);

#endif

	return (* this);
}


/*====================================================================*
 *
 *   ochannel & Print();
 *
 *--------------------------------------------------------------------*/

ochannel & ochannel::Print () 

{
	ointerface::Print ();
	oethernet::Print ();
	return (* this);
}


/*====================================================================*
 *
 *   ochannel () 
 *
 *--------------------------------------------------------------------*/

ochannel::ochannel () 

{
	ointellon intellon;
	oethernet::SetPeerAddress (intellon.PeerAddress ());
	oethernet::SetHostAddress (intellon.HostAddress ());
	oethernet::SetProtocol (intellon.Protocol ());
	this->mtimer = oCHANNEL_TIMEOUT;
	return;
}


/*====================================================================*
 *
 *   ~ochannel () 
 *
 *--------------------------------------------------------------------*/

ochannel::~ochannel () 

{
	ochannel::Close ();
	return;
}


/*====================================================================*
 *   end definition;
 *--------------------------------------------------------------------*/

#endif

