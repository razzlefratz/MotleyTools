/*====================================================================*
 *
 *   char * getifname (signed number);
 *
 *   ether.h
 *
 *   return the PCAP interface name for a given interface number; this
 *   function is only needed when using LIBPCAP or WINPCAP libraries;
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef GETIFNAME_SOURCE
#define GETIFNAME_SOURCE

#include <string.h>

#if defined (WINPCAP) || defined (LIBPCAP)
#include <pcap.h>
#endif

#include "../ether/ether.h"
#include "../tools/error.h"

char * getifname (signed index) 

{
	char * name = (char *)(0);

#if defined (WINPCAP) || defined (LIBPCAP)

	char buffer [PCAP_ERRBUF_SIZE];
	pcap_if_t *devices = (pcap_if_t *)(0);
	pcap_if_t *device;
	signed count;
	if (pcap_findalldevs (&devices, buffer) == -1) 
	{
		error (1, errno, "can't enumerate pcap devices");
	}
	for (device = devices, count = 1; device; device = device->next, count++) 
	{
		if (count == index) 
		{
			name = strdup (device->name);
			break;
		}
	}
	if (!device) 
	{
		error (1, EINVAL, "invalid interface: %d", index);
	}
	pcap_freealldevs (devices);

#endif

	return (name);
}


#endif

