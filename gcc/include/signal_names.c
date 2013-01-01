/*====================================================================*
 * 
 *   signal_names.c - signal name by signal number; 
 *
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SIGNAL_NAMES_SOURCE
#define SIGNAL_NAMES_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <signal.h>

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

char const *signal_names [] = 

{
	"SIGTEST",

/*   0 */

	"SIGHUP",

/*   1 */

	"SIGINT",

/*   2 */

	"SIGQUIT",

/*   3 */

	"SIGKILL",

/*   4 */

	"SIGTRAP",

/*   5 */

	"SIGABRT",

/*   6 */

	"SIGBUS",

/*   7 */

	"SIGFPE",

/*   8 */

	"SIGKILL",

/*   9 */

	"SIGUSR1",

/*  10 */

	"SIGSEGV",

/*  11 */

	"SIGUSR2",

/*  12 */

	"SIGPIPE",

/*  13 */

	"SIGALRM",

/*  14 */

	"SIGTERM",

/*  15 */

	"SIG????",

/*  16 */

/* not used by linux */

	"SIGCHLD",

/*  17 */

	"SIGCONT",

/*  18 */

	"SIGSTOP",

/*  19 */

	"SIGTSTP",

/*  20 */

	"SIGTTIN",

/*  21 */

	"SIGTTOU",

/*  22 */

	"SIGURG",

/*  23 */

	"SIGXCPU",

/*  24 */

	"SIGXFSZ",

/*  25 */

	"SIGVTALRM",

/*  26 */

	"SIGPROF",

/*  27 */

	"SIGWINCH",

/*  28 */

	"SIGIO",

/*  29 */

	"SIGPWR",

/*  30 */

	"SIGSYS",

/*  31 */

#ifdef NEEDED

	"SIGCLD",

/*   4 */

/* posix signal */

	"SIGILL",

/*   8 */

/* posix signal */

	"SIGIOT",

/*  11 */

/* posix signal */

	"SIGPOLL",

/*  14 */

/* posix signal */

	"SIGSTKFLT",

/*  19 */

/* posix signal */

#endif

/*  34 */

	(char *)(0)
};


/*====================================================================*
 *   
 *--------------------------------------------------------------------*/

#endif

