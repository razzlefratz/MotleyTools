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
		SIGABRT,
		"ABRT"
	},
	{
		SIGALRM,
		"ALRM"
	},
	{
		SIGBUS,
		"BUS"
	},
	{
		SIGCHLD,
		"CHLD"
	},
	{
		SIGCONT,
		"CONT"
	},
	{
		SIGFPE,
		"FPE"
	},
	{
		SIGHUP,
		"HUP"
	},
	{
		SIGILL,
		"ILL"
	},
	{
		SIGINT,
		"INT"
	},
	{
		SIGIO,
		"IO"
	},
	{
		SIGKILL,
		"KILL"
	},
	{
		SIGPIPE,
		"PIPE"
	},
	{
		SIGPROF,
		"PROF"
	},
	{
		SIGPWR,
		"PWR"
	},
	{
		SIGQUIT,
		"QUIT"
	},
	{
		SIGSEGV,
		"SEGV"
	},
	{
		16,
		"SPARE"
	},
	{
		SIGSTOP,
		"STOP"
	},
	{
		SIGSYS,
		"SYS"
	},
	{
		SIGTERM,
		"TERM"
	},
	{
		SIGTRAP,
		"TRAP"
	},
	{
		SIGTSTP,
		"TSTP"
	},
	{
		SIGTTIN,
		"TTIN"
	},
	{
		SIGTTOU,
		"TTOU"
	},
	{
		SIGURG,
		"URG"
	},
	{
		SIGUSR1,
		"USR1"
	},
	{
		SIGUSR2,
		"USR2"
	},
	{
		SIGVTALRM,
		"VTALRM"
	},
	{
		SIGWINCH,
		"WINCH"
	},
	{
		SIGXCPU,
		"XCPU"
	},
	{
		SIGXFSZ,
		"XFSZ"
	},

#else

	{
		SIGABRT,
		"ABRT"
	},
	{
		SIGALRM,
		"ALRM"
	},
	{
		SIGBUS,
		"BUS"
	},
	{
		SIGCHLD,
		"CHLD"
	},
	{
		SIGCLD,
		"CLD"
	},
	{
		SIGCONT,
		"CONT"
	},
	{
		SIGFPE,
		"FPE"
	},
	{
		SIGHUP,
		"HUP"
	},
	{
		SIGILL,
		"ILL"
	},
	{
		SIGINT,
		"INT"
	},
	{
		SIGIO,
		"IO"
	},

/*
 * POSIX 
 */

	{
		SIGIOT,
		"IOT"
	},
	{
		SIGKILL,
		"KILL"
	},
	{
		SIGPIPE,
		"PIPE"
	},

/*
 * POSIX 
 */

	{
		SIGPOLL,
		"POLL"
	},
	{
		SIGPROF,
		"PROF"
	},
	{
		SIGPWR,
		"PWR"
	},
	{
		SIGQUIT,
		"QUIT"
	},
	{
		SIGSEGV,
		"SEGV"
	},

/*
 * POSIX 
 */

	{
		SIGSTKFLT,
		"STKFLT"
	},
	{
		SIGSTOP,
		"STOP"
	},
	{
		SIGSYS,
		"SYS"
	},
	{
		SIGTERM,
		"TERM"
	},
	{
		SIGTRAP,
		"TRAP"
	},
	{
		SIGTSTP,
		"TSTP"
	},
	{
		SIGTTIN,
		"TTIN"
	},
	{
		SIGTTOU,
		"TTOU"
	},
	{
		SIGURG,
		"URG"
	},
	{
		SIGUSR1,
		"USR1"
	},
	{
		SIGUSR2,
		"USR2"
	},
	{
		SIGVTALRM,
		"VTALRM"
	},
	{
		SIGWINCH,
		"WINCH"
	},
	{
		SIGXCPU,
		"XCPU"
	},
	{
		SIGXFSZ,
		"XFSZ"
	},

#endif

	{
		0,
		(char *)(0)
	}
};


/*====================================================================*
 * 
 *--------------------------------------------------------------------*/

#endif

