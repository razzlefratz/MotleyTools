/*====================================================================*
 *
 *   oif.cpp - oif class definition;
 *
 *   host interface information;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oIF_SOURCE
#define oIF_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cerrno>

/*====================================================================*
 *   system header files (environment dependent);
 *--------------------------------------------------------------------*/

#if defined (__linux__)
#	include <sys/ioctl.h>
#	include <netinet/in.h>
#elif defined (__APPLE__)
#	include <net/bpf.h>
#	include <sys/types.h>
#	include <sys/socket.h>
#	include <net/if_dl.h>
#	include <ifaddrs.h>
#	include <sys/ioctl.h>
#	include <fcntl.h>
#elif defined (__OpenBSD__)
#	include <net/if_dl.h>
#	include <sys/poll.h>
#elif defined (WINPCAP)
#	include <pcap.h>
#	include <pcap/Packet32.h>
#	include <pcap/ntddndis.h>
#else
#error "Unknown environment."
#endif

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/oif.hpp"
#include "../classes/omemory.hpp"
#include "../classes/oerror.hpp"

/*====================================================================*
 *
 *   unsigned Index (void) const;
 *
 *   return the index of the selected interface; on some systems, the
 *   index is sequential; on others, it is not;
 *
 *--------------------------------------------------------------------*/

unsigned oif::Index (void) const 

{
	return (this->mindex);
}


/*====================================================================*
 *
 *   char const * Name (void) const;
 *
 *   return the NUL terminated interface name string;
 *
 *--------------------------------------------------------------------*/

char const * oif::Name (void) const 

{
	return (this->mname);
}


/*====================================================================*
 *
 *   char const * Text (void) const;
 *
 *   return the NUL terminated interface text string; on some systems
 *   this may be identical to the name string; on other it may not be;
 *
 *--------------------------------------------------------------------*/

char const * oif::Text (void) const 

{
	return (this->mtext);
}


/*====================================================================*
 *
 *   char const * HardwareAddress (void) const;
 *
 *   return the NUL terminated internet address string; the string is
 *   a sequence of hex octets seperated by colons;
 *
 *--------------------------------------------------------------------*/

char const * oif::HardwareAddress (void) const 

{
	return (this->mhwstring);
}


/*====================================================================*
 *
 *   char const * EthernetAddress (void) const;
 *
 *   return the NUL terminated internet address string; the string is
 *   a sequence of hex octets seperated by colons;
 *
 *--------------------------------------------------------------------*/

char const * oif::EthernetAddress (void) const 

{
	return (this->mhwstring);
}


/*====================================================================*
 *
 *   char const * InternetAddress (void) const;
 *
 *   return the NUL terminated hardware address string; the string is
 *   a sequence of decimal octets seperated by periods;
 *
 *--------------------------------------------------------------------*/

char const * oif::InternetAddress (void) const 

{
	return (this->mipstring);
}


/*====================================================================*
 *
 *   oif & GetHardwareAddress (void * memory);
 *
 *   copy the stored hardware address to external memory; this is a
 *   binary copy operation; return the object instance reference;
 *
 *--------------------------------------------------------------------*/

oif & oif::GetHardwareAddress (void * memory) 

{
	std::memcpy (memory, this->mhwaddr, sizeof (this->mhwaddr));
	return (* this);
}


/*====================================================================*
 *
 *   oif & GetEthernetAddress (void * memory);
 *
 *   copy the stored hardware address to external memory; this is a
 *   binary copy operation; return the object instance reference;
 *
 *--------------------------------------------------------------------*/

oif & oif::GetEthernetAddress (void * memory) 

{
	std::memcpy (memory, this->mhwaddr, sizeof (this->mhwaddr));
	return (* this);
}


/*====================================================================*
 *
 *   oif & GetInternetAddress (void * memory);
 *
 *   copy the stored internet address to external memory; this is a 
 *   binary copy operation; return the object instance reference;
 *
 *--------------------------------------------------------------------*/

oif & oif::GetInternetAddress (void * memory) 

{
	std::memcpy (memory, this->mipaddr, sizeof (this->mipaddr));
	return (* this);
}


/*====================================================================*
 *
 *   oif & Print (void);
 *
 *   print interface index, hardware address, internet address, name
 *   and text on stdout; return the object instance reference;
 *
 *--------------------------------------------------------------------*/

oif & oif::Print (void) 

