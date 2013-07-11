/*====================================================================*
 *
 *   runjobs.c - run executable scripts in (and below) a given folder;
 *
 *   Derived from Debian run-parts and revised beyond recognition by
 *   Charles Maier.
 *
 *   Based on run-parts.pl version 0.2, Copyright (C) 1994 Ian Jackson.
 *   Copyright (C) 1996 Jeff Noxon <jeff@router.patch.net>,
 *   Copyright (C) 1996-1999 Guy Maor <maor@debian.org>
 *   Copyright (C) 2002, 2003, 2004 Clint Adams
 *   Copyright (c) 2005 Charles Maier <cmaier@cmassoc.net>
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
#include <stdarg.h>
#include <stdlib.h>
#include <syslog.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <paths.h>
#include <ctype.h>

/*====================================================================*
 *   custom header files; 
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../files/files.h"
#include "../linux/linux.h"
#include "../linux/syslog.h"

/*====================================================================*
 *   custom source files; 
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../tools/error.c"
#include "../linux/setumask.c"
#include "../files/makefind.c"
#include "../files/makepath.c"
#include "../files/partpath.c"
#include "../files/partfile.c"
#include "../files/splitpath.c"
#include "../files/mergepath.c"
#include "../files/match.c"
#include "../files/plain.c"
#include "../linux/syslog_basic.c"
#include "../linux/syslog_error.c"
#endif

/*====================================================================*
 *   program constants;   
 *--------------------------------------------------------------------*/

#ifndef PATH_RUNJOBS
#define PATH_RUNJOBS "/etc/runjobs.d"
#endif

#ifndef PATH_BSHELL
#define PATH_BSHELL "/bin/bash"
#endif

/*====================================================================*
 *   program functions;   
 *--------------------------------------------------------------------*/

static void findfile (FIND * script, FIND * shell, flag_t flags); 
static void testfile (FIND * script, FIND * shell, flag_t flags); 

