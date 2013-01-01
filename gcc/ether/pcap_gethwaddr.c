/*====================================================================*
 *
 *   void pcap_gethwaddr (char const * name, void * memory);
 *
 *   ether.h
 *
 *   update the hardware address based on interface name in winpcap
 *   environment only; it has no effect in non-pcap environments;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef PCAP_GETHWADDR_SOURCE
#define PCAP_GETHWADDR_SOURCE

#include <pcap.h>
#include <stdlib.h>
#include <string.h>
#include <net/ethernet.h>    

#include "../ether/ether.h"
#include "../tools/error.h"

void pcap_gethwaddr (char const * name, void * memory) 

{

#if defined (WINPCAP)

	LPADAPTER adapter = PacketOpenAdapter ((PCHAR)(name));
	PPACKET_OID_DATA data = (PPACKET_OID_DATA)(malloc (ETHER_ADDR_LEN + sizeof (PACKET_OID_DATA)));
	if (!data) 
	{
		error (1, 0, "Can't allocate packet: %s", name);
	}
	data->Oid = OID_802_3_CURRENT_ADDRESS;
	data->Length = ETHER_ADDR_LEN;
	if ((!adapter) || (adapter->hFile == INVALID_HANDLE_VALUE)) 
	{
		error (1, 0, "Can't access interface: %s", name);
	}
	memset (memory, 0, ETHER_ADDR_LEN);
	if (PacketRequest (adapter, FALSE, data)) 
	{
		memcpy (memory, data->Data, data->Length);
	}
	PacketCloseAdapter (adapter);
	free (data);

#endif

	return;
}


#endif

