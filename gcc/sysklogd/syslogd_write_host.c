/*====================================================================*
 *
 *   void syslogd_write (struct syslogd *syslog, flag_t flags);
 *   
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SYSLOGD_WRITE_SOURCE
#define SYSLOGD_WRITE_SOURCE

#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>

#include "../sysklogd/syslogd.h"
#include "../tools/tools.h"
#include "../tools/flags.h"
#include "../strlib/strlib.h"

#define IOVECSIZE 10

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

void syslogd_write (struct syslogd *syslog, flag_t flags) 

{

#ifdef SYSLOGD_INETAF

	char packet [TEXTLINE_MAX];
	size_t length = 0;

#endif

	struct hostent *hostent;
	time_t now = time (&now);

#if SYSLOGD_TRACE

	trace_enter ("syslogd_write");

#endif

/*
 * lookup host IP address; this can fail due to name server delays or
 * server failure; if successful then update the syslog structure and
 * forward immediately; otherwise, decrement the retry count, set the
 * retry time and continue; retry after that time; abandon once retry
 * count has expired;
 */

	if (syslog->f_desc == -1) 
	{
		if (now < syslog->f_time) 
		{
			return;
		}
		if (syslog->f_retry == 0) 
		{
			_setbits (syslog->f_flags, SYSLOGD_FLAG_DISABLED);
			syslogd_error (ETIMEDOUT, "Cancelling message forwarding to host %s", syslog->f_name);
			_clrbits (syslog->f_flags, SYSLOGD_FLAG_DISABLED);
			syslog->f_type = SYSLOGD_TYPE_NONE;
			syslog->f_desc = -1;
			return;
		}
		if ((hostent = gethostbyname (syslog->f_name)) == (struct hostent *) (0)) 
		{
			_setbits (syslog->f_flags, SYSLOGD_FLAG_DISABLED);
			syslogd_error (EADDRNOTAVAIL, "Can't locate host %s: %s", syslog->f_name, sys_h_errlist [h_errno]);
			_clrbits (syslog->f_flags, SYSLOGD_FLAG_DISABLED);
			syslog->f_time = now + SYSLOGD_RETRY_TIME;
			syslog->f_retry--;
			return;
		}
		_setbits (syslog->f_flags, SYSLOGD_FLAG_DISABLED);
		getsocketname (packet, sizeof (packet), syslog->f_sockaddr_in);
		syslogd_print (SYSLOG_INFO, "Opening connection to host %s at %s", syslog->f_name, packet);
		_clrbits (syslog->f_flags, SYSLOGD_FLAG_DISABLED);
		memcpy (&syslog->f_sockaddr_in->sin_addr, *hostent->h_addr_list, hostent->h_length);
		syslog->f_desc = syslogd_inet_socket (syslog->f_sockaddr_in);
		syslog->f_retry = 0;
	}
	syslog->f_time = now;
	if ((syslog->f_desc != -1) && (syslog->f_sockaddr_in != (struct sockaddr_in *) (0))) 
	{
		length += snprintf (packet + length, sizeof (packet) - length, "<%d>", syslog->f_priority);
		length += snprintf (packet + length, sizeof (packet) - length, "%s\n", syslog->f_notice);
		if (sendto (syslog->f_desc, packet, length, (flag_t) (0), (struct sockaddr *) (syslog->f_sockaddr_in), sizeof (struct sockaddr_in)) != length) 
		{
			syslogd_error (errno, "Can't forward message to %s using descriptor %d", syslog->f_name, syslog->f_desc);
			syslog->f_time += SYSLOGD_RETRY_TIME;
			syslog->f_retry = SYSLOGD_RETRY_COUNT;
		}
	}
	return;
}


#endif

