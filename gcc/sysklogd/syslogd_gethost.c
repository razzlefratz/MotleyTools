/*====================================================================*
 *
 *   char const *syslogd_gethost (struct sockaddr_in *sockaddr, char const *hosts[], char const *domains[]);
 *
 *   syslogd.h
 *
 *   return the lowercase hostname from a socket, if possible; failng 
 *   that, return the IP address or the FQDN;
 *
 *   this function is called to abbreviate the origin field printed
 *   to syslogs; rather than <host>.<domain>, we want <host> only,
 *   when the host is in our local domain or some known domain; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SYSLOGD_GETHOST_SOURCE
#define SYSLOGD_GETHOST_SOURCE

#include <ctype.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "../linux/syslog.h"
#include "../sysklogd/syslogd.h"

#ifdef SYSLOGD_INETAF

char const * syslogd_gethost (struct sockaddr_in * sockaddr, char const * hosts [], char const * domains []) 

{ 
	extern char const * domain_name; 
	struct hostent * hostent; 
	char * sp; 
	if (sockaddr->sin_family != AF_INET) 
	{ 
		return ("nohost"); 
	} 
	hostent = gethostbyaddr (& sockaddr->sin_addr, sizeof (struct in_addr), sockaddr->sin_family); 
	if (hostent == (struct hostent *) (0)) 
	{ 
		return ((char const *) (inet_ntoa (sockaddr->sin_addr))); 
	} 
	for (sp = hostent->h_name; * sp != (char) (0); sp++) 
	{ 
		if (isupper (* sp)) 
		{ 
			* sp = tolower (* sp); 
		} 
	} 
	for (sp = hostent->h_name; * sp != (char) (0); sp++) 
	{ 
		if (* sp != '.') 
		{ 
			continue; 
		} 
		if (!strcmp (sp + 1, domain_name)) 
		{ 
			* sp = (char) (0); 
			return (hostent->h_name); 
		} 
		if (domains == (char const **) (0)) 
		{ 
			continue; 
		} 
		while (* domains != (char *) (0)) 
		{ 
			if (!strcmp (sp + 1, * domains)) 
			{ 
				* sp = (char) (0); 
				return (hostent->h_name); 
			} 
		} 
		if (hosts == (char const **) (0)) 
		{ 
			continue; 
		} 
		while (* hosts != (char const *) (0)) 
		{ 
			if (!strcmp (hostent->h_name, * hosts)) 
			{ 
				* sp = (char) (0); 
				return (hostent->h_name); 
			} 
		} 
	} 
	return (hostent->h_name); 
} 

#endif
#endif



