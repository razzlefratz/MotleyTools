/*====================================================================*
 *
 *   localhost.c - manage system host/domain name;
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
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/console.c"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define HOSTNAME1 "/proc/sys/kernel/hostname"
#define HOSTNAME2 "/etc/hostname"

/*====================================================================*
 *   main program;
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv []) 

{ 
	static char const * optv [] = 
	{ 
		"d:h:l", 
		PUTOPTV_S_DIVINE, 
		"manage system hostname and domainname", 
		"d s\tset domainname to (s)", 
		"h s\tset hostname to (s)", 
		"l\tcreate link " HOSTNAME2 "-->" HOSTNAME1, 
		(char const *)(0)
	}; 
	struct stat statinfo; 
	char machine [1024] = ""; 
	char network [1024] = ""; 
	signed c; 
	while ((c = getoptv (argc, argv, optv)) != - 1) 
	{ 
		switch (c) 
		{ 
		case 'h': 
			if (sethostname (optarg, strlen (optarg))) 
			{ 
				error (1, errno, "%s", argv [0]); 
			} 
			break; 
		case 'd': 
			if (setdomainname (optarg, strlen (optarg))) 
			{ 
				error (1, errno, "%s", argv [0]); 
			} 
			break; 
		case 'l': 
			if (stat (HOSTNAME1, & statinfo)) 
			{ 
				error (1, errno, "Can't stat %s", HOSTNAME1); 
			} 
			if (stat (HOSTNAME2, & statinfo)) 
			{ 
				error (1, errno, "Can't stat %s", HOSTNAME2); 
			} 
			if (remove (HOSTNAME2)) 
			{ 
				error (1, errno, "Can't remove %s", HOSTNAME2); 
			} 
			if (symlink (HOSTNAME1, HOSTNAME2)) 
			{ 
				error (1, errno, "Can't create %s", HOSTNAME2); 
			} 
			break; 
		default: 
			break; 
		} 
	} 
	if (gethostname (machine, sizeof (machine))) 
	{ 
		error (1, errno, "Can't read gethostname."); 
	} 
	if (getdomainname (network, sizeof (network))) 
	{ 
		error (1, errno, "Can't read domain name."); 
	} 
	printf ("%s.%s\n", machine, network); 
	exit (0); 
} 

