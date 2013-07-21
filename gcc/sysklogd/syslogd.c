/*====================================================================*
 *
 *   syslogd.c - system logging daemon;
 *
 *   a drastic re-write and update of the classic syslogd program;
 *
 *   some principle features are:
 *
 *   1) functions have been renamed and stored as individual files;
 *
 *      functions specific to the syslog or syslogd programs have
 *      the prefixes syslog_ or syslogd_ and reside in the sysklogd 
 *      directory; functions that are, or could be, used elsewhere 
 *      reside in an adjacent directory having several aliases that 
 *      are implemented by symbolic links; that is because many of
 *      the common functions come from other libraries with these
 *      directory names; modules often move between libraries and
 *      aliasing the directory names avoids editing modules after
 *      each move; 
 *
 *   2) variables have been renamed to improve package consistency;
 *
 *      constants specific to the syslog or syslogd programs have
 *      the prefixes SYSLOG_ or SYSLOGD_ and are defined in either
 *      syslog.h or syslogd.h; there are some exceptions that will
 *      be corrected in time;
 *
 *   3) dependence on global variables have been minimized in favor
 *      passing them as arguments where possible; this accomplishes
 *      two things: 1) it highlights program structure and 2) lends
 *      itself to object orientation at some point in the future;
 *
 *      the effort of collecting related variables into structures
 *      has actually streamlined and simplifed the entire program;
 *
 *   4) boolean and integer flag variables have been converted to
 *      bits in variable flag_t state which is passed by value to 
 *      subordinate functions; 
 *
 *   5) all syslog information is now stored in one circular linked 
 *      list with the console syslog as the first list member; this
 *      eliminated many array boundary checks and related variables;
 *      it also eliminated the console syslog as independent entity; 
 *
 *   5) pedantic, possibly redundant, type casts are used all over; 
 *      this clarifies data type at their point of use, in addition
 *      to their point of declaration;
 *
 *   7) variable types like file_t, flag_t, facility_t, severity_t,
 *      errno_t and signo_t are used throughout; the latter two are
 *      in anticipation of POSIX implementation of these or similar
 *      typedefs; 
 *
 *   8) common bitmaps test expressions are implemented with macros
 *      defined in flags.h; for example, "_clrbits (flag, mask)" is
 *      macro-speak for "flag &= ~mask";
 *
 *   9) non-essential include files have been removed where known;
 *
 *   10) socket and syslog details are no longer global; they are
 *       passed by reference to the functions that use them;  
 *
 *   11) inet and unix socket details are now stored as a linked
 *       list instead of a variable for inet and an array for unix
 *       sockets; the list is circular in both directions, so that
 *       additional inet or unix sockets can be easily inserted at
 *       either end; the linked list eliminated a handful of index 
 *       and limit variables;
 *
 *   12) function main() has been simplified; it parses arguments 
 *       and spawns the daemon; the daemon calls five functions to 
 *       start recording, start listening, listen, stop listening 
 *       stop recording; 
 *
 *   13) configuration file parsing, priority mapping and device
 *       validation are now independent functions, eliminating a
 *       rats-nest of decision statements; 
 *
 *   14) the internal NOPRI and ALLPRI mechanism has changed; see 
 *       syslogd_parse() and syslogd_index() for more information 
 *       about this;
 *
 *   15) the MARK facility is now permanent, making 24 facilities
 *       in total; the mark facility is now self-synchronizing so
 *       that marks are generated at the correct times regardless
 *       of syslogd start time or number of intervening restarts;
 *
 *   16) POSIX signals have replaced UNIX signals; event handlers 
 *       no longer need to re-register themselves because that is
 *       automatic unless suppressed; all signal handling is done
 *       in the syslogd-main module; 
 *
 *   17) syslogd optionally prints a routing matrix with syslog
 *       details to any file named by the "-o" option; this can 
 *       help operators analyse and debug syslog instructions; 
 *
 *   in the spirit of open source software, I acknowledge that I am
 *   standing on the shoulders of countless others and have learned
 *   a great deal reading their code; I have tried to maintain and
 *   improve functionality that has been thoughtfully included over 
 *   time; I have included the original code for reference in case 
 *   I misunderstood the original design or intent; 
 *   
 *   Regards,
 *   Charlie Maier
 *   Nashua NH USA
 *  
 *  
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#define _GETOPT_H

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

// #include <error.h>

#include <netdb.h>
#include <sys/wait.h>
#if defined(__linux__)
#include <paths.h>
#endif
#include <time.h>
#include <sys/socket.h>
#include <sys/un.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../linux/syslog.h"
#include "../sysklogd/syslogd.h"

#include "../tools/getoptv.h"
#include "../tools/version.h"
#include "../tools/tools.h"
#include "../tools/flags.h"
#include "../tools/error.h"
#include "../tools/paths.h"
#include "../linux/linux.h"
#include "../linux/pidfile.h"
#include "../strlib/strlib.h"
#include "../date/date.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../tools/uintspec.c"
#include "../tools/waitspec.c"
#include "../tools/statement.c"
#include "../tools/trace.c"
#include "../linux/checkpf.c"
#include "../linux/readpf.c"
#include "../linux/writepf.c"
#include "../linux/removepf.c"
#include "../strlib/strlwr.c"
#include "../strlib/strcut.c"
#include "../strlib/stov.c"
#include "../strlib/strfbits.c"
#endif

#ifndef MAKEFILE
#include "../sysklogd/syslog_facility_codes.c"
#include "../sysklogd/syslog_facility_names.c"
#include "../sysklogd/syslog_severity_codes.c"
#include "../sysklogd/syslog_severity_names.c"
#include "../sysklogd/syslog_lookup.c"
#endif

#ifndef MAKEFILE
#include "../sysklogd/syslogd_broadcast.c"
#include "../sysklogd/syslogd_admin.c"
#include "../sysklogd/syslogd_merge.c"
#include "../sysklogd/syslogd_stop.c"
#include "../sysklogd/syslogd_enumerate.c"
#include "../sysklogd/syslogd_error.c"
#include "../sysklogd/syslogd_print.c"
#include "../sysklogd/syslogd_flag_names.c"
#include "../sysklogd/syslogd_gethost.c"
#include "../sysklogd/syslogd_index.c"
#include "../sysklogd/syslogd_parse.c"
#include "../sysklogd/syslogd_queue.c"
#include "../sysklogd/syslogd_start.c"
#include "../sysklogd/syslogd_state.c"
#include "../sysklogd/syslogd_scrub.c"
#include "../sysklogd/syslogd_type_names.c"
#include "../sysklogd/syslogd_write.c"
#include "../sysklogd/syslogd_unix_socket.c"
#include "../sysklogd/syslogd_inet_socket.c"
#include "../sysklogd/syslogd_open_sockets.c"
#include "../sysklogd/syslogd_read_sockets.c"
#include "../sysklogd/syslogd_close_sockets.c"
#endif

/*====================================================================*
 *   program variables (public);
 *--------------------------------------------------------------------*/

