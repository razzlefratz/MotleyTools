/*====================================================================*
 *
 *   klogd.c - main program for Linux kernel log daemon.
 *   Copyright (c) 1995  Dr. G.W. Wettstein <greg@wind.rmcc.com>
 *   
 *   This file is part of the sysklogd package, a kernel and system log daemon.
 *   
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *   
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *   
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *--------------------------------------------------------------------*/

/*====================================================================*
 *
 * Steve Lord (lord@cray.com) 7th Nov 92
 *
 * Modified to check for kernel info by Dr. G.W. Wettstein 02/17/93.
 *
 * Fri Mar 12 16:53:56 CST 1993:  Dr. Wettstein
 *      Modified LogLine to use a newline as the line separator in
 *      the kernel message buffer.
 *
 *      Added debugging code to dump the contents of the kernel message
 *      buffer at the start of the LogLine function.
 *
 * Thu Jul 29 11:40:32 CDT 1993:  Dr. Wettstein
 *      Added syscalls to turn off logging of kernel messages to the
 *      console when klogd becomes responsible for kernel messages.
 *
 *      klogd now catches SIGTERM and SIGKILL signals.  Receipt of these
 *      signals cases the clean_up function to be called which shuts down
 *      kernel logging and re-enables logging of messages to the console.
 *
 * Sat Dec 11 11:54:22 CST 1993:  Dr. Wettstein
 *      Added fixes to allow compilation with no complaints with -Wall.
 *
 *      When the daemon catches a fatal signal (SIGTERM, SIGKILL) a 
 *      message is output to the logfile advising that the daemon is
 *      going to terminate.
 *
 * Thu Jan  6 11:54:10 CST 1994:  Dr. Wettstein
 *      Major re-write/re-organization of the code.
 *
 *      Klogd now assigns kernel messages to priority levels when output
 *      to the syslog facility is requested.  The priority level is
 *      determined by decoding the prioritization sequence which is
 *      tagged onto the start of the kernel messages.
 *
 *      Added the following program options: -f arg -c arg -s -o -d
 *
 *              The -f switch can be used to specify that output should
 *              be written to the named file.
 *
 *              The -c switch is used to specify the level of kernel
 *              messages which are to be directed to the console.
 *
 *              The -s switch causes the program to use the syscall
 *              interface to the kernel message facility.  This can be
 *              used to override the presence of the /proc filesystem.
 *
 *              The -o switch causes the program to operate in 'one-shot'
 *              mode.  A single call will be made to read the complete
 *              kernel buffer.  The contents of the buffer will be
 *              output and the program will terminate.
 *
 *              The -d switch causes 'debug' mode to be activated.  This
 *              will cause the daemon to generate LOTS of output to stderr.
 *
 *      The buffer decomposition function (LogLine) was re-written to
 *      squash a bug which was causing only partial kernel messages to
 *      be written to the syslog facility.
 *
 *      The signal handling code was modified to properly differentiate
 *      between the STOP and TSTP signals.
 *
 *      Added pid saving when the daemon detaches into the background.  Thank
 *      you to Juha Virtanen (jiivee@hut.fi) for providing this patch.
 *
 * Mon Feb  6 07:31:29 CST 1995:  Dr. Wettstein
 *      Significant re-organization of the signal handling code.  The
 *      signal handlers now only set variables.  Not earth shaking by any
 *      means but aesthetically pleasing to the code purists in the group.
 *
 *      Patch to make things more compliant with the file system standards.
 *      Thanks to Chris Metcalf for prompting this helpful change.
 *
 *      The routines responsible for reading the kernel log sources now
 *      initialize the buffers before reading.  I think that this will
 *      solve problems with non-terminated kernel messages producing
 *      output of the form:  new old old old
 *
 *      This may also help influence the occassional reports of klogd
 *      failing under significant load.  I think that the jury may still
 *      be out on this one though.  My thanks to Joerg Ahrens for initially
 *      tipping me off to the source of this problem.  Also thanks to
 *      Michael O'Reilly for tipping me off to the best fix for this problem.
 *      And last but not least Mark Lord for prompting me to try this as
 *      a means of attacking the stability problem.
 *
 *      Specifying a - as the arguement to the -f switch will cause output
 *      to be directed to stdout rather than a filename of -.  Thanks to
 *      Randy Appleton for a patch which prompted me to do this.
 *
 * Wed Feb 22 15:37:37 CST 1995:  Dr. Wettstein
 *      Added version information to logging startup messages.
 *
 * Wed Jul 26 18:57:23 MET DST 1995: Martin Schulze
 *      Added an commandline argument "-n" to avoid forking. This obsoletes
 *      the compiler define NO_FORK. It's more useful to have this as an
 *      argument as there are many binary versions and one doesn't need to
 *      recompile the daemon.
 *
 * Thu Aug 10 19:01:08 MET DST 1995: Martin Schulze
 *      Added my pidfile.[ch] to it to perform a better handling with pidfiles.
 *      Now both, syslogd and klogd, can only be started once. They check the
 *      pidfile.
 *
 * Fri Nov 17 15:05:43 CST 1995:  Dr. Wettstein
 *      Added support for kernel address translation.  This required moving
 *      some definitions and includes to the new klogd.h file.  Some small
 *      code cleanups and modifications.
 *
 * Mon Nov 20 10:03:39 MET 1995
 *      Added -v option to print the version and exit.
 *
 * Thu Jan 18 11:19:46 CST 1996:  Dr. Wettstein
 *      Added suggested patches from beta-testers.  These address two
 *      two problems.  The first is segmentation faults which occur with
 *      the ELF libraries.  This was caused by passing a null pointer to
 *      the strcmp function.
 *
 *      Added a second patch to remove the pidfile as part of the
 *      termination cleanup sequence.  This minimizes the potential for
 *      conflicting pidfiles causing immediate termination at boot time.
 *      
 * Wed Aug 21 09:13:03 CDT 1996:  Dr. Wettstein
 *      Added ability to reload static symbols and kernel module symbols
 *      under control of SIGUSR1 and SIGUSR2 signals.
 *
 *      Added -p switch to select 'paranoid' behavior with respect to the
 *      loading of kernel module symbols.
 *
 *      Informative line now printed whenever a state change occurs due
 *      to signal reception by the daemon.
 *
 *      Added the -i and -I command line switches to signal the currently
 *      executing daemon.
 *
 * Tue Nov 19 10:15:36 PST 1996: Leland Olds <olds@eskimo.com>
 *      Corrected vulnerability to buffer overruns by rewriting LogLine
 *      routine.  Obscenely long kernel messages will now be broken up
 *      into lines no longer than LOG_LINE_LENGTH.
 *
 *      The last version of LogLine was vulnerable to buffer overruns:
 *      - Kernel messages longer than LOG_LINE_LENGTH caused a buffer
 *        overrun.
 *      - If a line was determined to be shorter than LOG_LINE_LENGTH,
 *        the routine "ExpandKadds" could cause the line grow by
 *        an unknown amount and overrun a buffer.
 *      I turned these routines into a little parsing state machine that
 *      should not have these problems.
 *
 * Sun Jun 15 16:23:29 MET DST 1997: Michael Alan Dorman
 *      Some more glibc patches made by <mdorman@debian.org>.
 *
 * Thu Aug 21 12:11:27 MET DST 1997: Martin Schulze <joey@infodrom.north.de>
 *      Fixed little mistake which prevented klogd from accepting a
 *      console log 
 *
 * Fri Jan  9 00:39:52 CET 1998: Martin Schulze <joey@infodrom.north.de>
 *      Changed the behaviour of klogd when receiving a terminate
 *      signal.  Now the program terminates immediately instead of
 *      completing the receipt of a kernel message, i.e the read()
 *      call.  The old behaveiour could result in klogd being
 *      recognized as being undead, because it'll only die after a
 *      message has been received.
 *
 * Fri Jan  9 11:03:48 CET 1998: Martin Schulze <joey@infodrom.north.de>
 *      Corrected some code that caused klogd to dump core when
 *      receiving messages containing '%', some of them exist in
 *      2.1.78.  Thanks to Chu-yeon Park <kokids@doit.ajou.ac.kr> for
 *      informing me.
 *
 * Fri Jan  9 23:38:19 CET 1998: Florian La Roche <florian@knorke.saar.de>
 *      Added -x switch to omit EIP translation and System.map evaluation.
 *
 * Sun Jan 25 20:47:46 CET 1998: Martin Schulze <joey@infodrom.north.de>
 *      As the bug covering the %'s introduced a problem with
 *      unevaluated priorities I've worked out a real fix that strips
 *      %'s to an even number which is harmless for printf.
 *
 * Sat Oct 10 20:01:48 CEST 1998: Martin Schulze <joey@infodrom.north.de>
 *      Added support for TESTING define which will turn klogd into
 *      stdio-mode used for debugging.
 *
 * Mon Apr 13 18:18:45 CEST 1998: Martin Schulze <joey@infodrom.north.de>
 *      Modified System.map read function to try all possible map
 *      files until a file with matching version is found.  Added support for
 *      Debian release.
 *
 * Mon Oct 12 13:01:27 MET DST 1998: Martin Schulze <joey@infodrom.north.de>
 *      Used unsigned long and strtoul() to resolve kernel oops symbols.
 *
 * Sun Jan  3 18:38:03 CET 1999: Martin Schulze <joey@infodrom.north.de>
 *      Shortened LOG_LINE_LENGTH in order to get long lines splitted
 *      up earlier and syslogd has a better chance concatenating them
 *      together again.
 *
 * Sat Aug 21 12:27:02 CEST 1999: Martin Schulze <joey@infodrom.north.de>
 *      Skip newline when reading in messages.
 *
 * Tue Sep 12 22:14:33 CEST 2000: Martin Schulze <joey@infodrom.ffis.de>
 *      Don't feed a buffer directly to a printf-type routine, use
 *      "%s" as format string instead.  Thanks to Jouko Pynn�nen
 *      <jouko@solutions.fi> for pointing this out.
 *
 * Tue Sep 12 22:44:57 CEST 2000: Martin Schulze <joey@infodrom.ffis.de>
 *      Commandline option `-2': When symbols are expanded, print the
 *      line twice.  Once with addresses converted to symbols, once with the
 *      raw text.  Allows external programs such as ksymoops do their own
 *      processing on the original data.  Thanks to Keith Owens
 *      <kaos@ocs.com.au> for the patch.
 *
 * Mon Sep 18 09:32:27 CEST 2000: Martin Schulze <joey@infodrom.ffis.de>
 *      Added patch to fix priority decoding after moving kernel
 *      messgages into "%s".  Thanks to Solar Designer
 *      <solar@false.com> for the patch.
 *
 * Sun Mar 11 20:23:44 CET 2001: Martin Schulze <joey@infodrom.ffis.de>
 *      Stop LogLine() from being called with wrong argument when a
 *      former calculation failed already.  Thanks to Thomas Roessler
 *      <roessler@does-not-exist.org> for providing a patch.
 *
 *      Ignore zero bytes, no busy loop is entered anymore.  Several
 *      people have submitted patches: Troels Walsted Hansen
 *      <troels@thule.no>, Wolfgang Oertl <Wolfgang.Oertl@uibk.ac.at>
 *      and Thomas Roessler.
 *
 *--------------------------------------------------------------------*/

