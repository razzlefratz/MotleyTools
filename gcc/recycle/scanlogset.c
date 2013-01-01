/*====================================================================*
 *
 *   int scanlogset (SCAN *scan, RECYCLE *recycle);
 *
 *   a logset structure contains rotation rules and pointers to the
 *   filenames affected by those rules; filenames are stored in the
 *   the state vector and referenced by logsets; each file can only 
 *   be referenced by one logset; 
 *
 *   this function converts a logfile specification containing one
 *   or more wildcard filespecs, to a string vector and then globs 
 *   each filespec to produce the complete of filenames; filenames
 *   are added to the state vector; duplicates are rejected;
 *
 *   on entry, the logset contains default critera copied from the
 *   first logset; on return, the logset criteria will be modified 
 *   by options and arguments read from the configuration file; 
 *
 *   strargv() parses scan->token() using shell-like rules; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SCANLOGSET_SOURCE
#define SCANLOGSET_SOURCE

#include <glob.h>
#include <stdlib.h>
#include <string.h>
#include <alloca.h>
#include <popt.h>
#include <errno.h>

#include "../recycle/recycle.h"
#include "../strlib/strlib.h"
#include "../tools/error.h"
#include "../tools/sizes.h"

#if !defined(GLOB_ABORTED) && defined(GLOB_ABEND)
#define GLOB_ABORTED GLOB_ABEND
#endif

static int globerr (char const *pathname, int errnum) 

{
	error (0, errnum, "can't glob %s", pathname);
	return (1);
}

int scanlogset (SCAN *scan, RECYCLE *recycle) 

{
	LOGSET *logset = recycle->logset;
	char const *files [VECTORSIZE];
	size_t nfiles;
	size_t file;
	glob_t globfiles;
	size_t globfile;
	nfiles = strargv (VECTORSIZE, files, logset->filespec, (unsigned)(0));
	for (file = 0; file < nfiles; file++) 
	{
		if (glob (files [file], GLOB_NOCHECK, globerr, &globfiles) == GLOB_ABORTED) 
		{
			error_on_line (0, errno, scan->file, scan->line, "can't glob %s", files [file]);
			return (1);
		}
		logset->files = realloc (logset->files, sizeof (*logset->files) * (logset->nfiles + globfiles.gl_pathc));
		for (globfile = 0; globfile < globfiles.gl_pathc; globfile++) 
		{
			if (stat (globfiles.gl_pathv [globfile], &logset->statinfo)) 
			{
				error_on_line (0, errno, scan->file, scan->line, "ignoring %s", globfiles.gl_pathv [globfile]);
				continue;
			}
			if (!S_ISREG (logset->statinfo.st_mode)) 
			{
				error_on_line (0, EPERM, scan->file, scan->line, "ignoring %s: Not a regular file", globfiles.gl_pathv [globfile]);
				continue;
			}
			if (findstate (recycle, globfiles.gl_pathv [globfile])) 
			{
				error_on_line (0, 0, scan->file, scan->line, "ignoring %s: Criteria previously defined", globfiles.gl_pathv [globfile]);
				continue;
			}
			makestate (recycle, globfiles.gl_pathv [globfile]);
			logset->files [logset->nfiles++] = recycle->states [recycle->state].filename;
		}
	}
	return (0);
}


#endif

