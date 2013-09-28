/*====================================================================*
 *
 *   ochannel.hpp - interface for the ochannel class
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

#ifndef oCHANNEL_HEADER
#define oCHANNEL_HEADER

/*====================================================================*
 *  system header files;
 *--------------------------------------------------------------------*/

#include <stdint.h>
#include <net/if.h>
#if defined (__linux__)
#elif defined (__APPLE__)
#	include <sys/types.h>
#	include <sys/socket.h>
#	include <net/bpf.h>
#elif defined (__OpenBSD__)
#elif defined(WINPCAP)
#	include <pcap.h>
#	include <pcap/Packet32.h>
#	include <pcap/ntddndis.h>
#elif defined(LIBPCAP)
#	include <pcap/pcap.h>
#else
#error "Unknown environment."
#endif

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/oflagword.hpp"
#include "../classes/ointerface.hpp"
#include "../classes/oethernet.hpp"
#include "../classes/ointellon.hpp"

/*====================================================================*
 *   class constants;
 *--------------------------------------------------------------------*/

#define oCHANNEL_FLAG_VERBOSE (1 << 0)
#define oCHANNEL_FLAG_SILENCE (1 << 1)
#define oCHANNEL_FLAG_WARNING (1 << 2)
#define oCHANNEL_FLAG_SUCCESS (1 << 3)
#define oCHANNEL_FLAG_FAILURE (1 << 4)
#define oCHANNEL_FLAG_UPDATE_TARGET (1 << 5)
#define oCHANNEL_FLAG_UPDATE_SOURCE (1 << 6)
#define oCHANNEL_FLAG_LISTEN (1 << 7)

#define oCHANNEL_ETHERTYPE 0x88E1
#define oCHANNEL_BPFDEVICE "/dev/bpf%d"
#define oCHANNEL_TIMEOUT 100
#define oCHANNEL_BAILOUT 0
#define oCHANNEL_OPTIONS 0

#define oCHANNEL_CANTREAD "Read timeout or network error"
#define oCHANNEL_CANTSEND "Send timeout or network error"

/*====================================================================*
 *   class declaration;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) ochannel: public oflagword, public ointerface, public oethernet

{
public: 
	ochannel ();
	ochannel (char const * name);
	virtual ~ ochannel ();
	signed Descriptor () const;
	unsigned Timer () const;
	ochannel & SetTimer (unsigned);
	ochannel & Open ();
	ochannel & Open (unsigned);
	ochannel & Open (char const *);
	signed SendPacket (void const * memory, signed extent);
	signed ReadPacket (void * memory, signed extent);
	ochannel & Close ();
	ochannel & Print ();
private: 
	signed mfd;
	unsigned mtimer;

#if defined (__APPLE__)

	unsigned bpf_length;

#elif defined (WINPCAP)

	pcap_t * msocket;
	char merrbuf [PCAP_ERRBUF_SIZE];
	char mfilter [255];

#endif

};

/*====================================================================*
 *   end definition;
 *--------------------------------------------------------------------*/

#endif



