/*====================================================================* 
 * 
 *   sv_signals[] - posix signals by signal name;
 * 
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 * 
 *--------------------------------------------------------------------*/

#include <stddef.h>

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define SIGNALS_O_SIGABRT                   0
#define SIGNALS_O_SIGALRM                   1
#define SIGNALS_O_SIGBUS                    2
#define SIGNALS_O_SIGCHLD                   3
#define SIGNALS_O_SIGCLD                    4
#define SIGNALS_O_SIGCONT                   5
#define SIGNALS_O_SIGFPE                    6
#define SIGNALS_O_SIGHUP                    7
#define SIGNALS_O_SIGILL                    8
#define SIGNALS_O_SIGINT                    9
#define SIGNALS_O_SIGIO                    10
#define SIGNALS_O_SIGIOT                   11
#define SIGNALS_O_SIGKILL                  12
#define SIGNALS_O_SIGPIPE                  13
#define SIGNALS_O_SIGPOLL                  14
#define SIGNALS_O_SIGPROF                  15
#define SIGNALS_O_SIGPWR                   16
#define SIGNALS_O_SIGQUIT                  17
#define SIGNALS_O_SIGSEGV                  18
#define SIGNALS_O_SIGSTKFLT                19
#define SIGNALS_O_SIGSTOP                  20
#define SIGNALS_O_SIGSYS                   21
#define SIGNALS_O_SIGTERM                  22
#define SIGNALS_O_SIGTRAP                  23
#define SIGNALS_O_SIGTSTP                  24
#define SIGNALS_O_SIGTTIN                  25
#define SIGNALS_O_SIGTTOU                  26
#define SIGNALS_O_SIGURG                   27
#define SIGNALS_O_SIGUSR1                  28
#define SIGNALS_O_SIGUSR2                  29
#define SIGNALS_O_SIGVTALRM                30
#define SIGNALS_O_SIGWINCH                 31
#define SIGNALS_O_SIGXCPU                  32
#define SIGNALS_O_SIGXFSZ                  33
#define SIGNALS_O_NULL                     34

/*====================================================================*
 *   program variables;
 *--------------------------------------------------------------------*/

char const *sv_signals [] = 

{
	"SIGABRT",
	"SIGALRM",
	"SIGBUS",
	"SIGCHLD",
	"SIGCLD",
	"SIGCONT",
	"SIGFPE",
	"SIGHUP",
	"SIGILL",
	"SIGINT",
	"SIGIO",
	"SIGIOT",
	"SIGKILL",
	"SIGPIPE",
	"SIGPOLL",
	"SIGPROF",
	"SIGPWR",
	"SIGQUIT",
	"SIGSEGV",
	"SIGSTKFLT",
	"SIGSTOP",
	"SIGSYS",
	"SIGTERM",
	"SIGTRAP",
	"SIGTSTP",
	"SIGTTIN",
	"SIGTTOU",
	"SIGURG",
	"SIGUSR1",
	"SIGUSR2",
	"SIGVTALRM",
	"SIGWINCH",
	"SIGXCPU",
	"SIGXFSZ",
	(char *)(0)
};

