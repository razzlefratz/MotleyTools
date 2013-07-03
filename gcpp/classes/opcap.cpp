/*====================================================================*
 *
 *   opcap.cpp - opcap class definition;
 *
 *   host interface information;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oPCAP_SOURCE
#define oPCAP_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cerrno>

/*====================================================================*
 *   system header;
 *--------------------------------------------------------------------*/

#include <pcap.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/opcap.hpp"
#include "../classes/omemory.hpp"

/*====================================================================*
 *
 *   unsigned if_nametoindex (char const * name);
 *
 *   WinPcap version of POSIX if_nametoindex function; return error
 *   in non-pcap environments; Microsoft will support this function
 *   on Vista and future systems;
 *
 *   see The Open Group Base Specifications Issue 6 IEEE Std 1003.1, 
 *   2004 Edition for a description of this method;
 *
 *--------------------------------------------------------------------*/

unsigned opcap::if_nametoindex (char const * name) 

{

#if defined (WINPCAP)

	char buffer [PCAP_ERRBUF_SIZE];
	pcap_if_t * devices = (pcap_if_t *)(0);
	pcap_if_t * device;
	if (pcap_findalldevs (& devices, buffer) != -1) 
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
 *   char * if_indextoname (unsigned ifindex, char * ifname);
 *
 *   WinPcap version of POSIX if_indextoname function; return error 
 *   in non-pcap enviroements; Microsoft will support this function
 *   on Vista and future systems;
 *
 *   see The Open Group Base Specifications Issue 6 IEEE Std 1003.1, 
 *   2004 Edition for a description of this method;
 *
 *--------------------------------------------------------------------*/

char * opcap::if_indextoname (unsigned ifindex, char * ifname) 

{

#if defined (WINPCAP)

	char buffer [PCAP_ERRBUF_SIZE];
	pcap_if_t * devices = (pcap_if_t *)(0);
	pcap_if_t * device;
	if ((ifindex--) && (pcap_findalldevs (& devices, buffer) != -1)) 
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
 *   struct if_nameindex * if_nameindex (void) 
 *
 *   ether.h
 *
 *   a WinPcap version of POSIX if_nameindex function; return error
 *   in non-pcap environments;
 *
 *   see The Open Group Base Specifications Issue 6 IEEE Std 1003.1, 
 *   2004 Edition for a description of this function;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

struct if_nameindex * opcap::if_nameindex (void) 

{

#if defined (WINPCAP)

	char buffer [PCAP_ERRBUF_SIZE];
	pcap_if_t * devices = (pcap_if_t *)(0);
	pcap_if_t * device;
	if (pcap_findalldevs (& devices, buffer) != -1) 
	{
		struct if_nameindex * ifs;
		struct if_nameindex * ifp;
		unsigned count = 1;
		for (device = devices; device; device = device->next) 
		{
			count++;
		}
		ifp = ifs = (struct if_nameindex *)(malloc (count * sizeof (struct if_nameindex)));
		if (ifs) for (device = devices; device; device = device->next) 
		{
			ifp->if_index = device->index;
			ifp->if_name = strdup (device->name);
			ifp++;
		}
		memset (ifp, 0, sizeof (* ifp));
		pcap_freealldevs (devices);
		return (ifs);
	}

#endif

	return ((struct if_nameindex *)(0));
}

/*====================================================================*
 *
 *   void if_freenameindex (struct if_nameindex *) 
 *
 *   a WinPcap version of POSIX if_freenameindex function; 
 *
 *   see The Open Group Base Specifications Issue 6 IEEE Std 1003.1, 
 *   2004 Edition for a description of this function;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

void opcap::if_freenameindex (struct if_nameindex * if_nameindex) 

{

#if defined (WINPCAP)

	struct if_nameindex * ifp = if_nameindex;
	while (ifp->if_index) 
	{
		free (ifp->if_name);
	}
	free (if_nameindex);

#endif

	return;
}

/*====================================================================*
 *
 *   opcap () 
 *
 *--------------------------------------------------------------------*/

opcap::opcap () 

{
	return;
}

/*====================================================================*
 *
 *   ~opcap () 
 *
 *--------------------------------------------------------------------*/

opcap::~opcap () 

{
	return;
}

/*====================================================================*
 *   end definition;
 *--------------------------------------------------------------------*/

#endif

