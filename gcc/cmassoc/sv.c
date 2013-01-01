/*====================================================================*
 *
 *   sv.c - string vector declaration generator;
 *
 *   read a text file of names, one name per line; write a c language 
 *   data declaration that initializes a vector with the names; write 
 *   a #define statement for each name; write a switch statement with
 *   a case statement for each list item;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#define _GETOPT_H

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../strlib/strlib.h"
#include "../chrlib/chrlib.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/console.c"
#include "../tools/fgetline.c"
#include "../tools/efreopen.c"
#include "../tools/uintspec.c"
#include "../tools/todigit.c"
#include "../tools/serial.c"
#include "../tools/indent.c"
#endif

#ifndef MAKEFILE
#include "../strlib/strcomp.c"
#include "../strlib/strconv.c"
#include "../strlib/strselect.c"
#endif

#ifndef MAKEFILE
#include "../chrlib/chrupr.c"
#include "../chrlib/chrlwr.c"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define STRING_MAX 36
#define DIGITS_MAX 3

#define SV_B_DEFINE 0x0001
#define SV_B_VECTOR 0x0002
#define SV_B_SWITCH 0x0004

#define SV_S_RESTRICT "_ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"

/*====================================================================*
 *   program variables;
 *--------------------------------------------------------------------*/

static char *sv_prolog [] = 

{
	"/*================* ",
	" *   ",
	" *   sv_%s [] - ",
	" *   ",
	" *.  ",
	" *:  ",
	" *;  ",
	" *   ",
	" *----------------*/ ",
	" ",
	(char *) (0)
};

static char buffer [TEXTLINE_MAX + 1];
static signed length;
static char *title [2] = 

{
	"symbol",
	"SYMBOL"
};

static signed width = STRING_MAX;
static signed field = 0;
static signed count = 0;

/*====================================================================*
 *   
 *   void function1 (flag_t flags);
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

void function1 (flag_t flags) 

{
	signed margin = 0;
	indent (margin, "/*===*");
	indent (margin, " *   program constants;");
	indent (margin, " *---*/");
	indent (margin, "#ifndef %s", title [1]);
	for (count = 0; fgetline (buffer, sizeof (buffer), stdin) != -1; count++) 
	{
		strselect (strupr (buffer), SV_S_RESTRICT);
		if (*buffer == (char) (0)) 
		{
			serial (buffer, DIGITS_MAX + 1, (char) (0), count);
		}
		indent (margin, "#define %s_O_%-*s %3d", title [1], field, buffer, count);
	}
	indent (margin, "#define %sS  %-*s %3d", title [1], field, "", count);
	indent (margin, "#endif");
	rewind (stdin);
	return;
}


/*====================================================================*
 *   
 *   void function3 (flag_t flags);
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

void function2 (flag_t flags) 

{
	signed margin = 0;
	indent (margin, "/*===*");
	indent (margin, " *   program variables;");
	indent (margin, " *---*/");
	indent (margin, "#ifdef __cplusplus");
	indent (margin, "char const * %s::table [] =", title [0]);
	indent (margin, "const size_t %s::count = (sizeof (%s::table) / sizeof (char const *)) - 1;", title [0], title [0]);
	indent (margin, "#else");
	indent (margin, "#define %sS ((sizeof (sv_%s) / sizeof (char const *)) - 1)", title [1], title [0]);
	indent (margin, "char const * sv_%s [] =", title [0]);
	indent (margin, "#endif");
	indent (margin++, "{");
	for (count = 0; (length = fgetline (buffer, sizeof (buffer), stdin)) != -1; ++count) 
	{
		indent (margin, "\"%s\",", buffer);
	}
	indent (margin, "(char const *)(0)");
	indent (--margin, "};");
	rewind (stdin);
	return;
}


/*====================================================================*
 *   
 *   void function3 (flag_t flags);
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

void function3 (flag_t flags) 

{
	signed margin = 0;
	indent (margin, "/*=*");
	indent (margin, " *   switch statement;");
	indent (margin, " *-*/");
	indent (margin++, "#ifdef %s", title [1]);
	indent (margin, "switch(count)");
	indent (margin++, "{");
	for (count = 0; fgetline (buffer, sizeof (buffer), stdin) != -1; ++count) 
	{
		strselect (strupr (buffer), SV_S_RESTRICT);
		indent (margin++, "case %s_O_%s:", title [1], buffer);
		indent (margin--, "break;");
	}
	indent (margin++, "default:");
	indent (margin--, "break;");
	indent (--margin, "}");
	indent (--margin, "#endif");
	rewind (stdin);
	return;
}


/*====================================================================*
 *   
 *   void function (flag_t flags);
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

void function (flag_t flags) 

{
	for (count = 0; sv_prolog [count]; count++) 
	{
		printf (sv_prolog [count], title [0]);
		printf ("\n");
	}
	if (_anyset (flags, SV_B_DEFINE)) 
	{
		function1 (flags);
	}
	if (_anyset (flags, SV_B_VECTOR)) 
	{
		function2 (flags);
	}
	if (_anyset (flags, SV_B_SWITCH)) 
	{
		function3 (flags);
	}
	return;
}


/*====================================================================*
 *   main program;
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv []) 

{
	static char const * optv [] = 
	{
		"t:dvs",
		PUTOPTV_S_FILTER,
		"create c language string vector declaration and definitions from list",
		"t s\tvector title is (s)",
		"d\tgenerate define block",
		"v\tgenerate vector table",
		"s\tgenerate switch block",
		(char const *) (0)
	};
	flag_t flags = (flag_t)(0);
	signed c;
	while ((c = getoptv (argc, argv, optv)) != -1) 
	{
		switch (c) 
		{
		case 'i':
			width = uintspec (optarg, 0, SHRT_MAX);
			break;
		case 't':
			title [0] = strlwr (strdup (optarg));
			title [1] = strupr (strdup (optarg));
			break;
		case 'd':
			_setbits (flags, SV_B_DEFINE);
			break;
		case 'v':
			_setbits (flags, SV_B_VECTOR);
			break;
		case 's':
			_setbits (flags, SV_B_SWITCH);
			break;
		default:
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if (_allclr (flags, (SV_B_DEFINE | SV_B_VECTOR | SV_B_SWITCH))) 
	{
		_setbits (flags, (SV_B_DEFINE | SV_B_VECTOR | SV_B_SWITCH));
	}
	width &= STRING_MAX;
	field = width - strlen (title [0]) - DIGITS_MAX - 1;
	if (field > width) 
	{
		field = width;
	}
	if (width < DIGITS_MAX) 
	{
		width = DIGITS_MAX;
	}
	if (!argc) 
	{
		function (flags);
	}
	while ((argc) && (* argv)) 
	{
		if (efreopen (* argv, "rb", stdin)) 
		{
			function (flags);
		}
		argc--;
		argv++;
	}
	exit (0);
}

