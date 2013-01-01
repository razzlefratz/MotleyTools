/*====================================================================*
 *   
 *   configure.c - recycle.configuration file functions; 
 *   
 *   these functions read recycle.configuration files and return
 *   things for the main recycle program to do; files are read as
 *   one long string and scanned for comments, options, filespescs
 *   and option groups;  
 *
 *   struct _scan_ holds the parsing state with a line counter, two
 *   buffers and two pointers; one buffer contains the input string 
 *   and the other contains the current option keyword; one pointer 
 *   points to the next input character and the other points to any
 *   character that needs it; the structure can be stacked, queued,
 *   passed to other functions or converted to an object;
 *
 *   earlier versions of these functions only recognized newline as
 *   an option terminator; that meant one option per line; but this 
 *   version recognises left brace ('{'), semicolon (';') and right
 *   brace ('}') as well as newline; that means multiple options per  
 *   line when semicolons are used; 
 *
 *   _setbits() and _clrbits() are bitwise macros defined in our
 *   flags.h file; 
 *
 *   the bool data type is defined in a local types.h file; it can 
 *   be undefined for compilers that support boolean variables; 
 *
 *   option keywords are stored in alphabetical order in a string
 *   vector; alphabetic tokens are converted to a number by table
 *   lookup; the number is used in one large case statement; this
 *   has size and speed advantages;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#ifndef CONFIGURE_SOURCE
#define CONFIGURE_SOURCE

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <time.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../recycle/recycle.h"
#include "../recycle/keywords.h"

#include "../tools/tools.h"
#include "../tools/error.h"
#include "../tools/chars.h"
#include "../tools/sizes.h"
#include "../tools/memory.h"
#include "../linux/linux.h"
#include "../files/files.h"
#include "../date/date.h"
#include "../strlib/strlib.h"

/*====================================================================*
 *   custom macro definitions;
 *--------------------------------------------------------------------*/

#define ALLOWCONTINUATIONLINES
#define ENAMLEDEPRECATEDCOMMANDS

/*====================================================================*
 *
 *   static int readfile (char filename[], RECYCLE *recycle);
 *
 *   read and parse one recycle.configuration file;
 *
 *   the file is read as one string into SCAN scan having a
 *   token buffer, character pointers and line counter; scan is then
 *   passed to other parsing functions when needed; 
 *
 *   as a log (which can be broken) each pass through the main loop
 *   reads one line; some passes read more that one line; one or two
 *   do not and are special cases; scan->sp should always point to a
 *   newline at the bottom of the loop; if not, decrement scan->line
 *   and scan->sp before returning to the top; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *   
 *--------------------------------------------------------------------*/

static int readfile (RECYCLE * recycle, char filename []) 

