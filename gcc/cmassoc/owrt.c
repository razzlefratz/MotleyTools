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
#include <limits.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/getoptv.h"
#include "../tools/putoptv.h"
#include "../tools/error.h"
#include "../tools/types.h"
#include "../tools/flags.h"
#include "../tools/symbol.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../tools/efreopen.c"
#include "../tools/getargv.c"
#include "../tools/error.c"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define OWRT_VERBOSE (1 << 0)
#define OWRT_SILENCE (1 << 1)
#define OWRT_BAILOUT (1 << 2)

#define OWRT_COMPANY 0
#define OWRT_PACKAGE 1
#define OWRT_LIBRARY 2
#define OWRT_PROGRAM 3
#define OWRT_TITLE 4
#define OWRT_SUMMARY 5
#define OWRT_MAXIMUM 6

/*====================================================================*
 *
 *   void describe (flag_t flags)
 *
 *--------------------------------------------------------------------*/

static void describe (flag_t flags) 

{
	char const * argv [16];
	signed argc;
	while ((argc = getargv (SIZEOF (argv), argv)))
	{
		printf ("define %s/%s/%s\n", argv [OWRT_COMPANY], argv [OWRT_PACKAGE], argv [OWRT_PROGRAM]);
		printf (" define Package/%s-%s\n", argv [OWRT_PACKAGE], argv [OWRT_PROGRAM]);
		printf ("  $(call Package/%s/common)\n", argv [OWRT_PACKAGE]);
		printf ("  OWRT_TITLE:=%s\n", argv [OWRT_TITLE]);
		printf ("  DEPENDS+=%s\n", argv [OWRT_PACKAGE]);
		printf (" endef\n");
		printf (" define Package/%s-%s/description\n", argv [OWRT_PACKAGE], argv [OWRT_PROGRAM]);
		printf ("  %s\n", argv [OWRT_SUMMARY]);
		printf (" endef\n");
		printf (" define Package/%s-%s/install\n", argv [OWRT_PACKAGE], argv [OWRT_PROGRAM]);
		printf ("  $(INSTALL_DIR) $$(1)/usr/bin\n");
		printf ("  $(INSTALL_BIN) $(PKG_BUILD_DIR)/%s/%s $$(1)/usr/bin\n", argv [OWRT_LIBRARY], argv [OWRT_PROGRAM]);
		printf (" endef\n");
		printf (" $$(eval $$(call BuildPackage,%s-%s))\n", argv [OWRT_PACKAGE], argv [OWRT_PROGRAM]);
		printf ("endef\n");
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
		"qv",
		PUTOPTV_S_FUNNEL,
		"basic C language program",
		"q\tsuppress routine messages",
		"v\tenable verbose messages",
		(char const *)(0)
	};
	void (* function) () = describe;
	flag_t flags = (flag_t)(0);
	signed c;
	while ((c = getoptv (argc, argv, optv)) != -1) 
	{
		switch (c) 
		{
		case 'q':
			_setbits (flags, OWRT_SILENCE);
			break;
		case 'v':
			_setbits (flags, OWRT_VERBOSE);
			break;
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

