/*====================================================================*
 *
 *   ff-elf.c - find file utility;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

#define _GETOPT_H

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <libgen.h>
#include <time.h>
#include <errno.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../files/files.h"
#include "../strlib/strlib.h"
#include "../chrlib/chrlib.h"
#include "../date/date.h"
#include "../date/date.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../tools/emalloc.c"
#include "../tools/error.c"
#endif

#ifndef MAKEFILE
#include "../files/makepath.c"
#include "../files/splitpath.c"
#include "../files/mergepath.c"
#include "../files/makefind.c"
#include "../files/partpath.c"
#include "../files/partfile.c"
#include "../files/match.c"
#include "../files/find.c"
#endif

#ifndef MAKEFILE
#include "../date/datecomp.c"
#include "../date/timecomp.c"
#endif

#ifndef MAKEFILE
#include "../strlib/strsplit.c"
#endif

#ifndef MAKEFILE
#include "../chrlib/chrcount.c"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define MASK (S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IWGRP|S_IXGRP|S_IROTH|S_IWOTH|S_IXOTH)
#define MODEMASK 0x0FFF
#define ACCESS (S_ISUID|S_ISGID|S_ISVTX|S_IRWXU|S_IRWXG|S_IRWXO)
#define SHARED (S_IRUSR|S_IXUSR|S_IRGRP|S_IXGRP|S_IROTH|S_IXOTH)
#define STATIC (S_IRUSR|S_IRGRP|S_IROTH)
#define FF_B_ELF (1 << 0)
#define FF_B_ARCH (1 << 1)
#define FF_B_SH (1 << 2)
#define ELF "\177ELF"
#define ARCH "!<arch>"
#define SCRIPT "#!"

/*====================================================================*
 *   program functions;
 *--------------------------------------------------------------------*/

static void findfile(FIND * find, flag_t flags);
static void testfile(FIND * find, flag_t flags);

/*====================================================================*
 *
 *   void showfile (FIND *find, flag_t flags);
 *
 *   determine if the find basename matches the find wildcard; if so 
 *   the print the find.fullname, pathname or basename depending on 
 *   the flags; optionally, prefix each print line with the file date; 
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void showfile(FIND * find, flag_t flags)

{
	if (! match(find->filename, find->wildcard))
	{
		return;
	}
	if (find->flagword & (FIND_B_DATETIME))
	{
		char datetime[LOGTIME_LEN];
		strftime (datetime, sizeof(datetime), LOGTIME, localtime(& find->statinfo.st_mtime));
		printf ("%s ", datetime);
	}
	switch (find->flagword & (FIND_B_PATHNAME | FIND_B_FILENAME))
	{
	case FIND_B_PATHNAME:
		printf ("%s\n", find->pathname);
		break;
	case FIND_B_FILENAME:
		printf ("%s\n", find->filename);
		break;
	default: 
		printf ("%s\n", find->fullname);
		break;
	}
	return;
}

/*====================================================================*
 *
 *   void function (FIND *find, flag_t flags);
 *
 *   determine if the find basename matches the find wildcard; if so 
 *   the print the find.fullname, pathname or basename depending on 
 *   the flags; optionally, prefix each print line with the file date; 
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void function(FIND * find, flag_t flags)

{
	char signature[255];
	signed length;
	file_t fd;
	if ((fd = open(find->fullname, O_RDONLY)) > 0)
	{
		if ((length = read(fd, signature, sizeof(signature))) > 0)
		{
			if (! memcmp(signature, ELF, sizeof(ELF) - 1))
			{
				signature [sizeof(ELF) - 1] = (char)(0);
				if (_anyset(flags, FF_B_ELF))
				{

#ifdef FF_DETAIL

					printf ("[%04o] ", find->statinfo.st_mode & MODEMASK);
					printf ("[%s] ", signature +  1);

#endif

					showfile (find, flags);
				}
			}
			else if(! memcmp(signature, ARCH, sizeof(ARCH) - 1))
			{
				signature [sizeof(ARCH) - 1] = (char)(0);
				if (_anyset(flags, FF_B_ARCH))
				{

#ifdef FF_DETAIL

					printf ("[%04o] ", find->statinfo.st_mode & MODEMASK);
					printf ("[%s] ", signature);

#endif

					showfile (find, flags);
				}
			}
			else if(! memcmp(signature, SCRIPT, sizeof(SCRIPT) - 1))
			{
				signature [sizeof(SCRIPT) - 1] = (char)(0);
				if (_anyset(flags, FF_B_SH))
				{

#ifdef FF_DETAIL

					printf ("[%04o] ", find->statinfo.st_mode & MODEMASK);
					printf ("[%s] ", signature);

#endif

					showfile (find, flags);
				}
			}
		}
		close (fd);
	}
	return;
}

/*====================================================================*
 *
 *   void testfile (FIND *find, flag_t flags);
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void testfile(FIND * find, flag_t flags)

{
	if (lstat(find->fullname, & find->statinfo))
	{
		error (0, errno, "%s", find->fullname);
		return;
	}
	if (S_ISDIR(find->statinfo.st_mode))
	{
		char const * filename = find->filename;
		if (* filename == '.')
		{
			filename++;
		}
		if (* filename == '.')
		{
			filename++;
		}
		if (* filename == (char)(0))
		{
			return;
		}

#if 0

		if (_anyset(find->flagword, FIND_B_DIR))
		{
			function (find, flags);
		}

#endif

		if (_anyset(find->flagword, FIND_B_RECURSE))
		{
			findfile (find, flags);
		}
		return;
	}
	if (S_ISLNK(find->statinfo.st_mode))
	{
		if (_anyset(find->flagword, FIND_B_LNK))
		{
			function (find, flags);
		}
		return;
	}
	if (S_ISREG(find->statinfo.st_mode))
	{
		if (_anyset(find->flagword, FIND_B_REG))
		{
			function (find, flags);
		}
		return;
	}
	return;
}

/*====================================================================*
 *
 *   void findfile (FIND *find, flag_t flags);
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void findfile(FIND * find, flag_t flags)

{
	struct dirent * dirent;
	char * filename = find->fullname;
	DIR * dir = opendir(filename);
	if (dir == (DIR *)(0))
	{
		testfile (find, flags);
		return;
	}
	while (* filename != (char)(0))
	{
		filename++;
	}
	* filename = PATH_C_EXTENDER;
	while ((dirent = readdir(dir)) != (struct dirent *)(0))
	{
		strcpy (filename +  1, dirent->d_name);
		partpath (find->fullname, find->pathname, find->filename);
		partfile (find->filename, find->basename, find->extender);
		testfile (find, flags);
	}
	* filename = (char)(0);
	closedir (dir);
	return;
}

/*====================================================================*
 *   main program;
 *--------------------------------------------------------------------*/

