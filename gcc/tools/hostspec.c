/*====================================================================*
 *
 *   sockaddr_in * hostspec (char const * string);
 *
 *   tools.h
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef HOSTSPEC_SOURCE
#define HOSTSPEC_SOURCE

#include <ctype.h>
#include <string.h>
#include <error.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "../tools/tools.h"
#include "../tools/error.h"
#include "../tools/sizes.h"
#include "../strlib/strlib.h"

struct sockaddr_in * hostspec(char const * string)

{
	struct sockaddr_in * sockaddr_in;
	struct hostent * hostent;
	char buffer[HOSTNAME_MAX];
	char const * sp = string;
	char * cp = buffer;
	unsigned port = 0;
	while (isdigit(* sp) || (* sp == '.'))
	{
		* cp++ = * sp++;
	}
	* cp = (char)(0);
	if ((hostent = gethostbyname(buffer)) == (struct hostent *)(0))
	{
		error (1, 0, "Can't resolve hostname %s", string);
	}
	if (* sp == ':')
	{
		while (isdigit(* ++ sp))
		{
			port *= 10;
			port += * sp - '0';
		}
	}
	if (* sp)
	{
		error (1, 0, "Bad inet address syntax: %s", string);
	}
	sockaddr_in = NEW(struct sockaddr_in);
	if (sockaddr_in == (struct sockaddr_in *) (0))
	{
		error (1, errno, "Can't create socket %s", string);
	}
	memset (sockaddr_in, 0, sizeof(struct sockaddr_in));
	sockaddr_in->sin_family = AF_INET;
	sockaddr_in->sin_port = port;
	memcpy (& sockaddr_in->sin_addr, * hostent->h_addr_list, hostent->h_length);
	return (sockaddr_in);
}

#endif