#define _GETOPT_H

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

/* __GLIBC__ */

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <syslog.h>
#include <error.h>
#include <errno.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#if !defined(__GLIBC__)
#include <linux/time.h>
#endif 
#include <stdarg.h>
#include <paths.h>
#include <stdlib.h>

#define __LIBRARY__
#include <linux/unistd.h>
#if !defined(__GLIBC__)
# define __NR_ksyslog __NRSyslog

_syscall3 (int, ksyslog, int, type, char *, buf, int, len); 

#else
#include <sys/klog.h>
#define ksyslog klogctl
#endif

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../sysklogd/ksyms.h"
#include "../linux/syslog.h"
#include "../tools/getoptv.h"
#include "../tools/version.h"
#include "../tools/types.h"
#include "../linux/pidfile.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../linux/readpf.c"
#include "../linux/writepf.c"
#include "../linux/checkpf.c"
#include "../sysklogd/syslog-base.c"
#include "../sysklogd/ksyms.c"
#include "../sysklogd/kmodsyms.c"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define KLOG_DELAY 5

#define LOG_BUFFER_SIZE 4096
#define LOG_LINE_LENGTH 1000

static enum LOGSRC 

{ 
	none, 
	proc, 
	kernel
} 

logsrc; 

/*====================================================================*
 *   program variables;
 *--------------------------------------------------------------------*/

