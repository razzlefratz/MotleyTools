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

#include <sys/types.h>
#include <time.h>

/*====================================================================*
 *   custom header files; 
 *--------------------------------------------------------------------*/

#include "../tools/types.h"

/*====================================================================*
 *   constants; 
 *--------------------------------------------------------------------*/

#define NOTROOT "You are not the root user"
#define ROOTUID (uid_t)(0) 
#define ROOTGID (gid_t)(0)
#define INITPID (pid_t)(1)

/*====================================================================*
 *   functions;
 *--------------------------------------------------------------------*/

void msyslog (int facility, int severity, char const *format, ...);
void nsyslog (int severity, char const *format, ...);

/*====================================================================*
 *   functions;
 *--------------------------------------------------------------------*/

uid_t userid (char const *string);
mode_t setumask (char const *string);
char const * procname (pid_t pid);
char const * username (uid_t uid);
char const * groupname (gid_t gid);
char const * hostname ();
int getprocname (char buffer [], size_t length, pid_t pid);
int getusername (char buffer [], size_t length, uid_t uid);
int getgroupname (char buffer [], size_t length, gid_t gid);
void getviewport (unsigned *rows, unsigned *columns);

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

