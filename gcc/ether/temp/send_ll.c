/*====================================================================*
 *
 *   signed send_ll (struct channel * channel, uint8_t packet[], signed length);
 *
 *   channel.h
 *   
 *   send a raw packet over the specified channel; dump all outgoing
 *   frames on stdout when the channel->flags verbose bit is set and
 *   print warnings on stderr when the warning bit is set;
 *
 *   struct channel is defined in channel.h and the components used 
 *   here are:
 *
 *      channel->fd
 *      channel->sockaddr
 *      channel->sockaddrsize
 *      channel->bailout
 *      channel->flags
 *
 *.  Motley Tools by Charles Maier <cmaier@cmassoc.net>;
 *:  Published 2005 by Charles Maier Associates Limited;
 *;  Released under the GNU General Public Licence v2 and later;
 *
 *--------------------------------------------------------------------*/

#ifndef SENDTO_LL_SOURCE
#define SENDTO_LL_SOURCE

#include <errno.h>
#include <sys/socket.h>

#include "../ether/channel.h"
#include "../tools/memory.h"
#include "../tools/error.h"
 
signed send_ll (struct channel * channel, uint8_t packet [], signed length) 

{
	int status;
	if (channel->flags & CHANNEL_VERBOSE) 
	{
		hexdump (packet, 0, length, stdout);
	}
	status = sendto (channel->fd, packet, length, 0, (struct sockaddr *) (&channel->sockaddr), channel->sockaddrsize);
	if (status == -1) 
	{
		error (1, errno, "can't send your stupid little packet to whereever it was you wanted");
	}
	return (0);
}

#endif
 

