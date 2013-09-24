/*====================================================================*
 *
 *   struct sockaddr_un *sockspec (char const *string);
 *
 *   tools.h
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SOCKSPEC_SOURCE
#define SOCKSPEC_SOURCE

#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>

#include "../tools/memory.h"
#include "../tools/error.h"

struct sockaddr_un * sockspec(char const * string)

{
	struct sockaddr_un * sockaddr_un;
	sockaddr_un = NEW(struct sockaddr_un);
	if (sockaddr_un == (struct sockaddr_un *)(0))
	{
		error (1, errno, "Can't add sockaddr_un %s", string);
	}
	sockaddr_un->sun_family = AF_UNIX;
	strncpy (sockaddr_un->sun_path, string, sizeof(sockaddr_un->sun_path));
	return (sockaddr_un);
}

#endif



