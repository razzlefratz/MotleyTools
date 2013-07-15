/*====================================================================*
 *
 *   dump.cc - file dump program;
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
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../chrlib/chrlib.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/console.c"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define SIZE (BYTE|WORD)
#define BYTE 0x00
#define WORD 0x01
#define RECD 0x02
#define HEX 16
#define DEC 10
#define OCT  8
#define BIN  2

/*====================================================================*
 *
 *   void fputx(unsigned int value, unsigned radix, int width, char c, FILE *fp);
 *
 *   print an unsigned integer value as a string to a file; right justify
 *   digits within the specified field; left truncate or pad as needed to
 *   satisfy the width specification; use c to pad the field;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void fputx (unsigned value, unsigned radix, int width, char c, FILE * ofp) 

{ 
	if (width-- > 0) 
	{ 
		if ((radix < 2) || (radix > 16)) 
		{ 
			fputx (0, 0, width, c, ofp); 
			fputc (c, ofp); 
		} 
		else if (value < radix) 
		{ 
			fputx (0, 0, width, c, ofp); 
			fputc (DIGITS_HEX [value], ofp); 
		} 
		else 
		{ 
			fputx (value / radix, radix, width, c, ofp); 
			fputc (DIGITS_HEX [value % radix], ofp); 
		} 
	} 
	return; 
} 

/*====================================================================*
 *
 *   void func (int radix, flag_t flag, FILE *ifp, FILE *ofp);
 *
 *   read from stdin and write to stdout; display input file contents as
 *   specified by various combinations of base and flag;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

void func (int radix, flag_t flag, FILE * ifp, FILE * ofp) 

{ 
	char pad, 
	block [BUFSIZ]; 
	unsigned rec; 
	unsigned count; 
	unsigned width; 
	unsigned index; 
	unsigned lower; 
	unsigned upper; 
	unsigned group; 
	unsigned value; 
	switch (radix) 
	{ 
	case BIN: 
		group = 8; 
		width = 8; 
		pad = '0'; 
		break; 
	case OCT: 
		group = 16; 
		width = 4; 
		pad = '0'; 
		break; 
	case DEC: 
		group = 10; 
		width = 3; 
		pad = ' '; 
		break; 
	case HEX: 
		group = 16; 
		width = 2; 
		pad = '0'; 
		break; 
	default: 
		return; 
	} 
	width <<= (flag & (SIZE)); 
	for (rec = 0; (count = read (fileno (ifp), block, BUFSIZ)) > 0; rec++) 
	{ 
		fputs ("\nrecord = ", ofp); 
		fputx (rec, 10, 4, ' ', ofp); 
		fputs ("  length = ", ofp); 
		fputx ((count >> (flag & (SIZE))), 10, 4, ' ', ofp); 
		fputs ("\n", ofp); 
		for (lower = 0; lower < count; lower = upper) 
		{ 
			upper = lower + group; 
			fputc ('\n', ofp); 
			fputc (' ', ofp); 
			fputx ((lower >> (flag & (SIZE))), 16, 4, '0', ofp); 
			fputc (' ', ofp); 
			fputc (' ', ofp); 
			for (index = lower; index < upper; index++) 
			{ 
				switch (flag & (SIZE)) 
				{ 
				case WORD: 
					value = ((value << 8) | (block [index] & UCHAR_MAX)); 
				case BYTE: 
					value = ((value << 8) | (block [index] & UCHAR_MAX)); 
					break; 
				default: 
					value = 0; 
					break; 
				} 
				if (index > count) 
				{ 
					fputx (value, 0, width, ' ', ofp); 
				} 
				else 
				{ 
					fputx (value, radix, width, pad, ofp); 
				} 
				fputc (' ', ofp); 
			} 
			fputc (' ', ofp); 
			for (index = lower; index < upper; index++) 
			{ 
				if ((unsigned) (block [index]) < 0x20) 
				{ 
					fputc ('.', ofp); 
					continue; 
				} 
				if ((unsigned) (block [index]) > SCHAR_MAX) 
				{ 
					fputc ('.', ofp); 
					continue; 
				} 
				fputc (block [index], ofp); 
			} 
		} 
		fputc ('\n', ofp); 
	} 
	return; 
} 

/*====================================================================*
 *   main program
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv []) 

{ 
	static char const * optv [] = 
	{ 
		"wbodx", 
		PUTOPTV_S_FUNNEL, 
		"display file contents using various numeric formats ", 
		"w\tdisplay by word", 
		"b\tdisplay in binary", 
		"o\tdisplay in octal", 
		"d\tdisplay in decimal ", 
		"x\tdisplay in hexidecmal", 
		(char const *)(0)
	}; 
	flag_t flag = BYTE; 
	int base = HEX; 
	signed c; 
	while ((c = getoptv (argc, argv, optv)) != - 1) 
	{ 
		switch (c) 
		{ 
		case 'w': 
			_clrbits (flag, SIZE); 
			_setbits (flag, WORD); 
			break; 
		case 'b': 
			base = BIN; 
			break; 
		case 'o': 
			base = OCT; 
			break; 
		case 'd': 
			base = DEC; 
			break; 
		case 'x': 
			base = HEX; 
			break; 
		default: 
			break; 
		} 
	} 
	argc -= optind; 
	argv += optind; 
	if (!argc) 
	{ 
		func (base, flag, stdin, stdout); 
	} 
	while ((argc) && (* argv)) 
	{ 
		if (freopen (* argv, "rb", stdin)) 
		{ 
			func (base, flag, stdin, stdout); 
		} 
		argc--; 
		argv++; 
	} 
	exit (0); 
} 

