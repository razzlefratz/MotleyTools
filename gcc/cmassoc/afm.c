/*====================================================================*
 *
 *   afm - assembler format program;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

#define _GETOPT_H

/*====================================================================*
 *   custom header files;
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
#include "../tools/tabs.h"
#include "../chrlib/ascii.h"
#include "../chrlib/chrlib.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE 
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../tools/error.c"
#include "../tools/emalloc.c"
#include "../tools/uintspec.c"
#include "../tools/tabspec.c"
#include "../tools/tabs.c"
#include "../tools/todigit.c"
#include "../files/vfopen.c"
#include "../files/makepath.c"
#include "../files/splitpath.c"
#include "../files/mergepath.c"
#include "../strlib/strcomp.c"
#include "../strlib/strconv.c"
#include "../chrlib/chrupr.c"
#endif

/*====================================================================*
 *   program definitions and declarations;
 *--------------------------------------------------------------------*/

#define COMMENT_COL 40
#define COMMENT_CHR ';'

#define AFM_B_UPPER  (1 << 0)

/*====================================================================*
 *
 *   void func (unsigned column, int cc, flag_t flag);
 *
 *   format an assembly language source file; text is divided into
 *   the source code that precedes the comment character (cc) and
 *   the comments that follow it.
 *
 *   label, opcode, and operand fields are aligned to columns set on
 *   tabstop table (ruler); blank strings found after the rightmost
 *   character are replaced with one blank;
 *
 *   text preceding a comment field is forced to upper case, unless it
 *   is enclosed in either quotes (") or apostophes ('); comment field
 *   text is unaltered except for starting column;
 *
 *   comment text is aligned so that the comment character occurs in
 *   column (col); if neccessary, it is shifted right to preserve the
 *   source code;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void func (unsigned column, signed cc, flag_t flags) 

{ 
	unsigned col = 0; 
	signed pc = 0; 
	signed nc; 
	while ((nc = getc (stdin)) != EOF) 
	{ 
		if (nc == '\n') 
		{ 
			pc = putc (nc, stdout); 
			col = 0; 
		} 
		else if (pc == cc) 
		{ 
			putc (nc, stdout); 
			col++ ; 
		} 
		else if (nc == ',') 
		{ 
			pc = putc (nc, stdout); 
			col++ ; 
			pc = putc (' ', stdout); 
			col++ ; 
		} 
		else if (isquote (nc)) 
		{ 
			putc (nc, stdout); 
			col++ ; 
			if (nc == pc) 
			{ 
				pc = 0; 
			} 
		} 
		else if (nc == cc) 
		{ 
			if (col > 0) 
			{ 
				while (col < column) 
				{ 
					putc (' ', stdout); 
					col++ ; 
				} 
			} 
			pc = putc (nc, stdout); 
			col++ ; 
		} 
		else if (isblank (nc)) 
		{ 
			if (pc != ' ') 
			{ 
				pc = putc (' ', stdout); 
				col++ ; 
			} 
		} 
		else if (pc == ' ') 
		{ 
			while (tabcol (col) == false) 
			{ 
				putc (SP, stdout); 
				col++ ; 
			} 
			pc = putc (_anyset (flags, AFM_B_UPPER)? chrupr (nc):  nc, stdout); 
			col++ ; 
		} 
		else 
		{ 
			pc = putc (_anyset (flags, AFM_B_UPPER)? chrupr (nc):  nc, stdout); 
			col++ ; 
		} 
	} 
	return; 
} 

/*====================================================================*
 *
 *   int main (int argc, char const * argv []);
 *
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv []) 

{ 
	static char const * optv [] = 
	{ 
		"a:c:ut:", 
		PUTOPTV_S_FILTER, 
		"formats assembly language source files", 
		"a n\talign comments to column (n) [" LITERAL (COMMENT_COL) "]", 
		"c c\tcomment character is (c) [" LITERAL (COMMENT_CHR) "]", 
		"u\tconvert opcodes to upper case", 
		"t n.m\ttabspec is (n.m) ", 
		(char const * )(0)
	}; 
	flag_t flags = (flag_t)(0); 
	unsigned column = COMMENT_COL; 
	unsigned character = COMMENT_CHR; 
	signed c; 
	tabset (10, 0); 
	tabset (16, 1); 
	while ((c = getoptv (argc, argv, optv)) != - 1) 
	{ 
		switch (c) 
		{ 
		case 'u': 
			_setbits (flags, AFM_B_UPPER); 
			break; 
		case 'c': 
			character = * optarg; 
			break; 
		case 'a': 
			column = uintspec (optarg, 0, SHRT_MAX); 
			break; 
		case 't': 
			tabspec (optarg); 
			break; 
		default: 
			break; 
		} 
	} 
	argc -= optind; 
	argv += optind; 
	if (! argc) 
	{ 
		func (column, character, flags); 
	} 
	while ((argc) && (* argv)) 
	{ 
		if (vfopen (* argv)) 
		{ 
			func (column, character, flags); 
		} 
		argc-- ; 
		argv++ ; 
	} 
	exit (0); 
} 

