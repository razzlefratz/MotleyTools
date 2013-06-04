/*====================================================================*
 *
 *   owrt.c - 
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
#include <limits.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/getoptv.h"
#include "../tools/putoptv.h"
#include "../tools/symbol.h"
#include "../tools/error.h"
#include "../tools/types.h"
#include "../tools/flags.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../tools/efreopen.c"
#include "../tools/getfields.c"
#include "../tools/error.c"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define OFLD_VERBOSE (1 << 0)
#define OFLD_SILENCE (1 << 1)
#define OFLD_BAILOUT (1 << 2)
#define OFLD_ONELINE (1 << 3)

static char buffer [0x1000];
static char const * argv [0x10];

/*====================================================================*
 *
 *   void function (flag_t flags)
 *
 *--------------------------------------------------------------------*/

static void function () 

{
	signed limit;
	while ((limit = getfields (argv, SIZEOF (argv), buffer, sizeof (buffer)))) 
	{
		signed count;
		for (count = 0; count < limit; count++) 
		{
			printf ("field [%d]=[%s]\n", count, argv [count]);
		}
		printf ("\n");
	}
	return;
}


/*====================================================================*
 *
 *   int main (int argc, char const * argv []);
 *
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv []) 

{
	static char const * optv [] = 
	{
		"abeoqv",
		PUTOPTV_S_FUNNEL,
		"OpenWRT Makefile Tool",
		"q\tsuppress routine messages",
		"v\tenable verbose messages",
		(char const *)(0)
	};
	flag_t flags = (flag_t)(0);
	signed c;
	while ((c = getoptv (argc, argv, optv)) != -1) 
	{
		switch (c) 
		{
		case 'q':
			_setbits (flags, OFLD_SILENCE);
			break;
		case 'v':
			_setbits (flags, OFLD_VERBOSE);
			break;
		default:
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if (!argc) 
	{
		function ();
	}
	while ((argc) && (* argv)) 
	{
		if (efreopen (* argv, "rb", stdin)) 
		{
			function ();
		}
		argc--;
		argv++;
	}
	exit (0);
}

