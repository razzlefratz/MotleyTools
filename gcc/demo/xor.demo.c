/*====================================================================*
 *
 *   xor.c - display argument vector;
 *
 *   this program demonstrates the difference between logical not (!) and
 *   bitwise not (~) operations; command line arguments are converted to
 *   integers and printed along with their ! and ~ conversions;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

#include "../linux/network.h"
#include "../linux/IPAddress.c"
#include "../tools/itosn.c"

int main (int argc, char const *argv []) 

{
	uid_t uid = getuid ();
	char buffer [100];
	unsigned network;
	unsigned netmask;
	unsigned address;
	unsigned request;
	unsigned connect;
	if (argc == 5) 
	{
		network = IPNumber (argv [1]);
		netmask = IPNumber (argv [2]);
		address = IPNumber (argv [3]);
		request = IPNumber (argv [4]);
		connect = (network ^ netmask ^ request) & address;
		printf ("network [%8.8x] [%s] [%s]\n", network, itosn (network, buffer, 33, "01"), IPString (network));
		printf ("netmask [%8.8x] [%s] [%s]\n", netmask, itosn (netmask, buffer, 33, "01"), IPString (netmask));
		printf ("address [%8.8x] [%s] [%s]\n", address, itosn (address, buffer, 33, "01"), IPString (address));
		printf ("request [%8.8x] [%s] [%s]\n", request, itosn (request, buffer, 33, "01"), IPString (request));
		printf ("connect [%8.8x] [%s] [%s]\n", connect, itosn (connect, buffer, 33, "01"), IPString (connect));
	}
	printf ("uid=[%d]\n", uid);
	return (0);
}

