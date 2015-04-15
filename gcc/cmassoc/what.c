/*====================================================================*
 *
 *   what.c - print alphabetical list of processes on stdout;
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
#include <ctype.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <libgen.h>
#include <time.h>
#include <errno.h>
#include <stdlib.h>
#include <dirent.h>
#include <syslog.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../linux/linux.h"
#include "../linux/procstat.h"
#include "../strlib/strlib.h"
#include "../list/list.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/console.c"
#include "../tools/emalloc.c"
#include "../tools/erealloc.c"
#include "../tools/uintspec.c"
#include "../tools/todigit.c"
#endif

#ifndef MAKEFILE
#include "../list/listcreate.c"
#include "../list/listdelete.c"
#include "../list/listdetect.c"
#include "../list/listexpand.c"
#include "../list/listinsert.c"
#include "../list/listcolumn.c"
#endif

#ifndef MAKEFILE
#include "../linux/getviewport.c"
#endif

#ifndef MAKEFILE
#include "../strlib/strsplit.c"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define COUNT 0
#define WIDTH 0

/*====================================================================*
 *
 *   static void function (LIST * list);
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void function (LIST * list)

{
	DIR * dir;
	struct dirent * dirent;
	char pathname [FILENAME_MAX +  1] = PROCROOT;
	char * filename = pathname +  sizeof (PROCROOT) -1;
	if ((dir = opendir (pathname))) while ((dirent = readdir (dir)))
	{
		char * string;
		for (string = dirent->d_name; isdigit (* string); ++ string);
		if (* string == (char) (0))
		{
			signed fd;
			strcpy (filename, dirent->d_name);
			strcat (filename, STATFILE);
			if ((fd = open (pathname, O_RDONLY)) != -1)
			{
				static char * vector [PROCSTAT_CNT];
				char buffer [PROCSTAT_MAX];
				signed length = read (fd, buffer, sizeof (buffer) -1);
				buffer [length] = (char) (0);
				close (fd);
				strsplit ((char const **) (vector), SIZEOF (vector), buffer, ' ');
				for (string = vector [PROCSTAT_NAME]; * string; string++)
				{
					* string = * (string +  1);
					if (* string == ')')
					{
						* string = (char) (0);
					}
					if (* string == (char) (0))
					{
						break;
					}
				}
				listinsert (list, vector [PROCSTAT_NAME]);
			}
		}
	}
	closedir (dir);
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
		"print alphabetical list of processes on stdout",
		PUTOPTV_S_DIVINE,
		"c:nw:",
		"c n\tcolumn count is (n) [" LITERAL (COUNT) "]",
		"w n\tscreen width is (n) [" LITERAL (WIDTH) "]",
		"n\tnumber each list items",
		(char *) (0)
	};
	LIST list;
	size_t width = WIDTH;
	size_t count = COUNT;
	bool index = false;
	signed c;
	while (~ (c = getoptv (argc, argv, optv)))
	{
		switch (c)
		{
		case 'n':
			index = true;
			break;
		case 'w':
			width = uintspec (optarg, 1, 132);
			break;
		case 'c':
			count = uintspec (optarg, 1, 16);
			break;
		default: 
			break;
		}
	}
	listcreate (& list, _LISTSIZE);
	function (& list);
	listcolumn (& list, stdout, width, count, index);
	listdelete (& list);
	exit (0);
}

