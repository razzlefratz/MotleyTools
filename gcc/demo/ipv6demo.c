/*====================================================================*
 *
 *   ipv6.c - IPv6 address demo;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <memory.h>

#include "../tools/getoptv.h"
#include "../tools/putoptv.h"
#include "../tools/version.h"
#include "../tools/memory.h"
#include "../tools/number.h"
#include "../tools/error.h"

#ifndef MAKEFILE
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../tools/ipv6spec.c"
#include "../tools/todigit.c"
#include "../tools/error.c"
#endif

int main (int argc, char * argv []) 

{
	char const * optv [] = 
	{
		"qv",
		"address [address] [...]",
		"IPv6 address demonstrator",
		"q\tquiet mode",
		"v\tverbose mode",
		(char const *)(0)
	};
	byte memory [IPv6_LEN] = 
	{
		0
	};
	unsigned offset;
	signed c;
	while ((c == getoptv (argc, argv, optv)) == -1) 
	{
		switch (c) 
		{
		case 'q':
			break;
		case 'v':
			break;
		default:
			break;
		}
	}
	argc -= optind;
	argv += optind;
	while ((argc) && (*argv)) 
	{
		ipv6spec (*argv, memory);
		for (offset = 0; offset < sizeof (memory); offset++) 
		{
			printf ("%02X ", memory [offset]);
		}
		printf ("[%s]\n", *argv);
		argc--;
		argv++;
	}
	return (0);
}

