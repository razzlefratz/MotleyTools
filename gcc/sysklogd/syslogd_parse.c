/*====================================================================*
 *   
 *   void syslogd_parse (struct syslogd *syslog, flag_t flags, char const *string);
 *   
 *   read one syslog selector statement and update a struct syslogd;
 *
 *   statement :== <selector-list> <action-list>
 *   selector-list :== <selector>
 *   selector-list :== <selector-list>,<selector>
 *   selector-list :== <selector-list>;<selector-list>
 *   selector := <facility> 
 *   selector := <facility>.<severity> 
 *
 *   a syslog.conf statement consists of a selector list and target  
 *   list separated by blank space;
 *
 *   the selector list consists of one or more selectors separated
 *   by semicolons and terminated by the intervening blank space;
 *
 *   a selector consists of one or more facility names separated by
 *   comma and terminated by period and severity name; the severity 
 *   name applies to all facilities in the preceding list;
 *
 *   [facility[, facility[, ...]].[severity]; ...
 *
 *   this function scans each selector list for the severity then
 *   scans the list again for each facility; the severity is then
 *   applied to each facility by function syslogd_index();
 *
 *   the target list names a destination file, pipe, device, host 
 *   or userlist; target type is determined by the first character 
 *   as follows: 
 *
 *   target :== -<target>
 *   target :== <file>|<pipe>|<term>|<host>|<site>|<user>
 *   pipe :== |<filename>
 *   file :== /<filename>
 *   term :== /<filename>
 *   host :== @<hostname>
 *   site :== *
 *   user :== <username> 
 *   user :== <user>,<username> 
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SYSLOGD_PARSE_SOURCE
#define SYSLOGD_PARSE_SOURCE

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <fcntl.h>
#include <error.h>
#include <errno.h>
#include <ctype.h>

#include "../linux/syslog.h"
#include "../sysklogd/syslogd.h"
#include "../tools/flags.h"

void syslogd_parse (struct syslogd *syslog, flag_t flags, char const *string) 

{
	extern const struct _code_ syslog_facility_codes [];
	extern const struct _code_ syslog_severity_codes [];
	facility_t facility = (facility_t) (0);
	severity_t severity = (severity_t) (0);
	char symbol [TEXTLINE_MAX];
	char const *sp;
	char *cp;

#if SYSLOGD_TRACE

	trace_enter ("syslogd_parse");

#endif

#if SYSLOGD_DEBUG

	printf ("\nstatement=[%s]\n", string);

#endif

	while (!strchr (" \t", *string)) 
	{
		for (sp = string; !strchr (".; \t", *string); string++);
		if (*string == '.') 
		{
			string++;
		}
		for (cp = symbol; !strchr ("; \t", *string); *cp++ = *string++);
		*cp = '\0';

#if SYSLOGD_DEBUG

		printf ("severity=[%s]\n", symbol);

#endif

		cp = symbol;
		if (*cp == '!') 
		{
			_setbits (syslog->f_flags, SYSLOGD_FLAG_NEGATE_PRIORITY);
			cp++;
		}
		else 
		{
			_clrbits (syslog->f_flags, SYSLOGD_FLAG_NEGATE_PRIORITY);
		}
		if (*cp == '=') 
		{
			_setbits (syslog->f_flags, SYSLOGD_FLAG_SINGLE_PRIORITY);
			cp++;
		}
		else 
		{
			_clrbits (syslog->f_flags, SYSLOGD_FLAG_SINGLE_PRIORITY);
		}
		if ((severity = syslog_lookup (cp, syslog_severity_codes)) == -1) 
		{
			syslogd_error (EINVAL, "Don't recognize severity '%s' as per line %d", cp, syslog->f_line);
			return;
		}
		while (!strchr (".; \t", *sp)) 
		{
			for (cp = symbol; !strchr (",.; \t", *sp); *cp++ = *sp++);
			*cp = (char) (0);

#if SYSLOGD_DEBUG

			printf ("facility=[%s]\n", symbol);

#endif

			if ((facility = syslog_lookup (symbol, syslog_facility_codes)) == -1) 
			{
				syslogd_error (EINVAL, "Don't recognize facility '%s' as per line %d", symbol, syslog->f_line);
				return;
			}
			if (facility == SYSLOG_FACILITIES) 
			{
				for (facility = 0; facility < SYSLOG_FACILITIES; facility++) 
				{

#if SYSLOGD_DEBUG

					printf ("facility=[%04X] severity=[%02X]\n", facility, severity);

#endif

					syslogd_index (syslog, flags, facility, severity);
				}
			}
			else 
			{
				facility = SYSLOG_FACILITY (facility);

#if SYSLOGD_DEBUG

				printf ("facility=[%04X] severity=[%02X]\n", facility, severity);

#endif

				syslogd_index (syslog, flags, facility, severity);
			}
			if (*sp == ',') 
			{
				sp++;
			}
		}
		if (*string == ';') 
		{
			string++;
		}
	}
	while (isblank (*string)) 
	{
		string++;
	}

#if SYSLOGD_DEBUG

	printf ("resource=[%s]\n", string);

#endif

	if (*string == '-') 
	{
		_clrbits (syslog->f_flags, SYSLOGD_FLAG_SYNCHRONIZE);
		string++;
	}
	else 
	{
		_setbits (syslog->f_flags, SYSLOGD_FLAG_SYNCHRONIZE);
	}
	switch (*string) 
	{
	case '@':
		syslog->f_type = SYSLOGD_TYPE_HOST;
		syslog->f_name = strdup (++string);
		break;
	case '|':
		syslog->f_type = SYSLOGD_TYPE_PIPE;
		syslog->f_name = strdup (++string);
		break;
	case '/':
		syslog->f_type = SYSLOGD_TYPE_FILE;
		syslog->f_name = strdup (string);
		if (isatty (syslog->f_desc)) 
		{
			if (!strcmp (string, _PATH_CONSOLE)) 
			{
				syslog->f_type = SYSLOGD_TYPE_CONSOLE;
				break;
			}
			syslog->f_type = SYSLOGD_TYPE_TERM;
		}
		break;
	case '*':
		syslog->f_type = SYSLOGD_TYPE_SITE;
		syslog->f_name = strdup ("*");
		break;
	default:
		syslog->f_type = SYSLOGD_TYPE_USER;
		syslog->f_name = strdup (string);
		break;
	}

#if SYSLOGD_TRACE

	trace_leave ("syslogd_parse");

#endif

	return;
}


#endif