static char const * PidFile = _PATH_VARRUN "klogd.pid"; 
static char const * symfile = (char *) (0); 
static char buffer [LOG_BUFFER_SIZE] = ""; 
static int kmsg = 0; 
static int change_state = 0; 
static int terminate = 0; 
static int caught_TSTP = 0; 
static int reload_symbols = 0; 
static int console_log_level = - 1; 
static int use_syscall = 0; 
static int symbol_lookup = 1; 
static int symbols_twice = 0; 
static int one_shot = 0; 
static int no_fork = 0; 
static FILE * ofp = (FILE *) 0; 
int debugging = 0; 

/*====================================================================*
 *  Function prototypes. 
 *--------------------------------------------------------------------*/

extern int ksyslog (int type, char * buf, int len); 
static void CloseLogSrc (void); 
static void restart_klogd (signo_t sig); 
static void stop_logging (signo_t sig); 
static void stop_klogd (signo_t sig); 
static void reload_klogd (signo_t sig); 
static void exit_klogd (void); 
static void signal_klogd (signo_t sig); 
static void ReloadSymbols (void); 
static void ChangeLogging (void); 
static enum LOGSRC GetKernelLogSrc (void); 
static void LogLine (char * ptr, int len); 
static void LogKernelLine (void); 
static void LogProcLine (void); 

/*====================================================================*
 *
 *   extern void Syslog(int priority, char *format, ...);
 *
 *
 *--------------------------------------------------------------------*/

