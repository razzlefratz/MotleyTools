/*====================================================================*
 *
 *   cmerge.c - include all supporting C language files;
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
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/getoptv.h"
#include "../tools/putoptv.h"
#include "../tools/version.h"
#include "../tools/error.h"
#include "../tools/tools.h"
#include "../tools/chars.h"
#include "../tools/flags.h"
#include "../tools/paths.h"
#include "../tools/sizes.h"
#include "../tools/tools.h"
#include "../tools/types.h"
#include "../tools/vtdef.h"
#include "../tools/memory.h"
#include "../tools/number.h"
#include "../tools/symbol.h"
#include "../tools/format.h"
#include "../files/files.h"
#include "../linux/linux.h"
#include "../clang/clang.h"
#include "../date/date.h"
#include "../list/list.h"
#include "../scan/scan.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../tools/efopen.c"
#include "../tools/emalloc.c"
#include "../tools/erealloc.c"
#include "../tools/error.c"
#endif

#ifndef MAKEFILE
#include "../linux/getusername.c"
#endif

#ifndef MAKEFILE
#include "../files/makepath.c"
#include "../files/splitpath.c"
#include "../files/mergepath.c"
#include "../files/makefind.c"
#include "../files/partpath.c"
#include "../files/partfile.c"
#endif

#ifndef MAKEFILE
#include "../list/listcreate.c"
#include "../list/listdelete.c"
#include "../list/listappend.c"
#include "../list/listexpand.c"
#include "../list/listrubout.c"
#endif

#ifndef MAKEFILE
#include "../scan/scaninput.c"
#include "../scan/scanstart.c"
#include "../scan/scanflush.c"
#include "../scan/scanuntil.c"
#include "../scan/scantoken.c"
#include "../scan/scanalnum.c"
#include "../scan/scandigit.c"
#include "../scan/scanspace.c"
#include "../scan/havetoken.c"
#include "../scan/havebreak.c"
#include "../scan/nexttoken.c"
#include "../scan/nextbreak.c"
#include "../scan/tokentext.c"
#include "../scan/isbreak.c"
#include "../scan/istoken.c"
#endif

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

static char const * preamble = "/*====================================================================*\n *\n *   Merged %s by user %s on host %s\n *\n *--------------------------------------------------------------------*/\n\n";

/*====================================================================*
 *
 *   void function(LIST *list);
 *
 *   recursively read files and write stdout; load each line into a
 *   scan buffer and scan for processor include directives; include
 *   local files where specified; append included files to list;
 *
 *   list is the include file inventory; it is used to detect and
 *   avoid duplicate file inclusion and, thus, recursive inclusion; 
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

void function (FIND * find, LIST * list, size_t length)

{
	struct _scan_ scan;
	char buffer [length];
	FILE * fp;
	if ((fp = efopen (find->fullname, "rb")))
	{
		scaninput (& scan, buffer, sizeof (buffer));
		while (fgets (buffer, sizeof (buffer), fp))
		{
			scanstart (& scan);
			nexttoken (& scan);
			if (havetoken (& scan, "#") && havetoken (& scan, "include") && havetoken (& scan, "\""))
			{
				FIND file;
				scanuntil (& scan, "\"");
				makepath (file.fullname, find->pathname, tokentext (& scan));
				partpath (file.fullname, file.pathname, file.filename);
				partfile (file.filename, file.basename, file.extender);
				if (listappend (list, file.fullname))
				{
					function (& file, list, length);
				}
				continue;
			}
			fputs (buffer, stdout);
		}
		fclose (fp);
	}
	return;
}

/*====================================================================*
 *
 *   int main (int argc, char const * argv []);
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
		"",
		PUTOPTV_S_FUNNEL,
		"include all C language support files",
		(char const *) (0)
	};
	LIST list;
	FIND find;
	char datetime [DATETIME_MAX];
	char hostname [HOSTNAME_MAX];
	char username [USERNAME_MAX];
	size_t length = TEXTLINE_MAX;
	time_t now;
	signed c;
	while (~ (c = getoptv (argc, argv, optv)))
	{
		switch ((char) (c))
		{
		default: 
			break;
		}
	}
	argc -= optind;
	argv += optind;
	time (& now);
	gethostname (hostname, sizeof (hostname));
	getusername (username, sizeof (username), getuid ());
	strftime (datetime, sizeof (datetime), DAYTIME, localtime (& now));
	printf (preamble, datetime, username, hostname);
	listcreate (& list, _LISTSIZE);
	while ((argc) && (* argv))
	{
		makepath (find.fullname, getenv ("PWD"), * argv);
		partpath (find.fullname, find.pathname, find.filename);
		partfile (find.filename, find.basename, find.extender);
		listappend (& list, find.fullname);
		function (& find, & list, length);
		printf ("\n/*=*\n *\n");
		for (list.index = list.start; list.index < list.count; list.index++)
		{
			printf (" *   %s\n", list.table [list.index]);
		}
		printf (" *\n *-*/\n");
		listrubout (& list);
		argc--;
		argv++;
	}
	listdelete (& list);
	exit (0);
}

