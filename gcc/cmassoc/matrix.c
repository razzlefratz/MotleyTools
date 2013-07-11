/*====================================================================r
 *
 *   matrix.c - 
 *
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

#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/getoptv.h"
#include "../tools/putoptv.h"
#include "../tools/version.h"
#include "../tools/number.h"
#include "../tools/markup.h"
#include "../tools/format.h"
#include "../tools/error.h"
#include "../tools/types.h"
#include "../tools/sizes.h"
#include "../tools/chars.h"
#include "../linux/linux.h"
#include "../date/date.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../tools/indent.c"
#include "../tools/error.c"
#include "../tools/efreopen.c"
#include "../tools/uintspec.c"
#include "../tools/todigit.c"
#endif

#ifndef MAKEFILE
#include "../linux/hostname.c"
#include "../linux/username.c"
#include "../linux/getusername.c"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define LEVEL 0
#define EMPTY "&nbsp;"
#define MATCH ""
#define TITLE "Matrix"

/*====================================================================*
 *   program variables;
 *--------------------------------------------------------------------*/

typedef struct column 

{ 
	struct column * next; 
	char const * style; 
	char const * label; 
	char * name; 
} 

column; 
static unsigned line = 1; 
static unsigned cols = 0; 
static char string [_NAMESIZE] = ""; 
static char const * style = "matrix"; 
static char const * style_posted = "posted"; 
static char const * style_empty = "empty"; 
static char const * style_match = "match"; 
static char const * label_empty = EMPTY; 
static char const * label_match = MATCH; 