flag_t state = (flag_t) (SYSLOGD_STATE); 
time_t timer = (time_t) (SYSLOGD_TIMER); 
char const * host_name = "localhost"; 
char const * domain_name = ""; 
char const * cfgfile = _PATH_SYSLOG_CONF; 
char const * pidfile = _PATH_SYSLOGD_PID; 
char const * mapfile = (char const *) (0); 

#ifdef SYSLOGD_INETAF

char const ** ourhosts = (char const **) (0); 
char const ** ourdomains = (char const **) (0); 

#endif

static sig_atomic_t loop = true; 
static struct sigaction sighup; 
static struct sigaction sigquit; 
static struct sigaction sigterm; 
static struct sigaction sigalrm; 
static struct sigaction sigchld; 
static struct sigaction sigusr1; 
static struct sockaddr_un unixsock_addr = 

{ 
	AF_UNIX, 
	_PATH_SYSLOG
}; 

static struct sockaddr_in inetsock_addr = 

{ 
	AF_INET, 
	SYSLOGD_SERVICE_PORT, 
	{ 
		INADDR_ANY
	} 
}; 

static struct socket unixsock = 

{ 
	& unixsock, 
	& unixsock, 
	(file_t) (- 1), 
	(size_t) (sizeof (unixsock_addr)), 
	(struct sockaddr *) (& unixsock_addr), 
	(char *) (0)
}; 

struct socket inetsock = 

{ 
	& inetsock, 
	& inetsock, 
	(file_t) (- 1), 
	(size_t) (sizeof (inetsock_addr)), 
	(struct sockaddr *) (& inetsock_addr), 
	(char *) (0)
}; 

struct syslogd syslogs = 

