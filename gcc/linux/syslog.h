/*====================================================================*
 *
 *   syslog.h -
 *
 *   LOGTIME is the strftime() format string defined in date.h; it 
 *   has no SYSLOG prefix because it is used in other programs;      
 *
 *   ERRORMSG_MAX is the longest string returned by strerror();
 *
 *   TEXTLINE_MAX is the longest permitted message string; 
 *  
 *--------------------------------------------------------------------*/

#ifndef SYSLOG_HEADER
#define SYSLOG_HEADER

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <stdarg.h>
#include <sys/socket.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/types.h"

/*====================================================================*
 *   constant declarations;
 *--------------------------------------------------------------------*/

#define SYSLOG_SERVICE_NAME "syslog"
#define SYSLOG_SERVICE_TYPE "udp"
#define SYSLOG_EXTENDER '.'

#define SYSLOG_FACILITY_MAX 20
#define SYSLOG_SEVERITY_MAX 20

#define SYSLOG_FACILITIES 25
#define SYSLOG_SEVERITIES 8

#define SYSL0G_FACILITY_BITS 7
#define SYSL0G_SEVERITY_BITS 3

#define SYSLOG_FACILITY_SHIFT 3
#define SYSLOG_SEVERITY_SHIFT 0

#define SYSLOG_FACILITY_MASK 0x03F8
#define SYSLOG_SEVERITY_MASK 0x0007

/*
 * since severity 0 means "emergency" we need another value (outside 
 * the range of assigned priorities) to mean "no priority"; in zero-
 * based value schemes, the number of values is always greater than
 * the maximum value so we use that to mean "no priority"; 
 */

#define SYSLOG_FACILITY(priority) (((priority) & SYSLOG_FACILITY_MASK) >> SYSLOG_FACILITY_SHIFT)
#define SYSLOG_SEVERITY(priority) (((priority) & SYSLOG_SEVERITY_MASK) >> SYSLOG_SEVERITY_SHIFT)
#define SYSLOG_SEVERITY_MAP ((1 << SYSLOG_SEVERITIES) - 1) 
#define SYSLOG_SEVERITY_NONE SYSLOG_SEVERITIES + 1 

/* 
 *   SYSLOG_KERN	kernel messages 
 *   SYSLOG_USER	random user-level messages 
 *   SYSLOG_MAIL	mail system 
 *   SYSLOG_DAEMN	system daemons 
 *   SYSLOG_AUTH	security authorization messages 
 *   SYSLOG_SYSLOG	messages generated internally by syslogd 
 *   SYSLOG_LPR	 	line printer subsystem 
 *   SYSLOG_NEWS	network news subsystem 
 *   SYSLOG_UUCP	UUCP subsystem 
 *   SYSLOG_CRON	clock daemon 
 *   SYSLOG_AUTHPRIV 	securityauthorization messages (private) 
 *   SYSLOG_FTP	 	ftp daemon 
 *   SYSLOG_LOCAL0	reserved for local use 
 *   SYSLOG_LOCAL1	reserved for local use 
 *   SYSLOG_LOCAL2	reserved for local use 
 *   SYSLOG_LOCAL3	reserved for local use 
 *   SYSLOG_LOCAL4	reserved for local use 
 *   SYSLOG_LOCAL5	reserved for local use 
 *   SYSLOG_LOCAL6	reserved for local use 
 *   SYSLOG_LOCAL7	reserved for local use 
 */

