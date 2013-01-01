/*====================================================================*
 *
 *   int writestate (RECYCLE *recycle);
 *
 *   re-write the state file to record when logs were last recycle.;
 *
 *   the new state file format differs from older recycle versions;
 *   the format was changed to make it easier for people to read and
 *   to support automated editing of file dates and times, if needed;
 *   currently, the time is ignored it informs the administrator and
 *   might be used in the future;  
 *
 *   the new format is:
 *
 *   0000-00-00 00:00:00 <version-signature>
 *   2000-12-31 24:59:59 /path/file 
 *   2000-12-31 24:59:59 /path/file 
 *   2000-12-31 24:59:59 /path/file 
 *   2000-12-31 24:59:59 /path/file 
 *
 *   the header record has a null date and time so that it appears 
 *   first if the file is sorted; record order does not affect any
 *   program operations, except that the header must appear first;
 *
 *   in check mode, do not re-write the file unless force mode is 
 *   also set;
 * 
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef WRITESTATE_SOURCE
#define WRITESTATE_SOURCE

#include <stdio.h>
#include <errno.h>

#include "../recycle/recycle.h"
#include "../tools/sizes.h"
#include "../tools/error.h"
#include "../date/date.h"

int writestate (RECYCLE * recycle) 

{
	FILE *fp;
	if ((recycle->flags & RECYCLE_B_FORCE) == 0) 
	{
		if ((recycle->flags & RECYCLE_B_CHECK) != 0) 
		{
			error (0, 0, "leaving state file %s unchanged", recycle->statefilename);
			return (0);
		}
	}
	if ((fp = fopen (recycle->statefilename, "w")) == (FILE *) (0)) 
	{
		error (0, errno, "can't open state file %s", recycle->statefilename);
		return (1);
	}
	if ((recycle->flags & RECYCLE_B_VERBOSE) != 0) 
	{
		error (0, 0, "writing state file %s", recycle->statefilename);
	}
	fprintf (fp, SIGNATURE);
	for (recycle->state = 0; recycle->state < recycle->nstates; recycle->state++) 
	{
		STATE *state = &recycle->states [recycle->state];
		char recycletime [LOGTIME_LEN] = "";
		strftime (recycletime, sizeof (recycletime), LOGTIME, &state->tm);
		fprintf (fp, "%s %s\n", recycletime, state->filename);
	}
	fclose (fp);
	return (0);
}


#endif

