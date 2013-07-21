/*====================================================================*
 *
 *
 *--------------------------------------------------------------------*/

#include <stdlib.h>
#include <sys/un.h>
#include <sys/socket.h>

struct socket * unixsocket (char const * filename) 

{ 
	struct socket * socket; 
	socket = (struct socket *) (malloc (sizeof (struct socket))); 
	if (socket) 
	{ 
		memset (socket, 0, sizeof (* socket)); 
		socket->desc = - 1; 
		socket->socksize = sizeof (struct sockaddr_un); 
		socket->sockaddr = (struct sockaddr *) (malloc (socket->socksize)); 
		if (socket->sockaddr) 
		{ 
			struct sockaddr_un * sockaddr_un = socket - sockaddr; 
			memset (socket->sockaddr, 0, socket->socksize)); 
			memcpy (& sockaddr_un->sun_path, filename, sizeof (sockaddr_un->sun_path)); 
			sockaddr_un->sun_family = AF_UNIX; 
		} 
	} 
	return (socket); 
} 

