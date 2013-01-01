/*====================================================================*
 *
 *   syslogd.h - definitions and declarations for syslogd 
 *
 *.  Motley Tools by Charles Maier
 *:  Packaged as cmassoc-tools-1.4.10 by cmaier@cmassoc.net;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SYSLOGD_SOURCE
#define SYSLOGD_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <time.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/param.h>
#include <sys/uio.h>
#include <netinet/in.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/paths.h"
#include "../tools/types.h"
#include "../tools/sizes.h"
#include "../tools/trace.h"
#include "../linux/syslog.h"

/*====================================================================*
 *   constant definitions;
 *--------------------------------------------------------------------*/

#define SYSLOGD_DEBUG 0 /* display parser input and tokens on stderr */
#define SYSLOGD_TRACE 0 /* display function call hierarchy on stderr */

#define SYSLOGD_INETAF 1 /* enable inet domain sockets for logging */
#define SYSLOGD_UNIXAF 1 /* enable unix domain sockets for logging */
#define SYSLOGD_REPORT 1 /* enable administrator reporting facility */
#define SYSLOGD_ORIGIN 1
#define SYSLOGD_NATURE 1
#define SYSLOGD_NOTIME 1

/*====================================================================*
 *   constant definitions;
 *--------------------------------------------------------------------*/

#ifndef UTMP_FILE
#ifdef UTMP_FILENAME
#define UTMP_FILE UTMP_FILENAME
#else
#ifdef _PATH_UTMP
#define UTMP_FILE _PATH_UTMP
#else
#define UTMP_FILE "/etc/utmp"
#endif
#endif
#endif

#ifndef _PATH_SYSLOG_CONF
#define _PATH_SYSLOG_CONF "/etc/syslog.conf"
#endif

#ifndef _PATH_SYSLOGD_PID
#define _PATH_SYSLOGD_PID "/var/run/syslogd.pid"
#endif

#ifndef _PATH_DEV
#define _PATH_DEV	"/dev/"
#endif

#ifndef _PATH_CONSOLE
#define _PATH_CONSOLE	"/dev/console"
#endif

#ifndef _PATH_TTY
#define _PATH_TTY	"/dev/tty"
#endif

/*====================================================================*
 *   constant definitions;
 *--------------------------------------------------------------------*/

#define SYSLOGD_STATE_DAEMON  (1 << 0)
#define SYSLOGD_STATE_SILENT  (1 << 1)
#ifdef SYSLOGD_INETAF
#define SYSLOGD_STATE_RECEIVE (1 << 2)
#define SYSLOGD_STATE_FORWARD (1 << 3)
#endif
#define SYSLOGD_STATE_ORIGIN (1 << 4)
#define SYSLOGD_STATE_NATURE (1 << 5)

#define SYSLOGD_TYPE_NONE	0 /* unused entry */
#define SYSLOGD_TYPE_FILE	1 /* regular file */
#define SYSLOGD_TYPE_PIPE	2 /* named pipe */
#define SYSLOGD_TYPE_TERM	3 /* terminal */
#define SYSLOGD_TYPE_CONSOLE	4 /* console terminal */
#define SYSLOGD_TYPE_USER	5 /* named users */
#define SYSLOGD_TYPE_SITE	6 /* every user  */
#define SYSLOGD_TYPE_HOST    	7 /* remote host */

#define SYSLOGD_FLAG_DISABLED (1 << 0)
#define SYSLOGD_FLAG_SYNCHRONIZE (1 << 1)
#define SYSLOGD_FLAG_NEGATE_PRIORITY (1 << 2)
#define SYSLOGD_FLAG_SINGLE_PRIORITY (1 << 3)

#define SYSLOGD_STATE SYSLOGD_STATE_ORIGIN|SYSLOGD_STATE_NATURE
#define SYSLOGD_TIMER 1200
#define SYSLOGD_DELAY_TIME 60
#define SYSLOGD_FSYNC_TIME 10
#define SYSLOGD_RETRY_TIME 30
#define SYSLOGD_RETRY_COUNT 10

