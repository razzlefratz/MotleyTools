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

#include <stdio.h>
#include <string.h>
#include <ifaddrs.h>
#include <net/ethernet.h>
#include <netinet/in.h>
#include <linux/socket.h>
#include <errno.h>

#include "../ether/ether.h"

void osx_gethwaddr (char const * name, void * memory) 

{
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
		printf ("ifaddr->ifa_addr->sa_family=%d\n", ifaddr->ifa_addr->sa_family);
		if (ifaddr->ifa_addr->sa_family == AF_INET) 
		{
			struct sockaddr_in * sockaddr_in = (struct sockaddr_in *) (&ifaddr->ifa_addr);
			memcpy (memory, &sockaddr_in->sin_addr.s_addr, sizeof (uint32_t));
			continue;
		}

#if 0

		if (ifaddr->ifa_addr->sa_family == AF_LINK) 
		{
			struct sockaddr_dl * sockaddr_dl = (struct sockaddr_dl *) (ifaddr->ifa_addr);
			memcpy (memory, LLADDR (sockaddr_dl), ETHER_ADDR_LEN);
			continue;
		}

#endif

	}
	freeifaddrs (ifaddrs);
	return;
}

int main (int argc, char const * argv []) 

{
	uint8_t buffer [ETHER_ADDR_LEN];
	printf ("%d.%d.%d.%d\n", buffer [0], buffer [1], buffer [2], buffer [4]);
	osx_gethwaddr ("eth0", buffer);
	return (0);
}


#endif

