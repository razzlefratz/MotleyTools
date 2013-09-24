/*====================================================================*
 *
 *   trace.c -
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef TRACE_SOURCE
#define TRACE_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <unistd.h>
#include <string.h>

/*====================================================================*
 *   program constants;   
 *--------------------------------------------------------------------*/

#define ENTER "->"
#define LEAVE "<-"
#define LEVEL "--"
#define SPACE " "

/*====================================================================*
 *   program variables;   
 *--------------------------------------------------------------------*/

static signed level = 0;
static signed count = 0;

/*====================================================================*
 *
 *   void trace_enter (char const *string);
 *
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

void trace_enter(char const * string)

{
	level++;
	for (count = 0; count < level; count++)
	{
		write (STDERR_FILENO, LEVEL, sizeof(LEVEL) - 1);
	}
	write (STDERR_FILENO, ENTER, sizeof(ENTER) - 1);
	write (STDERR_FILENO, SPACE, sizeof(SPACE) - 1);
	write (STDERR_FILENO, string, strlen(string));
	write (STDERR_FILENO, "\n", 1);
	return;
}

/*====================================================================*
 *
 *   void trace_leave (char const *string);
 *
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

void trace_leave(char const * string)

{
	write (STDERR_FILENO, LEAVE, sizeof(LEAVE) - 1);
	for (count = 0; count < level; count++)
	{
		write (STDERR_FILENO, LEVEL, sizeof(LEVEL) - 1);
	}
	write (STDERR_FILENO, SPACE, sizeof(SPACE) - 1);
	write (STDERR_FILENO, string, strlen(string));
	write (STDERR_FILENO, "\n", 1);
	level--;
	return;
}

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif



