/*====================================================================*
 *
 *   englyph.c - replace special characters to iso glyph codes;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#define _GETOPT_H

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../chrlib/chrlib.h"
#include "../strlib/strlib.h"

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
#include "../strlib/strfglyph.c"
#endif

#ifndef MAKEFILE
#include "../sv/sv_glyph.c"
#endif

/*====================================================================*
 *
 *   void function (flag_t flags);
 *
 *   read stdin and write stdout; replace individual characters with
 *   their ISO glyph where appropriate;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

void function (flag_t flags) 

{
	char buffer [GLYPH_MAX];
	signed c;
	while ((c = getc (stdin)) != EOF) 
	{
		strfglyph (buffer, sizeof (buffer), (unsigned)(c));
		fputs (buffer, stdout);
	}
	return;
}


/*====================================================================*
 *   main function
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv []) 

{
	static char const * optv [] = 
	{
		"",
		PUTOPTV_S_FUNNEL,
		"convert special characters to ISO glyph codes",
		(char const *)(0)
	};
	flag_t flags = (flag_t) (0);
	signed c;
	while ((c = getoptv (argc, argv, optv)) != -1) 
	{
		switch (c) 
		{
		default:
			break;
		}
	}
	argc -= optind;
	argv += optind;
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

