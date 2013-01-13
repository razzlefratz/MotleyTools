/*====================================================================*
 *
 *   int bind_ll (const char *interface, struct sockaddr_ll * sockaddr);
 *   
 *   socket_ll.h
 *
 *   open a socket and bind it to a named interface (eth0, eth1, ...)
 *   and return a socket (file) descriptor; think if this functions as
 *   a socket version of open();
 *   
 *   obtain a socket descriptor then initialize the sockaddr structure
 *   with the ethernet card address and interface index; the sockaddr
 *   structure is needed by functions send_ll() and read_ll();
 *
 *   sockaddr->sll_protocol must be in network byte order when calling
 *   function socket(); in other words, use htons(ethertype) to store
 *   the protocol value; essentially, it will filter incoming frames;
 *   
 *.  Motley Tools by Charles Maier <cmaier@cmassoc.net>;
 *:  Published 2005 by Charles Maier Associates Limited;
 *;  Released under the GNU General Public Licence v2 and later;
 *
 *--------------------------------------------------------------------*/

#ifndef BIND_LL_SOURCE
#define BIND_LL_SOURCE

#include <string.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <netpacket/packet.h>
#include <net/if.h>

#include "../tools/error.h"

int bind_ll (const char *interface, struct sockaddr_ll * sockaddr) 

{
	struct ifreq ifreq;
	int fd;
	if ((fd = socket (sockaddr->sll_family, SOCK_RAW, sockaddr->sll_protocol)) == -1) 
	{
		error (1, errno, "Can't create socket for %s", interface);
	}
	memset (&ifreq, 0, sizeof (ifreq));
	memcpy (ifreq.ifr_name, interface, sizeof (ifreq.ifr_name));
	if (ioctl (fd, SIOCGIFFLAGS, &ifreq) < 0) 
	{
		error (1, errno, "Can't get %s device state", ifreq.ifr_name);
	}
	if (!(ifreq.ifr_flags & IFF_UP)) 
	{
		ifreq.ifr_flags |= IFF_UP;
		ifreq.ifr_flags |= IFF_BROADCAST;
		ifreq.ifr_flags |= IFF_MULTICAST;
		ifreq.ifr_flags &= ~IFF_ALLMULTI;

#if 0		
 
/*
 * 	this can cause trouble when wireshark is sampling the same interface; it is
 * 	best left out, for now;
 */
 
		ifreq.ifr_flags &= ~IFF_PROMISC;

#endif
 
		if (ioctl (fd, SIOCSIFFLAGS, &ifreq) < 0) 
		{
			error (1, errno, "Can't set %s device state", ifreq.ifr_name);
		}
	}
	if (ioctl (fd, SIOCGIFHWADDR, &ifreq) == -1) 
	{
		error (1, errno, "Can't get %s hardware address", ifreq.ifr_name);
	}
	memcpy (sockaddr->sll_addr, ifreq.ifr_ifru.ifru_hwaddr.sa_data, sizeof (sockaddr->sll_addr));
	if (ioctl (fd, SIOCGIFINDEX, &ifreq) == -1) 
	{
		error (1, errno, "Can't get %s interface index", ifreq.ifr_name);
	}
	sockaddr->sll_ifindex = ifreq.ifr_ifindex;
	if (bind (fd, (struct sockaddr *) (sockaddr), sizeof (struct sockaddr_ll)) == -1) 
	{
		error (1, errno, "Can't bind socket to %s", interface);
	}
	return (fd);
}

#endif
 

