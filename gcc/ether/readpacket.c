/*====================================================================*
 *
 *   signed readpacket (struct channel * channel, void * memory, size_t extent);
 *
 *   channel.h
 *
 *   read one packet from a raw packet channel; 
 *
 *   return the packet size on success, 0 on timeout or -1 on error; 
 *   dump packets on stdout when the channel VERBOSE flag is set; 
 *
 *   constant __MAGIC__ enables code that reads frames from stdin,
 *   instead of the network; you may use it whenever a network or
 *   transmitting device is not available; 
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under GNU General Public License Version 2 Only;
 *
 *--------------------------------------------------------------------*/

#ifndef READPACKET_SOURCE
#define READPACKET_SOURCE

#include <stdlib.h>
#include <unistd.h>
#include <memory.h>
#include <errno.h>

#include "../ether/channel.h"
#include "../tools/memory.h"
#include "../tools/error.h" 
#include "../tools/flags.h"

signed readpacket (struct channel * channel, void * memory, size_t extent) 

{

#if defined (__MAGIC__)

	memset (memory, 0, extent);
	extent = hexload (memory, extent, stdin);
	if (_anyset (channel->flags, CHANNEL_VERBOSE)) 
	{
		hexdump (memory, 0, extent, stdout);
	}
	return ((signed)(extent));

#elif defined (__linux__) 

#include <sys/poll.h>

	struct pollfd pollfd = 
	{
		channel->fd,
		POLLIN,
		0
	};
	signed status = poll (&pollfd, 1, channel->timeout);
	memset (memory, 0, extent);
	if (status < 0) 
	{
		error (0, errno, "%s can't poll %s", __func__, channel->ifname);
		return (-1);
	}
	if (status > 0) 
	{
		status = recvfrom (channel->fd, memory, extent, 0, (struct sockaddr *) (0), (socklen_t *)(0));
		if (status < 0) 
		{
			error (0, errno, "%s can't read %s", __func__, channel->ifname);
			return (-1);
		}
		if (status > 0) 
		{
			if (_anyset (channel->flags, CHANNEL_VERBOSE)) 
			{
				hexdump (memory, 0, status, stdout);
			}
			return (status);
		}
	}

#elif defined (__APPLE__) || defined (__OpenBSD__)

	struct bpf_hdr * bpf_packet;
	memset (memory, 0, extent);
	if (channel->bpf_bufused <= 0) 
	{
		channel->bpf_bufused = read (channel->fd, channel->bpf_buffer, channel->bpf_length);
		channel->bpf_bp = channel->bpf_buffer;
	}
	if (channel->bpf_bufused < 0) 
	{
		error (0, errno, "bpf");
		return (-1);
	}
	if (channel->bpf_bufused > 0) 
	{
		bpf_packet = (struct bpf_hdr *)(channel->bpf_bp);
		extent = bpf_packet->bh_caplen;
		memcpy (memory, channel->bpf_bp + bpf_packet->bh_hdrlen, bpf_packet->bh_caplen);
		channel->bpf_bufused -= BPF_WORDALIGN (bpf_packet->bh_hdrlen + bpf_packet->bh_caplen);
		channel->bpf_bp += BPF_WORDALIGN (bpf_packet->bh_hdrlen + bpf_packet->bh_caplen);
		if (_anyset (channel->flags, CHANNEL_VERBOSE)) 
		{
			hexdump (memory, 0, extent, stdout);
		}
		return ((signed)(extent));
	}

#elif defined (WINPCAP) || defined (LIBPCAP)

	struct pcap_pkthdr * header;
	const uint8_t *data;
	signed status = pcap_next_ex (channel->socket, &header, &data);
	memset (memory, 0, extent);
	if (status < 0) 
	{
		error (0, errno, "pcap_next_ex");
		return (-1);
	}
	if (status > 0) 
	{
		extent = header->caplen;
		memcpy (memory, data, extent);
		if (_anyset (channel->flags, CHANNEL_VERBOSE)) 
		{
			hexdump (memory, 0, extent, stdout);
		}
		return ((signed)(extent));
	}

#else
#error "Unknown Environment"
#endif

	return (0);
}


#endif

