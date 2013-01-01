/*====================================================================*
 *
 *   void pcap_freenameindex (struct if_nameindex *) 
 *
 *   ether.h
 *
 *   a WinPcap version of POSIX if_freenameindex function; 
 *
 *   see The Open Group Base Specifications Issue 6 IEEE Std 1003.1, 
 *   2004 Edition for a description of this function;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef PCAP_FREENAMEINDEX_SOURCE
#define PCAP_FREENAMEINDEX_SOURCE

#include <pcap.h>
#include <net/if.h>
#include <stdlib.h>

#include "../ether/ether.h"

void pcap_freenameindex (struct if_nameindex * if_nameindex) 

{

#if defined (WINPCAP)

	struct if_nameindex * ifp = if_nameindex;
	while (ifp->if_index) 
	{
		free (ifp->if_name);
	}
	free (if_nameindex);

#endif

	return;
}


#endif

