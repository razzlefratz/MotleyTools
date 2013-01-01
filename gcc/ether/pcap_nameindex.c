/*====================================================================*
 *
 *   struct if_nameindex * pcap_nameindex (void) 
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

#ifndef PCAP_NAMEINDEX_SOURCE
#define PCAP_NAMEINDEX_SOURCE

#include <pcap.h>
#include <net/if.h>
#include <string.h>
#include <stdlib.h>

#include "../ether/ether.h"

struct if_nameindex * pcap_nameindex (void) 

{

#if defined (WINPCAP)

	char buffer [PCAP_ERRBUF_SIZE];
	pcap_if_t * devices = (pcap_if_t *)(0);
	pcap_if_t * device;
	if (pcap_findalldevs (&devices, buffer) != -1) 
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


#endif