{
	extern char const *keywords [];
	LOGSET *logset = recycle->logsets;
	SCAN *scan;
	struct stat statinfo1;
	struct stat statinfo2;
	int fd;
	int length;

#ifndef J8H7G0B3
#define J8H7G0B3

/*
 * this code segement checks the keywords table for correct size 
 * and word order; it only needs to be executed once because the  
 * the table is static; the main benefit is detection of obvious 
 * errors made during table modifcation; this test only prevents
 * search failure and segment faults; people must check spelling
 * and word index values; 
 */

	static bool tested = false;
	if (!tested) 
	{
		svorder ("keywords", keywords, LR_O_NULL, strcmp);
		tested = true;
	}

#endif

	if ((fd = open (filename, O_RDONLY)) == -1) 
	{
		error (0, errno, "%s: can't open configuration file", filename);
		return (1);
	}
	if ((scan = malloc (sizeof (SCAN))) == (SCAN *) (0)) 
	{
		error (0, errno, "%s: can't allocate scanner", filename);
		return (1);
	}
	if (_anyset (recycle->flags, RECYCLE_B_VERBOSE)) 
	{
		error (0, 0, "%s: opened configuration file", filename);
	}
	length = lseek (fd, 0, SEEK_END);
	lseek (fd, 0, SEEK_SET);
	if ((scan->input = malloc (length + 2)) == (char *) (0)) 
	{
		error (0, errno, "%s: can't allocate input buffer", filename);
		close (fd);
		return (1);
	}
	scan->file = filename;
	scan->line = 1;
	if ((scan->token = malloc (STRINGSIZE)) == (char *) (0)) 
	{
		error (0, errno, "%s: can't allocate token buffer", filename);
		close (fd);
		return (1);
	}
	if (read (fd, scan->input, length) < length) 
	{
		error_on_line (0, errno, filename, 0, "can't read configuration file");
		close (fd);
		return (1);
	}
	close (fd);
	scan->input [length + 0] = '\n';
	scan->input [length + 1] = '\0';
	for (scan->cp = scan->input; *scan->cp != (char) (0); ++scan->cp) 
	{
		while (isblank (*scan->cp)) 
		{
			++scan->cp;
		}
		if (*scan->cp == '#') 
		{
			for (++scan->cp; !newline (*scan->cp); ++scan->cp);
		}
		else if (isalpha (*scan->cp)) 
		{
			for (scan->tp = scan->token; isalpha (*scan->cp); *scan->tp++ = *scan->cp++);
			*scan->tp = (char) (0);

#ifdef RECYCLE_TRACE

			if (_anyset (recycle->flags, RECYCLE_B_VERBOSE)) 
			{
				error (0, 0, "%s:%d reading '%s' option", scan->file, scan->line, scan->token);
			}

#endif

			switch (svindex (scan->token, keywords, LR_O_NULL, strcmp)) 
			{
			case LR_O_COMPRESS:
				_setbits (logset->flags, LOGSET_FLAG_COMPRESS);
				break;
			case LR_O_COMP_PROGRAM:
				if (scanargs (scan) != 0) 
				{
					return (1);
				}
				if (access (scan->token, X_OK)) 
				{
					error_on_line (0, errno, scan->file, scan->line, "can't execute %s", scan->token);
					return (1);
				}
				logset->comp_program = strdup (scan->token);
				break;
			case LR_O_COMP_EXT:
				if (scanargs (scan) != 0) 
				{
					return (1);
				}
				logset->comp_ext = strdup (scan->token);
				break;
			case LR_O_COMP_OPTIONS:
				if (scanargs (scan) != 0) 
				{
					return (1);
				}
				logset->comp_options = strdup (scan->token);
				break;
			case LR_O_COPYTRUNCATE:
				_setbits (logset->flags, LOGSET_FLAG_COPYTRUNCATE);
				break;
			case LR_O_CREATE:
				_setbits (logset->flags, LOGSET_FLAG_CREATE);
				if (scancreate (scan, logset) != 0) 
				{
					return (1);
				}
				break;
			case LR_O_DAILY:
				_clrbits (logset->flags, (LOGSET_FLAG_MONTHLY|LOGSET_FLAG_WEEKLY));
				_setbits (logset->flags, (LOGSET_FLAG_DAILY));
				logset->tm = recycle->tm;
				logset->threshold = 0;
				if (scandaily (scan, logset) != 0) 
				{
					return (1);
				}
				break;
			case LR_O_DELAYCOMPRESS:
				_setbits (logset->flags, LOGSET_FLAG_DELAYCOMPRESS);
				break;
			case LR_O_ENDSCRIPT:
				break;

#ifdef ENAMLEDEPRECATEDCOMMANDS

			case LR_O_ERRORS:
				error_on_line (0, 0, scan->file, scan->line, "ignoring option '%s': Option is deprecated", scan->token);
				break;

#endif

			case LR_O_EXTENSION:
				if (scanargs (scan) != 0) 
				{
					return (1);
				}
				logset->ext = strdup (scan->token);
				break;
			case LR_O_IFEMPTY:
				_clrbits (logset->flags, LOGSET_FLAG_NOTIFEMPTY);
				break;
			case LR_O_INCLUDE:
				if (logset != recycle->logsets) 
				{
					error_on_line (0, 0, scan->file, scan->line, "bailing out: 'include' option is not permitted inside a definition");
					return (1);
				}
				if (scanargs (scan) == 0) 
				{
					if (configure (recycle, scan->token) != 0) 
					{
						return (1);
					}
				}
				break;

#ifdef ENAMLEDEPRECATEDCOMMANDS

			case LR_O_RECYCLE:
				error_on_line (0, 0, scan->file, scan->line, "allowing option '%s': Option is deprecated", scan->token);

#endif

			case LR_O_KEEP:
				while (isblank (*scan->cp)) 
				{
					++scan->cp;
				}
				for (logset->keep = 0; isdigit (*scan->cp); ++scan->cp) 
				{
					logset->keep *= 10;
					logset->keep += *scan->cp - '0';
				}
				if (!isblank (*scan->cp) && !isbreak (*scan->cp)) 
				{
					error_on_line (0, 0, scan->file, scan->line, "count has isempty syntax");
					return (1);
				}
				break;
			case LR_O_MAIL:
				if (scanargs (scan) != 0) 
				{
					return (1);
				}
				logset->recipient = strdup (scan->token);
				break;
			case LR_O_MAILFIRST:
				_setbits (logset->flags, LOGSET_FLAG_MAILFIRST);
				break;
			case LR_O_MAILLAST:
				_clrbits (logset->flags, LOGSET_FLAG_MAILFIRST);
				break;
			case LR_O_MONTHLY:
				_clrbits (logset->flags, (LOGSET_FLAG_WEEKLY|LOGSET_FLAG_DAILY));
				_setbits (logset->flags, (LOGSET_FLAG_MONTHLY));
				logset->tm = recycle->tm;
				logset->threshold = 0;
				if (scanmonthly (scan, logset) != 0) 
				{
					return (1);
				}
				break;
			case LR_O_NOCOMPRESS:
				_clrbits (logset->flags, LOGSET_FLAG_COMPRESS);
				break;
			case LR_O_NOCOPYTRUNCATE:
				_clrbits (logset->flags, LOGSET_FLAG_COPYTRUNCATE);
				break;
			case LR_O_NOCREATE:
				_clrbits (logset->flags, LOGSET_FLAG_CREATE);
				break;
			case LR_O_NODELAYCOMPRESS:
				_clrbits (logset->flags, LOGSET_FLAG_DELAYCOMPRESS);
				break;
			case LR_O_NOMAIL:
				logset->recipient = "";
				break;
			case LR_O_NOOLDDIR:
				logset->folder = "";
				break;
			case LR_O_NOSHAREDSCRIPTS:
				_clrbits (logset->flags, LOGSET_FLAG_SHAREDSCRIPTS);
				break;
			case LR_O_NOTIFEMPTY:
				_setbits (logset->flags, LOGSET_FLAG_NOTIFEMPTY);
				break;
			case LR_O_OLDDIR:
				if (scanargs (scan) != 0) 
				{
					return (1);
				}
				if (stat (scan->token, &statinfo1)) 
				{
					error_on_line (0, errno, scan->file, scan->line, "can't stat %s", scan->token);
					return (1);
				}
				if (!S_ISDIR (statinfo1.st_mode)) 
				{
					error_on_line (0, ENOTDIR, scan->file, scan->line, "can't use %s", scan->token);
					return (1);
				}
				logset->folder = strdup (scan->token);
				break;

#ifdef ENAMLEDEPRECATEDCOMMANDS

			case LR_O_MISSINGOK:
				error_on_line (0, 0, scan->file, scan->line, "allowing option '%s': Option is deprecated", scan->token);

#endif

			case LR_O_OPTIONAL:
				_clrbits (logset->flags, LOGSET_FLAG_REQUIRED);
				break;
			case LR_O_POSTRECYCLE:
				logset->postscript = scanscript (scan);
				break;
			case LR_O_PRERECYCLE:
				logset->prescript = scanscript (scan);
				break;

#ifdef ENAMLEDEPRECATEDCOMMANDS

			case LR_O_NOMISSINGOK:
				error_on_line (0, 0, scan->file, scan->line, "allowing option '%s': Option is deprecated", scan->token);

#endif

			case LR_O_REQUIRED:
				_setbits (logset->flags, LOGSET_FLAG_REQUIRED);
				break;
			case LR_O_SHAREDSCRIPTS:
				_setbits (logset->flags, LOGSET_FLAG_SHAREDSCRIPTS);
				break;
			case LR_O_SIZE:
				_clrbits (logset->flags, (LOGSET_FLAG_MONTHLY|LOGSET_FLAG_WEEKLY|LOGSET_FLAG_DAILY));
				if (scansize (scan, logset) != 0) 
				{
					exit (1);
				}
				break;

#ifdef ENAMLEDEPRECATEDCOMMANDS

			case LR_O_TABOOEXT:
				error_on_line (0, 0, scan->file, scan->line, "ignoring option '%s': Option is deprecated", scan->token);
				break;

#endif

			case LR_O_UNCOMP_PROGRAM:
				if (scanargs (scan) != 0) 
				{
					return (1);
				}
				if (access (scan->token, X_OK)) 
				{
					error_on_line (0, 0, scan->file, scan->line, "can't use '%s'", scan->token);
					return (1);
				}
				logset->uncomp_program = strdup (scan->token);
				break;
			case LR_O_WEEKLY:
				_clrbits (logset->flags, (LOGSET_FLAG_MONTHLY|LOGSET_FLAG_DAILY));
				_setbits (logset->flags, (LOGSET_FLAG_WEEKLY));
				logset->tm = recycle->tm;
				logset->threshold = 0;
				if (scanweekly (scan, logset) != 0) 
				{
					return (1);
				}
				break;
			default:
				error_on_line (0, EINVAL, scan->file, scan->line, "ignoring option '%s'", scan->token);
				for (++scan->cp; !isbreak (*scan->cp); ++scan->cp);
				break;
			}
		}
		else if ((*scan->cp == '/') || isquote (*scan->cp)) 
		{
			if (logset != recycle->logsets) 
			{
				error_on_line (0, 0, scan->file, scan->line, "unexpected filename");
				return (1);
			}
			for (scan->tp = scan->token; !isbreak (*scan->cp); *scan->tp++ = *scan->cp++) 
			{

#ifdef ALLOWCONTINUATIONLINES

				if (*scan->cp == '\\') 
				{
					*scan->tp++ = *scan->cp++;
					if (*scan->cp == '\n') 
					{
						++scan->line;
						--scan->tp;
					}
				}

#endif

			}
			*scan->tp = (char) (0);
			logset = NEW (LOGSET);
			memcpy (logset, recycle->logsets, sizeof (LOGSET));
			logset->filespec = strdup (scan->token);
			logset->files = (char **) (0);
			logset->nfiles = 0;
			logset->file = 0;
			logset->next = recycle->logset->next;
			recycle->logset->next = logset;
			recycle->logset = logset;
			if (scanlogset (scan, recycle) != 0) 
			{
				return (1);
			}
		}
		else if (*scan->cp == '}') 
		{
			if (logset == recycle->logsets) 
			{
				error_on_line (0, 0, scan->file, scan->line, "unxpected right bracket in default configuration");
				return (1);
			}
			if (*logset->folder != (char) (0)) 
			{
				if (stat (logset->folder, &statinfo1)) 
				{
					error_on_line (0, errno, scan->file, scan->line, "can't stat %s", logset->folder);
					return (1);
				}
				for (logset->file = 0; logset->file < logset->nfiles; logset->file++) 
				{
					char const *dirName = pathpart (logset->files [logset->file]);
					if (stat (dirName, &statinfo2)) 
					{
						error_on_line (0, errno, scan->file, scan->line, "can't access %s information.", dirName);
						return (1);
					}
					if (statinfo1.st_dev != statinfo2.st_dev) 
					{
						error_on_line (0, 0, scan->file, scan->line, "old path %s and log file %s are on different devices.", logset->folder, logset->files [logset->file]);
						return (1);
					}
				}
			}
			logset = recycle->logsets;
		}

/*
 * an option started with something other that '#', letter, slash, quote or apostrophe; discard 
 * the option but not the entire line; cautious or brutal programmers should exit at this point;
 */

		else if (!isbreak (*scan->cp)) 
		{
			error_on_line (0, 0, scan->file, scan->line, "illegal syntax after '%s'", scan->token);
			error_on_line (0, 0, scan->file, scan->line, "ignoring entire of line");
			for (++scan->cp; !isbreak (*scan->cp); ++scan->cp);
		}

/*
 * options should end in left brace, semicolon, right brace or newline; if not then the user
 * probably goofed; backup one character and continue; any errors will be caught on the next
 * pass; see the previous comment;
 */

		while (isblank (*scan->cp)) 
		{
			++scan->cp;
		}
		if (!isbreak (*scan->cp)) 
		{
			error_on_line (0, 0, scan->file, scan->line, "option '%s' followed by unexpected text", scan->token);
			error_on_line (0, 0, scan->file, scan->line, "insert semicolon or newline after it.");
			--scan->cp;
		}
		else if (newline (*scan->cp)) 
		{
			++scan->line;
		}
	}
	return (0);
}


