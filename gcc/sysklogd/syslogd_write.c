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
#include <stdlib.h>
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

void syslogd_write (struct syslogd *syslog, flag_t flags) 

{

#if (SYSLOGD_ORIGIN | SYSLOGD_NATURE)

	extern flag_t state;

#endif

	struct iovec message [IOVECSIZE];
	struct iovec *element = message;

#ifdef SYSLOGD_INETAF

	char packet [TEXTLINE_MAX];
	size_t length = 0;

#endif

	char const **usernames;
	char const **username;
	time_t now = time (&now);

#if SYSLOGD_TRACE

	trace_enter ("syslogd_write");

#endif

	if (now < syslog->f_time) 
	{

#if SYSLOGD_TRACE

		trace_leave ("syslogd_write");

#endif

		return;
	}
	if (syslog->f_desc == -1) 
	{

#if SYSLOGD_TRACE

		trace_leave ("syslogd_write");

#endif

		return;
	}
	memset (message, 0, sizeof (message));
	element->iov_base = syslog->f_posted;
	element->iov_len = strlen (element->iov_base);
	element++;
	element->iov_base = " ";
	element->iov_len = 1;
	element++;

#if SYSLOGD_ORIGIN

	if (_anyset (state, SYSLOGD_STATE_ORIGIN)) 
	{
		element->iov_base = syslog->f_origin;
		element->iov_len = strlen (element->iov_base);
		element++;
		element->iov_base = " ";
		element->iov_len = 1;
		element++;
	}

#endif
#if SYSLOGD_NATURE

	if (_anyset (state, SYSLOGD_STATE_NATURE)) 
	{
		element->iov_base = syslog->f_nature;
		element->iov_len = strlen (element->iov_base);
		element++;
		element->iov_base = " ";
		element->iov_len = 1;
		element++;
	}

#endif

	element->iov_base = syslog->f_notice;
	element->iov_len = strlen (element->iov_base);
	element++;
	switch (syslog->f_type) 
	{
	case SYSLOGD_TYPE_USER:
	case SYSLOGD_TYPE_SITE:
	case SYSLOGD_TYPE_CONSOLE:
	case SYSLOGD_TYPE_TERM:
		element->iov_base = "\r";
		element->iov_len = 1;
		element++;
	case SYSLOGD_TYPE_FILE:
	case SYSLOGD_TYPE_PIPE:
		element->iov_base = "\n";
		element->iov_len = 1;
		element++;
	default:
		break;
	}
	switch (syslog->f_type) 
	{
	case SYSLOGD_TYPE_NONE:
		syslog->f_time = now;
		break;

#ifdef SYSLOGD_INETAF

	case SYSLOGD_TYPE_HOST:
		syslog->f_time = now;
		length += snprintf (packet + length, sizeof (packet) - length, "<%d>", syslog->f_priority);
		length += snprintf (packet + length, sizeof (packet) - length, "%s\n", syslog->f_notice);
		if (sendto (syslog->f_desc, packet, length, (flag_t) (0), (struct sockaddr *) (syslog->f_sockaddr_in), sizeof (struct sockaddr_in)) != length) 
		{
			syslogd_error (errno, "Can't forward message to %s using descriptor %d", syslog->f_name, syslog->f_desc);
			switch (errno) 
			{
			default:
				syslog->f_time += SYSLOGD_RETRY_TIME;
				syslog->f_retry = SYSLOGD_RETRY_COUNT;
				break;
			}
		}
		break;

#endif

	case SYSLOGD_TYPE_FILE:
	case SYSLOGD_TYPE_PIPE:
		syslog->f_time = now;
		if (writev (syslog->f_desc, message, element - message) == -1) 
		{
			syslogd_error (errno, "Can't write to file %s using discriptor %d", syslog->f_name, syslog->f_desc);
			switch (errno) 
			{
			case EAGAIN:
				syslog->f_retry = SYSLOGD_RETRY_COUNT;
				syslog->f_time += SYSLOGD_RETRY_TIME;
				break;
			default:
				syslog->f_type = SYSLOGD_TYPE_NONE;
				close (syslog->f_desc);
				syslog->f_desc = -1;
				break;
			}
			break;
		}
		if (_anyset (syslog->f_flags, SYSLOGD_FLAG_SYNCHRONIZE)) 
		{
			fsync (syslog->f_desc);
			sleep (SYSLOGD_FSYNC_TIME);
		}
		break;
	case SYSLOGD_TYPE_CONSOLE:
	case SYSLOGD_TYPE_TERM:
		syslog->f_time = now;
		if (writev (syslog->f_desc, message, element - message) == -1) 
		{
			syslogd_error (errno, "Can't write to %s", syslog->f_name);
			switch (errno) 
			{
			case EIO:
			case EBADF:
				syslog->f_type = SYSLOGD_TYPE_NONE;
				close (syslog->f_desc);
				syslog->f_desc = -1;
				break;
			case EAGAIN:
			default:
				syslog->f_retry = SYSLOGD_RETRY_COUNT;
				syslog->f_time += SYSLOGD_RETRY_TIME;
				break;
			}
		}
		break;
	case SYSLOGD_TYPE_SITE:
	case SYSLOGD_TYPE_USER:
		syslog->f_time = now;
		usernames = stov (syslog->f_name, ',');
		syslogd_broadcast (usernames, message, element - message, flags);
		for (username = usernames; *username != (char const *) (0); username++) 
		{
			free ((char *) (*username));
		}
		free (usernames);
		break;
	}

#if SYSLOGD_TRACE

	trace_leave ("syslogd_write");

#endif

	return;
}


#endif

