/*====================================================================*
 *
 *   linux.h - linux definitions and declarations;
 *
 *.  published 2005 by charles maier associates limited for internal use;
 *:  compiled for debian gnu/linux environment using gcc 2.95 compiler;
 *;  licensed according to the GNU Public License version two;
 *
 *--------------------------------------------------------------------*/

#ifndef LINUX_HEADER
#define LINUX_HEADER

/*====================================================================*
 *   system header files; 
 *--------------------------------------------------------------------*/

#include <sys/types.h>
#include <time.h>

/*====================================================================*
 *   custom header files; 
 *--------------------------------------------------------------------*/

#include "../classes/types.h"

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

char  *_dirname(char const *filename);
char *_basename(char const *filename);

/*====================================================================*
 *   
 *--------------------------------------------------------------------*/

uid_t userid (char const *string);
mode_t setumask (char const *string);

char *procname(pid_t pid);
char *username(uid_t uid);
char *hostname(uid_t uid);

int getprocname (char buffer[], size_t length, pid_t pid);
int getusername (char buffer[], size_t length, uid_t uid);

void getviewport(unsigned *rows, unsigned *columns);

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
 *   strcut stat.st_mode shift and mask values;   
 *--------------------------------------------------------------------*/

#define FILE_MODE_BITS 12
#define FILE_MODE_MASK 0x0FFF
#define FILE_TYPE_BITS 16
#define FILE_TYPE_MASK 0xFFFF

char ftypecode (mode_t ftypemask);
mode_t ftypemask (char ftypecode);

/*====================================================================*
 *   end definitions and declarations;
 *--------------------------------------------------------------------*/

#endif

