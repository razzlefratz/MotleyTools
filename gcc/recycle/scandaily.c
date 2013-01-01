/*====================================================================*
 *
 *   int scandaily (SCAN * scan, LOGSET *logset);
 *
 *   parse the recycle daily option arguments; the daily option
 *   recycle. files on each anniversary of the reference date; the
 *   default period is one day;
 *
 *   this function is self-synchronizing because it does not need  
 *   the last rotation date to compute the next one; it does need
 *   a reference date and period; if the reference date is in the
 *   past, then "due + (now.g - due) % period" computes
 *   the start date for the current period and adding period will
 *   compute the start date for the next period; we convert dates
 *   to midnight using "date - date % 86400 - timezone" to remove
 *   hours, minutes and seconds where 86400 is the number seconds
 *   in a day; the period must be expressed in seconds, not days;
 *
 *   daily [period [start]];
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SCANDAILY_SOURCE
#define SCANDAILY_SOURCE

#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>

#include "../recycle/recycle.h"
#include "../tools/error.h"
#include "../date/date.h"

int scandaily (SCAN * scan, LOGSET * logset) 

{
	extern long timezone;
	while (isblank (*scan->cp)) 
	{
		++scan->cp;
	}
	if (isbreak (*scan->cp)) 
	{
		return (0);
	}
	scan->tp = scan->token;
	for (logset->threshold = 0; isdigit (*scan->cp); *scan->tp++ = *scan->cp++) 
	{
		logset->threshold *= 10;
		logset->threshold += *scan->cp - '0';
	}
	*scan->tp = (char) (0);
	if (!isblank (*scan->cp) & !isbreak (*scan->cp)) 
	{
		error (0, 0, "%s:%d number of days '%s' has illegal terminator.", scan->file, scan->line, scan->token);
		return (1);
	}
	while (isblank (*scan->cp)) 
	{
		++scan->cp;
	}
	scan->tp = scan->token;
	for (scan->sp = scan->cp; isdigit (*scan->cp) || (*scan->cp == '-'); ++scan->cp) 
	{
		if (!isblank (*scan->cp)) 
		{
			while (scan->sp <= scan->cp) 
			{
				*scan->tp++ = *scan->sp++;
			}
		}
	}
	*scan->tp = (char) (0);
	memset (&logset->tm, 0, sizeof (logset->tm));
	if (!isblank (*scan->cp) && !isbreak (*scan->cp)) 
	{
		error_on_line (0, EINVAL, scan->file, scan->line, "start date '%s' has unexpected terminator.", scan->token);
		return (1);
	}
	if (scan->tp > scan->token) 
	{
		if (sscanf (scan->token, "%d-%d-%d", &logset->tm.tm_year, &logset->tm.tm_mon, &logset->tm.tm_mday) != 3) 
		{
			error_on_line (0, EINVAL, scan->file, scan->line, "datespec '%s' has isempty syntax", scan->token);
			return (-1);
		}
		if ((logset->tm.tm_year < 1970 || logset->tm.tm_year > 2035)) 
		{
			error_on_line (0, ERANGE, scan->file, scan->line, "year in datespec '%s' is out of range", scan->token);
			return (-1);
		}
		if ((logset->tm.tm_mon < 1) || (logset->tm.tm_mon > 12)) 
		{
			error_on_line (0, ERANGE, scan->file, scan->line, "month in datespec '%s' is out of range", scan->token);
			return (-1);
		}
		if ((logset->tm.tm_mday < 1) || (logset->tm.tm_mday > DATES_IN_MONTH)) 
		{
			error_on_line (0, ERANGE, scan->file, scan->line, "day in datespec '%s' is out of range", scan->token);
			return (-1);
		}
		logset->tm.tm_year -= 1900;
		logset->tm.tm_mon--;
		if (mktime (&logset->tm) == (time_t) (-1)) 
		{
			error_on_line (0, EINVAL, scan->file, scan->line, "can't convert '%s' to localtime.", scan->token);
			return (-1);
		}
	}

/*
 * compute next rotation date from current date, start date and period; the start date does not
 * matter when the period is zero; 
 */

	if (logset->threshold > 0) 
	{
		time_t now = time (&now);
		time_t due = mktime (&logset->tm);
		now -= now % SECONDS_IN_DAY;
		now += timezone;
		due -= due % SECONDS_IN_DAY;
		due += timezone;
		due -= now;
		due %= logset->threshold * SECONDS_IN_DAY;
		due += now;
		if (due < now) 
		{
			due += logset->threshold * SECONDS_IN_DAY;
		}
		logset->tm = *localtime (&due);
	}
	return (0);
}


#endif

