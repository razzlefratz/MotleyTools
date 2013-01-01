/*====================================================================*
 *
 *   paths.h - filename and pathname definitions and declarations;
 *
 *   these are our favorite definitions and declarations; they are used
 *   throughout our software for clarity and consistency; learn to love
 *   them and make them your own;
 *
 *.  Motley Tools by Charles Maier
 *:  modified tue 16 sep 03 by user root on host zeus;
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
 *   system pathnames;       
 *--------------------------------------------------------------------*/

#define _PATH_CONSOLE	"/dev/console"
#define _PATH_FASTBOOT	"/fastboot"		/ Enable fast boot. */
#define _PATH_FORCEFSCK	"/forcefsck"		/ Force fsck on boot */
#define _PATH_INITPATH	"/sbin/init"		/ Location of init itself. */
#define _PATH_INITSCRIPT "/etc/initscript"	/ */
#define _PATH_INITTAB	"/etc/inittab"		/ Location of inittab */
#define _PATH_PWRSTAT	"/etc/powerstatus"	/ COMPAT: SIGPWR reason (OK/BAD) */
#define _PATH_SDALLOW	"/etc/shutdown.allow"	/ Users allowed to shutdown */
#define _PATH_SDPIDFILE	"/var/run/shutdown.pid"	/ PID of shutdown program */
#define _PATH_SHELL	"/bin/sh"		/ default shell */
#define _PATH_SHUTDOWN	"/sbin/shutdown"	/ shutdown program */
#define _PATH_SULOGIN 	"/sbin/sulogin"		/ sulogin program */
#define _PATH_SYSLOG    "/dev/log"
#define _PATH_TERMINAL	"/dev/tty0"		/ virtual terminal */
#define _PATH_TEMPFILE  "/tmp/XXXXXX"		/ */
#define _PATH_PASSWD    "/etc/passwd"
#define _PATH_SHADOW    "/etc/shadow"
#define _PATH_HOSTNAME  "/etc/hostname"

/*====================================================================*
 *   custom pathnames;       
 *--------------------------------------------------------------------*/

#define PATH_CMASSOC "/usr/local/bin/cmassoc"
#define PATH_TEMPFILE "/tmp/XXXXXX"
#define PATH_RECYCLE "/etc/recycle.d"
#define PATH_RUNJOBS "/etc/runjobs.d"
#define PATH_SHELL "/bin/bash"
#define PATH_TAR "/bin/tar"

/*====================================================================*
 *   custom pathspecs;
 *--------------------------------------------------------------------*/

#define PATH_SYSDIRS "/etc:/bin:/sbin:/lib:/var"
#define PATH_BINDIRS "/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin"
#define PATH_LIBDIRS "/lib:/usr/lib:/usr/local/lib"
#define PATH_INCDIRS "/usr/include:/usr/local/include"

/*====================================================================*
 *   end definitions and declarations;
 *--------------------------------------------------------------------*/

#endif

