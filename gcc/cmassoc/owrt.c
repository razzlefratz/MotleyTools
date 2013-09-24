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

#define OWRT_VERBOSE (1 << 0)
#define OWRT_SILENCE (1 << 1)
#define OWRT_BAILOUT (1 << 2)
#define OWRT_ONELINE (1 << 3)

#define OWRT_NAME_HANDLER "MotleyTool"
#define OWRT_NAME_PACKAGE "MotleyTools"

#define OWRT_SIZE_VECTOR 0x10
#define OWRT_SIZE_BUFFER 0x1000

#define OWRT_HANDLER 0
#define OWRT_PACKAGE 1
#define OWRT_LIBRARY 2
#define OWRT_PROGRAM 3
#define OWRT_TITLE 4
#define OWRT_SUMMARY 5
#define OWRT_MAXIMUM 6

/*====================================================================*
 *
 *   void define_handler (char const * name, char const * package);
 *
 *   print a GNU make variable definition on stdout; the definition
 *   expands to OpenWRT steps needed to add one program to the menu
 *   coniguration; 
 *
 *   $(1) is the package folder where the compiled program exists;
 *   $(2) is the program name; 
 *   $(3) is the program title or short decription;
 *   $(4) is the program description;
 *
 *--------------------------------------------------------------------*/

static void define_handler (char const * handler, char const * package)

{
	printf ("# ===\n# define package program handler;\n# ---\n\n");
	printf ("define %s\n", handler);
	printf ("  define Package/%s-$(2)\n", package);
	printf ("    $(call Package/%s/default)\n", package);
	printf ("    TITLE:=$(3)\n");
	printf ("    DEPENDS+=%s\n", package);
	printf ("  endef\n");
	printf ("  define Package/%s-$(2)/description\n", package);
	printf ("    $(4)\n");
	printf ("  endef\n");
	printf ("  define Package/%s-$(2)/install\n", package);
	printf ("	$(INSTALL_DIR) $$(1)/usr/bin\n");
	printf ("	$(INSTALL_BIN) $(PKG_BUILD_DIR)/$(1)/$(2) $$(1)/usr/bin\n");
	printf ("  endef\n");
	printf ("  $$(eval $$(call BuildPackage,%s-$(2)))\n", package);
	printf ("endef\n\n");
	return;
}

/*====================================================================*
 *
 *   void invoke_handler (signed count, size_t length, flag_t flags);
 *
 *   print GNU make variable expansions on stdout; expansions have
 *   the form '$(eval $(call variable,.,.,.))' where the arguments
 *   are read from stdin using getargv;
 *
 *   enclose the last two arguments in single quotes because they
 *   often contain white space; there should be a better way since
 *   these quotes appear in the build menu;
 *
 *--------------------------------------------------------------------*/

static void invoke_handler (signed count, size_t length, flag_t flags)

{
	char const * fields [count];
	char buffer [length];
	printf ("# ===\n# call package program handler;\n# ---\n\n");
	while (getfields (fields, count, buffer, length))
	{
		if (_anyset (flags, OWRT_ONELINE))
		{
			printf ("$(eval $(call %s \\\n", fields [OWRT_HANDLER]);
			printf ("\t,%s \\\n", fields [OWRT_LIBRARY]);
			printf ("\t,%s \\\n", fields [OWRT_PROGRAM]);
			printf ("\t,'%s' \\\n", fields [OWRT_TITLE]);
			printf ("\t,'%s' \\\n", fields [OWRT_SUMMARY]);
			printf ("))\n");
		}
		else 
		{
			printf ("$(eval $(call %s", fields [OWRT_HANDLER]);
			printf (",%s", fields [OWRT_LIBRARY]);
			printf (",%s", fields [OWRT_PROGRAM]);
			printf (",'%s'", fields [OWRT_TITLE]);
			printf (",'%s'", fields [OWRT_SUMMARY]);
			printf ("))\n");
		}
	}
	printf ("\n");
	return;
}

/*====================================================================*
 *
 *   void enumerate (signed fields, size_t length);
 *
 *
 *--------------------------------------------------------------------*/

static void enumerate (signed fields, size_t length)

{
	char const * vector [fields];
	char buffer [length];
	signed count;
	while ((count = getfields (vector, fields, buffer, length)))
	{
		signed index;
		for (index = 0; index < count; index++)
		{
			printf ("field[%d]=[%s]\n", index, vector [index]);
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
		"ceh:p:qv",
		PUTOPTV_S_FUNNEL,
		"OpenWRT Makefile Tool",
		"c\tcontinuation line output",
		"e\tenumerate fields",
		"h s\thandler name is (s) [" LITERAL (OWRT_NAME_HANDLER) "]",
		"p s\tpackage name is (s) [" LITERAL (OWRT_NAME_PACKAGE) "]",
		"q\tsuppress routine messages",
		"v\tenable verbose messages",
		(char const *)(0)
	};
	char const * handler = OWRT_NAME_HANDLER;
	char const * package = OWRT_NAME_PACKAGE;
	signed vectorsize = OWRT_SIZE_VECTOR;
	signed buffersize = OWRT_SIZE_BUFFER;
	void (* function) () = invoke_handler;
	flag_t flags = (flag_t)(0);
	signed c;
	while (~ (c = getoptv (argc, argv, optv)))
	{
		switch (c)
		{
		case 'c':
			_setbits (flags, OWRT_ONELINE);
			break;
		case 'e':
			function = enumerate;
			break;
		case 'h':
			handler = optarg;
			break;
		case 'p':
			package = optarg;
			break;
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
	if (! argc)
	{
		define_handler (handler, package);
	}
	while ((argc) && (* argv))
	{
		if (efreopen (* argv, "rb", stdin))
		{
			function (vectorsize, buffersize, flags);
		}
		argc--;
		argv++;
	}
	exit (0);
}

