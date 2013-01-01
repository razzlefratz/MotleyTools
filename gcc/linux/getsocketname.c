/*====================================================================*
 *
 *   size_t getsocketname (char buffer[], size_t length, struct sockaddr_in *sockaddr_in);
 *
 *   encode a buffer with the address and port number of a socket;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef GETSOCKETNAME_SOURCE
#define GETSOCKETNAME_SOURCE

#include <stdio.h>
#include <arpa/inet.h>

size_t getsocketname (char buffer [], size_t length, struct sockaddr_in *sockaddr_in) 

{
	return (snprintf (buffer, length, "%s:%d", inet_ntoa (sockaddr_in->sin_addr), sockaddr_in->sin_port));
}


#endif