{
	std::cout << this->Index () << " ";
	std::cout << this->HardwareAddress () << " ";
	std::cout << this->InternetAddress () << " ";
	std::cout << this->Name () << " ";
	std::cout << this->Text () << std::endl;
	return (* this);
}


/*====================================================================*
 *
 *   oif & SetIndex (unsigned index);
 *
 *   change the interface index; automatically update the name and 
 *   text strings plus the hardware and internet addresses and their
 *   strings;
 *
 *   Microsoft claims to support function if_indextoname with Vista 
 *   and beyond; pcap_indextoname is a temporary solution;
 *
 *--------------------------------------------------------------------*/

oif & oif::SetIndex (unsigned index) 

{
	this->mindex = index;

#if defined (WINPCAP)

	oif::pcap_indextoname (this->mindex, this->mname);

#else

	if_indextoname (this->mindex, this->mname);

#endif

	std::memcpy (this->mtext, this->mname, sizeof (this->mname));
	oif::lookup ();
	return (* this);
}


/*====================================================================*
 *
 *   oif & oif::SetName (char const * name);
 *
 *   change the interface name string; automatically update the index 
 *   and text string plus the hardware and internet addresses and their 
 *   strings; return the object instance reference;
 *
 *   Microsoft claims to support function if_nametoindex with Vista 
 *   and beyond; pcap_nametoindex is a temporary solution;
 *
 *--------------------------------------------------------------------*/

oif & oif::SetName (char const * name) 

{

#if defined (WINPCAP) 

	this->mindex = oif::pcap_nametoindex (name);

#else

	this->mindex = if_nametoindex (name);

#endif

	std::memcpy (this->mname, name, std::strlen (name));
	std::memcpy (this->mtext, name, std::strlen (name));
	oif::lookup ();
	return (* this);
}


/*====================================================================*
 *
 *   oif & oif::SetText (char const * text);
 *
 *   replace interface text string and return the object instance
 *   reference; this string may change whenever the index or name
 *   are changed but changing the text string does not affect the 
 *   other properties;
 *
 *--------------------------------------------------------------------*/

oif & oif::SetText (char const * text) 

{
	std::memcpy (this->mtext, text, std::strlen (text));
	return (* this);
}


/*====================================================================*
 *
 *   oif & SetHardwareAddress (void const * memory);
 *
 *   copy the hardware address from external memory and return the 
 *   object instance referenc;
 *   
 *   format the hardware and internet address strings now to avoid
 *   decoding them each time they are displayed;
 *
 *--------------------------------------------------------------------*/

oif & oif::SetHardwareAddress (void const * memory) 

{
	std::memcpy (this->mhwaddr, memory, sizeof (this->mhwaddr));
	oif::format ();
	return (* this);
}


/*====================================================================*
 *
 *   oif & SetEthernetAddress (void const * memory);
 *
 *   copy the hardware address from external memory and return the 
 *   object instance referenc;
 *   
 *   format the hardware and internet address strings now to avoid
 *   decoding them each time they are displayed;
 *
 *--------------------------------------------------------------------*/

oif & oif::SetEthernetAddress (void const * memory) 

{
	std::memcpy (this->mhwaddr, memory, sizeof (this->mhwaddr));
	oif::format ();
	return (* this);
}


/*====================================================================*
 *
 *   oif & SetInternetAddress (void const * memory);
 *
 *   copy the internet address from external memory and return the
 *   object instance reference;
 *   
 *   format the hardware and internet address strings now to avoid
 *   decoding them each time they are displayed;
 *
 *--------------------------------------------------------------------*/

oif & oif::SetInternetAddress (void const * memory) 

{
	std::memcpy (this->mipaddr, memory, sizeof (this->mipaddr));
	oif::format ();
	return (* this);
}


/*====================================================================*
 *
 *   oif & oif::lookup ();
 *
 *   update hardware and internet addresses after the index and name
 *   are known; this is a rat's nest but that's life so deal with it!
 *   
 *--------------------------------------------------------------------*/

oif & oif::lookup () 