int main(int argc, char const * argv[])

{
	extern FIND find;
	static char const * optv[] = 
	{
		"aefprstE:PSBLIK",
		PUTOPTV_S_SEARCH,
		"search folders and/or standard paths for files",
		"s\tshell scripts",
		"e\telf binary files",
		"f\toutput filename only",
		"a\tarch (static) libraries",
		"p\toutput pathname only",
		"r\trecursive search",
		"t\tputput filetime",
		"E s\tsearch environment string ${s}",
		"P\tsearch environment string ${PATH}",
		"S\tsearch system folders",
		"B\tsearch binary folders",
		"L\tsearch library folders",
		(char const *)(0)
	};
	char * string = (char *)(0);
	char const ** folders = (char const **)(0);
	char const ** folder = (char const **)(0);
	flag_t flags = (flag_t)(0);
	signed c;
	while (~ (c = getoptv(argc, argv, optv)))
	{
		switch (c)
		{
		case 'a':
			_setbits (flags, FF_B_ARCH);
			break;
		case 'e':
			_setbits (flags, FF_B_ELF);
			break;
		case 'f':
			_clrbits (find.flagword, FIND_B_PATHNAME);
			_setbits (find.flagword, FIND_B_FILENAME);
			break;
		case 'p':
			_setbits (find.flagword, FIND_B_PATHNAME);
			_clrbits (find.flagword, FIND_B_FILENAME);
			break;
		case 'r':
			_setbits (find.flagword, FIND_B_RECURSE);
			break;
		case 's':
			_setbits (flags, FF_B_SH);
			break;
		case 't':
			_setbits (find.flagword, FIND_B_DATETIME);
			break;
		case 'E':
			if ((string = getenv(optarg)) == (char *)(0))
			{
				error (0, EINVAL, "symbol ${%s} is not defined", optarg);
			}
			break;
		case 'P':
			string = getenv("PATH");
			break;
		case 'S':
			string = strdup(PATH_SYSDIRS);
			break;
		case 'B':
			string = strdup(PATH_BINDIRS);
			break;
		case 'L':
			string = strdup(PATH_LIBDIRS);
			break;
		default: 
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if (_allclr(flags, (FF_B_ELF | FF_B_ARCH | FF_B_SH)))
	{
		_setbits (flags, (FF_B_ELF | FF_B_ARCH | FF_B_SH));
	}
	if (_allclr(find.flagword, (FIND_B_DIR | FIND_B_LNK | FIND_B_REG)))
	{
		_setbits (find.flagword, (FIND_B_DIR | FIND_B_LNK | FIND_B_REG));
	}
	if (string != (char *)(0))
	{
		size_t count = chrcount(string, PATH_C_SEPARATOR) +  2;
		folders = (char const **)(emalloc(count * sizeof(char const **)));
		strsplit (folders, count, string, PATH_C_SEPARATOR);
	}
	while ((argc) && (* argv))
	{
		if (folders != (char const **)(0))
		{
			for (folder = folders; * folder != (char *)(0); folder++)
			{
				makefind (& find, * argv);
				strcpy (find.pathname, * folder);
				strcpy (find.fullname, * folder);
				findfile (& find, flags);
			}
		}
		else 
		{
			makefind (& find, * argv);
			findfile (& find, flags);
		}
		argc--;
		argv++;
	}
	exit (0);
}

