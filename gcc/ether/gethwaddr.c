/*====================================================================*
 *   
 *   int gethwaddr (void volatile * memory, char const * device);
 *   
 *   ether.h
 *
 *   encode memory with the hardware address of a named host Ethernet
 *   interface;
 *
 *   there are two ways to obtain the hardware address on Linux; we
 *   use the first because some systems do not support getifaddrs() 
 *   and some implementations are inconsistent; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef GETHWADDR_SOURCE
#define GETHWADDR_SOURCE

#include <stdint.h>
#include <unistd.h>
#include <memory.h>

#include "../tools/error.h"
#include "../ether/ether.h"

int gethwaddr (void * memory, char const * device) 

{

#if defined (__linux__)

#	include <ifaddrs.h>
#	include <netpacket/packet.h>
#	include <sys/ioctl.h>

	struct ifreq ifreq;
	int fd;
	if ((fd = socket (AF_INET, SOCK_DGRAM, 0)) == -1) 
	{
		error (1, errno, "%s: %s", __func__, device);
	}
	memcpy (ifreq.ifr_name, device, sizeof (ifreq.ifr_name));
	if (ioctl (fd, SIOCGIFHWADDR, &ifreq) == -1) 
	{
		close (fd);
		return (-1);
	}
	memcpy (memory, ifreq.ifr_ifru.ifru_hwaddr.sa_data, ETHER_ADDR_LEN);
	close (fd);

#elif defined (__linux__) 

#include <ifaddrs.h>

	struct ifaddrs *ifaddrs;
	struct ifaddrs *ifaddr;
	if (getifaddrs (&ifaddrs) == -1) 
	{
		error (1, errno, "No interfaces available");
	}
	for (ifaddr = ifaddrs; ifaddr; ifaddr = ifaddr->ifa_next) 
	{
		if (strcmp (device, ifaddr->ifa_name)) 
		{
			continue;
		}
		if (!ifaddr->ifa_addr) 
		{
			continue;
		}
		if (ifaddr->ifa_addr->sa_family == AF_PACKET) 
		{
			struct sockaddr_ll * sockaddr = (struct sockaddr_ll *) (ifaddr->ifa_addr);
			memcpy (memory, sockaddr->sll_addr, ETHER_ADDR_LEN);
			break;
		}
	}
	freeifaddrs (ifaddrs);

#elif defined (__APPLE__) 

#include <ifaddrs.h>
#include <net/if_dl.h>

	struct ifaddrs *ifaddrs;
	struct ifaddrs *ifaddr;
	if (getifaddrs (&ifaddrs) == -1) 
	{
		error (1, errno, "No interfaces available");
	}
	for (ifaddr = ifaddrs; ifaddr; ifaddr = ifaddr->ifa_next) 
	{
		if (strcmp (device, ifaddr->ifa_name)) 
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

#elif defined (__OpenBSD__)

#include <ifaddrs.h>
#include <net/if_dl.h>

	struct ifaddrs *ifaddrs;
	struct ifaddrs *ifaddr;
	if (getifaddrs (&ifaddrs) == -1) 
	{
		error (1, errno, "No interfaces available");
	}
	for (ifaddr = ifaddrs; ifaddr; ifaddr = ifaddr->ifa_next) 
	{
		if (strcmp (device, ifaddr->ifa_name)) 
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

#elif defined (WINPCAP) || defined (LIBPCAP)

	LPADAPTER adapter = PacketOpenAdapter ((PCHAR)(device));
	PPACKET_OID_DATA data = (PPACKET_OID_DATA)(malloc (ETHER_ADDR_LEN + sizeof (PACKET_OID_DATA)));
	if (!data) 
	{
		error (1, errno, "Can't allocate packet: %s", device);
	}
	data->Oid = OID_802_3_CURRENT_ADDRESS;
	data->Length = ETHER_ADDR_LEN;
	if ((adapter == 0) || (adapter->hFile == INVALID_HANDLE_VALUE)) 
	{
		error (1, errno, "Can't access interface: %s", device);
	}
	if (!PacketRequest (adapter, FALSE, data)) 
	{
		memset (memory, 0, ETHER_ADDR_LEN);
		PacketCloseAdapter (adapter);
		free (data);
		return (-1);
	}
	memcpy (memory, data->Data, data->Length);
	PacketCloseAdapter (adapter);
	free (data);

#else
#error "Unknown environment"
#endif

	return (0);
}


#endif

