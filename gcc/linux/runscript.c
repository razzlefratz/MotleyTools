/*====================================================================*
 *
 *   int runscript (char const *script, char const *args);
 *
 *   execute a string as a script with the specified command line
 *   option string;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef RUNSCRIPT_SOURCE
#define RUNSCRIPT_SOURCE

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <paths.h>
#include <errno.h>

#include "../linux/linux.h"
#include "../tools/paths.h"
#include "../tools/error.h"
#include "../tools/sizes.h"

int runscript (char const * source, char const * option, flag_t flags) 

{
	char script [FILENAME_MAX + 1] = PATH_TEMPFILE;
	char header [FILENAME_MAX + 4] = "#!" PATH_SHELL "\n";
	pid_t pid;
	int fd;
	if ((fd = mkstemp (script)) == -1) 
	{
		error (0, errno, "%s: Can't create tempfile", script);
		close (fd);
		return (-1);
	}
	if (fchmod (fd, 0700) != 0) 
	{
		error (0, errno, "%s: Can't set permissions", script);
		close (fd);
		return (-1);
	}
	write (fd, header, strlen (header));
	write (fd, source, strlen (source));
	close (fd);
	pid = fork ();
	if (pid == (pid_t) (0)) 
	{
		char *argv [ARGVSIZE];
		int argc = 0;
		argv [argc++] = PATH_SHELL;
		argv [argc++] = script;
		argv [argc++] = (char *) (option);
		argv [argc++] = (char *) (0);
		execv (*argv, argv);
		error (1, errno, "Can't start shell %s", *argv);
	}
	if (pid < (pid_t) (0)) 
	{
		error (0, errno, "Can't spawn child");
		unlink (script);
		return (-1);
	}
	if (pid > (pid_t) (0)) 
	{
		int status;
		waitpid (pid, &status, 0);
		if (WIFEXITED (status)) 
		{
			if ((status = WEXITSTATUS (status)) != 0) 
			{
				error (0, 0, "%s: Exited with status %d", script, status);
				unlink (script);
				return (-1);
			}
		}
		if (WIFSIGNALED (status)) 
		{
			if ((status = WTERMSIG (status)) != 0) 
			{
				error (0, 0, "%s: Terminated by signal %d", script, status);
				unlink (script);
				return (-1);
			}
		}
	}
	unlink (script);
	return (0);
}


#endif

