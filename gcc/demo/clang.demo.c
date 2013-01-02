/*====================================================================*
 *
 *   cfm.c - c source code formatter;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#define _GETOPT_H
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <time.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/tools.h"
#include "../tools/types.h"
#include "../tools/flags.h"
#include "../tools/getopt.h"
#include "../tools/putopt.h"
#include "../clang/clang.h"
#include "../text/text.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#include "../tools/getopt.c"
#include "../tools/putopt.c"
#include "../tools/eprintf.c"
#include "../tools/eperror.c"
#include "../tools/emalloc.c"
#include "../files/vfopen.c"
#include "../files/makepath.c"
#include "../files/splitpath.c"
#include "../files/mergepath.c"
#include "../files/makefind.c"
#include "../files/partpath.c"
#include "../files/partfile.c"
#include "../strlib/strupr.c"
#include "../strlib/svindex.c"
#include "../clang/cgettoken.c"
#include "../clang/cgetspace.c"
#include "../clang/cputtoken.c"
#include "../clang/cputspace.c"
#include "../clang/cputbreak.c"
#include "../clang/cputstate.c"
#include "../clang/cputerror.c"
#include "../clang/cpadmargin.c"
#include "../clang/cexpandbar.c"
#include "../clang/coper.c"
#include "../clang/cword.c"
#include "../text/getchr.c"
#include "../text/getquote.c"
#include "../text/getgroup.c"
#include "../text/getmacro.c"
#include "../text/putchr.c"
#include "../text/putstr.c"
#include "../text/flushtext.c"
#include "../text/cleartext.c"
#include "../text/textstate.c"
#include "../text/assigntext.c"
#include "../linux/getusername.c"
#include "../tools/setinfo.c"
#include "../strlib/strlwr.c"

/*====================================================================*
 *   program variables;
 *--------------------------------------------------------------------*/

#ifdef NEEDED

int reserved = CWORD_O_NULL;
int operator = COPER_O_NULL;

#endif

int c = (char) (0);
int o = (char) (0);

/*====================================================================*
 *
 *   void function (TEXT *text);
 *   
 *--------------------------------------------------------------------*/

static void function (TEXT *text) 

{

#ifdef NEEDED

	extern int reserved;
	extern int operator;

#endif

	extern int c;
	extern int o;
	while (cgettoken (text) != EOF) 
	{
		printf ("[%c][%c][%s]\n", c, o, text->string);
		cleartext (text);
	}
	return;
}


/*====================================================================*
 *   main program;
 *--------------------------------------------------------------------*/

int main (int argc, char const *argv []) 

{
	static char const * usage [] = 
	{
		"ph",
		PUTOPT_S_FILTER,
		"demonstrate and test C Language token parser",
		"p\tparser report",
		"h\thelp summary ",
		(char *) (0)
	};
	struct _text_ text;
	signed c;
	optind = 1;
	opterr = 1;
	assigntext (&text, _MAXTOKEN, NONE);
	while ((c = getopt (argc, argv, usage [PUTOPT_I_OPTIONS])) != -1) 
	{
		switch (c) 
		{
		case 'p':
			_setbits (text.flags, CFLAG_STATUS);
			break;
		case 'h':
			putopt (usage);
			exit (0);
		case '?':
			exit (1);
		default:
			break;
		}
	}
	if (optind == argc) 
	{
		function (&text);
	}
	while ((optind < argc) && (argv [optind] != (char *) (0))) 
	{
		if (vfopen (argv [optind])) 
		{
			function (&text);
		}
		optind++;
	}
	exit (0);
}