void Syslog (int priority, char const * format, ...) 

{ 
	va_list ap; 
	if (debugging) 
	{ 
		fputs ("Logging line:\n", stderr); 
		fprintf (stderr, "\tLine: %s\n", format); 
		fprintf (stderr, "\tPriority: %d\n", priority); 
	} 
	if (ofp != (FILE *) (0)) 
	{ 
		va_start (ap, format); 
		vfprintf (ofp, format, ap); 
		va_end (ap); 
		fprintf (ofp, "\n"); 
		fflush (ofp); 
		if (!one_shot) 
		{ 
			fsync (fileno (ofp)); 
		} 
		return; 
	} 

/*
 * Output using syslog. 
 */

	if (!strcmp (format, "%s")) 
	{ 
		char * string; 
		va_start (ap, format); 
		string = va_arg (ap, char *); 
		if ((string [0] == '<') && (string [1] != (char) (0)) && (string [2] == '>')) 
		{ 
			switch (string [1]) 
			{ 
			case '0': 
				priority = LOG_EMERG; 
				break; 
			case '1': 
				priority = LOG_ALERT; 
				break; 
			case '2': 
				priority = LOG_CRIT; 
				break; 
			case '3': 
				priority = LOG_ERR; 
				break; 
			case '4': 
				priority = LOG_WARNING; 
				break; 
			case '5': 
				priority = LOG_NOTICE; 
				break; 
			case '6': 
				priority = SYSLOG_INFO; 
				break; 
			case '7': 
			default: 
				priority = LOG_DEBUG; 
			} 
			string += 3; 
		} 
		syslog (priority, format, string); 
		va_end (ap); 
		return; 
	} 
	va_start (ap, format); 
	vsyslog (priority, format, ap); 
	va_end (ap); 
	return; 
} 

/*====================================================================*
 *
 *   static void CloseLogSrc(void);
 *
 *
 *--------------------------------------------------------------------*/

static void CloseLogSrc (void) 

{ 

/*
 * Turn on logging of messages to console. 
 */

	ksyslog (7, NULL, 0); 

/*
 * Shutdown the log sources. 
 */

	switch (logsrc) 
	{ 
	case kernel: 
		ksyslog (0, 0, 0); 
		Syslog (SYSLOG_INFO, "Kernel logging (ksyslog) stopped."); 
		break; 
	case proc: 
		close (kmsg); 
		Syslog (SYSLOG_INFO, "Kernel logging (proc) stopped."); 
		break; 
	case none: 
		break; 
	} 
	if (ofp != (FILE *) (0)) 
	{ 
		fflush (ofp); 
	} 
	return; 
} 

/*====================================================================*
 *
 *   void restart_klogd (signo_t sig);
 *
 *
 *--------------------------------------------------------------------*/

void restart_klogd (signo_t sig) 

{ 
	signal (SIGCONT, restart_klogd); 
	change_state = 1; 
	caught_TSTP = 0; 
	return; 
} 

/*====================================================================*
 *
 *   void stop_logging(signo_t sig);
 *
 *
 *--------------------------------------------------------------------*/

void stop_logging (signo_t sig) 

{ 
	signal (SIGTSTP, stop_logging); 
	change_state = 1; 
	caught_TSTP = 1; 
	return; 
} 

/*====================================================================*
 *
 *   void reload_klogd(signo_t sig);
 *
 *
 *--------------------------------------------------------------------*/

void reload_klogd (signo_t sig) 

{ 
	change_state = 1; 
	reload_symbols = 1; 
	if (sig == SIGUSR1) 
	{ 

// signal (SIGUSR1, reload_klogd);

	} 
	if (sig == SIGUSR2) 
	{ 
		++ reload_symbols; 

// signal (SIGUSR2, reload_klogd);

	} 
	signal (sig, reload_klogd); 
	return; 
} 

/*====================================================================*
 *
 *   void stop_klogd(signo_t sig);
 *
 *
 *--------------------------------------------------------------------*/

void stop_klogd (signo_t sig) 

{ 
	exit_klogd (); 
	return; 
} 

/*====================================================================*
 *
 *   static void signal_klogd(signo_t sig);
 *
 *
 *--------------------------------------------------------------------*/

static void signal_klogd (signo_t sig) 

{ 
	pid_t pid = readpf (PidFile); 
	kill (pid, sig); 
	return; 
} 

/*====================================================================*
 *
 *   static void exit_klogd(void);
 *
 *
 *--------------------------------------------------------------------*/

static void exit_klogd (void) 

{ 
	CloseLogSrc (); 
	Syslog (SYSLOG_INFO, "terminating"); 
	sleep (1); 
	if (ofp != (FILE *) (0)) 
	{ 
		fclose (ofp); 
	} 
	closelog (); 
	remove (PidFile); 
	exit (1); 
} 