#define SYSLOGD_SERVICE_NAME "syslog"
#define SYSLOGD_SERVICE_TYPE "udp"
#define SYSLOGD_SERVICE_PORT 514

/*====================================================================*
 *   variable declarations; 
 *--------------------------------------------------------------------*/

typedef struct socket 

{
	struct socket *next;
	struct socket *prev;
	file_t desc;
	size_t socksize;
	struct sockaddr *sockaddr;
	char *buffer;
}

SOCKET;
typedef struct syslogd 

{
	struct syslogd *prev;
	struct syslogd *next;
	code_t f_type;
	char *f_name;
	size_t f_line;
	file_t f_desc;
	time_t f_time;
	flag_t f_flags;
	struct sockaddr_in *f_sockaddr_in;
	severity_t f_severity [SYSLOG_FACILITIES];
	char f_posted [DATETIME_MAX];

#if SYSLOGD_ORIGIN

	char f_origin [HOSTNAME_MAX];

#endif
#if SYSLOGD_NATURE

	char f_nature [ERRORMSG_MAX];

#endif

	char f_notice [TEXTLINE_MAX];
	size_t f_length;
	size_t f_priority;
	size_t f_repeat;
	size_t f_retry;
}

SYSLOG;

/*====================================================================*
 *   function declarations; 
 *--------------------------------------------------------------------*/

void syslogd_sighup (signo_t signal);
void syslogd_sigalrm (signo_t signal);
void syslogd_sigusr1 (signo_t signal);
void syslogd_sigterm (signo_t signal);
void syslogd_sigterm1 (signo_t signal);
void syslogd_sigchld (signo_t signal);

#ifdef SYSLOGD_INETAF

file_t syslogd_inet_socket (struct sockaddr_in *sockaddr_in);
char const *syslogd_gethost (struct sockaddr_in *sockaddr, char const *hosts [], char const *domains []);

#endif

#ifdef SYSLOGD_UNIXAF

file_t syslogd_unix_socket (struct sockaddr_un *sockaddr_un);

#endif

void syslogd_start (struct syslogd *syslogs, flag_t flags, char const *filename);
void syslogd_admin (struct syslogd *syslogs, flag_t flags, char const *filename);
void syslogd_configure (struct syslogd *syslogs, flag_t flags, char const *filename);
void syslogd_parse (struct syslogd *syslog, flag_t flags, char const *string);
void syslogd_ready (struct syslogd *syslog, flag_t flags);
void syslogd_index (struct syslogd *syslog, flag_t flags, facility_t facility, severity_t severity);
void syslogd_listen (struct syslogd *syslogs, flag_t flags);
void syslogd_stop (struct syslogd *syslogs, flag_t flags);
void syslogd_enumerate (struct syslogd *syslogs, flag_t flags, FILE *fp);
void syslogd_state (struct syslogd *syslog, flag_t flags, FILE *fp);
void syslogd_priority (struct syslogd *syslog);
void syslogd_merge (struct socket *socket, char const *origin, char const buffer [], size_t length);
void syslogd_scrub (char const *origin, char const *message);
void syslogd_queue (int priority, char const *origin, char const *notice);
void syslogd_write (struct syslogd *syslog, flag_t flags);
void syslogd_broadcast (char const **usernames, struct iovec message [], size_t elements, flag_t flags);
void syslogd_open_sockets (struct socket *sockets);
void syslogd_read_sockets (struct socket *sockets);
void syslogd_close_sockets (struct socket *sockets);
void syslogd_alloc_buffers ();
void syslogd_free_buffers ();
size_t getsocketname (char buffer [], size_t length, struct sockaddr_in *);

/*====================================================================*
 *   
 *--------------------------------------------------------------------*/

#ifdef __GNUC__

__attribute__ ((format (printf, 2, 3))) 

#endif

void syslogd_error (errno_t number, char const *format, ...);

#ifdef __GNUC__

__attribute__ ((format (printf, 2, 3))) 

#endif

void syslogd_print (int priority, char const *format, ...);

/*====================================================================*
 *   end; 
 *--------------------------------------------------------------------*/

#endif