{ 
	& syslogs, 
	& syslogs, 
	SYSLOGD_TYPE_CONSOLE, 
	_PATH_CONSOLE, 
	(size_t) (0), 
	(file_t) (- 1), 
	(time_t) (0), 
	(flag_t) (0), 
	(struct sockaddr_in *) (0), 
	{ 
		(severity_t) (0), 
		(severity_t) (0), 
		(severity_t) (0), 
		(severity_t) (0), 
		(severity_t) (0), 
		(severity_t) (0), 
		(severity_t) (0), 
		(severity_t) (0), 
		(severity_t) (0), 
		(severity_t) (0), 
		(severity_t) (0), 
		(severity_t) (0), 
		(severity_t) (0), 
		(severity_t) (0), 
		(severity_t) (0), 
		(severity_t) (0), 
		(severity_t) (0), 
		(severity_t) (0), 
		(severity_t) (0), 
		(severity_t) (0), 
		(severity_t) (0), 
		(severity_t) (0), 
		(severity_t) (0), 
		(severity_t) (0), 
		(severity_t) (0)
	}, 
	"", 

#if SYSLOGD_ORIGIN

	"", 

#endif
#if SYSLOGD_NATURE

	"", 

#endif

	"", 
	(size_t) (0), 
	(size_t) (0), 
	(size_t) (0), 
	(size_t) (0), 
}; 

/*====================================================================*
 *   
 *   void syslogd_sighup (signo_t number);
 *   
 *   handle SIGHUP for the daemon; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

void syslogd_sighup (signo_t number) 

{ 
	extern flag_t state; 
	extern struct syslogd syslogs; 
	extern char const * cfgfile; 
	extern char const * mapfile; 
	syslogd_stop (& syslogs, state); 
	syslogd_start (& syslogs, state, cfgfile); 

#ifdef SYSLOGD_REPORT

	syslogd_admin (& syslogs, state, mapfile); 

#endif

	return; 
} 

/*====================================================================*
 *   
 *   void syslogd_sigalrm (signo_t number);
 *   
 *   handle SIGALRM for the daemon; print numbered mark messages to
 *   the mark facility at uniform intervals; re-synchonize the time
 *   after each mark;
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

void syslogd_sigalrm (signo_t number) 

{ 
	extern time_t timer; 
	static size_t index = 0; 
	syslogd_print (SYSLOG_MARK | SYSLOG_INFO, "--- MARK %06d ---", index++); 
	if (timer) 
	{ 
		time_t clock = time (& clock); 
		alarm (timer - clock % timer); 
	} 
	return; 
} 

/*====================================================================*
 *
 *   void syslogd_sigusr1 (signo_t number);
 *
 *   handle SIGUSR1 for the daemon;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

void syslogd_sigusr1 (signo_t number) 

{ 
	return; 
} 

/*====================================================================*
 *
 *   void syslogd_sigchld (signo_t number);
 *
 *   handle SIGCHLD for the parent and the daemon;
 *
 *   fetch status from terminated children; failure to do so leaves 
 *   defunct processes laying about and they litter the ps displays
 *   until removed;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

void syslogd_sigchld (signo_t number) 

{ 
	signed status; 
	while (waitpid ((pid_t) (0), & status, WNOHANG) > 0); 
	return; 
} 

/*====================================================================*
 *   
 *   void syslogd_sigquit (signo_t number);
 *   
 *   handle SIGINT and SIGQUIT signals for the parent;
 *
 *   the parent responses to keyboard interrupts with immediate exit
 *   but the daemon ignores them; this is the barbaric way to stop
 *   program execution; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

void syslogd_sigquit (signo_t number) 

{ 
	exit (0); 
} 

/*====================================================================*
 *   
 *   void syslogd_sigterm (signo_t number);
 *   
 *   handle SIGCHLD for the parent and the daemon;
 *
 *   exit the main read loop on the next iteration; the civilized
 *   way to stop program execution;
 *  
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

void syslogd_sigterm (signo_t number) 

{ 
	extern sig_atomic_t loop; 
	loop = 0; 
	return; 
} 

/*====================================================================*
 *
 *   int main (int argc, char const *argv[]);
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv []) 

{ 
	extern char const * host_name; 
	extern char const * domain_name; 
	static char const * optv [] = 
	{ 
		"a:df:" 

#ifdef SYSLOGD_INETAF

		"hi:l:" 

#endif

		"m:no:p:" 

#ifdef SYSLOGD_INETAF

		"rs:" 

#endif

		"xvw:", 
		"System Logging Daemon", 
		"a s\tadd unix socket path s", 
		"d\trun as daemon (background)", 
		"f s\tuse configuration file s [" _PATH_SYSLOG_CONF "]", 

#ifdef SYSLOGD_INETAF

		"h\tforward messages to other hosts", 
		"i n\tadd inet socket on port n", 
		"l s\tlist of hostnames separated by ':'", 

#endif

		"m nn\tmark internal is nn[s|S|m|M|h|H]", 
		"n\trun as normal program (foreground)", 
		"o s\toutput file is s", 
		"p s\tlocal log device path is s [" _PATH_SYSLOG "]", 

#ifdef SYSLOGD_UNIXAF

		"r\treceive messages from other hosts", 
		"s s\tdomain list is s", 

#endif

		"v\tdisplay version and exit", 
		"w n\twait n seconds for klogd to start", 
		"x\tnot implemented", 
		(char const *) (0)
	}; 

#ifdef SYSLOGD_INETAF

	struct servent * servent; 
	struct sockaddr_in * sockaddr_inet; 

#endif
#ifdef SYSLOGD_UNIXAF

	struct socket * socket; 
	struct sockaddr_un * sockaddr_unix; 

#endif

	struct hostent * hostent; 
	char fqdn [HOSTNAME_MAX]; 
	time_t delay = SYSLOGD_DELAY_TIME; 
	file_t fd; 
	int c; 
	chdir ("/"); 

/*--------------------------------------------------------------------*
 * point host_name and domain_name to constant strings; technically,
 * the fqdn is the name returned by gethostbyname when given the name 
 * returned by gethostname; store the fqdn then break it at the first  
 * '.', if present; 
 *--------------------------------------------------------------------*/

	gethostname (fqdn, sizeof (fqdn)); 
	if ((hostent = gethostbyname (fqdn)) != (struct hostent *) (0)) 
	{ 
		strncpy (fqdn, hostent->h_name, sizeof (fqdn)); 
	} 
	strlwr (fqdn); 
	for (host_name = domain_name = fqdn; * domain_name != (char) (0); domain_name++) 
	{ 
		if (* domain_name == '.') 
		{ 
			fqdn [domain_name++ - host_name] = (char) (0); 
			break; 
		} 
	} 

