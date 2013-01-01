/*====================================================================*
 *
 *   paths.h -
 *
 *.  Motley Tools by Charles Maier
 *:
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef PATHS_HEADER
#define PATHS_HEADER

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <paths.h>

/*====================================================================*
 *   
 *--------------------------------------------------------------------*/

#define _PATH_CONSOLE	"/dev/console"
#define _PATH_FASTBOOT	"/fastboot"		/* Enable fast boot. */
#define _PATH_FORCEFSCK	"/forcefsck"		/* Force fsck on boot */
#define _PATH_INITPATH	"/sbin/init"		/* Location of init itself. */
#define _PATH_INITSCRIPT "/etc/initscript"	/* */
#define _PATH_INITTAB	"/etc/inittab"		/* Location of inittab */
#define _PATH_PWRSTAT	"/etc/powerstatus"	/* COMPAT: SIGPWR reason (OK/BAD) */
#define _PATH_RECYCLE 	"/etc/recycle.d"
#define _PATH_RUNJOBS 	"/etc/runjobs.d"
#define _PATH_SDALLOW	"/etc/shutdown.allow"	/* Users allowed to shutdown */
#define _PATH_SDPIDFILE	"/var/run/shutdown.pid"	/* PID of shutdown program */
#define _PATH_SHELL	"/bin/sh"		/* default shell */
#define _PATH_SHUTDOWN	"/sbin/shutdown"	/* shutdown program */
#define _PATH_SULOGIN 	"/sbin/sulogin"		/* sulogin program */
#define _PATH_SYSLOG    "/dev/log"
#define _PATH_TERMINAL	"/dev/tty0"		/* virtual terminal */
#define _PATH_TEMPFILE  "/tmp/XXXXXX"		/* */
#define _PATH_PASSWD    "/etc/passwd"
#define _PATH_SHADOW    "/etc/shadow"
#define _PATH_HOSTNAME  "/etc/hostname"

/*====================================================================*
 *  
 *--------------------------------------------------------------------*/

#if 0
#define _PATH_INITLVL1		"/etc/initrunlvl"	/* COMPAT: New runlevel */
#define _PATH_INITLVL2		"/var/log/initrunlvl"	/* COMPAT: New runlevel */
#endif

/*====================================================================*
 *   
 *--------------------------------------------------------------------*/

#endif

