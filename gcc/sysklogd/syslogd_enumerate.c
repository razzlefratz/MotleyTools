/*====================================================================*
 *   
 *   syslogd_enumerate.c -
 *
 *   syslogd.h
 *
 *   print a syslogs facility and priority matrix, similar to that 
 *   shown below, on stdout; the matrix is effectively a map of the
 *   syslog.conf settings; it is displayed with the -X option;
 *   
 *   00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20 21 22 23
 *   FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF file /var/log/system.log
 *   80 80 80 80 80 80 80 80 80 80 80 80 80 80 80 80 -- 80 80 80 80 80 80 80 file /var/log/debug.log
 *   70 70 70 70 70 70 70 70 70 70 70 70 70 70 70 70 -- 70 70 70 70 70 70 70 file /var/log/messages
 *   -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- file /var/log/auth.log
 *   -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- file /var/log/authpriv.log
 *   -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- file /var/log/cron.log
 *   -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- file /var/log/daemon.log
 *   -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- file /var/log/ftp.log
 *   FF -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- file /var/log/kern.log
 *   -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- file /var/log/lpr.log
 *   -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- FF -- -- -- -- -- -- -- file /var/log/mail.log
 *   -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- file /var/log/news.log
 *   -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- file /var/log/system.log
 *   -- -- -- -- -- -- -- -- FF -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- file /var/log/user.log 
 *   -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- file /var/log/uucp.log
 *   -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- file /var/log/local0.log 
 *   -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- file /var/log/local1.log 
 *   -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- file /var/log/local2.log 
 *   -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- file /var/log/local3.log 
 *   -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- file /var/log/local4.log 
 *   -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- file /var/log/slapd.log 
 *   -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- file /var/log/local5.log 
 *   -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- file /var/log/local6.log 
 *   -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- file /var/log/imapd.log
 *   -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- file /var/log/local7.log 
 *   01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 world *
 *   3F 3F 3F 3F 3F 3F 3F 3F 3F 3F 3F 3F 3F 3F 3F 3F 3F 3F 3F 3F 3F 3F 3F 3F user root,cmaier
 *   -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 7F -- -- -- -- -- -- -- file /var/log/mail.info
 *   -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 1F -- -- -- -- -- -- -- file /var/log/mail.warn
 *   -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 0F -- -- -- -- -- -- -- file /var/log/mail.err
 *   -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- file /var/log/news/news.crit
 *   -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- file /var/log/news/news.err
 *   -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- file /var/log/news/news.notice
 *   -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- console /dev/console
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SYSLOGD_ENUMERATE_SOURCE
#define SYSLOGD_ENUMERATE_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <sys/syslog.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../linux/syslog.h"
#include "../sysklogd/syslogd.h"

/*====================================================================*
 *   
 *   char *syslogd_facility (struct syslogd *syslog, char buffer[], size_t length);
 *
 *   if syslog is null then encode buffer with the two-digit decimal
 *   number of each facility for the matrix header;
 *
 *   if syslog is not null then encode buffer with the two-digit hex 
 *   bitmap indicting priority for each facility or with "--" for no 
 *   priority; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

static char *syslogd_facility (struct syslogd *syslog, char buffer [], size_t length) 

{
	facility_t facility;
	size_t offset = 0;
	if (syslog == (struct syslogd *)(0)) 
	{
		for (facility = 0; facility < SYSLOG_FACILITIES; facility++) 
		{
			offset += snprintf (buffer + offset, length - offset, " %02d", facility);
		}
		offset += snprintf (buffer + offset, length - offset, "\n");
		return (buffer);
	}
	for (facility = 0; facility < SYSLOG_FACILITIES; facility++) 
	{
		if (syslog->f_severity [facility] != (severity_t)(0)) 
		{
			offset += snprintf (buffer + offset, length - offset, " %02X", syslog->f_severity [facility]);
		}
		else 
		{
			offset += snprintf (buffer + offset, length - offset, " --");
		}
	}
	return (buffer);
}


/*====================================================================*
 *   
 *   static void syslogd_enumerate (struct syslogd *syslogs, FILE *fp);
 *
 *   print syslog facility and priority information on stdout; the 
 *   output is a table with one row for each syslog and one column 
 *   for each facility; table cells are priority bitmap values;
 *
 *   use syslog_state() to inspect individual struct syslogd state;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

void syslogd_enumerate (struct syslogd *syslogs, flag_t flags, FILE *fp) 

{
	extern char const *syslogd_type_names [];
	struct syslogd *syslog;
	char buffer [256];
	fprintf (fp, " %s", syslogd_facility ((struct syslogd *)(0), buffer, sizeof (buffer)));
	for (syslog = syslogs->next; syslog != syslogs; syslog = syslog->next) 
	{
		fprintf (fp, " %s", syslogd_facility (syslog, buffer, sizeof (buffer)));
		fprintf (fp, " %s", syslogd_type_names [syslog->f_type]);
		fprintf (fp, " %s", syslog->f_name);
		fprintf (fp, "\n");
	}
	fprintf (fp, " %s", syslogd_facility (syslog, buffer, sizeof (buffer)));
	fprintf (fp, " %s", syslogd_type_names [syslog->f_type]);
	fprintf (fp, " %s", syslog->f_name);
	fprintf (fp, "\n");
	fprintf (fp, "\n");
	return;
}


#endif

