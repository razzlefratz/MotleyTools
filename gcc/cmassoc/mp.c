/*====================================================================*
 *
 *   mp.c - man page header;
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
#include <time.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/console.h"
#include "../tools/profile.h"
#include "../tools/error.h"
#include "../tools/sizes.h"
#include "../tools/chars.h"
#include "../files/files.h"
#include "../tidy/tidy.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/console.c"
#include "../tools/profile.c"
#include "../tools/totruth.c"
#include "../tools/error.c"
#endif

#ifndef MAKEFILE
#include "../files/vfopen.c"
#include "../files/splitpath.c"
#include "../files/mergepath.c"
#include "../files/makepath.c"
#endif

#ifndef MAKEFILE
#include "../tidy/keep.c"
#include "../tidy/literal.c"
#include "../tidy/escaped.c"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define MP_PROFILE "/etc/mp.ini"
#define MP_SECTION "default"
#define MP_PROGRAM ""
#define MP_PROJECT PROJECT
#define MP_ARCHIVE PACKAGE "-" VERSION "." RELEASE
#define MP_PUBLISH "%b %Y"

#define MP_VERBOSE (1 << 0)
#define MP_SILENCE (1 << 1)

/*====================================================================*
 *
 *   void function (char const * program, char const * project, char const * package, char const * release, flag_t flags);
 *
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 * 
 *--------------------------------------------------------------------*/

static void function (char const * program, char const * project, char const * package, char const * release, flag_t flags) 

{
	signed c = getc (stdin);
	while (c != EOF) 
	{
		while ((c == '\r') || (c == '\n')) 
		{
			c = getc (stdin);
		}
		if (c == '.') 
		{
			char symbol [SYMBOLSIZE];
			char * sp = symbol;
			do 
			{
				*sp++ = c;
				c = getc (stdin);
			}
			while (isalpha (c));
			*sp = (char) (0);
			if (!strcmp (symbol, ".TH")) 
			{
				while (nobreak (c)) 
				{
					c = getc (stdin);
				}
				sp += snprintf (sp, sizeof (symbol) + sp - symbol, " %s", program);
				sp += snprintf (sp, sizeof (symbol) + sp - symbol, " \"%s\"", release);
				sp += snprintf (sp, sizeof (symbol) + sp - symbol, " \"%s\"", package);
				sp += snprintf (sp, sizeof (symbol) + sp - symbol, " \"%s\"", project);
			}
			else if (!strcmp (symbol, ".SH")) 
			{
				putc ('\n', stdout);
			}
			else if (!strcmp (symbol, ".TP")) 
			{
				putc ('\n', stdout);
			}
			fputs (symbol, stdout);
		}
		while (nobreak (c)) 
		{
			if (isquote (c)) 
			{
				c = literal (c, c);
				continue;
			}
			if (c == '[') 
			{
				c = literal (c, ']');
				continue;
			}
			if (c == '.') 
			{
				c = keep (c);
				if (isblank (c)) 
				{
					do 
					{
						c = getc (stdin);
					}
					while (isblank (c));
					putc ('\n', stdout);
				}
				continue;
			}
			c = keep (c);
		}
		c = keep (c);
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
		"op:s:",
		"man page group editor",
		PUTOPTV_S_FILTER,
		"o\tprint default profile on stdout",
		"p f\tuse profile (s) [" MP_PROFILE "]",
		"s s\tuse profile section (s) [" MP_SECTION "]",
		(char const *) (0)
	};
	char buffer [16];
	time_t now = time ((time_t *)(0));;
	char const * profile = MP_PROFILE;
	char const * section = MP_SECTION;
	char const * program = MP_PROGRAM;
	char const * project = MP_PROJECT;
	char const * package = MP_ARCHIVE;
	char const * release = buffer;
	char * sp;
	flag_t flags;
	signed c;
	strftime (buffer, sizeof (buffer), MP_PUBLISH, localtime (&now));
	while ((c = getoptv (argc, argv, optv)) != -1) 
	{
		switch (c) 
		{
		case 'p':
			profile = optarg;
			break;
		case 's':
			section = optarg;
			break;
		case 'o':
			printf ("[%s]\n", MP_SECTION);
			printf ("project=%s\n", MP_PROJECT);
			printf ("package=%s\n", MP_ARCHIVE);
			printf ("release=%s\n", buffer);
			return (0);
		default:
			break;
		}
	}
	argc -= optind;
	argv += optind;
	project = profilestring (profile, section, "project", project);
	package = profilestring (profile, section, "package", package);
	release = profilestring (profile, section, "release", release);
	if ((!argc) || (!*argv)) 
	{
		function ("unamed 7", project, package, release, flags);
	}
	while ((argc) && (* argv)) 
	{
		if (vfopen (* argv)) 
		{
			program = * argv;
			for (sp = (char *)(* argv); *sp; ++sp) 
			{
				if (*sp == PATH_C_EXTENDER) 
				{
					program = sp + 1;
				}
				if (*sp == FILE_C_EXTENDER) 
				{
					*sp = ' ';
				}
			}
			function (program, project, package, release, flags);
		}
		argc--;
		argv++;
	}
	exit (0);
}

