/*====================================================================*
 *
 *
 *
 *--------------------------------------------------------------------*/

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <stdlib.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <sys/stat.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/types.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../socket/plc_unix_socket.c"
#endif

#ifndef MAKEFILE
#include "../tools/error.c"
#endif

#define SOCKET "/tmp/mysocket"
#define ACCESS S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH 

/*====================================================================*
 *
 *
 *
 *--------------------------------------------------------------------*/

char const * program_name = "server";
int main (int argc, char const * argv []) 

{
	file_t fd;
	struct sockaddr_un sockaddr_un;
	if ((fd = socket (AF_UNIX, SOCK_DGRAM, 0)) == -1) 
	{
		error (1, errno, "Can't create socket");
	}
	if (unlink (SOCKET)) 
	{
		if (errno != ENOENT) 
		{
			error (1, errno, "Can't remove %s", SOCKET);
		}
	}
	memset (&sockaddr_un, 0, sizeof (sockaddr_un));
	sockaddr_un.sun_family = AF_UNIX;
	memcpy (&sockaddr_un.sun_path, SOCKET, sizeof (sockaddr_un.sun_path));
	if (bind (fd, (struct sockaddr *) (&sockaddr_un), sizeof (sockaddr_un.sun_family) + strlen (sockaddr_un.sun_path)) == -1) 
	{
		error (1, errno, "%s", SOCKET);
	}
	if (chmod (SOCKET, ACCESS) == -1) 
	{
		error (1, errno, "%s", SOCKET);
	}

#if 0

	if (unlink (SOCKET)) 
	{
		error (0, errno, "%s", SOCKET);
	}

#endif

	close (fd);
	return (0);
}

