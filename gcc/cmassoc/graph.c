/*====================================================================*
 *
 *   graph.c - print a histogram;
 *
 *   read x and y integer pairs from stdin or from one or more named
 *   files and print a histogram on stdout; each file prints a new 
 *   histogram; input consists of two integers per line seperated by
 *   whitespace; negative values are converted to zero;
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
#include <limits.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../tools/uintspec.c"
#include "../tools/sintspec.c"
#include "../tools/todigit.c"
#include "../tools/efreopen.c"
#include "../tools/error.c"
#include "../tools/error_on_line.c"
#include "../tools/alert.c"
#endif

/*====================================================================*
 *   program constants; 
 *--------------------------------------------------------------------*/

#define GRAPH_TITLE "Distribution"
#define GRAPH_COUNT 10000

#define GRAPH_INVERT (1 << 0)

/*====================================================================*
 *   program variables; 
 *--------------------------------------------------------------------*/

typedef struct graph 

{ 
	char const * title; 
	signed limit; 
	signed count; 
	signed lower; 
	signed upper; 
	signed shift; 
	signed scale; 
} 

GRAPH; 

/*====================================================================*
 *
 *   void display (signed x [], signed y [], signed count, struct graph * graph) 
 *
 *   display datasets x and y as a histogram; level and scale dataset 
 *   y;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void display (signed x [], signed y [], signed count, struct graph * graph) 

{ 
	printf ("%s\n", graph->title); 
	for (graph->count = 0; graph->count < count; graph->count++) 
	{ 
		signed value = * y; 
		printf ("%6d[%6d]", * x++, * y++); 
		if (value < graph->lower) 
		{ 
			graph->lower = value; 
		} 
		if (value > graph->upper) 
		{ 
			graph->upper = value; 
		} 
		value += graph->shift; 
		while (value > (graph->scale >> 1)) 
		{ 
			putc ('#', stdout); 
			value -= graph->scale; 
		} 
		putc ('\n', stdout); 
	} 
	printf ("count=%d ", graph->count); 
	printf ("lower=%d ", graph->lower); 
	printf ("upper=%d ", graph->upper); 
	printf ("shift=%d ", graph->shift); 
	printf ("scale=%d\n", graph->scale); 
	return; 
} 

/*====================================================================*
 *
 *   void arrange (signed x [], signed y [], signed count);
 *
 *   arrange datasets x and y in ascending order by x values using
 *   a bridge player sort; return no value;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void arrange (signed x [], signed y [], signed count) 

{ 
	signed lower; 
	signed upper; 
	signed value; 
	for (upper = 0; upper < count; upper++) 
	{ 
		for (lower = upper; lower > 0; lower--) 
		{ 
			if (x [lower] < x [lower - 1]) 
			{ 
				value = x [lower]; 
				x [lower] = x [lower - 1]; 
				x [lower - 1] = value; 
				value = y [lower]; 
				y [lower] = y [lower - 1]; 
				y [lower - 1] = value; 
			} 
		} 
	} 
	return; 
} 

/*====================================================================*
 *
 *   void collect (char const * filename, unsigned pairs, struct graph * graph, flag_t flags);
 *
 *   read stdin; parse x and y components; arrange and display;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void collect (char const * filename, signed limit, struct graph * graph, flag_t flags) 

{ 
	signed x [limit]; 
	signed y [limit]; 
	signed index = 0; 
	signed value = 0; 
	signed sign = 0; 
	signed line = 1; 
	signed c = getc (stdin); 
	while ((c != EOF) && (index < limit)) 
	{ 
		if ((c == '#') || (c == ';')) 
		{ 
			do 
			{ 
				c = getc (stdin); 
			} 
			while (nobreak (c)); 
		} 
		if (isspace (c)) 
		{ 
			if (c == '\n') 
			{ 
				line++; 
			} 
			c = getc (stdin); 
			continue; 
		} 
		if (c == '-') 
		{ 
			c = getc (stdin); 
			sign = - 1; 
		} 
		else if (c == '+') 
		{ 
			c = getc (stdin); 
			sign = 1; 
		} 
		else 
		{ 
			sign = 1; 
		} 
		if (!isdigit (c)) 
		{ 
			error_on_line (1, EINVAL, filename, line, "x value"); 
		} 
		value = 0; 
		while (isdigit (c)) 
		{ 
			value *= 10; 
			value += c - '0'; 
			c = getc (stdin); 
		} 
		x [index] = sign * value; 
		while (isblank (c)) 
		{ 
			c = getc (stdin); 
		} 
		if (c == '-') 
		{ 
			c = getc (stdin); 
			sign = - 1; 
		} 
		else if (c == '+') 
		{ 
			c = getc (stdin); 
			sign = 1; 
		} 
		else 
		{ 
			sign = 1; 
		} 
		if (!isdigit (c)) 
		{ 
			error_on_line (1, EINVAL, filename, line, "y value"); 
		} 
		value = 0; 
		while (isdigit (c)) 
		{ 
			value *= 10; 
			value += c - '0'; 
			c = getc (stdin); 
		} 
		y [index] = sign * value; 
		while (isblank (c)) 
		{ 
			c = getc (stdin); 
		} 
		if (nobreak (c)) 
		{ 
			error_on_line (1, EINVAL, filename, line, "line end"); 
		} 
		if (x [index] || y [index]) 
		{ 
			index++; 
		} 
	} 
	if (_anyset (flags, GRAPH_INVERT)) 
	{ 
		arrange (y, x, index); 
		display (y, x, index, graph); 
	} 
	else 
	{ 
		arrange (x, y, index); 
		display (x, y, index, graph); 
	} 
	if (index >= limit) 
	{ 
		error (0, 0, "More than %d data items available.", limit); 
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
		"c:o:s:t:x", 
		PUTOPTV_S_FUNNEL, 
		"print a histogram", 
		"c n\tmaximum data points", 
		"o n\tshift data [+|-]", 
		"s n\tscale data", 
		"t s\tgraph title", 
		"x\texchange x and y values", 
		(char const *)(0)
	}; 
	struct graph graph = 
	{ 
		GRAPH_TITLE, 
		0, 
		0, 
		0, 
		0, 
		0, 
		1
	}; 
	signed count = GRAPH_COUNT; 
	flag_t flags = 0; 
	signed c; 
	while ((c = getoptv (argc, argv, optv)) != - 1) 
	{ 
		switch (c) 
		{ 
		case 'c': 
			count = (signed)(uintspec (optarg, 1, INT_MAX)); 
			break; 
		case 'o': 
			graph.shift = (signed)(sintspec (optarg, graph.shift)); 
			break; 
		case 's': 
			graph.scale = (signed)(uintspec (optarg, 1, INT_MAX)); 
			break; 
		case 't': 
			graph.title = optarg; 
			break; 
		case 'x': 
			_setbits (flags, GRAPH_INVERT); 
			break; 
		default: 
			break; 
		} 
	} 
	argc -= optind; 
	argv += optind; 
	if (!argc) 
	{ 
		collect ("stdin", count, & graph, flags); 
	} 
	while ((argc) && (argv)) 
	{ 
		if (efreopen (* argv, "rb", stdin)) 
		{ 
			collect (* argv, count, & graph, flags); 
		} 
		argc--; 
		argv++; 
	} 
	return (0); 
} 

