/*====================================================================*
 *
 *   void syslogd_merge (struct socket *socket, char const *origin, char const record[], size_t length);
 *
 *   syslogd.h
 *
 *   manage fragmented messages received by sockets; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SYSLOGD_MERGE_SOURCE
#define SYSLOGD_MERGE_SOURCE

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "../sysklogd/syslogd.h"
#include "../tools/tools.h"
#include "../tools/flags.h"

void syslogd_merge (struct socket *socket, char const *origin, char const record [], size_t length) 

{
	char buffer [TEXTLINE_MAX];
	char *sp = buffer;
	if (socket->buffer) 
	{
		char const * record = socket->buffer;
		while (*record) 
		{
			if ((sp - buffer) > (sizeof (buffer) - 2)) 
			{
				*sp = (char) (0);
				syslogd_scrub (origin, buffer);
				sp = buffer;
				*sp++ = '+';
			}
			*sp++ = *record++;
		}
		free (socket->buffer);
		socket->buffer = (char *) (0);
	}
	while (length-- > 0) 
	{
		if (*record == (char) (0)) 
		{
			*sp = (char) (0);
			syslogd_scrub (origin, buffer);
			sp = buffer;
			record++;
			continue;
		}
		if ((sp - buffer) > (sizeof (buffer) - 2)) 
		{
			*sp = (char) (0);
			syslogd_scrub (origin, buffer);
			sp = buffer;
			*sp++ = '+';
		}
		*sp++ = *record++;
	}
	*sp = (char) (0);
	if (sp > buffer) 
	{
		socket->buffer = strdup (buffer);
		if (socket->buffer == (char *) (0)) 
		{
			syslogd_error (errno, "can't store message fragment");
		}
	}
	return;
}


#endif

