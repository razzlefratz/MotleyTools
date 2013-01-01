/*====================================================================*
 *
 *   bool due (RECYCLE *recycle);
 *
 *   determine if a file is due for recyle based on file size or 
 *   current date or elapsed time or operator demand; 
 *
 *   the default criteria is file size; otherwise monthly, weeky and 
 *   daily rotatiion occur when the month, week or day change unless
 *   more specific information is provided in the configuration file; 
 *
 *   last cycle date is read from the state file; next cycle date is
 *   is computed once the period is parsed; if the current date exceeds 
 *   next cycle date then files are recycled now; otherwise, they are
 *   recycled on schedule;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef DUE_SOURCE
#define DUE_SOURCE

#include <sys/stat.h>
#include <time.h>

#include "../recycle/recycle.h"
#include "../tools/error.h"
#include "../date/date.h"

bool due (RECYCLE * recycle) 

{
	LOGSET *logset = recycle->logset;
	STATE *state = &recycle->states [recycle->state];
	if (recycle->flags & (RECYCLE_B_VERBOSE)) 
	{
		error (0, 0, "checking %s", logset->files [logset->file]);
		if (logset->flags & (LOGSET_FLAG_MONTHLY | LOGSET_FLAG_WEEKLY | LOGSET_FLAG_DAILY)) 
		{
			error (0, 0, "last cycle %s", daytime (&state->tm));
			error (0, 0, "next cycle %s", daytime (&logset->tm));
		}
	}

/*
 * recycle everything now to create a snapshot or starting point; this may be
 * at some time for legal reasons or in case of security breaches; 
 */

	if (recycle->flags & (RECYCLE_B_FORCE)) 
	{
		if (recycle->flags & (RECYCLE_B_VERBOSE)) 
		{
			error (0, 0, "recycling %s now because the operator requested it !", state->filename);
		}
		return (true);
	}

/*
 * prevent multiple recyles in one day for whatever reason; use 'force' TO 
 * override this feature;
 */

	if (!datecomp (&recycle->tm, &state->tm)) 
	{
		if (recycle->flags & (RECYCLE_B_VERBOSE)) 
		{
			error (0, 0, "skipping %s because it was recycled once today.", state->filename);
		}
		return (false);
	}

/*
 * prevent unecessary recycling of empty files; this feature prevents useful
 *  information being displaced by no information; 
 */

	if (logset->flags & (LOGSET_FLAG_NOTIFEMPTY)) 
	{
		if (logset->statinfo.st_size == 0) 
		{
			if (recycle->flags & (RECYCLE_B_VERBOSE)) 
			{
				error (0, 0, "skipping %s because it is empty.", state->filename);
			}
			return (false);
		}
	}
	if (logset->flags & (LOGSET_FLAG_MONTHLY)) 
	{
		if (logset->threshold > 0) 
		{
			if (datecomp (&recycle->tm, &logset->tm) > 0) 
			{
				if (recycle->flags & (RECYCLE_B_VERBOSE)) 
				{
					error (0, 0, "recycling %s because a monthly cycle is overdue.", state->filename);
				}
				return (true);
			}
			else if (datecomp (&recycle->tm, &logset->tm) == 0) 
			{
				if (recycle->flags & (RECYCLE_B_VERBOSE)) 
				{
					error (0, 0, "recycling %s because a monthly change is due.", state->filename);
				}
				return (true);
			}
		}
		else if (logset->tm.tm_year != state->tm.tm_year) 
		{
			if (recycle->flags & (RECYCLE_B_VERBOSE)) 
			{
				error (0, 0, "recycling %s because a monthly change is due.", state->filename);
			}
			return (true);
		}
		else if (logset->tm.tm_mon != state->tm.tm_mon) 
		{
			if (recycle->flags & (RECYCLE_B_VERBOSE)) 
			{
				error (0, 0, "recycling %s because a monthly change is due.", state->filename);
			}
			return (true);
		}
	}
	else if (logset->flags & (LOGSET_FLAG_WEEKLY)) 
	{
		if (logset->threshold > 0) 
		{
			if (datecomp (&recycle->tm, &logset->tm) > 0) 
			{
				if (recycle->flags & (RECYCLE_B_VERBOSE)) 
				{
					error (0, 0, "recycling %s because a weekly cycle is overdue.", state->filename);
				}
				return (true);
			}
			else if (datecomp (&recycle->tm, &logset->tm) == 0) 
			{
				if (recycle->flags & (RECYCLE_B_VERBOSE)) 
				{
					error (0, 0, "recycling %s because a weekly change is due.", state->filename);
				}
				return (true);
			}
		}
		else if (logset->tm.tm_wday == 0) 
		{
			if (recycle->flags & (RECYCLE_B_VERBOSE)) 
			{
				error (0, 0, "recycling %s because a weekly change is due.", state->filename);
			}
			return (true);
		}
	}
	else if (logset->flags & (LOGSET_FLAG_DAILY)) 
	{
		if (logset->threshold > 0) 
		{
			if (datecomp (&recycle->tm, &logset->tm) > 0) 
			{
				if (recycle->flags & (RECYCLE_B_VERBOSE)) 
				{
					error (0, 0, "recycling %s because a daily cycle is overdue.", state->filename);
				}
				return (true);
			}
			else if (datecomp (&recycle->tm, &logset->tm) == 0) 
			{
				if (recycle->flags & (RECYCLE_B_VERBOSE)) 
				{
					error (0, 0, "recycling %s because a daily change is due.", state->filename);
				}
				return (true);
			}
		}
		else if (logset->tm.tm_year != state->tm.tm_year) 
		{
			if (recycle->flags & (RECYCLE_B_VERBOSE)) 
			{
				error (0, 0, "recycling %s because a daily change is due.", state->filename);
			}
			return (true);
		}
		else if (logset->tm.tm_yday != state->tm.tm_yday) 
		{
			if (recycle->flags & (RECYCLE_B_VERBOSE)) 
			{
				error (0, 0, "recycling %s because a daily change is due.", state->filename);
			}
			return (true);
		}
	}
	else if (logset->threshold > 0) 
	{
		if (logset->statinfo.st_size > logset->threshold) 
		{
			if (recycle->flags & (RECYCLE_B_VERBOSE)) 
			{
				error (0, 0, "recycling %s because it exceeds %lu bytes.", state->filename, logset->threshold);
			}
			return (true);
		}
	}
	return (false);
}


#endif

