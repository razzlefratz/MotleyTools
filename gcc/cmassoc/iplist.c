/*====================================================================*
 *
 *   iplist.c - 
 *
 *   read from stdin and write to stdout; print only dotted decimal 
 *   IPv4 address strings;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

#define _GETOPT_H

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../ether/IPAddr.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../tools/efreopen.c"
#include "../tools/emalloc.c"
#include "../tools/error.c"
#endif

#ifndef MAKEFILE
#include "../ether/IPAddr.c"
#include "../ether/IsIPv4.c"
#include "../ether/getIPv4.c"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define IPLIST_DEBUG (1 << 0)

/*====================================================================*
 *
 *   static void function (flag_t flags);
 *
 *
 *
 *--------------------------------------------------------------------*/

static void function (flag_t flags) 

{
	char buffer [100];
	while (getIPv4 (buffer, sizeof (buffer), stdin)) 
	{
		write (STDOUT_FILENO, buffer, strlen (buffer));
		write (STDOUT_FILENO, "\n", 1);
	}
	return;
}

/*====================================================================*
 *   main program;
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv []) 

{
	static char const * optv [] = 
	{
		"d",
		PUTOPTV_S_FUNNEL,
		"read stdin and write IPv4 addresses to stdout",
		(char const *) (0)
	};
	flag_t flags = 0;
	signed c;
	while ((c = getoptv (argc, argv, optv)) != -1) 
	{
		switch (c) 
		{
		case 'd':
			_setbits (flags, IPLIST_DEBUG);
			break;
		default:
			break;
		}
	}
	argc-= optind;
	argv+= optind;
	if (!argc) 
	{
		function (flags);
	}
	while ((argc) && (* argv)) 
	{
		if (efreopen (* argv, "rb", stdin)) 
		{
			function (flags);
		}
		argc--;
		argv++;
	}
	exit (0);
}