/*====================================================================*
 *
 *   static void ReloadSymbols(void);
 *
 *
 *--------------------------------------------------------------------*/

static void ReloadSymbols (void) 

{ 
	if (symbol_lookup) 
	{ 
		if (reload_symbols > 1) 
		{ 
			InitKsyms (symfile); 
		} 
		InitMsyms (); 
	} 
	reload_symbols = change_state = 0; 
	return; 
} 

/*====================================================================*
 *
 *   static void ChangeLogging(void);
 *
 *
 *--------------------------------------------------------------------*/

static void ChangeLogging (void) 

{ 

/*
 * exit_klogd kernel logging. 
 */

	if (terminate == 1) 
	{ 
		exit_klogd (); 
	} 

/*
 * Indicate that something is happening. 
 */

	Syslog (SYSLOG_INFO, "klogd %s.%s, ---------- state change ----------\n", VERSION, RELEASE); 

/*
 * Reload symbols. 
 */

	if (reload_symbols > 0) 
	{ 
		ReloadSymbols (); 
		return; 
	} 

/*
 * Stop kernel logging. 
 */

	if (caught_TSTP == 1) 
	{ 
		CloseLogSrc (); 
		logsrc = none; 
		change_state = 0; 
		return; 
	} 

/*
 * The rest of this function is responsible for restarting
 * kernel logging after it was stopped.
 *
 * In the following section we make a decision based on the
 * kernel log state as to what is causing us to restart.  Somewhat
 * groady but it keeps us from creating another static variable.
 */

	if (logsrc != none) 
	{ 
		Syslog (SYSLOG_INFO, "Kernel logging re-started after SIGSTOP."); 
		change_state = 0; 
		return; 
	} 

/*
 * Restart logging. 
 */

	logsrc = GetKernelLogSrc (); 
	change_state = 0; 
	return; 
} 

/*====================================================================*
 *
 *   static enum LOGSRC GetKernelLogSrc(void);
 *
 *
 *--------------------------------------------------------------------*/

static enum LOGSRC GetKernelLogSrc (void) 

{ 
	struct stat sb; 

/*
 * Set level of kernel console messaging.. 
 */

	if ((console_log_level != - 1) && (ksyslog (8, NULL, console_log_level) < 0) && (errno == EINVAL)) 
	{ 

/*
 * An invalid arguement error probably indicates that
 * a pre-0.14 kernel is being run.  At this point we
 * issue an error message and simply shut-off console
 * logging completely.
 */

		Syslog (LOG_WARNING, "Cannot set console log level - disabling console output."); 
		ksyslog (6, NULL, 0); 
	} 

/*
 * First do a stat to determine whether or not the proc based
 * file system is available to get kernel messages from.
 */

	if (use_syscall || ((stat (_PATH_KLOG, & sb) < 0) && (errno == ENOENT))) 
	{ 

/*
 * Initialize kernel logging. 
 */

		ksyslog (1, NULL, 0); 

#ifdef DEBRELEASE

		Syslog (SYSLOG_INFO, "klogd %s.%s#%s, log source = ksyslog started.", VERSION, RELEASE, DEBRELEASE); 

#else

		Syslog (SYSLOG_INFO, "klogd %s.%s, log source = ksyslog started.", VERSION, RELEASE); 

#endif

		return (kernel); 
	} 
	if ((kmsg = open (_PATH_KLOG, O_RDONLY)) < 0) 
	{ 
		error (0, errno, "can't open proc file system"); 
		ksyslog (7, NULL, 0); 
		exit (1); 
	} 

#ifdef DEBRELEASE

	Syslog (SYSLOG_INFO, "klogd %s.%s#%s, log source = %s started.", VERSION, RELEASE, DEBRELEASE, _PATH_KLOG); 

#else

	Syslog (SYSLOG_INFO, "klogd %s.%s, log source = %s started.", VERSION, RELEASE, _PATH_KLOG); 

#endif

	return (proc); 
} 

/*====================================================================*
 *
 *   static int copyin( char *line, int space, char const *ptr, int len, char const *delim);
 *
 *   Copy characters from ptr to line until a char in the delim
 *   string is encountered or until min( space, len ) chars have
 *   been copied.
 *
 *   Returns the actual number of chars copied.
 *
 *--------------------------------------------------------------------*/

static int copyin (char * line, int space, char const * ptr, int len, char const * delim) 

{ 
	int i; 
	int count; 
	count = len < space? len: space; 
	for (i = 0; i < count && !strchr (delim, * ptr); i++) 
	{ 
		* line++ = * ptr++; 
	} 
	return (i); 
} 

