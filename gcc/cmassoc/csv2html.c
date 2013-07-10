/*====================================================================*
 *
 *   csv2html.c - 
 *
 *   Read a .csv file and write a .html file;
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
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../tools/markup.h"
#include "../tools/format.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/console.c"
#include "../tools/efreopen.c"
#include "../tools/uintspec.c"
#include "../tools/todigit.c"
#include "../tools/indent.c"
#endif

#ifndef MAKEFILE
#include "../files/filepart.c"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define CSV2HTML_HTML (1 << 0)
#define CSV2HTML_PAGE (1 << 1)

#define STYLE "box"

/*====================================================================*
 *   
 *   signed header (signed margin, char const * string);
 *   
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

signed header (signed margin, char const * string) 

{ 
	indent (margin, "<?xml version='%s' encoding='%s'?>", XML_VERSION, XML_CHARSET); 
	indent (margin, "<!doctype html public '%s' '%s'>", W3C_STD, W3C_DTD); 
	indent (margin++ , "<html xmlns='%s' lang='%s'>", XML_NAMESPACE, XML_LANGUAGE); 
	indent (margin++ , "<head>"); 
	indent (margin++ , "<title>"); 
	indent (margin, "%s", string); 
	indent (margin-- , "</title>"); 
	indent (margin, "<meta http-equiv='content-type' content='%s'/>", HTML_CONTENT); 
	indent (margin, "<meta name='generator' content='%s'/>", HTML_PROGRAM); 
	indent (margin, "<meta name='author' content='%s'/>", HTML_AUTHOR); 
	indent (margin, "<meta name='robots' content='%s'/>", HTML_ROBOTS); 
	indent (margin, "<link rel='stylesheet' href='%s' type='%s'/>", CSS_STYLESHEET, CSS_CONTENT); 
	indent (margin++ , "<style type='text/css'>"); 
	indent (margin, "table { table-layout: fixed; background: transparent; border-collapse: separate; border-spacing: 1pt; font: normal 10pt verdana; }"); 
	indent (margin, "th { background: inherit; padding: 2px 10px; text-align: center; vertical-align: middle; }"); 
	indent (margin, "td { background: inherit; padding: 2px 10px; text-align: left; vertical-align: top; }"); 
	indent (margin-- , "</style>"); 
	indent (margin++ , "<style type='text/css'>"); 
	indent (margin, "table.box { border: solid 1pt black; }"); 
	indent (margin, "td.box { border: solid 1pt silver; }"); 
	indent (margin, "th.box { border: solid 1pt silver; }"); 
	indent (margin-- , "</style>"); 
	indent (margin-- , "</head>"); 
	indent (margin++ , "<body>"); 
	return (margin); 
} 

/*====================================================================*
 *   
 *   signed footer (signed margin, char const * string);
 *   
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

signed footer (signed margin, char const * string) 

{ 
	indent (margin-- , "</body>"); 
	indent (margin-- , "</html>"); 
	return (margin); 
} 

/*====================================================================*
 *   
 *   void function (char const * string, size_t column, flag_t flags);
 *   
 *   fields are separated by comma; prefix embedded commas with one
 *   backslash; empty fields are output as "&nbsp;"; an extra comma
 *   should be appeded to lines where the last field is empty;
 *   
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void function (char const * string, size_t column, flag_t flags) 

{ 
	unsigned margin = 2; 
	unsigned row; 
	unsigned col; 
	signed c; 
	char field [_LINESIZE]; 
	char * cp; 
	char * sp; 
	if (_anyset (flags, CSV2HTML_PAGE)) 
	{ 
		margin = header (0, string); 
	} 
	indent (margin++ , "<h1>"); 
	indent (margin, "%s", string); 
	indent (margin-- , "</h1>"); 
	indent (margin++ , "<table class='box'>"); 
	for (row = 0; (c = getc (stdin)) != EOF; row++ ) 
	{ 
		while (isspace (c)) 
		{ 
			c = getc (stdin); 
		} 
		if (c == '#') 
		{ 
			do 
			{ 
				c = getc (stdin); 
			} 
			while (nobreak (c)); 
			continue; 
		} 
		indent (margin++ , "<tr>"); 
		for (col = 0; nobreak (c); col++ ) 
		{ 
			sp = cp = field; 
			while (nobreak (c)) 
			{ 
				if (c == ';') 
				{ 
					c = getc (stdin); 
					break; 
				} 
				if (c == '\\') 
				{ 
					c = getc (stdin); 
					if (c != EOF) 
					{ 
						* cp++ = (char)(c); 
						c = getc (stdin); 
						sp = cp; 
					} 
					continue; 
				} 
				if (c == '\\') 
				{ 
					c = getc (stdin); 
				} 
				if ((c < 0x20) || (c > 0x7E)) 
				{ 
					c = ' '; 
				} 
				if (c == ',') 
				{ 
					* cp++ = '<'; 
					* cp++ = 'b'; 
					* cp++ = 'r'; 
					* cp++ = '/'; 
					* cp++ = '>'; 
					c = getc (stdin); 
				} 
				* cp++ = (char)(c); 
				if (c != ' ') 
				{ 
					sp = cp; 
				} 
				c = getc (stdin); 
			} 
			* sp = (char) (0); 
			if (sp == field) 
			{ 
				strcpy (field, "&nbsp;"); 
			} 
			if (! row) 
			{ 
				indent (margin++ , "<th class='%s'>", STYLE); 
				indent (margin, "%s", field); 
				indent (margin-- , "</th>"); 
			} 
			else 
			{ 
				indent (margin++ , "<td class='%s'>", STYLE); 
				indent (margin, "%s", field); 
				indent (margin-- , "</td>"); 
			} 
			while (isblank (c)) 
			{ 
				c = getc (stdin); 
			} 
		} 
		while (col++ < column) 
		{ 
			if (! row) 
			{ 
				indent (margin++ , "<th class='%s'>", STYLE); 
				indent (margin, "Column%d", col); 
				indent (margin-- , "</th>"); 
			} 
			else 
			{ 
				indent (margin++ , "<td class='%s'>", STYLE); 
				indent (margin, "&nbsp;"); 
				indent (margin-- , "</td>"); 
			} 
		} 
		indent (margin-- , "</tr>"); 
	} 
	indent (margin-- , "</table>"); 
	if (_anyset (flags, CSV2HTML_PAGE)) 
	{ 
		margin = footer (margin, string); 
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
		"n:ps:t", 
		PUTOPTV_S_FUNNEL, 
		"convert .csv data to .html file", 
		"n n\tminimum number of columns", 
		"p\tprint HTML page with header", 
		"s s\tpage title string", 
		"t\tprint HTML table only", 
		(char const * )(0)
	}; 
	char const * string = (char * )(0); 
	char * field = (char * )(0); 
	unsigned length = 1024; 
	unsigned column = 0; 
	flag_t flags = (flag_t)(0); 
	signed c; 
	while ((c = getoptv (argc, argv, optv)) != - 1) 
	{ 
		switch (c) 
		{ 
		case 'l': 
			column = uintspec (optarg, 1, USHRT_MAX); 
			break; 
		case 'n': 
			column = uintspec (optarg, 1, UCHAR_MAX); 
			break; 
		case 'p': 
			_setbits (flags, CSV2HTML_PAGE); 
			break; 
		case 's': 
			string = optarg; 
			break; 
		case 't': 
			_setbits (flags, CSV2HTML_HTML); 
			break; 
		default: 
			break; 
		} 
	} 
	argc -= optind; 
	argv += optind; 
	if (! (field = malloc (length))) 
	{ 
		error (1, errno, "Can't allocate %u bytes", length); 
	} 
	if (! argc) 
	{ 
		if (! string) 
		{ 
			string = "untitled"; 
		} 
		function (string, column, flags); 
	} 
	while ((argc) && (* argv)) 
	{ 
		if (efreopen (* argv, "rb", stdin)) 
		{ 
			if (! string) 
			{ 
				string = filepart (* argv); 
			} 
			function (string, column, flags); 
		} 
		argc-- ; 
		argv++ ; 
	} 
	return (0); 
} 

