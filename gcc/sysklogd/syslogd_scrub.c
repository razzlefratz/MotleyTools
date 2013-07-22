/*====================================================================*
 *
 *   void syslogd_scrub (char const *origin, char const *string);
 *
 *   decode, cleanse and print a raw message string; 
 *
 *   in most cases, the input message is limited to TEXTLINE_MAX
 *   and could contain non-printable characters; replacing them with 
 *   control sequences can produce an output string longer than that;
 *   the worst case is a string that is 4 times longer; this function 
 *   allows for double the size on the assumption that so much trash
 *   in a buffer is just that, ... trash; the excess is discarded; 
 *
 *   in this implementation syslogd_merge is the only place 
 *   where this function is called; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SYSLOGD_SCRUB_SOURCE
#define SYSLOGD_SCRUB_SOURCE

#include <ctype.h>
#include <string.h>
#include <unistd.h>

#include "../sysklogd/syslogd.h"
#include "../linux/syslog.h"
#include "../tools/flags.h"

void syslogd_scrub (char const * origin, char const * string) 

{ 
	char buffer [TEXTLINE_MAX + TEXTLINE_MAX]; 
	char * sp = buffer; 
	int priority = 0; 

#if SYSLOGD_TRACE

	trace_enter ("syslogd_scrub"); 

#endif

	if (* string == '<') 
	{ 
		while (isdigit (* ++ string)) 
		{ 
			priority *= 10; 
			priority += (* string - '0'); 
		} 
		if (* string == '>') 
		{ 
			string++; 
		} 
	} 

#if SYSLOGD_NOTIME

/*
 * some applications insert ctime() in strings; detect this and remove it; this effort is essentially a waste of 
 * time because there are so many different formats; cmaier@cmassoc.net
 */

/* mmm dd hh:mm:ss yyy */

	if ((string [3] == ' ') && (string [6] == ' ') && (string [9] == ':') && (string [12] == ':') && (string [15] == ' ')) 
	{ 
		string += 16; 
	} 

/* www mmm dd hh:mm:ss yyy */

	else if ((string [3] == ' ') && (string [7] == ' ') && (string [10] == ' ') && (string [13] == ':') && (string [16] == ':') && (string [19] == ' ')) 
	{ 
		string += 24; 
	} 
	else if ((string [4] == '-') && (string [7] == '-') && (string [10] == ' ') && (string [13] == ':') && (string [16] == ':') && (string [19] == ' ')) 
	{ 
		string += 20; 
	} 

#endif

	memset (buffer, 0, sizeof (buffer)); 
	while (((sp - buffer) < (sizeof (buffer) - 4))) 
	{ 
		if (* string == (char) (0)) 
		{ 
			break; 
		} 
		else if (* string == '\n') 
		{ 
			* sp++ = ' '; 
		} 
		else if (* string < 0x20) 
		{ 
			* sp++ = '^'; 
			* sp++ = * string | 0100; 
		} 
		else if ((* string == 0x3F) || ((* string & 0x3F) < 0x20)) 
		{ 
			* sp++ = '\\'; 
			* sp++ = '0' + ((* string >> 6) & 07); 
			* sp++ = '0' + ((* string >> 3) & 07); 
			* sp++ = '0' + ((* string >> 0) & 07); 
		} 
		else 
		{ 
			* sp++ = * string; 
		} 
		string++; 
	} 
	* sp = (char) (0); 
	syslogd_queue (priority, origin, buffer); 

#if SYSLOGD_TRACE

	trace_leave ("syslogd_scrub"); 

#endif

	return; 
} 

#endif



