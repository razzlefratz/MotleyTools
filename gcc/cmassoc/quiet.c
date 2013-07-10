/*====================================================================*
 *
 *   quiet.c - diable message broatcasts on your terminal;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

#define _GETOPT_H

/*====================================================================*
 *  system header files;
 *--------------------------------------------------------------------*/

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <grp.h>

/*====================================================================*
 *  custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"

/*====================================================================*
 *  custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../tools/error.c"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define GROUPNAME "tty"

/*====================================================================*
 *
 *   int main(int argc, char ** argv);
 *
 *
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv []) 

{ 
	static char const * optv [] = 
	{ 
		"", 
		"[yes|no]", 
		"permit or restrict public access to your terminal", 
		(char const * ) (0)
	}; 
	struct stat statinfo; 
	struct group * group; 
	mode_t mode; 
	mode_t prev; 
	bool system = false; 
	bool member = false; 
	int c; 
	while ((c = getoptv (argc, argv, optv)) != - 1) 
	{ 
		switch (c) 
		{ 
		default: 
			break; 
		} 
	} 
	argc -= optind; 
	argv += optind; 
	if (! isatty (STDIN_FILENO)) 
	{ 
		error (1, 0, "stdin is not a tty"); 
	} 
	if (fstat (STDIN_FILENO, & statinfo)) 
	{ 
		error (1, errno, "can't fstat stdin"); 
	} 
	if ((group = getgrnam (GROUPNAME)) != (struct group * ) (0)) 
	{ 
		system = true; 
		if ((group = getgrgid (statinfo.st_gid)) != (struct group * ) (0)) 
		{ 
			if (strcmp (group->gr_name, GROUPNAME) == 0) 
			{ 
				member = true; 
			} 
		} 
	} 
	if (! argc) 
	{ 
		mode = ((system) && (member))? (S_IWGRP | S_IWOTH):  (S_IWOTH); 
		printf ("%s\n", (statinfo.st_mode & mode)? "no":  "yes"); 
		return (0); 
	} 
	if (strcmp (* argv, "yes") && strcmp (* argv, "no")) 
	{ 
		error (1, 0, "argument '%s' has no meaning: only 'yes' or 'no' have meaning", * argv); 
	} 

/*
 * permit no but not yes if group is non-standard.
 */

	mode = (system)? (S_IWGRP):  (S_IWGRP | S_IWOTH); 
	if ((system) && (! member) && (strcmp (* argv, "yes") == 0)) 
	{ 
		error (1, 0, "stdin is not a %s group member", GROUPNAME); 
	} 
	prev = statinfo.st_mode; 
	if (strcmp (* argv, "yes") == 0) 
	{ 
		_setbits (statinfo.st_mode, mode); 
	} 
	if (strcmp (* argv, "no") == 0) 
	{ 
		_clrbits (statinfo.st_mode, mode); 
	} 
	if (statinfo.st_mode == prev) 
	{ 
		return (0); 
	} 
	if (fchmod (STDIN_FILENO, statinfo.st_mode)) 
	{ 
		error (1, errno, "%s", ttyname (STDIN_FILENO)); 
	} 
	return (0); 
} 

