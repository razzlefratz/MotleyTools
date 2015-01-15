/*====================================================================*
 *   
 *   signed spawn (signed noerr, char *program, ...);
 *   
 *   spawn a program;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SPAWN_SOURCE
#define SPAWN_SOURCE

#include <stdio.h>
#include <stdarg.h>
#include <error.h>
#include <errno.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>

#include "../tools/basic.h"
#include "../files/files.h"
#include "../linux/linux.h"

char * export [ENVPSIZE] =

{
	"HOME=/",
	"PATH=/bin:/usr/bin:/sbin:/usr/sbin",
	"TERM=dumb",
	(char *) (0),
};

signed spawn (signed nostderr, char * program, ...)

{
	extern char ** environ;
	int count;
	for (count = 0; count < 10; count++)
	{
		pid_t pid = fork ();
		if (pid < (pid_t) (0))
		{
			error (0, errno, "Can't fork %s", program);
			sleep (1);
		}
		if (pid > (pid_t) (0))
		{
			int status;
			pid_t cpid;
			while ((cpid = wait (& status)) != pid)
			{
				if (cpid == -1)
				{
					if (errno == ECHILD)
					{
						return (-1);
					}
				}
			}
			return (WEXITSTATUS (status));
		}
		if (pid == (pid_t) (0))
		{
			va_list arglist;
			char * argv [ARGVSIZE];
			int argc = 0;
			if (nostderr)
			{
				fclose (stderr);
			}
			chdir ("/");
			environ = export;
			argv [argc++] = program;
			va_start (arglist, program);
			while ((argc < (ARGVSIZE -1)) && (arglist != (void *) (0)))
			{
				argv [argc++] = va_arg (arglist, char *);
			}
			va_end (arglist);
			if (arglist != (void *) (0))
			{
				error (1, E2BIG, "Won't exec %s", program);
			}
			argv [argc] = (char *) (0);
			execvp (* argv, argv);
			error (1, errno, "Can't exec %s", program);
		}
	}
	return (-1);
}

#endif