#ifdef SYSLOGD_INETAF

/*--------------------------------------------------------------------*
 * confirm that the service is registered; the name is "syslog", the 
 * type is "udp" and it should appear in "/etc/services"; record the
 * port number in struct sockaddr_in for global reference;
 *--------------------------------------------------------------------*/

	servent = getservbyname (SYSLOGD_SERVICE_NAME, SYSLOGD_SERVICE_TYPE); 
	if (servent == (struct servent *) (0)) 
	{ 
		error (1, ENOTSUP, "The %s %s service is not registered on %s", SYSLOGD_SERVICE_NAME, SYSLOGD_SERVICE_TYPE, host_name); 
	} 
	if (servent != (struct servent *) (0)) 
	{ 
		inetsock_addr.sin_port = servent->s_port; 
	} 

#endif

	optind = 1; 
	opterr = 1; 
	while ((c = getoptv (argc, argv, optv)) != - 1) 
	{ 
		switch ((char) (c)) 
		{ 

#ifdef SYSLOGD_UNIXAF

/*--------------------------------------------------------------------*
 * create additional unix socket with specified pathname and append 
 * it to the sockets list; 
 *--------------------------------------------------------------------*/

		case 'a': 
			sockaddr_unix = NEW (struct sockaddr_un); 
			if (sockaddr_unix == (struct sockaddr_un *) (0)) 
			{ 
				break; 
			} 
			memset (sockaddr_unix, 0, sizeof (struct sockaddr_un)); 
			sockaddr_unix->sun_family = AF_UNIX; 
			memcpy (& sockaddr_unix->sun_path, optarg, sizeof (sockaddr_unix->sun_path)); 
			socket = NEW (struct socket); 
			if (socket == (struct socket *) (0)) 
			{ 
				error (0, errno, "Can't add socket %s", optarg); 
				free (sockaddr_unix); 
				break; 
			} 
			memset (socket, 0, sizeof (struct socket)); 
			socket->desc = - 1; 
			socket->socksize = sizeof (struct sockaddr_un); 
			socket->sockaddr = (struct sockaddr *) (sockaddr_unix); 
			socket->next = & unixsock; 
			socket->prev = unixsock.prev; 
			unixsock.prev->next = socket; 
			unixsock.prev = socket; 
			break; 

#endif
#ifdef SYSLOGD_INETAF

		case 'i': 
			sockaddr_inet = NEW (struct sockaddr_in); 
			if (sockaddr_inet == (struct sockaddr_in *) (0)) 
			{ 
				break; 
			} 
			sockaddr_inet->sin_family = AF_INET; 
			sockaddr_inet->sin_port = (unsigned short) (uintspec (optarg, IPPORT_RESERVED, IPPORT_USERRESERVED)); 
			socket = NEW (struct socket); 
			if (socket == (struct socket *) (0)) 
			{ 
				error (0, errno, "Can't add socket %s", optarg); 
				free (sockaddr_inet); 
				break; 
			} 
			memset (socket, 0, sizeof (struct socket)); 
			socket->desc = - 1; 
			socket->socksize = sizeof (struct sockaddr_in); 
			socket->sockaddr = (struct sockaddr *) (sockaddr_inet); 
			socket->next = & inetsock; 
			socket->prev = inetsock.prev; 
			inetsock.prev->next = socket; 
			inetsock.prev = socket; 
			break; 

#endif

		case 'd': 
			_setbits (state, SYSLOGD_STATE_DAEMON); 
			break; 
		case 'f': 
			cfgfile = optarg; 
			break; 

#ifdef SYSLOGD_INETAF

		case 'h': 
			_setbits (state, SYSLOGD_STATE_FORWARD); 
			break; 

#endif
#ifdef SYSLOGD_INETAF

		case 'l': 
			if (ourhosts != (char const **) (0)) 
			{ 
				error (0, EINVAL, "discarding '%s': only one host list allowed", optarg); 
				break; 
			} 
			ourhosts = stov (optarg, ':'); 
			break; 

#endif

		case 'm': 
			timer = waitspec (optarg); 
			break; 
		case 'n': 
			_clrbits (state, SYSLOGD_STATE_DAEMON); 
			break; 
		case 'o': 
			mapfile = optarg; 
			break; 

#ifdef SYSLOGD_UNIXAF

		case 'p': 
			strncpy (unixsock_addr.sun_path, optarg, sizeof (unixsock_addr.sun_path)); 
			break; 

#endif
#ifdef SYSLOGD_INETAF

		case 'r': 
			_setbits (state, SYSLOGD_STATE_RECEIVE); 
			break; 

#endif
#ifdef SYSLOGD_INETAF

		case 's': 
			if (ourdomains != (char const **) (0)) 
			{ 
				error (0, 0, "ignoring '%s': only one -s argument allowed", optarg); 
				break; 
			} 
			ourdomains = stov (optarg, ':'); 
			break; 

#endif

		case 't': 
			delay = uintspec (optarg, 0, 3600); 
			break; 
		case 'v': 
			version (); 
			exit (0); 
		case 'w': 
			delay = waitspec (optarg); 
			break; 
		case 'x': 
			break; 
		default: 
			break; 
		} 
	} 
	argc -= optind; 
	argv += optind; 
	if (getuid ()) 
	{ 
		error (1, EACCES, NOTROOT); 
	} 
	if (checkpf (pidfile)) 
	{ 
		error (1, 0, "service is already running"); 
	} 