/*====================================================================*
 *
 * Messages are separated by "\n".  Messages longer than
 * LOG_LINE_LENGTH are broken up.
 *
 * Kernel symbols show up in the input buffer as : "[<aaaaaa>]",
 * where "aaaaaa" is the address.  These are replaced with
 * "[symbolname+offset/size]" in the output line - symbolname,
 * offset, and size come from the kernel symbol table.
 *
 * If a kernel symbol happens to fall at the end of a message close
 * in length to LOG_LINE_LENGTH, the symbol will not be expanded.
 * (This should never happen, since the kernel should never generate
 * messages that long.
 *
 * To preserve the original addresses, lines containing kernel symbols
 * are output twice.  Once with the symbols converted and again with the
 * original text.  Just in case somebody wants to run their own Oops
 * analysis on the syslog, e.g. ksymoops.
 *
 *--------------------------------------------------------------------*/

static void LogLine (char * ptr, int len) 

{ 
	enum parse_state_enum 
	{ 
		PARSING_TEXT, 
		PARSING_SYMSTART, 
		PARSING_SYMBOL, 
		PARSING_SYMEND
	}; 
	static char line_buff [LOG_LINE_LENGTH]; 
	static char * line = line_buff; 
	static enum parse_state_enum parse_state = PARSING_TEXT; 
	static int space = sizeof (line_buff) - 1; 

/*
 * points at the '<' of a symbol 
 */

	static char * sym_start; 

/*
 * number of chars copied        
 */

	int delta = 0; 

/*
 * 1 if symbols were expanded 
 */

	int symbols_expanded = 0; 

/*
 * skip symbol lookup on this pass 
 */

	int skip_symbol_lookup = 0; 

/*
 * save start of input line 
 */

	char * save_ptr = ptr; 

/*
 * save length at start of input line 
 */

	int save_len = len; 
	while (len > 0) 
	{ 

/*
 * line buffer is full 
 */

		if (space == 0) 
		{ 

/*
 ** Line too long.  Start a new line.
 */

/*
 * force null terminator 
 */

			* line = 0; 
			if (debugging) 
			{ 
				fputs ("Line buffer full:\n", stderr); 
				fprintf (stderr, "\tLine: %s\n", line); 
			} 
			Syslog (SYSLOG_INFO, "%s", line_buff); 
			line = line_buff; 
			space = sizeof (line_buff) - 1; 
			parse_state = PARSING_TEXT; 
			symbols_expanded = 0; 
			skip_symbol_lookup = 0; 
			save_ptr = ptr; 
			save_len = len; 
		} 
		switch (parse_state) 
		{ 
		case PARSING_TEXT: 
			delta = copyin (line, space, ptr, len, "\n[%"); 
			line += delta; 
			ptr += delta; 
			space -= delta; 
			len -= delta; 
			if (space == 0 || len == 0) 
			{ 

/*
 * full line_buff or end of input buffer 
 */

				break; 
			} 

/*
 * zero byte 
 */

			if (* ptr == '\0') 
			{ 

/*
 * skip zero byte 
 */

				ptr++; 
				space -= 1; 
				len -= 1; 
				break; 
			} 

/*
 * newline 
 */

			if (* ptr == '\n') 
			{ 

/*
 * skip newline 
 */

				ptr++; 
				space -= 1; 
				len -= 1; 

/*
 * force null terminator 
 */

				* line = 0; 
				Syslog (SYSLOG_INFO, "%s", line_buff); 
				line = line_buff; 
				space = sizeof (line_buff) - 1; 
				if (symbols_twice) 
				{ 
					if (symbols_expanded) 
					{ 

/*
 * reprint this line without symbol lookup 
 */

						symbols_expanded = 0; 
						skip_symbol_lookup = 1; 
						ptr = save_ptr; 
						len = save_len; 
					} 
					else 
					{ 
						skip_symbol_lookup = 0; 
						save_ptr = ptr; 
						save_len = len; 
					} 
				} 
				break; 
			} 

/*
 * possible kernel symbol 
 */

			if (* ptr == '[') 
			{ 
				* line++ = * ptr++; 
				space -= 1; 
				len -= 1; 

/*
 * at < 
 */

				if (!skip_symbol_lookup) parse_state = PARSING_SYMSTART; 
				break; 
			} 

/*
 * dangerous printf marker 
 */

			if (* ptr == '%') 
			{ 
				delta = 0; 
				while (len && * ptr == '%') 
				{ 

/*
 * copy it in 
 */

					* line++ = * ptr++; 
					space -= 1; 
					len -= 1; 
					delta++; 
				} 

/*
 * odd amount of %'s 
 */

				if (delta % 2) 
				{ 
					if (space) 
					{ 

/*
 * so simply add one 
 */

						* line++ = '%'; 
						space -= 1; 
					} 
					else 
					{ 

/*
 * remove the last one / terminate the string 
 */

						* line++ = '\0'; 
					} 
				} 
			} 
			break; 
		case PARSING_SYMSTART: 
			if (* ptr != '<') 
			{ 

/*
 * not a symbol 
 */

				parse_state = PARSING_TEXT; 
				break; 
			} 

/*
 ** Save this character for now.  If this turns out to
 ** be a valid symbol, this char will be replaced later.
 ** If not, we'll just leave it there.
 */

/*
 * this will point at the '<' 
 */

			sym_start = line; 
			* line++ = * ptr++; 
			space -= 1; 
			len -= 1; 

/*
 * symbol... 
 */

			parse_state = PARSING_SYMBOL; 
			break; 
		case PARSING_SYMBOL: 
			delta = copyin (line, space, ptr, len, ">\n["); 
			line += delta; 
			ptr += delta; 
			space -= delta; 
			len -= delta; 
			if (space == 0 || len == 0) 
			{ 

/*
 * full line_buff or end of input buffer 
 */

				break; 
			} 
			if (* ptr != '>') 
			{ 
				parse_state = PARSING_TEXT; 
				break; 
			} 

/*
 * copy the '>' 
 */

			* line++ = * ptr++; 
			space -= 1; 
			len -= 1; 
			parse_state = PARSING_SYMEND; 
			break; 
		case PARSING_SYMEND: 
			if (* ptr != ']') 
			{ 

/*
 * not a symbol 
 */

				parse_state = PARSING_TEXT; 
				break; 
			} 

/*
 ** It's really a symbol!  Replace address with the
 ** symbol text.
 */

			{ 
				int sym_space; 
				unsigned long value; 
				struct symbol sym; 
				char const * symbol; 

/*
 * null terminate the address string 
 */

				* (line - 1) = 0; 
				value = strtoul (sym_start + 1, (char **) 0, 16); 

/*
 * put back delim 
 */

				* (line - 1) = '>'; 
				symbol = LookupSymbol (value, & sym); 
				if (!symbol_lookup || symbol == (char *) 0) 
				{ 
					parse_state = PARSING_TEXT; 
					break; 
				} 

/*
 ** verify there is room in the line buffer
 */

				sym_space = space + (line - sym_start); 

/*
 *(30 should be overkill)
 */

				if (sym_space < strlen (symbol) + 30) 
				{ 

/*
 * not enough space 
 */

					parse_state = PARSING_TEXT; 
					break; 
				} 
				delta = sprintf (sym_start, "%s+%d/%d]", symbol, sym.offset, sym.size); 
				space = sym_space + delta; 
				line = sym_start + delta; 
				symbols_expanded = 1; 
			} 
			ptr++; 
			len--; 
			parse_state = PARSING_TEXT; 
			break; 

/*
 * Can't get here! 
 */

		default: 
			parse_state = PARSING_TEXT; 
		} 
	} 
	return; 
} 

