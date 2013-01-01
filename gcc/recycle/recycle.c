/*====================================================================*
 *
 *   recycle.c - system log rotation utility; 
 *
 *   This software is an adaptation the recycle program
 *
 *   Copyright (C) 1995-2001 Red Hat, Inc.;
 *   Copyright (C) 2004 Charles Maier Associates Ltd.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#define _GETOPT_H

/*====================================================================*
 * system header files;
 *--------------------------------------------------------------------*/

#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>

/*====================================================================*
 * custom header files;
 *--------------------------------------------------------------------*/

#include "../recycle/recycle.h"
#include "../tools/cmassoc.h"
#include "../tools/symbol.h"
#include "../linux/linux.h"

/*====================================================================*
 * custom source files; 
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../recycle/scanargs.c"
#include "../recycle/scanlogset.c"
#include "../recycle/scansize.c"
#include "../recycle/scandaily.c"
#include "../recycle/scanmonthly.c"
#include "../recycle/scanweekly.c"
#include "../recycle/scancreate.c"
#include "../recycle/scanscript.c"
#include "../recycle/keywords.c"
#include "../recycle/findstate.c"
#include "../recycle/makestate.c"
#include "../recycle/readconfig.c"
#include "../recycle/readstate.c"
#include "../recycle/writestate.c"
#include "../recycle/copyfile.c"
#include "../recycle/due.c"
#endif

/*====================================================================*
 * shared source files; 
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/console.c"
#include "../tools/emalloc.c"
#include "../tools/error_on_line.c"
#include "../files/match.c"
#include "../linux/runscript.c"
#include "../date/daytime.c"
#include "../date/datecomp.c"
#include "../date/weekdays.c"
#include "../files/filepart.c"
#include "../files/pathpart.c"
#include "../strlib/svorder.c"
#include "../strlib/svfirst.c"
#include "../strlib/svindex.c"
#include "../strlib/strargv.c"
#endif

/*====================================================================*
 *
 *   int compresslog (RECYCLE *recycle, char const *filename);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

static int compresslog (RECYCLE * recycle, char const *filename) 

{
	LOGSET *logset = recycle->logset;
	char command [TEXTLINE_MAX];
	if (empty (filename)) 
	{
		recycle->error = true;
		return (1);
	}
	snprintf (command, sizeof (command), "%s %s '%s'", logset->comp_program, logset->comp_options, filename);
	if (system (command)) 
	{
		error (0, errno, "can't compress %s", filename);
		recycle->error = true;
		return (1);
	}
	return (0);
}


/*====================================================================*
 *
 *   int maillog (RECYCLE * recycle, char const *filename, char const *subject);
 *
 *   suppress mail without error when the recipient address is empty;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

static int maillog (RECYCLE * recycle, char const *filename, char const *subject) 

{
	LOGSET *logset = recycle->logset;
	char command [TEXTLINE_MAX];
	if (empty (logset->recipient)) 
	{
		return (0);
	}
	if (empty (filename)) 
	{
		recycle->error = true;
		return (1);
	}
	if (empty (subject)) 
	{
		subject = filename;
	}
	if (access (filename, F_OK)) 
	{
		recycle->error = true;
		return (1);
	}
	if (_anyset (logset->flags, LOGSET_FLAG_COMPRESS) && _allclr (logset->flags, LOGSET_FLAG_DELAYCOMPRESS)) 
	{
		snprintf (command, sizeof (command), "%s %s < %s | %s %s '%s' %s", logset->uncomp_program, logset->uncomp_options, filename, recycle->mail_program, recycle->mail_options, subject, logset->recipient);
	}
	else 
	{
		snprintf (command, sizeof (command), "%s %s '%s' %s < %s", recycle->mail_program, recycle->mail_options, subject, logset->recipient, filename);
	}
	if (system (command)) 
	{
		error (0, errno, "can't mail %s to %s", filename, logset->recipient);
		recycle->error = true;
		return (1);
	}
	return (0);
}


/*====================================================================*
 *
 *   int cyclelogs (RECYCLE *recycle);
 *
 *   recycle->logset points to the current logset in a logsets list  
 *   stored in the recycle structure; a logset is a set of rotation
 *   rules and a list of files that share those rules;
 *
 *   for each file in the logset, determine if rotation is due; if 
 *   rotation is due and this is not a trial run, rotate the file; 
 *
 *   FILENAME_FORMAT defines filename format; it is defined as
 *   a constant because 1) it is used in many places and 2) I set
 *   it the way I want but other people may want something else;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

int cyclelogs (RECYCLE * recycle) 

{
	LOGSET *logset = recycle->logset;
	for (logset->file = 0; logset->file < logset->nfiles; logset->file++) 
	{
		if (!findstate (recycle, logset->files [logset->file])) 
		{
			error (0, 0, "configured log '%s' is missing from the state vector.", logset->files [logset->file]);
			makestate (recycle, logset->files [logset->file]);
		}
		if (stat (logset->files [logset->file], &logset->statinfo)) 
		{
			if (_anyset (logset->flags, LOGSET_FLAG_REQUIRED) && (errno == ENOENT)) 
			{
				error (0, errno, "can't stat %s", logset->files [logset->file]);
				recycle->error = true;
				continue;
			}
		}
		if (due (recycle)) 
		{
			STATE *state = &recycle->states [recycle->state];
			struct swap 
			{
				struct swap *prev;
				char name [FILENAME_MAX];
				struct stat stat;
			}
			old,
			new,
			*log;
			char *pathname = (char *) (pathpart (logset->files [logset->file]));
			char *filename = (char *) (filepart (logset->files [logset->file]));
			char *extender = "";
			size_t start = 1;
			size_t count = start + logset->keep;
			size_t index = count;
			if (_anyset (recycle->flags, RECYCLE_B_CHECK)) 
			{
				continue;
			}
			old.prev = &new;
			new.prev = &old;
			state->tm = recycle->tm;
			if (valid (logset->folder)) 
			{
				pathname = logset->folder;
			}
			if (valid (logset->ext)) 
			{
				int offset = strlen (filename) - strlen (logset->ext);
				if (strncmp (&filename [offset], logset->ext, strlen (logset->ext)) == 0) 
				{
					filename [offset] = (char) (0);
				}
			}
			if (_anyset (logset->flags, LOGSET_FLAG_COMPRESS)) 
			{
				extender = logset->comp_ext;
			}
			snprintf (new.name, sizeof (new.name), FILENAME_FORMAT, pathname, filename, start, logset->ext, "");
			snprintf (old.name, sizeof (old.name), FILENAME_FORMAT, pathname, filename, count, logset->ext, extender);
			if (_allset (logset->flags, (LOGSET_FLAG_COMPRESS | LOGSET_FLAG_DELAYCOMPRESS))) 
			{
				if (!stat (new.name, &new.stat)) 
				{
					compresslog (recycle, new.name);
				}
			}
			for (log = &new; index-- > start; log = log->prev) 
			{
				snprintf (log->name, FILENAME_MAX, FILENAME_FORMAT, pathname, filename, index, logset->ext, extender);

#ifdef RECYCLE_TRACE

				fprintf (stderr, "renaming %s to %s\n", log->name, log->prev->name);

#endif

				if ((rename (log->name, log->prev->name) != 0) && (errno != ENOENT)) 
				{
					error (0, errno, "can't rename %s to %s", log->name, log->prev->name);
					break;
				}
			}
			snprintf (new.name, sizeof (new.name), FILENAME_FORMAT, pathname, filename, start, logset->ext, "");
			snprintf (old.name, sizeof (old.name), FILENAME_FORMAT, pathname, filename, count, logset->ext, extender);
			if (_anyset (logset->flags, LOGSET_FLAG_SHAREDSCRIPTS)) 
			{
				if (valid (logset->prescript)) 
				{
					if (runscript (logset->prescript, logset->files [logset->file], recycle->flags)) 
					{
						error (0, errno, "%s: Precycle script failed", logset->files [logset->file]);
						recycle->error = true;
						continue;
					}
				}
			}
			if (_anyset (logset->flags, LOGSET_FLAG_COPYTRUNCATE)) 
			{
				copyfile (logset->files [logset->file], new.name, &logset->statinfo, recycle->flags);
			}
			if (_allclr (logset->flags, LOGSET_FLAG_COPYTRUNCATE)) 
			{

#ifdef RECYCLE_TRACE

				fprintf (stderr, "renaming %s to %s\n", logset->files [logset->file], new.name);

#endif

				if (rename (logset->files [logset->file], new.name)) 
				{
					error (0, errno, "can't rename %s to %s", logset->files [logset->file], new.name);
					recycle->error = true;
					continue;
				}
				if (_anyset (logset->flags, LOGSET_FLAG_CREATE)) 
				{
					file_t fd;
					if (logset->uid == (uid_t) (-1)) 
					{
						new.stat.st_uid = logset->statinfo.st_uid;
					}
					else 
					{
						new.stat.st_uid = logset->uid;
					}
					if (logset->gid == (gid_t) (-1)) 
					{
						new.stat.st_gid = logset->statinfo.st_gid;
					}
					else 
					{
						new.stat.st_gid = logset->gid;
					}
					if (logset->mode == (mode_t) (-1)) 
					{
						new.stat.st_mode = logset->statinfo.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO);
					}
					else 
					{
						new.stat.st_mode = logset->mode;
					}
					if ((fd = open (logset->files [logset->file], O_CREAT | O_RDWR, new.stat.st_mode)) == -1) 
					{
						error (0, errno, "can't create %s", logset->files [logset->file]);
						recycle->error = true;
						continue;
					}
					if (fchmod (fd, new.stat.st_mode)) 
					{
						error (0, errno, "can't set %s permissions.", logset->files [logset->file]);
						recycle->error = true;
						close (fd);
						continue;
					}
					if (fchown (fd, new.stat.st_uid, new.stat.st_gid)) 
					{
						error (0, errno, "can't set %s ownership.", logset->files [logset->file]);
						recycle->error = true;
						close (fd);
						continue;
					}
					close (fd);
				}
			}
			if (_allclr (logset->flags, LOGSET_FLAG_SHAREDSCRIPTS)) 
			{
				if (valid (logset->postscript)) 
				{
					if (runscript (logset->postscript, logset->files [logset->file], recycle->flags)) 
					{
						error (0, errno, "%s: Postcycle script failed", logset->files [logset->file]);
						recycle->error = true;
						continue;
					}
				}
			}
			if (valid (logset->recipient)) 
			{
				if (_anyset (logset->flags, LOGSET_FLAG_MAILFIRST)) 
				{
					maillog (recycle, new.name, filename);
				}
				else 
				{
					maillog (recycle, old.name, filename);
				}
			}
			if (logset->keep == 0) 
			{

#ifdef RECYCLE_TRACE

				fprintf (stderr, "unlinking new %s\n", new.name);

#endif

				if (unlink (new.name)) 
				{
					error (0, errno, "can't remove %s", new.name);
					recycle->error = true;
				}
				continue;
			}
			if (_anyset (logset->flags, LOGSET_FLAG_COMPRESS)) 
			{
				if (_allclr (logset->flags, LOGSET_FLAG_DELAYCOMPRESS)) 
				{
					compresslog (recycle, new.name);
				}
			}

#ifdef RECYCLE_TRACE

			fprintf (stderr, "unlinking old %s\n", old.name);

#endif

			if (unlink (old.name) && (errno != ENOENT)) 
			{
				error (0, errno, "can't remove %s", old.name);
				recycle->error = true;
			}
		}
	}
	return (0);
}


/*====================================================================*
 *
 *   int main (signed argc, char const *argv[]);
 *
 *   file rotation occurs in four phases; specification, research,
 *   rotation and recording; the main program loop reflects this
 *   sequence; 
 *
 *   during specification, one or more config files are read to
 *   identify file that should be recycle., how often and how;
 *
 *   during research, the rotation state file is read to identify  
 *   files that have been recycle. and determine when;
 *
 *   during rotation, each file that should be recycle. is checked 
 *   to determine if it should be recycle. now, or later, and then 
 *   recycle. if necessary; 
 *
 *   during recording, the rotation state file is re-written with 
 *   the rotation date, time and name of files that should be, or 
 *   have been, recycle.;
 *
 *   the program supports a verbose mode that prints messages as 
 *   stages progress; it supports a check mode that does everything 
 *   except recycle.the files; verbose checks detect and identify 
 *   problems like missing config files, syntax errors, duplicate 
 *   file specifications and so on;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv []) 

{
	static char const *program_help [] = 
	{
		"dfm:s:tv",
		"[config-file] [config-file] ...",
		"recycle (rotate) log files",
		"f\tforce rotation now",
		"m s\tmail command is s [" MAIL_PROGRAM "]",
		"s s\tstate file path is s [" RECYCLE_PATH_STATUS "]",
		"t\ttest configuration",
		"v\tverbose messages",
		(char const *) (0)
	};
	LOGSET logset = 
	{
		&logset,
		"*",
		(char **) (0),
		(int) (0),
		(int) (0),
		(flag_t) (0),
		1048576,
		(int) (0),
		"",
		"",
		"",
		"",
		COMPRESS_COMMAND,
		COMPRESS_OPTIONS,
		COMPRESS_EXT,
		UNCOMPRESS_COMMAND,
		UNCOMPRESS_OPTIONS,
		UNCOMPRESS_EXT,
		{
			0,
			0,
			0,
			0
		},
		{
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0
		},
		(mode_t) (-1),
		(uid_t) (-1),
		(gid_t) (-1),
		false
	};
	RECYCLE recycle = 
	{
		(flag_t) (0),
		{
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0
		},
		RECYCLE_PATH_STATUS,
		MAIL_PROGRAM,
		MAIL_OPTIONS,
		&logset,
		&logset,
		(STATE *) (0),
		(size_t) (0),
		(size_t) (0),
		false
	};
	time_t now = time (&now);
	char filename [FILENAME_MAX] = RECYCLE_PATH_CONFIG;
	signed c;
	recycle.tm = *localtime (&now);
	logset.tm = *localtime (&now);
	optind = 1;
	opterr = 1;
	while ((c = getoptv (argc, argv, program_help)) != -1) 
	{
		switch (c) 
		{
		case 'f':
			_setbits (recycle.flags, RECYCLE_B_FORCE);
			break;
		case 'm':
			recycle.mail_program = (char const *) (optarg);
			break;
		case 's':
			recycle.statefilename = (char const *) (optarg);
			break;
		case 't':
			_setbits (recycle.flags, RECYCLE_B_VERBOSE | RECYCLE_B_CHECK);
			break;
		case 'v':
			_setbits (recycle.flags, RECYCLE_B_VERBOSE);
			break;
		default:
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if (argc == 0) 
	{
		if (configure (&recycle, filename) != 0) 
		{
			exit (1);
		}
	}
	while ((argc-- > 0) && (*argv != (char *) (0))) 
	{
		strcpy (filename, *argv++);
		if (configure (&recycle, filename) != 0) 
		{
			exit (1);
		}
	}
	if (readstate (&recycle)) 
	{
		exit (1);
	}
	while (recycle.logsets->next != recycle.logsets) 
	{
		recycle.logset = recycle.logsets->next;
		if (recycle.logset->flags & LOGSET_FLAG_SHAREDSCRIPTS) 
		{
			if (valid (recycle.logset->prescript)) 
			{
				if (runscript (recycle.logset->prescript, recycle.logset->filespec, recycle.flags)) 
				{
					error (0, errno, "%s: logset precycle script failed", recycle.logset->filespec);
					recycle.error = true;
				}
			}
		}
		cyclelogs (&recycle);
		if (recycle.logset->flags & LOGSET_FLAG_SHAREDSCRIPTS) 
		{
			if (valid (recycle.logset->postscript)) 
			{
				if (runscript (recycle.logset->postscript, recycle.logset->filespec, recycle.flags)) 
				{
					error (0, errno, "%s: logset postcycle script failed", recycle.logset->filespec);
					recycle.error = true;
				}
			}
		}
		recycle.logsets->next = recycle.logset->next;
		recycle.logset->next = (LOGSET *) (0);
		free (recycle.logset);
	}
	if (writestate (&recycle)) 
	{
		exit (1);
	}
	if (_anyset (recycle.flags, RECYCLE_B_VERBOSE)) 
	{
		error (0, 0, "exit status %d", recycle.error);
	}
	exit (recycle.error);
}

