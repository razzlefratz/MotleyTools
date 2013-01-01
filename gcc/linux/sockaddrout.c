/*====================================================================*
 *
 *   void sockaddrout (struct sockaddr_ll * sockaddr);
 *   
 *   
 *--------------------------------------------------------------------*/

#ifndef SOCKADDROUT_SOURCE
#define SOCKADDROUT_SOURCE

#include <stdio.h>
#include <netpacket/packet.h>
#include "../ether/packet_ll.h"

void sockaddrout (struct sockaddr_ll * sockaddr, FILE *fp) 

{
	size_t octet;
	fprintf (fp, "sockaddr->sll_family(%d)\n", sockaddr->sll_family);
	fprintf (fp, "sockaddr->sll_protocol(0x%02X)\n", sockaddr->sll_protocol);
	fprintf (fp, "sockaddr->sll_ifindex=(%d)\n", sockaddr->sll_ifindex);
	fprintf (fp, "sockaddr->sll_hatype=(%d)\n", sockaddr->sll_hatype);
	fprintf (fp, "sockaddr->sll_pkttype=(%d)\n", sockaddr->sll_pkttype);
	fprintf (fp, "sockaddr->sll_halen=(%d)\n", sockaddr->sll_halen);
	for (octet = 0; octet < sockaddr->sll_halen; octet++) 
	{
		fprintf (fp, "sockaddr->sll_addr[%d]=(0x%02X)\n", octet, sockaddr->sll_addr [octet]);
	}
	fprintf (fp, "\n");
	return;
}


#endif

