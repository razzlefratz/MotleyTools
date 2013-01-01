/*====================================================================*
 *
 *   linux.h - linux definitions and declarations;
 *
 *.  Motley Tools by Charles Maier
 *:  compiled for debian gnu/linux environment using gcc 2.95 compiler;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef LINUX_HEADER
#define LINUX_HEADER

/*====================================================================*
 *   system header files; 
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <time.h>

/*====================================================================*
 *   custom header files; 
 *--------------------------------------------------------------------*/

#include "../tools/types.h"

/*====================================================================*
 *   system gid, uid and pid values;
 *--------------------------------------------------------------------*/

#define NOTROOT "You are not the root user"
#define ROOTUID (uid_t)(0) /* uid of superuser */
#define ROOTGID (gid_t)(0) /* gid of superuser */
#define INITPID (pid_t)(1) /* pid of init process */

/*====================================================================*
 *   
 *--------------------------------------------------------------------*/

void msyslog (int facility, int severity, char const *format, ...);
void nsyslog (int severity, char const *format, ...);

/*====================================================================*
 *   define macros for common, but error prone, bitmap operations; 
 *--------------------------------------------------------------------*/

char const *_pathname (char const *filename);
char const *_filename (char const *filename);

/*====================================================================*
 *   
 *--------------------------------------------------------------------*/

uid_t userid (char const *string);
mode_t setumask (char const *string);
struct sockaddr_in *hostspec (char const *string);
struct sockaddr_un *sockspec (char const *string);
char *procname (pid_t pid);
char *username (uid_t uid);
char *hostname (uid_t uid);
int getprocname (char buffer [], size_t length, pid_t pid);
int getusername (char buffer [], size_t length, uid_t uid);
size_t strfpid (char buffer [], size_t length, pid_t pid);
size_t strfuid (char buffer [], size_t length, uid_t uid);
size_t strfgid (char buffer [], size_t length, gid_t gid);

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#ifndef _ERROR_H
#ifdef __GNUC__

__attribute__ ((format (printf, 3, 4))) 

#endif

void error (int status, errno_t number, char const *format, ...);

#ifdef __GNUC__

__attribute__ ((format (printf, 3, 4))) 

#endif

void event (int status, signo_t number, char const *format, ...);

#ifdef __GNUC__

__attribute__ ((format (printf, 5, 6))) 

#endif

void error_at_line (int status, errno_t number, char const *filename, unsigned lineno, char const *format, ...);

#endif

/*====================================================================*
 *   end definitions and declarations;
 *--------------------------------------------------------------------*/

#endif

