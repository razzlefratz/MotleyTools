/*====================================================================*
 * 
 *   signal_names.c - signal code by signal name; 
 *
 *   signals.h
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SIGNAL_CODES_SOURCE
#define SIGNAL_CODES_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <signal.h>
#include <ctype.h>
#include <error.h>
#include <errno.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../linux/signals.h"

/*====================================================================*
 *   program variables;
 *--------------------------------------------------------------------*/

const struct _code_ signal_codes [_SIGNALS+1] = 

{

#ifdef __linux__

	{
		"ABRT",
		SIGABRT
	},
	{
		"ALRM",
		SIGALRM
	},
	{
		"BUS",
		SIGBUS
	},
	{
		"CHLD",
		SIGCHLD
	},
	{
		"CONT",
		SIGCONT
	},
	{
		"FPE",
		SIGFPE
	},
	{
		"HUP",
		SIGHUP
	},
	{
		"ILL",
		SIGILL
	},
	{
		"INT",
		SIGINT
	},
	{
		"IO",
		SIGIO
	},
	{
		"KILL",
		SIGKILL
	},
	{
		"PIPE",
		SIGPIPE
	},
	{
		"PROF",
		SIGPROF
	},
	{
		"PWR",
		SIGPWR
	},
	{
		"QUIT",
		SIGQUIT
	},
	{
		"SEGV",
		SIGSEGV
	},
	{
		"SPARE",
		16
	},
	{
		"STOP",
		SIGSTOP
	},
	{
		"SYS",
		SIGSYS
	},
	{
		"TERM",
		SIGTERM
	},
	{
		"TRAP",
		SIGTRAP
	},
	{
		"TSTP",
		SIGTSTP
	},
	{
		"TTIN",
		SIGTTIN
	},
	{
		"TTOU",
		SIGTTOU
	},
	{
		"URG",
		SIGURG
	},
	{
		"USR1",
		SIGUSR1
	},
	{
		"USR2",
		SIGUSR2
	},
	{
		"VTALRM",
		SIGVTALRM
	},
	{
		"WINCH",
		SIGWINCH
	},
	{
		"XCPU",
		SIGXCPU
	},
	{
		"XFSZ",
		SIGXFSZ
	},

#else

	{
		"ABRT",
		SIGABRT
	},
	{
		"ALRM",
		SIGALRM
	},
	{
		"BUS",
		SIGBUS
	},
	{
		"CHLD",
		SIGCHLD
	},
	{
		"CLD",
		SIGCLD
	},
	{
		"CONT",
		SIGCONT
	},
	{
		"FPE",
		SIGFPE
	},
	{
		"HUP",
		SIGHUP
	},
	{
		"ILL",
		SIGILL
	},
	{
		"INT",
		SIGINT
	},
	{
		"IO",
		SIGIO
	},

/*
 * POSIX 
 */

	{
		"IOT",
		SIGIOT
	},
	{
		"KILL",
		SIGKILL
	},
	{
		"PIPE",
		SIGPIPE
	},

/*
 * POSIX 
 */

	{
		"POLL",
		SIGPOLL
	},
	{
		"PROF",
		SIGPROF
	},
	{
		"PWR",
		SIGPWR
	},
	{
		"QUIT",
		SIGQUIT
	},
	{
		"SEGV",
		SIGSEGV
	},

/*
 * POSIX 
 */

	{
		"STKFLT",
		SIGSTKFLT
	},
	{
		"STOP",
		SIGSTOP
	},
	{
		"SYS",
		SIGSYS
	},
	{
		"TERM",
		SIGTERM
	},
	{
		"TRAP",
		SIGTRAP
	},
	{
		"TSTP",
		SIGTSTP
	},
	{
		"TTIN",
		SIGTTIN
	},
	{
		"TTOU",
		SIGTTOU
	},
	{
		"URG",
		SIGURG
	},
	{
		"USR1",
		SIGUSR1
	},
	{
		"USR2",
		SIGUSR2
	},
	{
		"VTALRM",
		SIGVTALRM
	},
	{
		"WINCH",
		SIGWINCH
	},
	{
		"XCPU",
		SIGXCPU
	},
	{
		"XFSZ",
		SIGXFSZ
	},

#endif

	{
		(char *)(0),
		0
	}
};


/*====================================================================*
 * 
 *--------------------------------------------------------------------*/

#endif

