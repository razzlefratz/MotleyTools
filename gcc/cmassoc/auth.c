/*====================================================================*
 *
 *   auth.c - print auth.log statistics
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
#include <ctype.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../clang/clang.h"
#include "../linux/linux.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../tools/efreopen.c"
#include "../tools/error.c"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define BUFFER_SIZE 1024
#define VECTOR_SIZE 100

/*====================================================================*
 *   program variables;
 *--------------------------------------------------------------------*/

struct _record_

{
	struct _record_ * next;
	char * vector [VECTOR_SIZE];
	char buffer [BUFFER_SIZE];
	size_t count;
};

struct _column_

{
	size_t number;
	char * string;
};

struct _column_ rootuser [] = 

{
	{
		5,
		"Failed"
	},
	{
		8,
		"root"
	},
	{
		- 1,
		""
	}
};

struct _column_ rootlist [] = 

{
	{
		0,
		"date"
	},
	{
		8,
		"user"
	},
	{
		10,
		"host"
	},
	{
		- 1,
		""
	}
};

/*====================================================================*
 *
 *   void func (char * buffer, size_t length, size_t extent, unsigned start, flag_t flags);
 *
 *   read from ifp and write to ofp; modify marked c language comment lines
 *   to creaate clear section breaks and standard program annotations;
 *
 *   replace occurances of [/@...@] and [ @...@/] comments with standard
 *   length bars;
 *
 *   delete empty lines at the start of the file; append one empty line to the 
 *   end of the file if missing; remove redundant empty lines elsewhere; insert
 *   an empty line before and after cmassoc comment blocks; 
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

void function (struct _column_ columns [], struct _column_ outputs [], flag_t flags)

{
	struct _column_ * column;
	struct _record_ * record;
	struct _record_ one;
	struct _record_ two;
	char ** vector;
	char * string;
	one.next = & two;
	two.next = & one;
	record = & two;
	for (string = record->buffer; fgets (string, BUFFER_SIZE, stdin) != (char *) (0); string = record->buffer)
	{
		vector = record->vector;
		for (* vector++ = string; (* string != (char) (0)) && ((string - record->buffer) < (BUFFER_SIZE - 1)); string++)
		{
			if (isspace (* string) && ((vector - record->vector) < (VECTOR_SIZE - 1)))
			{
				* vector++ = string +  1;
				* string = (char) (0);
			}
		}
		* vector = (char *) (0);
		for (column = columns; column->number != - 1; column++)
		{
			if (strcmp (record->vector [column->number], column->string))
			{
				break;
			}
		}
		if (column->number == - 1)
		{
			for (column = outputs; column->number != - 1; column++)
			{
				printf ("%4lu %s:%s\n", (long unsigned) (column->number), column->string, record->vector [column->number]);
			}
			printf ("\n");
		}
		record = record->next;
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
		"",
		PUTOPTV_S_FUNNEL,
		"print auth.log statistics",
		(char const *) (0)
	};
	struct _column_ * columns = rootuser;
	struct _column_ * outputs = rootlist;
	flag_t flags = (flag_t) (0);
	signed c;
	while (~ (c = getoptv (argc, argv, optv)))
	{
		switch (c)
		{
		default: 
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if (! argc)
	{
		function (columns, outputs, flags);
	}
	while ((argc) && (* argv))
	{
		if (efreopen (* argv, "rb", stdin))
		{
			function (columns, outputs, flags);
		}
		argc--;
		argv++;
	}
	exit (0);
}

