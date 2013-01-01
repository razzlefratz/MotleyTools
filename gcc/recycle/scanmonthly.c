/*====================================================================*
 *
 *   int scanmonthly (SCAN * scan, LOGSET * logset);
 *   
 *   parse arguments for the recycle monthly option;
 *
 *   we recycle.on the last day of the month; the date is computed 
 *   by incremeting the month and setting the day of month to 0 then 
 *   calling mktime() to recompute the absolute date;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SCANMONTHLY_SOURCE
#define SCANMONTHLY_SOURCE

#include <ctype.h>
#include <errno.h>
#include <string.h>
#include <time.h>

#include "../recycle/recycle.h"
#include "../tools/error.h"
#include "../date/date.h"

int scanmonthly (SCAN * scan, LOGSET * logset) 

{
	while (isblank (*scan->cp)) 
	{
		++scan->cp;
	}
	scan->tp = scan->token;
	for (logset->threshold = 0; isdigit (*scan->cp); *scan->tp++ = *scan->cp++) 
	{
		logset->threshold *= 10;
		logset->threshold += *scan->cp - '0';
	}
	*scan->tp = (char) (0);
	if (!isblank (*scan->cp) && !isbreak (*scan->cp)) 
	{
		error_on_line (0, EINVAL, scan->file, scan->line, "number of months '%s' has unexpected terminator", scan->token);
		return (1);
	}
	if ((logset->threshold < 0) || (logset->threshold > MONTHS_IN_YEAR)) 
	{
		error_on_line (0, ERANGE, scan->file, scan->line, "number of months '%s' is out of range", scan->token);
		return (-1);
	}
	if (logset->threshold) 
	{
		logset->tm.tm_mon += logset->threshold;
		logset->tm.tm_mday = 0;
	}
	else 
	{
		logset->tm.tm_mon += 1;
		logset->tm.tm_mday = 0;
	}
	mktime (&logset->tm);
	return (0);
}


#endif

