/*====================================================================*
 *
 *   whom.c - list usernames and/or groupnames in aphabetical; 
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
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <pwd.h>
#include <grp.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../linux/linux.h"
#include "../regex/regex.h"
#include "../chrlib/chrlib.h"
#include "../list/list.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/console.c"
#include "../tools/erealloc.c"
#include "../tools/emalloc.c"
#include "../tools/uintspec.c"
#include "../tools/todigit.c"
#endif

#ifndef MAKEFILE
#include "../list/listcreate.c"
#include "../list/listdelete.c"
#include "../list/listinsert.c"
#include "../list/listdetect.c"
#include "../list/listexpand.c"
#include "../list/listcolumn.c"
#endif

#ifndef MAKEFILE
#include "../regex/regexmake.c"
#include "../regex/regexspan.c"
#include "../regex/regexcomp.c"
#include "../regex/regexfree.c"
#include "../regex/regexhelp.c"
#include "../regex/regexshow.c"
#endif

#ifndef MAKEFILE
#include "../chrlib/charset.c"
#include "../chrlib/chruesc.c"
#include "../chrlib/chruescmap.c"
#endif

#ifndef MAKEFILE
#include "../linux/getviewport.c"
#endif

#ifndef MAKEFILE
#include "../sv/sv_ascii.c"
#endif

/*====================================================================*
 *   program constants; 
 *--------------------------------------------------------------------*/

#define WHOM_B_USR (1 << 0)
#define WHOM_B_GRP (1 << 1)
#define WHOM_B_SHW (1 << 2)

#define COUNT 0
#define WIDTH 0

/*====================================================================*
 *
 *   void function ();
 *
 *   search pwent and grent for usernames and groupnames that match
 *   the regular expression in regex; add matching names to a list;
 *   print the list in multi-column format when done;
 *  
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void function (LIST * list, regexp * regex, flag_t flags) 

{
	char const * string;
	if (_anyset (flags, WHOM_B_USR)) 
	{
		struct passwd * passwd;
		while ((passwd = getpwent ())) 
		{
			string = regexspan (regex, passwd->pw_name);
			if ((string) && (!* string)) 
			{
				listinsert (list, passwd->pw_name);
			}
		}
	}
	if (_anyset (flags, WHOM_B_GRP)) 
	{
		struct group * group;
		while ((group = getgrent ())) 
		{
			string = regexspan (regex, group->gr_name);
			if ((string) && (!* string)) 
			{
				listinsert (list, group->gr_name);
			}
		}
	}
	return;
}

/*====================================================================*
 *   
 *   int main (int argc, char const * argv[]);
 *   
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv []) 

{
	extern const unsigned char ct_unescape [];
	static char const * optv [] = 
	{
		"c:e:gHnw:uRT",
		PUTOPTV_S_DIVINE,
		"print user/group names in alphabetcial order in columns",
		"c n\tcolumn count is (n) [" LITERAL (COUNT) "]",
		"w n\tscreen width is (n) [" LITERAL (WIDTH) "]",
		"e s\texpression is s [.+]",
		"g\tlist groupnames",
		"H\tregular expression help",
		"u\tlist usernames",
		"n\tnumber list items",
		"R\tregular expression help",
		"T\tescape sequence rules",
		(char *) (0)
	};
	LIST list;
	regexp * regex = (regexp *) (0);
	char const * expression = ".+";
	flag_t flags = (flag_t) (0);
	size_t count = COUNT;
	size_t width = WIDTH;
	bool index = false;
	int c;
	while ((c = getoptv (argc, argv, optv)) != -1) 
	{
		switch (c) 
		{
		case 'w':
			width = uintspec (optarg, 1, 132);
			break;
		case 'c':
			count = uintspec (optarg, 1, 16);
			break;
		case 'g':
			_setbits (flags, WHOM_B_GRP);
			break;
		case 'e':
			expression = optarg;
			break;
		case 'n':
			index = true;
			break;
		case 'u':
			_setbits (flags, WHOM_B_USR);
			break;
		case 'H':
			_setbits (flags, WHOM_B_SHW);
			break;
		case 'R':
			regexhelp ();
			exit (0);
		case 'T':
			chruescmap (ct_unescape, REGEX_C_ESC);
			exit (0);
		default:
			break;
		}
	}
	argc-= optind;
	argv+= optind;
	if (_anyset (flags, (WHOM_B_SHW))) 
	{
		regex = regexmake (expression);
		regexshow (regex);
		return (0);
	}
	if (_allclr (flags, (WHOM_B_USR | WHOM_B_GRP))) 
	{
		_setbits (flags, (WHOM_B_USR | WHOM_B_GRP));
	}
	setpwent ();
	listcreate (& list, _LISTSIZE);
	regex = regexmake (expression);
	function (& list, regex, flags);
	regex = regexfree (regex);
	listcolumn (& list, stdout, width, count, index);
	listdelete (& list);
	endpwent ();
	exit (0);
}