{

#if defined (__linux__)

	struct ifreq ifreq;
	struct sockaddr_in * sockaddr_in = (struct sockaddr_in *)(&ifreq.ifr_ifru.ifru_addr);
	int fd;
	if ((fd = socket (AF_INET, SOCK_RAW, 0)) < 0) 
	{
		oerror::error (1, errno, "Can't open socket: %s", this->mname);
	}
	std::memcpy (ifreq.ifr_name, this->mname, sizeof (ifreq.ifr_name));
	if (ioctl (fd, SIOCGIFHWADDR, &ifreq) == -1) 
	{
		oerror::error (1, errno, "Can't fetch hardware address: %s", this->mname);
		close (fd);
		return (* this);
	}
	std::memcpy (this->mhwaddr, ifreq.ifr_ifru.ifru_hwaddr.sa_data, sizeof (this->mhwaddr));
	if (ioctl (fd, SIOCGIFADDR, &ifreq) == -1) 
	{
		oerror::error (1, errno, "Can't fetch ethernet address: %s", this->mname);
		close (fd);
		return (* this);
	}
	std::memcpy (this->mipaddr, &sockaddr_in->sin_addr.s_addr, sizeof (this->mipaddr));
	close (fd);

#elif defined (__APPLE__)

	oif::osx_gethwaddr ();

#elif defined (WINPCAP) 

	oif::pcap_gethwaddr ();
	oif::pcap_getipaddr ();

#else
#error "Unknown environment."
#endif

	oif::format ();
	return (* this);
}


/*====================================================================*
 *
 *   oif & oif::format ();
 *
 *   format hardware and internet address strings; this is a private 
 *   method that should be called whenever either address changes;
 *
 *--------------------------------------------------------------------*/

oif & oif::format () 

{
	omemory::hexdecode (this->mhwaddr, sizeof (this->mhwaddr), this->mhwstring, sizeof (this->mhwstring));
	omemory::decdecode (this->mipaddr, sizeof (this->mipaddr), this->mipstring, sizeof (this->mipstring));
	return (* this);
}


/*====================================================================*
 *
 *   void osx_gethwaddr ();
 *
 *   update the hardware address based on interface name in Mac OSX
 *   environment only;
 *
 *--------------------------------------------------------------------*/

void oif::osx_gethwaddr () 

{

#if defined (__APPLE__)

	struct ifaddrs * ifaddrs;
	struct ifaddrs * ifaddr;
	if (getifaddrs (&ifaddrs) == -1) 
	{
		oerror::error (1, errno, "No interfaces available");
	}
	for (ifaddr = ifaddrs; ifaddr; ifaddr = ifaddr->ifa_next) 
	{
		if (std::strcmp (this->mname, ifaddr->ifa_name)) 
		{
			continue;
		}
		if (!ifaddr->ifa_addr) 
		{
			continue;
		}
		if (ifaddr->ifa_addr->sa_family == AF_INET) 
		{
			struct sockaddr_in * sockaddr_in = (struct sockaddr_in *) (ifaddr->ifa_addr);
			std::memcpy (this->mipaddr, &sockaddr_in->sa_data.s_addr, sizeof (this->mipaddr));
			continue;
		}
		if (ifaddr->ifa_addr->sa_family == AF_LINK) 
		{
			struct sockaddr_dl * sockaddr_dl = (struct sockaddr_dl *) (ifaddr->ifa_addr);
			std::memcpy (this->mhwaddr, LLADDR (sockaddr_dl), sizeof (this->mhwaddr));
			continue;
		}
	}
	freeifaddrs (ifaddrs);

#endif

	return;
}


/*====================================================================*
 *
 *   unsigned pcap_nametoindex (char const * name) const;
 *
 *   WinPcap version of POSIX if_nametoindex function; return error
 *   in non-pcap environments; Microsoft will support this function
 *   on Vista and future systems;
 *
 *   see The Open Group Base Specifications Issue 6 IEEE Std 1003.1, 
 *   2004 Edition for a description of this method;
 *
 *--------------------------------------------------------------------*/

unsigned oif::pcap_nametoindex (char const * name) const 

{

#if defined (WINPCAP)

	char buffer [PCAP_ERRBUF_SIZE];
	pcap_if_t * devices = (pcap_if_t *)(0);
	pcap_if_t * device;
	if (pcap_findalldevs (&devices, buffer) != -1) 
	{
		unsigned index = 1;
		for (device = devices; device; device = device->next) 
		{
			if (std::strcmp (name, device->name)) 
			{
				index++;
				continue;
			}
			pcap_freealldevs (devices);
			return (index);
		}
		pcap_freealldevs (devices);
	}
#endif

	errno = ENXIO;
	return (0);
}


