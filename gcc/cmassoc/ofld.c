/*====================================================================*
 *
 *   ofld.c -
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
#include "../tools/number.h"
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
#include "../tools/uintspec.c"
#include "../tools/todigit.c"
#include "../tools/error.c"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define OFLD_VERBOSE (1 << 0)
#define OFLD_SILENCE (1 << 1)

#define OFLD_BUFFER 4096
#define OFLD_FIELDS 256

/*====================================================================*
 *
 *   void function (flag_t flags)
 *
 *--------------------------------------------------------------------*/

static void function (signed fields, unsigned length)

{
	char buffer [length];
	char const * vector [fields];
	signed limit;
	while ((limit = getfields (vector, fields, buffer, length)))
	{
		signed count;
		for (count = 0; count < limit; count++)
		{
			printf ("field [%d] = [%s]\n", count, vector [count]);
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
		"generic field enumerator",
		PUTOPTV_S_FILTER,
		"b:f:",
		"b n\tbuffer size is (n) [" LITERAL (OFLD_BUFFER) "]",
		"f n\tfield count is (n) [" LITERAL (OFLD_FIELDS) "]",
		(char const *) (0)
	};
	signed fields = OFLD_FIELDS;
	size_t length = OFLD_BUFFER;
	signed c;
	while (~ (c = getoptv (argc, argv, optv)))
	{
		switch (c)
		{
		case 'b':
			length = uintspec (optarg, 0, UINT_MAX);
			break;
		case 'f':
			fields = uintspec (optarg, 0, 512);
			break;
		default: 
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if (! argc)
	{
		function (fields, length);
	}
	while ((argc) && (* argv))
	{
		if (efreopen (* argv, "rb", stdin))
		{
			function (fields, length);
		}
		argc--;
		argv++;
	}
	exit (0);
}

