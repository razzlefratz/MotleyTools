/*====================================================================*
 *
 *   int scanweekly (SCAN * scan, LOGSET * logset);
 *   
 *   parse arguments for the recycle weekly option;
 *
 *   the weekly option recycles files on a specific day of the week;
 *   the weekday is specified using the full weekday name or three
 *   character abberviation; the default weekday is defined by the
 *   initial value logset->threshold; 
 *
 *   this option is self-synchronizing because it does not need the
 *   last recycled date to compute the next one; for any given date,
 *   subtract the weekday number from the date and add the desired 
 *   weekday number; if the desired weekday number is less than the 
 *   actual, add seven days; the result is the next recycle date; 
 *
 *   the weekly option has the following form:
 *
 *   weekly [sun|mon|tue|wed|thu|fri|sat|sunday|monday|tuesday|wednesday|thursday|friday|saturday];
 *
 *   weekday names are stored in a vector in order of their weekday
 *   number; short names names first then long names; we search the   
 *   the vector for a match, short or long, and use modulo seven of
 *   the index; function svfirst() does the linear search; 
 *
 *   we adjust the date by maipulating the tm_mday value of the tm
 *   structure and calling mktime() to recompute everything; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SCANWEEKLY_SOURCE
#define SCANWEEKLY_SOURCE

#include <ctype.h>
#include <string.h>
#include <time.h>
#include <errno.h>

#include "../recycle/recycle.h"
#include "../tools/error.h"
#include "../date/date.h"
#include "../date/weekdays.h"
#include "../strlib/strlib.h"

int scanweekly (SCAN * scan, LOGSET * logset) 

{
	extern char const *weekdays [];
	while (isblank (*scan->cp)) 
	{
		++scan->cp;
	}
	for (scan->tp = scan->token; isalpha (*scan->cp); *scan->tp++ = *scan->cp++);
	*scan->tp = (char) (0);
	if (!isblank (*scan->cp) && !isbreak (*scan->cp)) 
	{
		error_on_line (0, EINVAL, scan->file, scan->line, "weekday name '%s' has unexpected terminator", scan->token);
		return (1);
	}
	if (scan->tp > scan->token) 
	{
		logset->threshold = svfirst (scan->token, weekdays, WEEKDAYS_O_NULL, strcmp);
		if (logset->threshold == WEEKDAYS_O_NULL) 
		{
			error_on_line (0, EINVAL, scan->file, scan->line, "weekday name '%s' is isempty", scan->token);
			return (1);
		}
		logset->threshold %= DAYS_IN_WEEK;
	}
	if (logset->tm.tm_wday > logset->threshold) 
	{
		logset->tm.tm_mday += DAYS_IN_WEEK;
	}
	logset->tm.tm_mday -= logset->tm.tm_wday;
	logset->tm.tm_mday += logset->threshold;
	mktime (&logset->tm);
	return (0);
}


#endif