/*====================================================================*
 *
 *   char * pcap_indextoname (unsigned ifindex, char * ifname) const;
 *
 *   WinPcap version of POSIX if_indextoname function; return error 
 *   in non-pcap enviroements; Microsoft will support this function
 *   on Vista and future systems;
 *
 *   see The Open Group Base Specifications Issue 6 IEEE Std 1003.1, 
 *   2004 Edition for a description of this method;
 *
 *--------------------------------------------------------------------*/

char * oif::pcap_indextoname (unsigned ifindex, char * ifname) const 

{

#if defined (WINPCAP)

	char buffer [PCAP_ERRBUF_SIZE];
	pcap_if_t * devices = (pcap_if_t *)(0);
	pcap_if_t * device;
	if ((ifindex--) && (pcap_findalldevs (&devices, buffer) != -1)) 
	{
		for (device = devices; device; device = device->next) 
		{
			if (!ifindex--) 
			{
				std::memcpy (ifname, device->name, std::strlen (device->name));
				pcap_freealldevs (devices);
				return (ifname);
			}
		}
		pcap_freealldevs (devices);
	}
#endif

	errno = ENXIO;
	return ((char *)(0));
}


/*====================================================================*
 *
 *   void pcap_gethwaddr ();
 *
 *   update the hardware address based on interface name in winpcap
 *   environment only; it has no effect in non-pcap environments;
 *
 *--------------------------------------------------------------------*/

void oif::pcap_gethwaddr () 

{

#if defined (WINPCAP)

	LPADAPTER adapter = PacketOpenAdapter ((PCHAR)(this->mname));
	PPACKET_OID_DATA data = (PPACKET_OID_DATA)(std::malloc (ETHER_ADDR_LEN + sizeof (PACKET_OID_DATA)));
	if (!data) 
	{
		oerror::error (1, 0, "Can't allocate packet: %s", this->mname);
	}
	data->Oid = OID_802_3_CURRENT_ADDRESS;
	data->Length = ETHER_ADDR_LEN;
	if ((!adapter) || (adapter->hFile == INVALID_HANDLE_VALUE)) 
	{
		oerror::error (1, 0, "Can't access %s", this->mname);
	}
	std::memset (this->mhwaddr, 0, sizeof (this->mhwaddr));
	if (PacketRequest (adapter, FALSE, data)) 
	{
		std::memcpy (this->mhwaddr, data->Data, data->Length);
	}
	PacketCloseAdapter (adapter);
	std::free (data);

#endif

	return;
}


/*====================================================================*
 *
 *   void pcap_getipaddr ();
 *
 *   update the internet address based on interface name in winpcap
 *   environment only; it has no effect in non-pcap environments;
 *
 *--------------------------------------------------------------------*/

void oif::pcap_getipaddr () 

{

#if defined (WINPCAP)

	char buffer [PCAP_ERRBUF_SIZE];
	pcap_if_t * devices = (pcap_if_t *)(0);
	pcap_if_t * device;
	if (pcap_findalldevs (&devices, buffer) == -1) 
	{
		oerror::error (1, errno, "Can't enumerate interfaces");
	}
	for (device = devices; device; device = device->next) 
	{
		if (std::strcmp (this->mname, device->name)) 
		{
			continue;
		}
		std::memcpy (this->mtext, device->description, std::strlen (device->description));
		if (device->addresses) 
		{
			struct pcap_addr * pcap_addr = device->addresses;
			struct sockaddr_in * sockaddr_in = (struct sockaddr_in *)(pcap_addr->addr->sa_data);
			std::memcpy (this->mipaddr, &sockaddr_in->sin_addr.s_addr, sizeof (this->mipaddr));
		}
		break;
	}
	pcap_freealldevs (devices);

#endif

	return;
}


/*====================================================================*
 *
 *   oif () 
 *
 *--------------------------------------------------------------------*/

oif::oif () 

{
	this->mindex = 0;
	std::memset (this->mname, 0, sizeof (this->mname));
	std::memset (this->mtext, 0, sizeof (this->mtext));
	std::memset (this->mhwaddr, 0, sizeof (this->mhwaddr));
	std::memset (this->mipaddr, 0, sizeof (this->mipaddr));
	oif::format ();
	return;
}


/*====================================================================*
 *
 *   ~oif () 
 *
 *--------------------------------------------------------------------*/

oif::~oif () 

{
	return;
}


/*====================================================================*
 *   end definition;
 *--------------------------------------------------------------------*/

#endif

