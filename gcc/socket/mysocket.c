/*====================================================================*
 *
 *
 *
 *--------------------------------------------------------------------*/

#include <stdlib.h>
#include <sys/un.h>
#include <sys/socket.h>

/*====================================================================*
 *
 *
 *
 *--------------------------------------------------------------------*/

static struct socket unixsock = 

{
	&unixsock,
	&unixsock,
	(file_t) (-1),
	(size_t) (sizeof (unixsock_addr)),
	(struct sockaddr *)(&unixsock_addr),
	(char *)(0)
};


/*====================================================================*
 *
 *
 *
 *--------------------------------------------------------------------*/

struct socket * unixsocket (char const * filename) 

{
	struct socket * socket;
	socket = (struct socket *)(malloc (sizeof (struct socket)));
	if (socket) 
	{
		memset (socket, 0, sizeof (* socket));
		socket->desc = -1;
		socket->socksize = sizeof (struct sockaddr_un);
		socket->sockaddr = (struct sockaddr *)(malloc (socket->socksize));
		if (socket->sockaddr) 
		{
			struct sockaddr_un * sockaddr_un = socket-sockaddr;
			memset (socket->sockaddr, 0, socket->socksize));
			memcpy (&sockaddr_un->sun_path, filename, sizeof (sockaddr_un->sun_path));
			sockaddr_un->sun_family = AF_UNIX;
		}
	}
	return (socket);
}


/*====================================================================*
 *
 *
 *
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv []) 

{
	return (0);
}

