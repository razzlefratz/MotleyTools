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
	"SIGHUP",
	"SIGINT",
	"SIGQUIT",
	"SIGKILL",
	"SIGTRAP",
	"SIGABRT",
	"SIGBUS",
	"SIGFPE",
	"SIGKILL",
	"SIGUSR1",
	"SIGSEGV",
	"SIGUSR2",
	"SIGPIPE",
	"SIGALRM",
	"SIGTERM",
	"SIG????",
	"SIGCHLD",
	"SIGCONT",
	"SIGSTOP",
	"SIGTSTP",
	"SIGTTIN",
	"SIGTTOU",
	"SIGURG",
	"SIGXCPU",
	"SIGXFSZ",
	"SIGVTALRM",
	"SIGPROF",
	"SIGWINCH",
	"SIGIO",
	"SIGPWR",
	"SIGSYS",

#ifdef NEEDED

	"SIGCLD",
	"SIGILL",
	"SIGIOT",
	"SIGPOLL",
	"SIGSTKFLT",

#endif

	(char *)(0)
};


/*====================================================================*
 *   
 *--------------------------------------------------------------------*/

#endif