#ifdef SYSLOGD_INETAF

	if (_allset (state, (SYSLOGD_STATE_RECEIVE | SYSLOGD_STATE_FORWARD))) 
	{ 
		error (1, EPERM, "Can't receive and forward messages in same session"); 
	} 

#endif

	memset (& sigquit, 0, sizeof (struct sigaction)); 
	sigquit.sa_handler = syslogd_sigquit; 
	sigquit.sa_flags = SA_ONESHOT; 
	sigemptyset (& sigquit.sa_mask); 
	memset (& sigterm, 0, sizeof (struct sigaction)); 
	sigterm.sa_handler = syslogd_sigterm; 
	sigterm.sa_flags = SA_ONESHOT; 
	sigemptyset (& sigterm.sa_mask); 
	memset (& sigchld, 0, sizeof (struct sigaction)); 
	sigchld.sa_handler = syslogd_sigchld; 
	sigchld.sa_flags = 0; 
	sigemptyset (& sigchld.sa_mask); 
	memset (& sigalrm, 0, sizeof (struct sigaction)); 
	sigalrm.sa_handler = syslogd_sigalrm; 
	sigalrm.sa_flags = 0; 
	sigemptyset (& sigalrm.sa_mask); 
	memset (& sigusr1, 0, sizeof (struct sigaction)); 
	sigusr1.sa_handler = syslogd_sigusr1; 
	sigusr1.sa_flags = 0; 
	sigemptyset (& sigusr1.sa_mask); 
	memset (& sighup, 0, sizeof (struct sigaction)); 
	sighup.sa_handler = syslogd_sighup; 
	sighup.sa_flags = 0; 
	sigemptyset (& sighup.sa_mask); 
	sigaction (SIGINT, & sigquit, (struct sigaction *) (0)); 
	sigaction (SIGTERM, & sigquit, (struct sigaction *) (0)); 
	sigaction (SIGQUIT, & sigquit, (struct sigaction *) (0)); 
	if (_allset (state, SYSLOGD_STATE_DAEMON)) 
	{ 
		if (fork ()) 
		{ 
			sleep (delay); 
			error (1, 0, "daemon did not start"); 
		} 
		setsid (); 
		for (fd = getdtablesize (); fd-- > 0; close (fd)); 
		kill (getppid (), SIGTERM); 
		sigquit.sa_handler = SIG_IGN; 
	} 
	sigaction (SIGTERM, & sigterm, (struct sigaction *) (0)); 
	sigaction (SIGCHLD, & sigchld, (struct sigaction *) (0)); 
	sigaction (SIGALRM, & sigalrm, (struct sigaction *) (0)); 
	sigaction (SIGHUP, & sighup, (struct sigaction *) (0)); 
	setlinebuf (stdout); 
	if (!writepf (pidfile)) 
	{ 
		error (1, errno, "can't create pidfile %s", pidfile); 
	} 

