/*====================================================================*
 *
 *   lp2824.c - Zebra LP2824 Label Printer
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#define _GETOPT_H

/*====================================================================*"
 *   system header files;
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/console.c"
#include "../tools/efopen.c"
#endif

/*====================================================================*
 *   constants;
 *--------------------------------------------------------------------*/

#define LP2824_VERBOSE (1 << 0)
#define LP2824_SILENCE (1 << 1)
#define LP2824_EXAMPLE (1 << 2)

#define OVER 20
#define DOWN 10
#define WIDE 24
#define HIGH 35

/*====================================================================*
 *
 *   void function (int argc, char * argv []);
 *
 *--------------------------------------------------------------------*/

void example (int argc, char const * argv []) 

{
	while ((argc) && (* argv)) 
	{
		printf ("|%-24.24s|\n", * argv++);
	}
	printf ("+------------------------+\n");
	return;
}


/*====================================================================*
 *
 *   void function (int argc, char * argv []);
 *
 *--------------------------------------------------------------------*/

void function (int argc, char const * argv []) 

{
	FILE * fp = efopen ("/dev/lp0", "w");
	unsigned over = OVER;
	unsigned down = DOWN;
	fprintf (fp, "N\n");
	while ((argc) && (* argv)) 
	{
		fprintf (fp, "A%03d,%03d,0,4,1,1,N,\"%-24.24s\"\n", over, down, * argv++);
		down += HIGH;
	}
	fprintf (fp, "P\n");
	fclose (fp);
	return;
}


/*====================================================================*
 *
 *   int main (int argc, char const * argv []);
 *   
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv []) 

{
	static char const * optv [] = 
	{
		"e",
		"text [text] [...]",
		"Zebra LP 2824 Label Printer",
		"e\tprint example label on console",
		(char const *) (0)
	};
	flag_t flags = (flag_t) (0);
	signed c;
	while ((c = getoptv (argc, argv, optv)) != -1) 
	{
		switch (c) 
		{
		case 'e':
			_setbits (flags, LP2824_EXAMPLE);
			break;
		default:
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if (argc > 4) 
	{
		error (1, 0, "Maximum 4 lines per label");
	}
	if (_anyset (flags, LP2824_EXAMPLE)) 
	{
		example (argc, argv);
	}
	else 
	{
		function (argc, argv);
	}
	return (0);
}

