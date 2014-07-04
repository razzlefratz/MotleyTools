/*====================================================================*
 *
 *   oconnect.hpp - interface for the oconnect class
 *
 *   raw Ethernet packet I/O channel managment;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oCONNECT_HEADER
#define oCONNECT_HEADER

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

/*====================================================================*
 *   class constants;
 *--------------------------------------------------------------------*/

#define oCONNECT_FLAG_VERBOSE (1 << 0)
#define oCONNECT_FLAG_SILENCE (1 << 1)
#define oCONNECT_FLAG_WARNING (1 << 2)
#define oCONNECT_FLAG_SUCCESS (1 << 3)
#define oCONNECT_FLAG_FAILURE (1 << 4)
#define oCONNECT_FLAG_UPDATE_TARGET (1 << 5)
#define oCONNECT_FLAG_UPDATE_SOURCE (1 << 6)
#define oCONNECT_FLAG_LISTEN (1 << 7)

#define oCONNECT_ETHERTYPE 0x88E1
#define oCONNECT_BPFDEVICE "/dev/bpf%d"
#define oCONNECT_TIMEOUT 100
#define oCONNECT_BAILOUT 0
#define oCONNECT_OPTIONS 0

#define oCONNECT_CANTREAD "Read timeout or network error"
#define oCONNECT_CANTSEND "Send timeout or network error"

/*====================================================================*
 *   class declaration;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) oconnect: public oflagword, public ointerface, public oethernet

{
public: 
	oconnect ();
	oconnect (char const * name);
	virtual ~ oconnect ();
	signed Descriptor () const;
	unsigned Timer () const;
	oconnect & SetTimer (unsigned);
	oconnect & Open ();
	oconnect & Open (unsigned);
	oconnect & Open (char const *);
	signed SendPacket (void const * memory, signed extent);
	signed ReadPacket (void * memory, signed extent);
	oconnect & Close ();
	oconnect & Print ();
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



