/*====================================================================*
 *
 *   shout.c - send broadcast message to all users; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#define _GETOPT_H

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <syslog.h>
#include <errno.h>
#include <pwd.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../linux/linux.h"
#include "../linux/broadcast.h"
#include "../linux/syslog.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../tools/emalloc.c"
#include "../tools/error.c"
#endif

#ifndef MAKEFILE
#include "../linux/broadcast.c"
#include "../linux/syslog_basic.c"
#include "../linux/syslog_error.c"
#endif

/*====================================================================*
 *   
 *   int main(int argc, char ** argv);
 *   
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv []) 

{
	extern char const *program_name;
	static char const * optv [] = 
	{
		"bcnrt",
		"message [message] [...] or [< stdin]",
		"broadcast a message on all terminals",
		"b\tprint each argument as one bullet point",
		"n\tdiscard broadcast preamble for root only",
		"c\tdisplay broadcast terminal count",
		"t\tdisplay broadcast terminal 


