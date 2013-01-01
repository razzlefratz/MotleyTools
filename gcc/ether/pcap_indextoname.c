/*====================================================================*
 *
 *   char * pcap_indextoname (unsigned ifindex, char *ifname);
 *
 *   ether.h
 *
 *   a WinPcap version of POSIX if_indextoname function; return error 
 *   in non-pcap environments; set errno to ENXIO on error on MacOSX; 
 *
 *   see The Open Group Base Specifications Issue 6 IEEE Std 1003.1, 
 *   2004 Edition for a description of this function;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef PCAP_INDEXTONAME_SOURCE
#define PCAP_INDEXTONAME_SOURCE

#include <pcap.h>
#include <string.h>
#include <errno.h>

#include "../ether/ether.h"

char * pcap_indextoname (unsigned ifindex, char * ifname) 

{

#if defined (WINPCAP)

	char buffer [PCAP_ERRBUF_SIZE];
	pcap_if_t * devices = (pcap_if_t *)(0);
	pcap_if_t * device;
	if ((index--) && (pcap_findalldevs (&devices, buffer) != -1)) 
	{
		for (device = devices; device; device = device->next) 
		{
			if (!index--) 
			{
				memcpy (ifname, device->name, strlen (device->name));
				pcap_freealldevs (devices);
				return (ifname);
			}
		}
		pcap_freealldevs (devices);
	}

#endif
#if defined (__APPLE__)

	errno = ENXIO;

#endif

	return ((char *)(0));
}


#endif

