/*====================================================================*
 *
 *   oif.hpp - interface for the oif class  
 *
 *   host interface information;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oIF_HEADER
#define oIF_HEADER

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <net/if.h>
#include <net/ethernet.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"

/*====================================================================*
 *   class declaration;
 *--------------------------------------------------------------------*/

class __declspec(dllexport) oif

{
public: 
	oif ();
	oif (unsigned);
	virtual ~ oif();
	unsigned Index(void) const;
	char const * Name(void) const;
	char const * Text(void) const;
	char const * HardwareAddress(void) const;
	char const * EthernetAddress(void) const;
	char const * InternetAddress(void) const;
	oif & GetHardwareAddress(void * memory);
	oif & GetEthernetAddress(void * memory);
	oif & GetInternetAddress(void * memory);
	oif & Print(void);
	oif & SetIndex(unsigned);
	oif & SetName(char const *);
	oif & SetText(char const *);
private: 
	oif & SetHardwareAddress(void const * memory);
	oif & SetEthernetAddress(void const * memory);
	oif & SetInternetAddress(void const * memory);
	oif & format();
	oif & lookup();
	unsigned pcap_nametoindex(char const * ifname) const;
	char * pcap_indextoname(unsigned ifindex, char * ifname) const;
	void osx_gethwaddr();
	void osx_getipaddr();
	void pcap_gethwaddr();
	void pcap_getipaddr();
	unsigned mindex;
	uint8_t mhwaddr[ETHER_ADDR_LEN];
	uint8_t mipaddr[4];
	char mhwstring[ETHER_ADDR_LEN * 3];
	char mipstring[4 * 4];
	char mname[IF_NAMESIZE];
	char mtext[255];
};

/*====================================================================*
 *   end declaration;
 *--------------------------------------------------------------------*/

#endif