#ifdef SYSLOGD_INETAF

/*--------------------------------------------------------------------*
 * the next two checks require some double-think; the forward and 
 * receive flags cannot occur together because that is eliminated
 * above; thus only one or the other or neither flag is set here;
 *
 * we disable receiving and forwarding at the same time to avoid 
 * accidental message loops; this means that each syslog host is
 * either a divinity (source) or a black hole (sink);
 *
 * when forwardng messages we do not add inet sockets to the socket 
 * list but we use the first inet socket (inetsock) as the template 
 * for host-type syslogs; consequently, we allocate the descriptor  
 * calling syslogd_parse() where it is used in * that way;
 *
 * when receiving messages then we add inet sockets to the socket 
 * list and let syslogd_open_sockets() allocate their descriptors
 *  since syslog_parse() does not use inetsock in receive mode; 
 *--------------------------------------------------------------------*/

	if (_anyset (state, SYSLOGD_STATE_RECEIVE)) 
	{ 
		socket = unixsock.next; 
		unixsock.next = inetsock.next; 
		inetsock.next = socket; 
		socket = unixsock.prev; 
		unixsock.prev = inetsock.prev; 
		inetsock.prev = socket; 
	} 
	if (_anyset (state, SYSLOGD_STATE_FORWARD)) 
	{ 
		inetsock.desc = syslogd_inet_socket ((struct sockaddr_in *) (inetsock.sockaddr)); 
		if (inetsock.desc == - 1) 
		{ 
			error (1, errno, "Can't start %s %s service", SYSLOGD_SERVICE_NAME, SYSLOGD_SERVICE_TYPE); 
		} 
	} 

#endif

/*--------------------------------------------------------------------*
 * start mark message timer so that it activates on even multiples of
 * clock time relative to minute 0; timer must be an integral divisor
 * of 3600 and greater than 60 for this to work as intended; function
 * waitspec() filters input to ensure this;
 *--------------------------------------------------------------------*/

	if (timer) 
	{ 
		time_t clock = time (& clock); 
		alarm (timer - clock % timer); 
	} 

/*--------------------------------------------------------------------*
 * read configuration, create syslogs and open them; write the syslog
 * map file, if enabled and requested; open sockets; read messages and
 * dispatch them until terminated; close sockets then close syslogs;
 *--------------------------------------------------------------------*/

	syslogd_start (& syslogs, state, cfgfile); 

#ifdef SYSLOGD_REPORT

	syslogd_admin (& syslogs, state, mapfile); 

#endif

	syslogd_open_sockets (& unixsock); 
	while (loop) 
	{ 
		syslogd_read_sockets (& unixsock); 
	} 
	syslogd_close_sockets (& unixsock); 
	syslogd_stop (& syslogs, state); 
	removepf (pidfile); 
	exit (0); 
} 

