/*====================================================================*
 *
 *   void osx_gethwaddr (char const * name, void * memory);
 *
 *   ether.h
 *
 *   update the hardware address based on interface name in Mac OSX
 *   environment only;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef OSX_GETHWADDR_SOURCE
#define OSX_GETHWADDR_SOURCE

#include <string.h>
#include <ifaddrs.h>
#include <net/ethernet.h>
#include <errno.h>

#include "../ether/ether.h"

void osx_gethwaddr (char const * name, void * memory) 

{

#if defined (__APPLE__)

	struct ifaddrs *ifaddrs;
	struct ifaddrs *ifaddr;
	if (getifaddrs (&ifaddrs) == -1) 
	{
		error (1, errno, "No interfaces available");
	}
	for (ifaddr = ifaddrs; ifaddr; ifaddr = ifaddr->ifa_next) 
	{
		if (strcmp (name, ifaddr->ifa_name)) 
		{
			continue;
		}
		if (!ifaddr->ifa_addr) 
		{
			continue;
		}
		if (ifaddr->ifa_addr->sa_family == AF_LINK) 
		{
			struct sockaddr_dl * sockaddr = (struct sockaddr_dl *) (ifaddr->ifa_addr);
			memcpy (memory, LLADDR (sockaddr), ETHER_ADDR_LEN);
			break;
		}
	}
	freeifaddrs (ifaddrs);

#endif

	return;
}


#endif

