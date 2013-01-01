/*====================================================================*
 *
 *   signed closechannel (struct channel * channel);
 *
 *   channel.h
 *
 *   close ethernet raw packet channel;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef CLOSECHANNEL_SOURCE
#define CLOSECHANNEL_SOURCE

#include <unistd.h>
#include <stdlib.h>

#include "../ether/channel.h"

signed closechannel (struct channel * channel) 

{

#if defined (__linux__) 

	return (close (channel->fd));

#elif defined (__APPLE__) || (__OpenBSD__)

	free (channel->bpf_buffer);
	return (close (channel->fd));

#elif defined (WINPCAP) || defined (LIBPCAP)

	pcap_close (channel->socket);
	return (0);

#else
#error "Unknown Environment"
#endif

}


#endif

