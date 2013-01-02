/*====================================================================*
 *
 *   oifs.cpp - oifs class definition;
 *
 *   host interface enumerator;  
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oIFS_SOURCE
#define oIFS_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cerrno>

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <net/if.h>
#include <net/ethernet.h>

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#if defined (__linux__)
#	include <sys/ioctl.h>
#	include <netinet/in.h>
#elif defined (__APPLE__)
#	include <net/bpf.h>
#	include <sys/types.h>
#	include <sys/socket.h>
#	include <net/if_dl.h>
#	include <ifaddrs.h>
#	include <sys/ioctl.h>
#	include <fcntl.h>
#elif defined (__OpenBSD__)
#	include <net/if.h>
#	include <net/if_dl.h>
#	include <sys/poll.h>
#	include <net/ethernet.h>
#elif defined (WINPCAP)
#	include <pcap.h>
#	include <pcap/Packet32.h>
#	include <pcap/ntddndis.h>
#	include <net/ethernet.h>
#else
#error "Unknown environment."
#endif

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/oifs.hpp"
#include "../classes/omemory.hpp"
#include "../classes/oerror.hpp"

/*====================================================================*
 *
 *   unsigned Count (void) const;
 *
 *   return the number of interfaces;
 *
 *--------------------------------------------------------------------*/

unsigned oifs::Count (void) const 

{
	return (this->mcount);
}


/*====================================================================*
 *
 *   unsigned Index (void) const;
 *
 *   return the current interface index;
 *
 *--------------------------------------------------------------------*/

unsigned oifs::Index (void) const 

{
	return (this->mindex);
}


/*====================================================================*
 *
 *   oifs & SelectFirst (void);
 *
 *   select first interfac;
 *
 *--------------------------------------------------------------------*/

oifs & oifs::SelectFirst (void) 

{
	this->mindex = 0;
	return (*this);
}


/*====================================================================*
 *
 *   oifs & SelectFinal (void);
 *
 *   select final interface;
 *
 *--------------------------------------------------------------------*/

oifs & oifs::SelectFinal (void) 

{
	this->mindex = this->mcount - 1;
	return (*this);
}


/*====================================================================*
 *
 *   oifs & SelectPrev (void) 
 *
 *   select the prev interface unless the current interface is the
 *   first interface; same as operator --;
 *
 *--------------------------------------------------------------------*/

oifs & oifs::SelectPrev (void) 

{
	if (this->mindex > 0) 
	{
		this->mindex--;
	}
	return (*this);
}


/*====================================================================*
 *
 *   oifs & SelectNext (void) 
 *
 *   select the next interface unless the current interface is the
 *   final interface; same as operator ++; 
 *
 *--------------------------------------------------------------------*/

oifs & oifs::SelectNext (void) 

{
	if (this->mindex < this->mcount) 
	{
		this->mindex++;
	}
	return (*this);
}


/*====================================================================*
 *
 *   oifs & Select (unsigned index);
 *
 *   select an interface by number; same as operator [];
 *
 *--------------------------------------------------------------------*/

oifs & oifs::Select (unsigned index) 

{
	this->mindex = index;
	if (this->mindex > this->mcount) 
	{
		this->mindex = this->mcount;
	}
	return (*this);
}


/*====================================================================*
 *
 *   oif & Selected (unsigned index) 
 *
 *   return the selected interface; 
 *
 *--------------------------------------------------------------------*/

oif & oifs::Selected () const 

{
	return (this->mtable [this->mindex]);
}


/*====================================================================*
 *
 *   oifs & Enumerate (void);
 *
 *   interate through interfaces and print them on stdout; do not
 *   change the selected interface;
 *
 *--------------------------------------------------------------------*/

oifs & oifs::Enumerate (void) 

{
	unsigned index;
	for (index = 0; index < this->mcount; index++) 
	{
		this->mtable [index].Print ();
	}
	return (*this);
}


/*====================================================================*
 *
 *   oif & operator [] (unsigned index) 
 *
 *   select an interface then return an instance of it;
 *
 *--------------------------------------------------------------------*/

oif & oifs::operator [] (unsigned index) 

{
	return (this->Select (index).Selected ());
}


/*====================================================================*
 *
 *   oifs & operator ++ (signed) 
 *
 *   select the next interface unless the current interface is the
 *   final interface; same as method SelectNext;
 *
 *--------------------------------------------------------------------*/

oifs & oifs::operator ++ (signed) 

{
	return (this->SelectNext ());
}


/*====================================================================*
 *
 *   oifs & operator -- (signed) 
 *
 *   select the prev interface unless the current interface is the
 *   first interface; same as method SelectPrev; 
 *
 *--------------------------------------------------------------------*/

oifs & oifs::operator -- (signed) 

{
	return (this->SelectPrev ());
}


/*====================================================================*
 *
 *   oifs () 
 *
 *   construct a collection oif objects each representing one
 *   host Ethernet interface;
 *
 *--------------------------------------------------------------------*/

oifs::oifs () 

{

#if defined (__linux__)

	struct ifconf ifc;
	struct ifreq *ifr;
	char buffer [1024];
	signed fd;
	if ((fd = socket (AF_INET, SOCK_DGRAM, 0)) < 0) 
	{
		oerror::error (1, errno, "can't open socket");
	}
	ifc.ifc_len = sizeof (buffer);
	ifc.ifc_buf = buffer;
	if (ioctl (fd, SIOCGIFCONF, &ifc) < 0) 
	{
		oerror::error (1, errno, "Can't enumerate interfaces");
	}
	ifr = ifc.ifc_req;
	this->mindex = 0;
	this->mcount = ifc.ifc_len / sizeof (struct ifreq);
	this->mtable = new oif [this->mcount];
	while (this->mindex < this->mcount) 
	{
		oif ifp;
		ifp.SetName (ifr->ifr_ifrn.ifrn_name);
		ifp.SetText (ifr->ifr_ifrn.ifrn_name);
		this->mtable [this->mindex++] = ifp;
		ifr++;
	}
	close (fd);

#elif defined (WINPCAP) 

	char buffer [PCAP_ERRBUF_SIZE];
	pcap_if_t * devices = (pcap_if_t *)(0);
	pcap_if_t * device;
	if (pcap_findalldevs (&devices, buffer) == -1) 
	{
		oerror::error (1, errno, "Can't enumerate interfaces");
	}
	this->mindex = 0;
	this->mcount = 0;
	for (device = devices; device; device = device->next) 
	{
		this->mcount++;
	}
	this->mtable = new oif [this->mcount];
	for (device = devices; device; device = device->next) 
	{
		oif ifp;
		ifp.SetName (device->name);
		ifp.SetText (device->description);
		this->mtable [this->mindex++] = ifp;
	}
	pcap_freealldevs (devices);

#endif

	return;
}


/*====================================================================*
 *
 *   ~oifs () 
 *
 *--------------------------------------------------------------------*/

oifs::~oifs () 

{
	return;
}


/*====================================================================*
 *   end definition;
 *--------------------------------------------------------------------*/

#endif

