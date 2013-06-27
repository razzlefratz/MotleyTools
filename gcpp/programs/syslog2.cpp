/*====================================================================*
 *
 *   syslog2.cpp -  
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <cerrno>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/ogetoptv.hpp"
#include "../classes/oflagword.hpp"
#include "../classes/osyslog.hpp"
#include "../classes/osyslogspec.hpp"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#include "../classes/files.h"
#include "../classes/flags.h"

#ifndef MAKEFILE
#include "../classes/ogetoptv.cpp"
#include "../classes/oputoptv.cpp"
#include "../classes/oversion.cpp"
#include "../classes/oerror.cpp"
#include "../classes/oflagword.cpp"
#include "../classes/osyslog.cpp"
#include "../classes/osyslogspec.cpp"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define SYSLOG2_FLAG_TEST (1 << 0)

/*====================================================================*
 *   program variables;
 *--------------------------------------------------------------------*/

static osyslog msyslog;
static osyslogspec msyslogspec;
static oerror merror;

/*====================================================================*
 *
 *   void mysyslogtest (unsigned priority);
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

static void mysyslogtest (unsigned priority) 

{
	unsigned facility = (priority & SYSLOG_FACILITY_MASK);
	msyslog.syslog (facility | SYSLOG_EMERG, "sample emergency message");
	msyslog.syslog (facility | SYSLOG_ALERT, "sample alert message");
	msyslog.syslog (facility | SYSLOG_CRIT, "sample critical message");
	msyslog.syslog (facility | SYSLOG_ERR, "sample error message");
	msyslog.syslog (facility | SYSLOG_WARNING, "sample warning message");
	msyslog.syslog (facility | SYSLOG_NOTICE, "sample notice message");
	msyslog.syslog (facility | SYSLOG_INFO, "sample information message");
	msyslog.syslog (facility | SYSLOG_DEBUG, "sample debug messaage");
	return;
}

/*====================================================================*
 *   main program;
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv []) 

{
	static char const * optv [] = 
	{
		"b:ef:i:np:t",
		"[message]",
		"write a message to the system logging facility",
		"b s\tidentity is basename of s",
		"e\tlog to stderr",
		"f s\tmessage file is s",
		"i s\tidentity is s",
		"p s\tpriority is s in facility.severity format",
		"n\tinclude PID number",
		"t\ttest",
		(char const *) (0)
	};
	ogetoptv getopt;
	oflagword flagword;
	oflagword options;
	char message [BUFSIZ] = "";
	char * bp = message;
	char const * identity = getlogin ();
	priority_t priority = SYSLOG_USER | SYSLOG_INFO;
	signed c;
	while ((c = getopt.getoptv (argc, argv, optv)) != -1) 
	{
		switch ((char) (c)) 
		{
		case 'b':
			identity = getopt.optarg ();
			for (char const * sp = identity; * sp != (char) (0); ++sp) 
			{
				if (* sp == PATH_C_EXTENDER) 
				{
					identity = sp;
				}
			}
			break;
		case 'e':
			options.setbits (SYSLOG_PERROR);
			break;
		case 'f':
			if (freopen (getopt.optarg (), "r", stdin) == (FILE *) (0)) 
			{
				merror.error (1, errno, "%s", getopt.optarg ());
			}
			break;
		case 'i':
			identity = getopt.optarg ();
			break;
		case 'n':
			options.setbits (SYSLOG_PROCESS);
			break;
		case 'p':
			priority = msyslogspec.encode (getopt.optarg ());
			break;
		case 't':
			flagword.setbits (SYSLOG2_FLAG_TEST);
			break;
		default:
			break;
		}
	}
	msyslog.identity (identity).facility (priority).options (options.getbits ());
	if (flagword.anyset (SYSLOG2_FLAG_TEST)) 
	{
		mysyslogtest (priority);
		return (0);
	}
	if (!getopt.argc ()) 
	{
		while (std::cin.getline (message, sizeof (message)).good ()) 
		{
			msyslog.syslog (priority, "%s", message);
		}
		return (0);
	}
	while (getopt.argc () && * getopt.argv ()) 
	{
		char const * sp = * getopt.argv ();
		while (* sp) 
		{
			if ((unsigned)(bp - message) < (sizeof (message)-1)) 
			{
				* bp++ = * sp++;
			}
		}
		* bp++ = (* getopt.argv ()? ' ': (char) (0); getopt++; } msyslog.syslog (priority, "%s", message); return (0); } 
