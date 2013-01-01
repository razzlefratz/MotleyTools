/*====================================================================*
 *
 *   signed anynic (char buffer [], size_t length);
 *
 *   find an available host Ethernet interface and copy the name
 *   into the designated buffer; truncate the name if necessary;
 *   return 0 on success or -1 on error;
 *
 *   if the only interface is loopback then -1 is returned since 
 *   lo is of no use;
 *
 *   this function is only available for Linux at this time and
 *   is only used by the CGI device manager;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef ANYNIC_SOURCE
#define ANYNIC_SOURCE

#include <memory.h>
#include <errno.h>
#include <net/if.h>
#include <sys/ioctl.h>

#include "../ether/ether.h"
#include "../tools/error.h"

signed anynic (char buffer [], size_t length) 

{
	char memory [1024];
	struct ifconf ifc;
	struct ifreq *ifr;
	signed fd;
	memset (buffer, 0, length);
	if ((fd = socket (AF_INET, SOCK_DGRAM, 0)) < 0) 
	{
		error (1, errno, "Can't open socket");
	}
	ifc.ifc_len = sizeof (memory);
	ifc.ifc_buf = memory;
	if (ioctl (fd, SIOCGIFCONF, &ifc) < 0) 
	{
		error (1, errno, "Can't read configuration");
	}
	ifr = ifc.ifc_req;
	if ((length) && (ifc.ifc_len > sizeof (struct ifreq))) 
	{
		memcpy (buffer, (++ifr)->ifr_name, --length);
		return (0);
	}
	return (-1);
}


#endif