#define	SYSLOG_KERN	(0 << SYSLOG_FACILITY_SHIFT)	
#define	SYSLOG_USER	(1 << SYSLOG_FACILITY_SHIFT)	
#define	SYSLOG_MAIL	(2 << SYSLOG_FACILITY_SHIFT)	
#define	SYSLOG_DAEMON	(3 << SYSLOG_FACILITY_SHIFT)	
#define	SYSLOG_AUTH	(4 << SYSLOG_FACILITY_SHIFT)	
#define	SYSLOG_SYSLOG	(5 << SYSLOG_FACILITY_SHIFT)	
#define	SYSLOG_LPR	(6 << SYSLOG_FACILITY_SHIFT)	
#define	SYSLOG_NEWS	(7 << SYSLOG_FACILITY_SHIFT)	
#define	SYSLOG_UUCP	(8 << SYSLOG_FACILITY_SHIFT)	
#define	SYSLOG_CRON	(9 << SYSLOG_FACILITY_SHIFT)	
#define	SYSLOG_AUTHPRIV	(10 << SYSLOG_FACILITY_SHIFT)	
#define	SYSLOG_FTP	(11 << SYSLOG_FACILITY_SHIFT)	
#define	SYSLOG_LOCAL0	(16 << SYSLOG_FACILITY_SHIFT)	
#define	SYSLOG_LOCAL1	(17 << SYSLOG_FACILITY_SHIFT)	
#define	SYSLOG_LOCAL2	(18 << SYSLOG_FACILITY_SHIFT)	
#define	SYSLOG_LOCAL3	(19 << SYSLOG_FACILITY_SHIFT)	
#define	SYSLOG_LOCAL4	(20 << SYSLOG_FACILITY_SHIFT)	
#define	SYSLOG_LOCAL5	(21 << SYSLOG_FACILITY_SHIFT)	
#define	SYSLOG_LOCAL6	(22 << SYSLOG_FACILITY_SHIFT)	
#define	SYSLOG_LOCAL7	(23 << SYSLOG_FACILITY_SHIFT)	
#define SYSLOG_MARK     (24 << SYSLOG_FACILITY_SHIFT)

/*
 *   SYSLOG_EMERG 	system is unusable 
 *   SYSLOG_ALERT   	action must be taken immediately 
 *   SYSLOG_CRIT	critical conditions 
 *   SYSLOG_ERR		error conditions 
 *   SYSLOG_WARNING	warning conditions 
 *   SYSLOG_NOTICE	normal but significant condition 
 *   SYSLOG_INFO	informational 
 *   SYSLOG_DEBUG	debug-level messages 
 */

#define	SYSLOG_EMERG	0	
#define	SYSLOG_ALERT	1	
#define	SYSLOG_CRIT	2	
#define	SYSLOG_ERR	3	
#define	SYSLOG_WARNING	4	
#define	SYSLOG_NOTICE	5	
#define	SYSLOG_INFO	6	
#define	SYSLOG_DEBUG	7	

/*
 *   LOG_PROCESS log the process ID with each message 
 *   LOG_CONSOLE log on the console if errors in sending 
 *   LOG_ODELAY	delay open until first syslog() (default) 
 *   LOG_NDELAY	don't delay open 
 *   LOG_NOWAIT don't wait for console forks: DEPRECATED 
 *   LOG_PERROR	log to stderr as well 
 */

#define SYSLOG_PROCESS (1 << 0)
#define SYSLOG_CONSOLE (1 << 1)
#define SYSLOG_ODELAY (1 << 2)
#define SYSLOG_NDELAY (1 << 3)
#define SYSLOG_NOWAIT (1 << 4)
#define SYSLOG_PERROR (1 << 5)

/*====================================================================*
 *   variable declarations; 
 *--------------------------------------------------------------------*/

typedef unsigned priority_t;
typedef unsigned facility_t;
typedef unsigned severity_t;

/*====================================================================*
 *   function delcarations; 
 *--------------------------------------------------------------------*/

int setlogmask (int severity);
void openlog (char const *identity, int options, int facility);
void vsyslog (int priority, char const *format, va_list arglist);
void closelog ();

/*====================================================================*
 *   function delcarations; 
 *--------------------------------------------------------------------*/

#ifdef __GNUC__

__attribute__ ((format (printf, 2, 3))) 

#endif

void syslog (int priority, char const *format, ...);

#ifdef __GNUC__

__attribute__ ((format (printf, 3, 4))) 

#endif

void syslog_event (int priority, signo_t signal, char const *format, ...);

#ifdef __GNUC__

__attribute__ ((format (printf, 3, 4))) 

#endif

void syslog_error (int priority, errno_t number, char const *format, ...);

#ifdef __GNUC__

__attribute__ ((format (printf, 5, 6))) 

#endif

void syslog_error_at_line (int priority, errno_t number, char const *filename, size_t lineno, char const *format, ...);

/*====================================================================*
 *   function delcarations; 
 *--------------------------------------------------------------------*/

int syslog_encode (char const *string);
char const *syslog_decode (int priority);
int syslog_lookup (char const *string, const struct _code_ table []);
size_t strfpri (char buffer [], size_t length, flag_t option);

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif

