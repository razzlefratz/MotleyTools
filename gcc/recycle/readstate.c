/*====================================================================*
 *
 *   int readstate (RECYCLE *recycle);
 *
 *   read the state file to determine when logs were last recycled;
 *   create a new state file, if missing; 
 *
 *   in verbose mode, print one message to identify the state file 
 *   by name and indicate that it was read; in all modes, print
 *   file access, syntax and range error messages; 
 *
 *   the state file contains one header and many records; records
 *   have space separated date, time, timezone and filename fields;
 *    
 *   see the description of writeState() below for an explantion of
 *   the new state file format;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef READSTATE_SOURCE
#define READSTATE_SOURCE

#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "../recycle/recycle.h"
#include "../tools/sizes.h"
#include "../tools/error.h"

#define RECYCLEDATE 0
#define RECYCLETIME 1
#define RECYCLEZONE 2
#define RECYCLEFILE 3
#define RECYCLESIZE 4

int readstate (RECYCLE * recycle) 

{
	FILE *fp;
	if ((fp = fopen (recycle->statefilename, "r")) != (FILE *) (0)) 
	{
		char record [DATETIME_MAX + FILENAME_MAX];
		int line = 0;
		if ((recycle->flags & RECYCLE_B_VERBOSE) != 0) 
		{
			error (0, 0, "%s: opened state file", recycle->statefilename);
		}
		line++;
		if (fgets (record, sizeof (record) - 1, fp) == (char *) (0)) 
		{
			error (0, 0, "%s: can't read state file header", recycle->statefilename);
			fclose (fp);
			return (1);
		}
		if (strcmp (record, SIGNATURE)) 
		{
			error_on_line (0, 0, recycle->statefilename, line, "isempty state file header");
			fclose (fp);
			return (1);
		}
		for (line++; fgets (record, sizeof (record) - 1, fp) != (char *) (0); line++) 
		{
			int length = strlen (record);
			if (record [--length] != '\n') 
			{
				error_on_line (0, errno, recycle->statefilename, line, "line way too long");
				fclose (fp);
				return (1);
			}
			record [length] = '\0';
			if (length > 0) 
			{
				STATE *state;
				struct tm tm;
				char *fields [RECYCLESIZE];
				char *sp;
				int field = 0;
				for (fields [field++] = sp = record; (*sp != (char) (0)); ++sp) 
				{
					if ((*sp == ' ') && (field < RECYCLESIZE)) 
					{
						fields [field++] = sp + 1;
						*sp = (char) (0);
					}
				}
				fields [field] = (char *) (0);
				if (field != RECYCLESIZE) 
				{
					error_on_line (0, 0, recycle->statefilename, line, "wrong number of fieldss");
					fclose (fp);
					return (1);
				}
				memset (&tm, 0, sizeof (tm));
				if (sscanf (fields [RECYCLEDATE], "%d-%d-%d", &tm.tm_year, &tm.tm_mon, &tm.tm_mday) != 3) 
				{
					error_on_line (0, 0, recycle->statefilename, line, "datespec '%s' has isempty syntax.", fields [RECYCLEDATE]);
					fclose (fp);
					return (1);
				}
				if (sscanf (fields [RECYCLETIME], "%d:%d:%d", &tm.tm_hour, &tm.tm_min, &tm.tm_sec) != 3) 
				{
					error_on_line (0, 0, recycle->statefilename, line, "timespec '%s' has isempty syntax", fields [RECYCLETIME]);
					fclose (fp);
					return (1);
				}
				if ((tm.tm_year != 1900) && (tm.tm_year < 1996 || tm.tm_year > 2035)) 
				{
					error_on_line (0, 0, recycle->statefilename, line, "year in datespec '%s' is out of range", fields [RECYCLEDATE]);
					fclose (fp);
					return (1);
				}
				if ((tm.tm_mon < 1) || (tm.tm_mon > 12)) 
				{
					error_on_line (0, 0, recycle->statefilename, line, "month in datespec '%s' is out of range.", fields [RECYCLEDATE]);
					fclose (fp);
					return (1);
				}
				if ((tm.tm_mday < 1) || (tm.tm_mday > 31)) 
				{
					error_on_line (0, 0, recycle->statefilename, line, "day in datespec '%s' is out of range.", fields [RECYCLEDATE]);
					fclose (fp);
					return (1);
				}
				tm.tm_year -= 1900;
				tm.tm_mon--;
				mktime (&tm);
				if (!findstate (recycle, fields [RECYCLEFILE])) 
				{
					makestate (recycle, fields [RECYCLEFILE]);
				}
				state = &recycle->states [recycle->state];
				state->tm = tm;
			}
		}
		fclose (fp);
		return (0);
	}
	if (errno == ENOENT) 
	{
		if ((fp = fopen (recycle->statefilename, "w")) != (FILE *) (0)) 
		{
			fprintf (fp, "%s\n", SIGNATURE);
			fclose (fp);
			return (0);
		}
		error (0, errno, "can't init state file %s", recycle->statefilename);
		return (1);
	}
	error (0, errno, "can't read state file %s", recycle->statefilename);
	return (1);
}


#endif