/*====================================================================*
 *
 *   signed runscript (FIND * script, FIND * shell, flag_t flags)
 *
 *   run a script file using a given shell; check script access 
 *   permissions and internal header before spawning the shell; 
 *   test mode inhibits execution; verbose mode reports outcome;
 *
 *   scripts must start with the header "#!/path/shell"; this shell
 *   must exist, be executable and match the user specified shell;
 *
 *   this function is generic and could be used elsewhere; it should
 *   be kept free of unecessary functionality; exit condition checks
 *   is not very useful as they stand and may be eliminated;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static signed runscript (FIND * script, FIND * shell, flag_t flags) 

{ 
	static char * argv [ARGVSIZE]; 
	static int argc = 0; 
	char buffer [BUFSIZ]; 
	char * sp = buffer; 
	file_t fd = (file_t) (0); 
	pid_t pid = (pid_t) (0); 
	if (access (script->fullname, (R_OK | X_OK))) 
	{ 
		if (_anyset (flags, FIND_B_VERBOSE)) 
		{ 
			syslog_error (LOG_ERR, errno, "%s", script->fullname); 
		} 
		return (0); 
	} 
	if ((fd = open (script->fullname, O_RDONLY)) == - 1) 
	{ 
		if ((flags & (FIND_B_VERBOSE)) != 0) 
		{ 
			syslog_error (LOG_ERR, errno, "%s", script->fullname); 
		} 
		return (- 1); 
	} 
	if ((read (fd, sp, 2) != 2) || (* sp++ != '#') || (* sp++ != '!')) 
	{ 
		if ((flags & (FIND_B_VERBOSE)) != 0) 
		{ 
			syslog (LOG_DEBUG, "Can't execute %s: Bad script header", script->fullname); 
		} 
		close (fd); 
		return (0); 
	} 
	for (sp = buffer; sp < (buffer + sizeof (buffer) - 1); sp++ ) 
	{ 
		if ((read (fd, sp, 1) != 1) || isspace (* sp) || iscntrl (* sp)) 
		{ 
			break; 
		} 
	} 
	* sp = (char) (0); 
	close (fd); 
	if (stat (buffer, & script->statinfo)) 
	{ 
		if (_anyset (flags, FIND_B_VERBOSE)) 
		{ 
			syslog_error (LOG_ERR, errno, "%s", script->fullname); 
		} 
		return (- 1); 
	} 
	if (access (buffer, X_OK) != 0) 
	{ 
		if (_anyset (flags, FIND_B_VERBOSE)) 
		{ 
			syslog_error (LOG_ERR, errno, "%s", script->fullname); 
		} 
		return (- 1); 
	} 
	if (script->statinfo.st_ino != shell->statinfo.st_ino) 
	{ 
		if (_anyset (flags, FIND_B_VERBOSE)) 
		{ 
			syslog (LOG_DEBUG, "Can't execute %s: Wrong command interpreter", script->fullname); 
		} 
		return (- 1); 
	} 
	if (_anyset (flags, FIND_B_TESTRUN)) 
	{ 
		if (_anyset (flags, FIND_B_VERBOSE)) 
		{ 
			syslog (LOG_INFO, "Can execute %s", script->fullname); 
		} 
		return (0); 
	} 
	pid = fork (); 
	if (pid < (pid_t) (0)) 
	{ 
		syslog_error (LOG_DEBUG, errno, "Can't start %s", shell->fullname); 
		return (1); 
	} 
	if (pid > (pid_t) (0)) 
	{ 
		signed status; 
		if (_allclr (flags, FIND_B_SILENCE)) 
		{ 
			syslog (LOG_INFO, "Started %s", script->fullname); 
		} 
		waitpid (pid, & status, 0); 
		if (WIFEXITED (status)) 
		{ 
			if ((status = WEXITSTATUS (status)) != 0) 
			{ 
				syslog (LOG_DEBUG, "Terminated %s with status %d", script->fullname, status); 
				return (1); 
			} 
		} 
		if (WIFSIGNALED (status)) 
		{ 
			if ((status = WTERMSIG (status)) != 0) 
			{ 
				syslog (LOG_DEBUG, "Terminated %s with signal %d", script->fullname, status); 
				return (1); 
			} 
		} 
		if (_allclr (flags, FIND_B_SILENCE)) 
		{ 
			syslog (LOG_INFO, "Stopped %s", script->fullname); 
		} 
		return (0); 
	} 
	argv [argc++ ] = shell->fullname; 
	argv [argc++ ] = script->fullname; 
	argv [argc++ ] = (char * ) (0); 
	execv (* argv, argv); 
	syslog_error (LOG_DEBUG, errno, "Can't start %s", shell->fullname); 
	exit (1); 
} 

/*====================================================================*
 *
 *   void testfile (FIND *script, FIND *shell, flag_t flags);
 *
 *   search a folder and check each file; optionaly recurse through
 *   subfolders or traverse symbolic links or exit on first error; 
 *
 *   FIND is defined files.h; it contains buffers to store filename 
 *   components, a flagword and a stat structure;
 *
 *   this is a standard module structure used throughout the motley
 *   tools suite; it should be kept free of functionality and error
 *   handling;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void testfile (FIND * script, FIND * shell, flag_t flags) 

{ 
	if (stat (script->fullname, & script->statinfo)) 
	{ 
		error (0, errno, "can't stat %s", script->fullname); 
		return; 
	} 
	if (S_ISDIR (script->statinfo.st_mode)) 
	{ 
		char * filename = script->filename; 
		if (* filename == '.') 
		{ 
			filename++ ; 
		} 
		if (* filename == '.') 
		{ 
			filename++ ; 
		} 
		if (* filename == (char) (0)) 
		{ 
			return; 
		} 
		if (_anyset (flags, FIND_B_RECURSE)) 
		{ 
			findfile (script, shell, flags); 
		} 
		return; 
	} 
	if (_anyset (flags, FIND_B_FILENAME)) 
	{ 
		if (! plain (script->filename)) 
		{ 
			return; 
		} 
	} 
	else 
	{ 
		if (! match (script->filename, script->wildcard)) 
		{ 
			return; 
		} 
	} 
	if (S_ISLNK (script->statinfo.st_mode)) 
	{ 
		if (_anyset (flags, FIND_B_TRAVERSE)) 
		{ 
			runscript (script, shell, flags); 
		} 
		return; 
	} 
	if (S_ISREG (script->statinfo.st_mode)) 
	{ 
		runscript (script, shell, flags); 
		return; 
	} 
	return; 
} 

/*====================================================================*
 *
 *   void findfile (FIND *script, FIND *shell, flag_t flags);
 *
 *   search a folder and check each file; optionaly recurse through
 *   subfolders or traverse symbolic links or exit on first error; 
 *
 *   FIND is defined files.h; it contains buffers to store filename 
 *   components, a flagword and a stat structure;
 *
 *   this is a standard module structure used throughout the motley
 *   tools suite; it should be kept free of functionality and error
 *   handling;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void findfile (FIND * script, FIND * shell, flag_t flags) 

{ 
	DIR * dir; 
	char * filename = script->fullname; 
	if ((dir = opendir (filename))) 
	{ 
		struct dirent * dirent; 
		while (* filename) 
		{ 
			filename++ ; 
		} 
		* filename = PATH_C_EXTENDER; 
		while ((dirent = readdir (dir))) 
		{ 
			strcpy (filename + 1, dirent->d_name); 
			partpath (script->fullname, script->pathname, script->basename); 
			partfile (script->basename, script->filename, script->extender); 
			testfile (script, shell, flags); 
		} 
		* filename = (char) (0); 
		closedir (dir); 
		return; 
	} 
	testfile (script, shell, flags); 
	return; 
} 

/*====================================================================*
 *  
 *   int main (int argc, char const * argv[]);
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv []) 

{ 
	extern char const * program_name; 
	static char const * optv [] = 
	{ 
		"a:elpqrs:Stu:v", 
		PUTOPTV_S_SEARCH, 
		"execute named scripts", 
		"a s\tpass argument s to all scripts", 
		"e\texit on first error", 
		"l\tfollow symbolic links", 
		"p\texecute plain filenames only", 
		"q\tsuppress normal messages", 
		"r\tconduct recursive search", 
		"s s\tshell program is s", 
		"S\tshell program is ${SHELL}", 
		"t\ttest mode (find but do not execute)", 
		"u n\tset umask value to n [022]", 
		"v\tdisplay verbose messages", 
		(char const * ) (0)
	}; 
	FIND shell = 
	{ 
		{ 
			0, 
			0, 
			0, 
			0
		} , 
		PATH_BSHELL, 
		"", 
		"", 
		"", 
		"", 
		FILE_S_WILDCARD, 
		(flag_t) (0)
	}; 
	FIND script = 
	{ 
		{ 
			0, 
			0, 
			0, 
			0
		} , 
		PATH_RUNJOBS, 
		FILE_S_EXTENDER, 
		FILE_S_WILDCARD, 
		"", 
		"", 
		FILE_S_WILDCARD, 
		(flag_t) (0)
	}; 
	flag_t flags = (flag_t) (0); 
	signed c; 
	umask (022); 
	optind = 1; 
	opterr = 1; 
	while ((c = getoptv (argc, argv, optv)) != - 1) 
	{ 
		switch (c) 
		{ 
		case 'a': 
			if (argc < ARGVSIZE - 1) 
			{ 
				argv [argc++ ] = optarg; 
				argv [argc] = (char * ) (0); 
			} 
			break; 
		case 'e': 
			_setbits (flags, FIND_B_BAILOUT); 
			break; 
		case 'l': 
			_setbits (flags, FIND_B_TRAVERSE); 
			break; 
		case 'p': 
			_setbits (flags, FIND_B_FILENAME); 
			break; 
		case 'r': 
			_setbits (flags, FIND_B_RECURSE); 
			break; 
		case 's': 
			strcpy (shell.fullname, (char * ) (optarg)); 
			break; 
		case 'S': 
			if (getenv ("SHELL") == (char * ) (0)) 
			{ 
				error (1, 0, "symbol ${SHELL} is not defined."); 
			} 
			strcpy (shell.fullname, getenv ("SHELL")); 
			break; 
		case 't': 
			_setbits (flags, FIND_B_TESTRUN); 
			_setbits (flags, FIND_B_VERBOSE); 
			break; 
		case 'u': 
			if (setumask (optarg) == 0) 
			{ 
				error (1, 0, "umask value %s is invalid or illegal.", optarg); 
			} 
			break; 
		case 'v': 
			_setbits (flags, FIND_B_VERBOSE); 
			break; 
		case 'q': 
			_setbits (flags, FIND_B_SILENCE); 
			break; 
		default: 
			break; 
		} 
	} 
	argc -= optind; 
	argv += optind; 
	openlog (program_name, LOG_PERROR, LOG_USER); 
	if (stat (shell.fullname, & shell.statinfo)) 
	{ 
		error (1, errno, "Can't execute shell %s", shell.fullname); 
	} 
	if (access (shell.fullname, X_OK)) 
	{ 
		error (1, errno, "Can't execute shell %s", shell.fullname); 
	} 
	if (! argc) 
	{ 
		findfile (& script, & shell, flags); 
	} 
	while ((argc) && (* argv)) 
	{ 
		makefind (& script, * argv); 
		findfile (& script, & shell, flags); 
		argc-- ; 
		argv++ ; 
	} 
	return (0); 
} 

