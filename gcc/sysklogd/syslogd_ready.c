/*====================================================================*
 *   
 *   void syslogd_ready (struct syslogd *syslog, flag_t flags);
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SYSLOGD_READY_SOURCE
#define SYSLOGD_READY_SOURCE

/*--------------------------------------------------------------------*
 *   system headers;
 *--------------------------------------------------------------------*/

#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <fcntl.h>
#include <error.h>
#include <errno.h>
#include <time.h>

/*--------------------------------------------------------------------*
 *   custom headers;
 *--------------------------------------------------------------------*/

#include "../linux/syslog.h"
#include "../sysklogd/syslogd.h"
#include "../tools/tools.h"
#include "../tools/sizes.h"
#include "../tools/flags.h"

/*--------------------------------------------------------------------*
 *   variables;
 *--------------------------------------------------------------------*/

#ifdef SYSLOGD_INETAF

static char const *sys_h_errlist [] = 

{
	"No problem",
	"Authoritative answer: host not found",
	"Non-authoritative answer: host not found or serverfail",
	"Non recoverable errors",
	"Valid name but no data record of requested type",
	"No address. Look for MX record"
};


#endif

/*--------------------------------------------------------------------*
 *
 *   syslogd_ready (struct syslogd *syslog, flag_t flags);
 *
 *
 *
 *--------------------------------------------------------------------*/

void syslogd_ready (struct syslogd *syslog, flag_t flags) 

{

#ifdef SYSLOGD_INETAF

	extern struct socket inetsock;

#endif

#ifdef SYSLOGD_INETAF

	struct hostent *hostent;
	struct sockaddr_in *sockaddr_in;
	char buffer [HOSTADDR_MAX];

#endif

	time_t now = time (&now);

#if SYSLOGD_TRACE

	trace_enter ("syslogd_ready");

#endif

	if (now < syslog->f_time) 
	{

#if SYSLOGD_TRACE

		trace_leave ("syslogd_ready");

#endif

		return;
	}
	if (syslog->f_desc != -1) 
	{

#if SYSLOGD_TRACE

		trace_leave ("syslogd_ready");

#endif

		return;
	}
	switch (syslog->f_type) 
	{
	case SYSLOGD_TYPE_NONE:
		break;
	case SYSLOGD_TYPE_HOST:

#ifdef SYSLOGD_INETAF

/*
 * either receive messages or forward messages but not both; this prevents message loops
 * where one host forwards to another to another and back; the receive/forward interlock 
 * here is a companion to that in main(); 
 */

		if (_anyset (flags, SYSLOGD_STATE_RECEIVE)) 
		{
			syslogd_error (EPERM, "Can't forward messages to '%s' as per line %d", syslog->f_name, syslog->f_line);
			break;
		}
		if (_allclr (flags, SYSLOGD_STATE_FORWARD)) 
		{
			syslogd_error (EPERM, "Can't forward messages to '%s' as per line %d", syslog->f_name, syslog->f_line);
			break;
		}

#ifdef NEEDED

		if (_anyset (syslog->f_severity [SYSLOG_MARK >> SYSLOG_FACILITY_SHIFT], SYSLOG_SEVERITY_MAP)) 
		{
			syslogd_error (EPERM, "Disabling MARK messages to '%s'; Ignoring line %d", syslog->f_name, syslog->f_line);
			_clrbits (syslog->f_severity [SYSLOG_MARK >> SYSLOG_FACILITY_SHIFT], SYSLOG_SEVERITY_MAP);
		}

#endif

		if ((hostent = gethostbyname (syslog->f_name)) == (struct hostent *) (0)) 
		{
			syslogd_error (EADDRNOTAVAIL, "Can't resolve hostname %s: %s", syslog->f_name, sys_h_errlist [h_errno]);
			syslog->f_time += SYSLOGD_RETRY_TIME;
			syslog->f_retry = SYSLOGD_RETRY_COUNT;
			break;
		}
		syslog->f_sockaddr_in = NEW (struct sockaddr_in);
		if (syslog->f_sockaddr_in == (struct sockaddr_in *)(0)) 
		{
			syslogd_error (errno, "can't forward messages to %s", syslog->f_name);
			break;
		}
		sockaddr_in = (struct sockaddr_in *)(inetsock.sockaddr);
		syslog->f_sockaddr_in->sin_family = sockaddr_in->sin_family;
		syslog->f_sockaddr_in->sin_port = sockaddr_in->sin_port;
		memcpy (&syslog->f_sockaddr_in->sin_addr, *hostent->h_addr_list, hostent->h_length);
		syslog->f_desc = inetsock.desc;
		getsocketname (buffer, sizeof (buffer), syslog->f_sockaddr_in);
		syslogd_print (SYSLOG_SYSLOG|SYSLOG_INFO, "Forward messages to %s using %s", syslog->f_name, buffer);

#else

		syslogd_error (ENOSYS, "Can't forward messages to '%s' as per line %d", syslog->f_name, syslog->f_line);

#endif

		break;
	case SYSLOGD_TYPE_PIPE:
		syslog->f_desc = open (syslog->f_name, O_RDWR | O_NONBLOCK);
		if (syslog->f_desc == -1) 
		{
			syslogd_error (errno, "Can't log messages to '%s' as per line %d", syslog->f_name, syslog->f_line);
			syslog->f_retry = SYSLOGD_RETRY_COUNT;
			syslog->f_time += SYSLOGD_RETRY_TIME;
		}
		break;
	case SYSLOGD_TYPE_FILE:
		syslog->f_desc = open (syslog->f_name, O_WRONLY | O_APPEND | O_NOCTTY | O_CREAT, 0644);
		if (syslog->f_desc == -1) 
		{
			syslogd_error (errno, "Can't log messages to '%s' as per line %d", syslog->f_name, syslog->f_line);
			syslog->f_retry = SYSLOGD_RETRY_COUNT;
			syslog->f_time += SYSLOGD_RETRY_TIME;
		}
		break;
	case SYSLOGD_TYPE_CONSOLE:
		if (_anyset (flags, SYSLOGD_STATE_SILENT)) 
		{
			syslogd_error (EPERM, "Can't log messages to '%s' as per line %d", syslog->f_name, syslog->f_line);
			syslog->f_type = SYSLOGD_TYPE_NONE;
		}
	case SYSLOGD_TYPE_TERM:
		syslog->f_desc = open (syslog->f_name, O_WRONLY | O_APPEND | O_NOCTTY);
		if (syslog->f_desc == -1) 
		{
			syslogd_error (errno, "Can't log messages to '%s' as per line %d", syslog->f_name, syslog->f_line);
			syslog->f_type = SYSLOGD_TYPE_NONE;
		}
		break;
	case SYSLOGD_TYPE_SITE:
	case SYSLOGD_TYPE_USER:
		break;
	default:
		break;
	}

#if SYSLOGD_TRACE

	trace_leave ("syslogd_ready");

#endif

	return;
}


#endif

