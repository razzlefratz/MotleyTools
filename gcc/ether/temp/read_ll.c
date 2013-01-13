/*====================================================================*
 *
 *   signed read_ll (struct channel *channel, uint8_t packet [], signed packetsize);
 *
 *   channel.h
 *   
 *   receive a raw packet over the specified channel; dump incoming
 *   frames on stdout when the channel->flags verbose bit is set and
 *   print warnings on stderr when the warning bit is set;
 *
 *   struct channel is defined in channel.h and the components used
 *   here are:
 *
 *      channel->fd
 *      channel->sockaddr
 *      channel->sockaddrsize
 *      channel->timeout
 *      channel->flags
 *
 *.  Motley Tools by Charles Maier <cmaier@cmassoc.net>;
 *:  Published 2005 by Charles Maier Associates Limited;
 *;  Released under the GNU General Public Licence v2 and later;
 *
 *--------------------------------------------------------------------*/

#ifndef READ_LL_SOURCE
#define READ_LL_SOURCE

#include <string.h>
#include <stdint.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/poll.h>

#include "../ether/channel.h"
#include "../tools/memory.h"
#include "../tools/error.h"
 
signed read_ll (struct channel * channel, uint8_t packet [], signed packetsize) 

{
	struct pollfd pollfd = 
	{
		channel->fd,
		POLLIN,
		0 
	};
	int status = poll (&pollfd, 1, channel->timeout);
	if (status < 0) 
	{
		error (1, errno, "transmission error");
	}
	if (status > 0) 
	{
		memset (packet, 0, packetsize);
		packetsize = recvfrom (channel->fd, packet, packetsize, 0, (struct sockaddr *) (&channel->sockaddr), &channel->sockaddrsize);
		if (packetsize < 0) 
		{
			error (1, errno, "can't read response");
		}
		if (channel->flags & CHANNEL_VERBOSE) 
		{
			hexdump (packet, 0, packetsize, stdout);
		}
		return (packetsize);
	}
	return (status);
}

#endif
 

