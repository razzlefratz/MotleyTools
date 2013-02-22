/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#ifndef SERVER_SOURCE
#define SERVER_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <string.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "ServerSocket.h"
#include "SocketException.h"

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

int main (int argc, int argv []) 

{
	std::cout << "running....\n";
	try 
	{
		ServerSocket server (30000);
		while (true) 
		{
			ServerSocket new_sock;
			server.accept (new_sock);
			try 
			{
				while (true) 
				{
					std::string data;
					new_sock >> data;
					new_sock << data;
				}
			}
			catch (SocketException &) 
			{
			}
		}
	}
	catch (SocketException & e) 
	{
		std::cout << "Exception was caught:" << e.description () << "\nExiting.\n";
	}
	exit (0);
}


#endif