/*====================================================================*
 *
 *   static int search (RECYCLE *recycle, char pathname[]);
 *   
 *   search filename and call readfile() for each file present;
 *
 *   this function distiguishes between folders, files and links; we
 *   can enable/disable directory recursion and link traversal using 
 *   flags; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *   
 *--------------------------------------------------------------------*/

static int findfile (RECYCLE * recycle, char pathname []) 

{
	DIR *dir;
	if ((dir = opendir (pathname)) != (DIR *) (0)) 
	{
		struct dirent *dirent;
		char *basename;
		for (basename = pathname; *basename != (char) (0); basename++);
		*basename = PATH_C_EXTENDER;
		while ((dirent = readdir (dir)) != (struct dirent *) (0)) 
		{
			struct stat statinfo;
			char *sp = dirent->d_name;
			if (*sp == FILE_C_EXTENDER) 
			{
				sp++;
			}
			if (*sp == FILE_C_EXTENDER) 
			{
				sp++;
			}
			if (*sp == (char)(0)) 
			{
				continue;
			}
			strcpy (basename + 1, dirent->d_name);
			if (lstat (pathname, &statinfo)) 
			{
				error (0, errno, "can't lstat %s", pathname);
				continue;
			}
			if (S_ISDIR (statinfo.st_mode)) 
			{
				if (recycle->flags & RECYCLE_B_RECURSE) 
				{
					findfile (recycle, pathname);
				}
				continue;
			}
			if (S_ISLNK (statinfo.st_mode)) 
			{
				if (recycle->flags & RECYCLE_B_TRAVERSE) 
				{
					readfile (recycle, pathname);
				}
				continue;
			}
			if (S_ISREG (statinfo.st_mode)) 
			{
				readfile (recycle, pathname);
				continue;
			}
		}
		*basename = (char) (0);
		closedir (dir);
		return (0);
	}
	return (1);
}


/*====================================================================*
 *
 *   int configure (RECYCLE *recycle, char filename[]);
 *
 *   determine if filename is a folder or a file and then call either 
 *   readfile or search, respectively; the decision was 
 *   placed here keep the other functions clean;
 *
 *   filename is declared as a buffer because it is read and written  
 *   by search if that function wants to recurse through the
 *   subfolders;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

int configure (RECYCLE * recycle, char filename []) 

{
	struct stat statinfo;
	if (lstat (filename, &statinfo) == -1) 
	{
		error (0, errno, "can't use configuration file %s", filename);
		return (1);
	}
	else if (S_ISDIR (statinfo.st_mode)) 
	{
		if (findfile (recycle, filename) != 0) 
		{
			return (1);
		}
	}
	else if (S_ISREG (statinfo.st_mode)) 
	{
		if (readfile (recycle, filename) != 0) 
		{
			return (1);
		}
	}
	else if (S_ISLNK (statinfo.st_mode)) 
	{
		if (readfile (recycle, filename) != 0) 
		{
			return (1);
		}
	}
	return (0);
}


#endif

