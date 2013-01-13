/*====================================================================*
 *
 *   signed open_ll (struct channel * channel);
 *   
 *   channel.h
 *   
 *   open a raw socket and bind it to the channel interface (eth0, 
 *   eth1, ..., ethn) named in channel->name; 
 *
 *   fetch the interface index and store it in the channel sockaddr
 *   structure for reference by sendto() and recvfrom();
 * 
 *   return 0 on success or -1 on failure;
 *
 *   struct channel is defined in channel.h and the components used
 *   here are:
 *
 *      channel->fd to store socket file descriptor;
 *      channel->name to get interface name string;
 *      channel->sockaddr to store interface index and hardware address;
 *   
 *.  Motley Tools by Charles Maier <cmaier@cmassoc.net>;
 *:  Published 2005 by Charles Maier Associates Limited;
 *;  Released under the GNU General Public Licence v2 and later;
 *
 *--------------------------------------------------------------------*/

#ifndef OPEN_LL_SOURCE
#define OPEN_LL_SOURCE

#include <string.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <net/if.h>
#include <netpacket/packet.h>
// #include <net/ethernet.h>

#include "../ether/channel.h"
#include "../tools/error.h"
 
signed open_ll (struct channel * channel) 

{
	struct ifreq ifreq;
	if ((channel->fd = socket (channel->sockaddr.sll_family, SOCK_RAW, channel->sockaddr.sll_protocol)) == -1) 
	{
		error (1, errno, "Can't create socket for %s", channel->name);
	}
	memset (&ifreq, 0, sizeof (ifreq));
	memcpy (ifreq.ifr_name, channel->name, sizeof (ifreq.ifr_name));
	if (ioctl (channel->fd, SIOCGIFFLAGS, &ifreq) == -1) 
	{
		error (1, errno, "Can't get %s hardware state", ifreq.ifr_name);
	}
	ifreq.ifr_flags |= IFF_UP;
	if (ioctl (channel->fd, SIOCSIFFLAGS, &ifreq) == -1) 
	{
		error (1, errno, "Can't set %s hardware state", ifreq.ifr_name);
	}
	if (ioctl (channel->fd, SIOCGIFINDEX, &ifreq) == -1) 
	{
		error (1, errno, "Can't get %s interface index", ifreq.ifr_name);
	}
	channel->sockaddr.sll_ifindex = ifreq.ifr_ifindex;
	if (ioctl (channel->fd, SIOCGIFHWADDR, &ifreq) == -1) 
	{
		error (1, errno, "Can't get %s hardware address", ifreq.ifr_name);
	}
	memcpy (channel->sockaddr.sll_addr, ifreq.ifr_ifru.ifru_hwaddr.sa_data, sizeof (channel->sockaddr.sll_addr));
	if (bind (channel->fd, (struct sockaddr *) (&channel->sockaddr), sizeof (struct sockaddr_ll)) == -1) 
	{
		error (1, errno, "Can't bind to %s", ifreq.ifr_name);
	}
	return (0);
}

#endif
 