/*====================================================================*
 *
 *   signed gettoken (char * string);
 *
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static signed gettoken (char * string) 

{ 
	extern unsigned line; 
	signed c; 
	do 
	{ 
		c = getc (stdin); 
		if (c == '\n') 
		{ 
			line++ ; 
		} 
	} 
	while (isspace (c)); 
	if (isalpha (c) || (c == '_')) 
	{ 
		do 
		{ 
			* string++ = c; 
			c = getc (stdin); 
		} 
		while (isalnum (c) || (c == '.') || (c == '_') || (c == '-')); 
		ungetc (c, stdin); 
		c = 'A'; 
	} 
	else if (isdigit (c)) 
	{ 
		do 
		{ 
			* string++ = c; 
			c = getc (stdin); 
		} 
		while (isdigit (c) || (c == '.')); 
		ungetc (c, stdin); 
		c = '0'; 
	} 
	else if (isquote (c)) 
	{ 
		char o = getc (stdin); ; 
		while ((o != c) && (c != EOF)) 
		{ 
			if (o == '\\') 
			{ 
				o = getc (stdin); 
			} 
			* string++ = o; 
			o = getc (stdin); 
		} 
	} 
	else 
	{ 
		* string++ = c; 
	} 
	* string++ = (char) (0); 
	return (c); 
} 

/*====================================================================*
 *
 *   static void headers (struct column * column);
 *
 *   read first file statement and store column names;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void headers (struct column * column) 

{ 
	extern char const * style_empty; 
	extern char const * label_empty; 
	extern char string []; 
	if (~ gettoken (string)) 
	{ 
		column->next = (struct column * ) (0); 
		column->name = strdup (string); 
		column->label = label_empty; 
		column->style = style_empty; 
		for (cols = 0; ~ gettoken (string) && (* string != ';'); cols++ ) 
		{ 
			column->next = (struct column * )(malloc (sizeof (struct column))); 
			column = column->next; 
			column->next = (struct column * ) (0); 
			column->name = strdup (string); 
			column->label = label_empty; 
			column->style = style_empty; 
		} 
	} 
	return; 
} 

/*====================================================================*
 *
 *   static void columns (struct column * column);
 *
 *   read next file statement to store row names and match column
 *   headers;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void columns (struct column * column) 

{ 
	extern char const * style_match; 
	extern char const * style_empty; 
	extern char const * label_match; 
	extern char const * label_empty; 
	extern char string []; 
	if (~ gettoken (string)) 
	{ 
		strcpy (column->name, string); 
		while (~ gettoken (string) && (* string != ';')) 
		{ 
			struct column * object; 
			for (object = column->next; object; object = object->next) 
			{ 
				if (! strcmp (object->name, string)) 
				{ 
					object->style = style_match; 
					object->label = * label_match? label_match:  object->name; 
					break; 
				} 
			} 
			if (! object) 
			{ 
				error (0, 0, "%s \"%s\" on line %d is an orphan", column->name, string, line); 
			} 
		} 
	} 
	return; 
} 

/*====================================================================*
 *
 *   void finish (struct column * column);
 *
 *   free memory used to format table;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void finish (struct column * column) 

{ 
	column->style = 0; 
	column->label = 0; 
	free (column->name); 
	while (column->next) 
	{ 
		struct column * object = column->next; 
		column->next = object->next; 
		object->next = (struct column * )(0); 
		object->style = 0; 
		object->label = 0; 
		free (object->name); 
		free (object); 
	} 
	return; 
} 

/*====================================================================*
 *
 *   static unsigned stylesheet (unsigned margin);
 *
 *   print CSS2 stylesheet for HTML page;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static unsigned stylesheet (unsigned margin) 

{ 
	indent (margin, "table { table-layout: fixed; background: transparent; border: solid 1pt black; border-collapse: separate; border-spacing: 1px; font: normal 10pt verdana; }"); 
	indent (margin, "th { background: inherit; border: solid 1pt black; padding: 2px 10px; text-align: center; vertical-align: top; color: maroon; }"); 
	indent (margin, "td { background: inherit; border: solid 1pt black; padding: 2px 10px; text-align: left; vertical-align: top; color: navy; }"); 
	indent (margin, "td.%s { background: #FFFF00; }", style_match); 
	indent (margin, "td.%s { background: #FFFFFF; }", style_empty); 
	indent (margin, "div.%s { text-align: center; margin: 10px; };", style_posted); 
	return (margin); 
} 

/*====================================================================*
 *
 *   unsigned posted ();
 *
 *   output posting date and time plus username and hostname;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static unsigned posted (unsigned margin) 

{ 
	time_t now = time (& now); 
	static char datetime [LOGTIME_LEN]; 
	strftime (datetime, sizeof (datetime), LOGTIME, localtime (& now)); 
	indent (margin++ , "<div class='%s'>", style_posted); 
	indent (margin, "Posted %s on %s by %s", datetime, hostname (), username (getuid ())); 
	indent (margin-- , "</div>"); 
	return (margin); 
} 

/*====================================================================*
 *
 *   unsigned table1 (unsigned margin, char const * string, struct column * column);
 *
 *   print table in HTML format;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static unsigned table1 (unsigned margin, char const * string, struct column * column) 

{ 
	extern unsigned line; 
	extern char const * style; 
	extern char const * style_empty; 
	extern char const * label_empty; 
	struct column * object; 
	line = 1; 
	headers (column); 
	indent (margin++ , "<table class='%s'>", style); 
	indent (margin++ , "<tr class='%s'>", style); 
	indent (margin++ , "<th class='%s'>", style); 
	indent (margin, "%s", column->name); 
	indent (margin-- , "</th>"); 
	for (object = column->next; object; object = object->next) 
	{ 
		indent (margin++ , "<th class='%s'>", style); 
		indent (margin, "%s", object->name); 
		indent (margin-- , "</th>"); 
	} 
	indent (margin-- , "</tr>"); 
	for (columns (column); ! feof (stdin); columns (column)) 
	{ 
		indent (margin++ , "<tr class='%s'>", style); 
		indent (margin++ , "<td class='%s'>", style); 
		indent (margin, "%s", column->name); 
		indent (margin-- , "</td>"); 
		for (object = column->next; object; object = object->next) 
		{ 
			indent (margin++ , "<td class='%s'>", object->style); 
			indent (margin, "%s", object->label); 
			indent (margin-- , "</td>"); 
			object->style = style_empty; 
			object->label = label_empty; 
		} 
		indent (margin-- , "</tr>"); 
	} 
	indent (margin-- , "</table>"); 
	posted (margin); 
	finish (column); 
	return (margin); 
} 

/*====================================================================*
 *
 *   void table2 (unsigned margin, char const * string, struct column * column);
 *
 *   print table in DOCBOOK format;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static unsigned table2 (unsigned margin, char const * string, struct column * column) 

{ 
	extern unsigned line; 
	extern unsigned cols; 
	extern char const * style_empty; 
	extern char const * label_empty; 
	struct column * object; 
	line = 1; 
	headers (column); 
	indent (margin++ , "<table>"); 
	indent (margin++ , "<title>"); 
	indent (margin, "%s", string); 
	indent (margin-- , "</title>"); 
	indent (margin++ , "<tgroup cols='%d'>", cols); 
	indent (margin, "<colspec colname='%s'/>", column->name); 
	for (object = column->next; object; object = object->next) 
	{ 
		indent (margin, "<colspec colname='%s'/>", object->name); 
	} 
	indent (margin++ , "<thead>"); 
	indent (margin++ , "<row>"); 
	indent (margin++ , "<entry>"); 
	indent (margin, "%s", column->name); 
	indent (margin-- , "</entry>"); 
	for (object = column->next; object; object = object->next) 
	{ 
		indent (margin++ , "<entry>"); 
		indent (margin, "%s", object->name); 
		indent (margin-- , "</entry>"); 
	} 
	indent (margin-- , "</row>"); 
	indent (margin-- , "</thead>"); 
	indent (margin++ , "<tbody>"); 
	for (columns (column); ! feof (stdin); columns (column)) 
	{ 
		indent (margin++ , "<row>"); 
		indent (margin++ , "<entry>"); 
		indent (margin, "%s", column->name); 
		indent (margin-- , "</entry>"); 
		for (object = column->next; object; object = object->next) 
		{ 
			indent (margin++ , "<entry>"); 
			indent (margin, "%s", object->label); 
			indent (margin-- , "</entry>"); 
			object->style = style_empty; 
			object->label = label_empty; 
		} 
		indent (margin-- , "</row>"); 
	} 
	indent (margin-- , "</tbody>"); 
	indent (margin-- , "</tgroup>"); 
	indent (margin-- , "</table>"); 
	finish (column); 
	return (margin); 
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
		"de:hl:m:st:", 
		PUTOPTV_S_FUNNEL, 
		"print sparse matrix table", 
		"d\tprint DOCBOOK table on stdout", 
		"e s\tempty label is (s) [" LITERAL (EMPTY) "]", 
		"h\tprint HTML table on stdout", 
		"l n\tindent level is (n) [" LITERAL (LEVEL) "]", 
		"m s\tmatch label is (s) [" LITERAL (MATCH) "]", 
		"s\tprint CSS2 stylesheet on stdout", 
		"t s\ttitle is (s) [" LITERAL (TITLE) "]", 
		(char const * )(0)
	}; 
	unsigned (* table) (unsigned, char const * , struct column * ) = table1; 
	unsigned margin = LEVEL; 
	char const * header = TITLE; 
	struct column column = 
	{ 
		(struct column * ) (0), 
		(char const * )(0), 
		(char const * )(0), 
		(char * )(0)
	}; 
	signed c; 
	while ((c = getoptv (argc, argv, optv)) != - 1) 
	{ 
		switch (c) 
		{ 
		case 'd': 
			table = table2; 
			break; 
		case 'e': 
			label_empty = optarg; 
			break; 
		case 'h': 
			table = table1; 
			break; 
		case 'l': 
			margin = (unsigned)(uintspec (optarg, 0, 16)); 
			break; 
		case 'm': 
			label_match = optarg; 
			break; 
		case 's': 
			stylesheet (margin); 
			return (0); 
		case 't': 
			header = optarg; 
			break; 
		default: 
			break; 
		} 
	} 
	argc -= optind; 
	argv += optind; 
	if (! argc) 
	{ 
		margin = table (margin, header, & column); 
	} 
	while ((argc) && (* argv)) 
	{ 
		if (efreopen (* argv, "rb", stdin)) 
		{ 
			margin = table (margin, header, & column); 
		} 
		argc-- ; 
		argv++ ; 
	} 
	return (0); 
} 