/*====================================================================*
 *
 *   static void LogKernelLine(void);
 *
 *   Zero-fill the log buffer.  This should cure a multitude of
 *   problems with klogd logging the tail end of the message buffer
 *   which will contain old messages.  Then read the kernel log
 *   messages into this fresh buffer.
 *
 *--------------------------------------------------------------------*/

static void LogKernelLine (void) 

{ 
	int count; 
	memset (buffer, '\0', sizeof (buffer)); 
	if ((count = ksyslog (2, buffer, sizeof (buffer) - 1)) > 0) 
	{ 
		LogLine (buffer, count); 
	} 
	else if (errno != EINTR) 
	{ 
		error (0, errno, "error return from sys_sycall"); 
	} 
	return; 
} 

/*====================================================================*
 *
 *   static void LogProcLine(void);
 *
 *   Zero-fill the log buffer.  This should cure a multitude of
 *   problems with klogd logging the tail end of the message buffer
 *   which will contain old messages.  Then read the kernel messages
 *   from the message pseudo-file into this fresh buffer.
 *
 *--------------------------------------------------------------------*/

static void LogProcLine (void) 

{ 
	int count; 
	memset (buffer, '\0', sizeof (buffer)); 
	if ((count = read (kmsg, buffer, sizeof (buffer) - 1)) > 0) 
	{ 
		LogLine (buffer, count); 
	} 
	else if (errno != EINTR) 
	{ 
		Syslog (LOG_ERR, "can't read proc file system: %d - %s.", errno, strerror (errno)); 
	} 
	return; 
} 

