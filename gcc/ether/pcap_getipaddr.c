/*====================================================================*
 *
 *   void pcap_getipaddr (char const * name, void * memory);
 *
 *   ether.h
 *
 *   update the internet address based on interface name in winpcap
 *   environment only; it has no effect in non-pcap environments;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef PCAP_GETIPADDR_SOURCE
#define PCAP_GETIPADDR_SOURCE

#include <pcap.h>
#include <string.h>
#include <errno.h>

#include "../ether/ether.h"

void pcap_getipaddr (char const * name, void * memory) 

{

#if defined (WINPCAP)

	char buffer [PCAP_ERRBUF_SIZE];
	pcap_if_t * devices = (pcap_if_t *)(0);
	pcap_if_t * device;
	if (pcap_findalldevs (&devices, buffer) == -1) 
	{
		error (1, errno, "Can't enumerate interfaces");
	}
	for (device = devices; device; device = device->next) 
	{
		if (strcmp (name, device->name)) 
		{
			continue;
		}
		if (device->addresses) 
		{
			struct pcap_addr * pcap_addr = device->addresses;
			struct sockaddr_in * sockaddr_in = (struct sockaddr_in *)(pcap_addr->addr->sa_data);
			memcpy (memory, &sockaddr_in->sin_addr.s_addr, sizeof (uint32_t));
		}
		break;
	}
	pcap_freealldevs (devices);

#endif

	return;
}


#endif