/*====================================================================*
 *
 *   int main(int argc, char *argv);
 *
 *
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv []) 

{ 
	static char const * optv [] = 
	{ 
		"c:df:iIk:nopsx2", 
		"", 
		"Kernel Log Daemon", 
		"c s\tconsole message level is s", 
		"d\tdebug mode", 
		"f s\toutput file is s", 
		"i\treload module symbols", 
		"I\treload module symbols", 
		"k s\tkernel symbols file is s", 
		"n\tdo not fork", 
		"o\t", 
		"p\tload symbols on oops", 
		"s\tuse syscall interface", 
		"x\t", 
		"2\tprint lines with symbols twice", 
		(char const *) (0)
	}; 
	signo_t sig; 
	int c; 
	chdir ("/"); 
	optind = 1; 
	opterr = 1; 
	while ((c = getoptv (argc, argv, optv)) != - 1) 
	{ 
		switch ((char) (c)) 
		{ 
		case '2': 
			symbols_twice = 1; 
			break; 
		case 'c': 
			if ((strlen (optarg) != 1) || (strchr ("12345678", * optarg) == (char *) (0))) 
			{ 
				error (1, 0, "invalid console logging level <%s> specified", optarg); 
			} 
			console_log_level = * optarg - '0'; 
			break; 
		case 'd': 
			debugging = 1; 
			break; 
		case 'f': 
			if (strcmp (optarg, "-") == 0) 
			{ 
				ofp = stdout; 
			} 
			else if ((ofp = fopen (optarg, "w")) == (FILE *) 0) 
			{ 
				error (1, errno, "can't open %s for output", optarg); 
			} 
			break; 
		case 'i': 
			signal_klogd (SIGUSR1); 
			return (0); 
		case 'I': 
			signal_klogd (SIGUSR2); 
			return (0); 
		case 'k': 
			symfile = optarg; 
			break; 
		case 'n': 
			no_fork++; 
			break; 
		case 'o': 
			one_shot = 1; 
			break; 
		case 'p': 
			SetParanoiaLevel (1); 
			break; 
		case 's': 
			use_syscall = 1; 
			break; 
		case 'x': 
			symbol_lookup = 0; 
			break; 
		default: 
			break; 
		} 
	} 
	argc -= optind; 
	argv += optind; 

/*
 * The following code allows klogd to -background itself.
 * What happens is that the program forks and the parent quits.
 * The child closes all its open file descriptors, and issues a
 * call to setsid to establish itself as an independent session
 * immune from control signals.
 *
 * fork() is only called if it should run in daemon mode, fork is
 * not disabled with the command line argument and there's no
 * such process running.
 */

	if (checkpf (PidFile)) 
	{ 
		error (1, 0, "already running"); 
	} 
	if (!one_shot && !no_fork) 
	{ 
		pid_t pid = fork (); 
		if (pid < 0) 
		{ 
			error (1, errno, "can't fork process"); 
		} 
		if (pid > 0) 
		{ 
			exit (0); 
		} 
		if (pid == 0) 
		{ 
			int fd = getdtablesize (); 
			while (fd-- > 0) 
			{ 
				if ((ofp != stdout) && (fd != fileno (stdout))) 
				{ 
					close (fd); 
				} 
			} 
			setsid (); 
		} 
	} 
	if (!writepf (PidFile)) 
	{ 
		exit_klogd (); 
	} 
	for (sig = 1; sig < NSIG; sig++) 
	{ 
		signal (sig, SIG_IGN); 
	} 
	signal (SIGINT, stop_klogd); 
	signal (SIGKILL, stop_klogd); 
	signal (SIGTERM, stop_klogd); 
	signal (SIGHUP, stop_klogd); 
	signal (SIGTSTP, stop_logging); 
	signal (SIGCONT, restart_klogd); 
	signal (SIGUSR1, reload_klogd); 
	signal (SIGUSR2, reload_klogd); 

/*
 * Open outputs. 
 */

	if (ofp == (FILE *) (0)) 
	{ 
		openlog ("kernel", 0, LOG_KERN); 
	} 

/*
 * Handle one-shot logging. 
 */

	if (one_shot) 
	{ 
		if (symbol_lookup) 
		{ 
			InitKsyms (symfile); 
			InitMsyms (); 
		} 
		if ((logsrc = GetKernelLogSrc ()) == kernel) 
		{ 
			LogKernelLine (); 
		} 
		else 
		{ 
			LogProcLine (); 
		} 
		exit_klogd (); 
	} 

/*
 * Determine where kernel logging information is to come from. 
 */

#if defined(KLOGD_DELAY)

	sleep (KLOGD_DELAY); 

#endif

	logsrc = GetKernelLogSrc (); 
	if (symbol_lookup) 
	{ 
		InitKsyms (symfile); 
		InitMsyms (); 
	} 
	while (1) 
	{ 
		if (change_state) 
		{ 
			ChangeLogging (); 
		} 
		switch (logsrc) 
		{ 
		case kernel: 
			LogKernelLine (); 
			break; 
		case proc: 
			LogProcLine (); 
			break; 
		case none: 
			pause (); 
			break; 
		} 
	} 
	exit (0); 
} 

