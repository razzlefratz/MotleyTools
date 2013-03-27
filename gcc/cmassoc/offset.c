/*====================================================================*
 *
 *   offset.c - print offset table;  
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
#include <errno.h>
#include <limits.h>
#include <string.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../tools/markup.h"
#include "../tools/format.h"
#include "../linux/linux.h"
#include "../date/date.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/console.c"
#include "../tools/efreopen.c"
#include "../tools/emalloc.c"
#include "../tools/uintspec.c"
#include "../tools/todigit.c"
#include "../tools/indent.c"
#endif

#ifndef MAKEFILE
#include "../linux/hostname.c"
#include "../linux/username.c"
#include "../linux/getusername.c"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define OFFSET_HTML (1 << 0)
#define OFFSET_PAGE (1 << 1)
#define OFFSET_TEXT (1 << 2)
#define OFFSET_EFSU (1 << 3)
#define OFFSET_BOOK (1 << 4)
#define OFFSET_ZERO (1 << 5)

#define COLUMN 0
#define MARGIN 0

/*====================================================================*
 *   program variables;
 *--------------------------------------------------------------------*/

static char const * style = "offset";
static char const * style_posted = "posted";
static char const * style_offset = "offset";
static char const * style_length = "length";
static char const * style_symbol = "symbol";
static char const * style_string = "string";
static char const * label_offset = "offset";
static char const * label_length = "length";
static char const * label_symbol = "symbol";
static char const * label_string = "description";
static unsigned margin = MARGIN;
static unsigned column = COLUMN;
static unsigned lineno = 0;
static unsigned origin = 0;
static unsigned offset = 0;
static unsigned length = 0;
static char * symbol = (char *)(0);
static char * string = (char *)(0);
static signed c;

/*====================================================================*
 *   
 *   unsigned object ();
 *
 *   scan and parse an object definition;
 *
 *   <definition> := <offset> <symbol> <string>
 *
 *   <symbol> := <alpha> | '_'
 *   <symbol> := <symbol> <alpha> 
 *   <symbol> := <symbol> '-' 
 *   <symbol> := <symbol> '_' 
 *   <symbol> := <symbol> '.' 
 *   <symbol> := <symbol> ':' 
 *   <symbol> := <symbol> '[' <number> ']'
 *
 *   <string> := <alpha> | <digit> | <punct>
 *   <string> := <string> <alpha>
 *   <string> := <string> <digit>
 *   <string> := <string> <punct>
 *   <string> := <string> <blank>
 *   
 *   <number> := <digit>
 *   <number> := <number> <digit>
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static unsigned object () 

{
	extern unsigned lineno;
	extern unsigned length;
	extern char * symbol;
	extern char * string;
	extern signed c;
	unsigned radix = 10;
	unsigned digit = 0;
	unsigned count = 0;
	char * sp;
	char * cp;
	length = 0;
	while (c == '0') 
	{
		c = getc (stdin);
		count++;
	}
	if ((c == 'x') || (c == 'X')) 
	{
		c = getc (stdin);
		radix = 16;
	}
	while ((digit = todigit (c)) < radix) 
	{
		length *= radix;
		length += digit;
		c = getc (stdin);
	}
	while (isblank (c)) 
	{
		c = getc (stdin);
	}
	sp = symbol;
	if (isalpha (c) || (c == '_')) 
	{
		do 
		{
			*sp++ = (char)(c);
			c = getc (stdin);
		}
		while (isalnum (c) || (c == '_') || (c == '-') || (c == '.') || (c == ':'));
	}
	while (isblank (c)) 
	{
		c = getc (stdin);
	}
	if (c == '[') 
	{
		*sp++ = (char)(c);
		c = getc (stdin);
		while (isblank (c)) 
		{
			c = getc (stdin);
		}
		while (isdigit (c)) 
		{
			*sp++ = (char)(c);
			c = getc (stdin);
		}
		while (isblank (c)) 
		{
			c = getc (stdin);
		}
		*sp = (char)(0);
		if (c != ']') 
		{
			error (1, EINVAL, "Have '%s' but need ']' on line %d", symbol, lineno);
		}
		*sp++ = (char)(c);
		c = getc (stdin);
	}
	*sp = (char)(0);
	while (isblank (c)) 
	{
		c = getc (stdin);
	}
	sp = cp = string;
	while (nobreak (c)) 
	{
		*cp++ = (char)(c);
		if (!isspace (c)) 
		{
			sp = cp;
		}
		c = getc (stdin);
	}
	*sp = (char)(0);
	return (count);
}


/*====================================================================*
 *
 *   unsigned stylesheet (unsigned margin);
 *   
 *   print css stylesheet on stdout; this ensures that element class 
 *   names agree;
 *   
 *   table.offset { border: solid 1pt black; border-spacing: 1px; background: white; } 
 *   th.offset, td.offset { border: solid 1pt silver; text-align: right; width: 080px; }
 *   th.length, td.length { border: solid 1pt silver; text-align: right; width: 080px; }
 *   th.symbol, td.symbol { border: solid 1pt silver; text-align: right; width: 300px; }
 *   th.string, td.string { border: solid 1pt silver; }
 *   
 *   table.data { border: solid 1pt black; border-spacing: 1px; background: white; } 
 *   th.base, td.base { border: solid 1pt silver; text-align: right; width: 080px; }
 *   th.size, td.size { border: solid 1pt silver; text-align: right; width: 080px; }
 *   th.name, td.name { border: solid 1pt silver; text-align: right; width: 300px; }
 *   th.text, td.text { border: solid 1pt silver; }
 *   div.posted { text-align: center; margin: 10px; }
 *   
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static unsigned stylesheet (unsigned margin) 

{
	indent (margin, "table { table-layout: fixed; background: transparent; border: solid 1pt black; border-collapse: separate; border-spacing: 1px; font: normal 10pt verdana; }");
	indent (margin, "th { background: inherit; border: solid 1pt silver; padding: 2px 10px; text-align: center; vertical-align: middle; }");
	indent (margin, "td { background: inherit; border: solid 1pt silver; padding: 2px 10px; text-align: left; vertical-align: top; }");
	indent (margin, "td.%s { text-align: right; width: 080px; }", style_offset);
	indent (margin, "td.%s { text-align: right; }", style_length);
	indent (margin, "td.%s { text-align: right; }", style_symbol);
	indent (margin, "td.%s { text-align: left;  }", style_string);
	indent (margin, "div.%s { text-align: center; margin: 10px; };", style_posted);
	return (margin);
}


/*====================================================================*
 *
 *   void posted ();
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void posted () 

{
	time_t now = time (&now);
	static char datetime [LOGTIME_LEN];
	strftime (datetime, sizeof (datetime), LOGTIME, localtime (&now));
	indent (margin++, "<div class='%s'>", style_posted);
	indent (margin, "Posted %s on %s by %s", datetime, hostname (), username (getuid ()));
	indent (margin--, "</div>");
	return;
}


/*====================================================================*
 *   
 *   void html (char const * colors [], unsigned count, flag_t flags);
 *   
 *   
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void html (char const * colors [], unsigned count, flag_t flags) 

{
	extern unsigned lineno;
	extern unsigned margin;
	extern unsigned offset;
	extern unsigned length;
	extern char * symbol;
	extern char * string;
	extern signed c;
	lineno = 1;
	offset = 0;
	length = 0;
	while ((c = getc (stdin)) != EOF) 
	{
		unsigned index;
		if (isspace (c)) 
		{
			if (c == '\n') 
			{
				lineno++;
			}
			continue;
		}
		if ((c == '#') || (c == ';')) 
		{
			do 
			{
				c = getc (stdin);
			}
			while (nobreak (c));
			lineno++;
			continue;
		}
		index = object () % count;
		if (!length) 
		{
			if (offset) 
			{
				indent (margin--, "</table>");
			}
			indent (margin++, "<h2 class='%s'>", style);
			indent (margin, "%s %s", symbol, string);
			indent (margin--, "</h2>");
			indent (margin++, "<table class='%s'>", style);
			indent (margin++, "<tr class='%s'>", style);
			indent (margin++, "<th class='%s'>", style_offset);
			indent (margin, "%s", label_offset);
			indent (margin--, "</th>");
			indent (margin++, "<th class='%s'>", style_length);
			indent (margin, "%s", label_length);
			indent (margin--, "</th>");
			indent (margin++, "<th class='%s'>", style_symbol);
			indent (margin, "%s", label_symbol);
			indent (margin--, "</th>");
			indent (margin++, "<th class='%s'>", style_string);
			indent (margin, "%s", label_string);
			indent (margin--, "</th>");
			indent (margin--, "</tr>");
		}
		else 
		{
			indent (margin++, "<tr class='%s'>", style);
			indent (margin++, "<td class='%s' style='background: %s;'>", style_offset, colors [index]);
			indent (margin, "%08X", offset);
			indent (margin--, "</td>");
			indent (margin++, "<td class='%s' style='background: %s;'>", style_length, colors [index]);
			indent (margin, "%6d", length);
			indent (margin--, "</td>");
			indent (margin++, "<td class='%s' style='background: %s;'>", style_symbol, colors [index]);
			indent (margin, "%s", *symbol? symbol: "&nbsp;");
			indent (margin--, "</td>");
			indent (margin++, "<td class='%s' style='background: %s;'>", style_string, colors [index]);
			indent (margin, "%s", *string? string: "&nbsp;");
			indent (margin--, "</td>");
			indent (margin--, "</tr>");
		}
		offset += length;
		lineno++;
	}
	if (offset) 
	{
		indent (margin--, "</table>");
	}
	posted ();
	return;
}


/*====================================================================*
 *   
 *   void text (flag_t flags);
 *   
 *   
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void text (flag_t flags) 

{
	extern unsigned lineno;
	extern unsigned margin;
	extern unsigned column;
	extern unsigned origin;
	extern unsigned offset;
	extern unsigned length;
	extern char * symbol;
	extern char * string;
	extern signed c;
	lineno = 1;
	origin = 0;
	offset = 0;
	length = 0;
	while ((c = getc (stdin)) != EOF) 
	{
		if (isspace (c)) 
		{
			if (c == '\n') 
			{
				lineno++;
			}
			continue;
		}
		if ((c == '#') || (c == ';')) 
		{
			do 
			{
				c = getc (stdin);
			}
			while (nobreak (c));
			lineno++;
			continue;
		}
		object ();
		if (length) 
		{
			unsigned output = printf (" %08X %10d %s", offset, length, symbol);
			while (output++ < column) 
			{
				putc (' ', stdout);
			}
			if (*string) 
			{
				printf (" (%s)", string);
			}
			printf ("\n");
		}
		else 
		{
			if (offset) 
			{
				printf (" -------- %10d bytes\n\n", offset - origin);
			}
			printf (" -------- %10d %s %s\n", offset, symbol, string);
			origin = offset;
		}
		offset += length;
		lineno++;
	}
	if (offset) 
	{
		printf (" -------- %10d bytes\n\n", offset - origin);
	}
	printf (" %08X  %10d bytes\n", offset, offset);
	return;
}


/*====================================================================*
 *   
 *   void efsu (flag_t flags);
 *   
 *   
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void efsu (flag_t flags) 

{
	extern unsigned lineno;
	extern unsigned margin;
	extern unsigned column;
	extern unsigned origin;
	extern unsigned offset;
	extern unsigned length;
	extern char * symbol;
	extern char * string;
	extern signed c;
	lineno = 1;
	origin = 0;
	offset = 0;
	length = 0;
	while ((c = getc (stdin)) != EOF) 
	{
		if (isspace (c)) 
		{
			if (c == '\n') 
			{
				lineno++;
			}
			continue;
		}
		if ((c == '#') || (c == ';')) 
		{
			do 
			{
				c = getc (stdin);
			}
			while (nobreak (c));
			lineno++;
			continue;
		}
		object ();
		if (length) 
		{
			unsigned column = 0;
			printf ("# %s\n", symbol);
			while (column < length) 
			{
				putc ('0', stdout);
				putc ('0', stdout);
				putc (++column%16? ' ': '\n', stdout);
			}
			if (column%16) 
			{
				putc ('\n', stdout);
			}
		}
		offset += length;
		lineno++;
	}
	return;
}


/*====================================================================*
 *   
 *   void tabs (flag_t flags);
 *   
 *   
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void tabs (flag_t flags) 

{
	extern unsigned lineno;
	extern unsigned margin;
	extern unsigned offset;
	extern unsigned length;
	extern char * symbol;
	extern char * string;
	extern signed c;
	lineno = 1;
	offset = 0;
	length = 0;
	while ((c = getc (stdin)) != EOF) 
	{
		if (isspace (c)) 
		{
			if (c == '\n') 
			{
				lineno++;
			}
			continue;
		}
		if ((c == '#') || (c == ';')) 
		{
			do 
			{
				c = getc (stdin);
			}
			while (nobreak (c));
			lineno++;
			continue;
		}
		object ();
		if (length) 
		{
			printf ("%08X\t%6d\t%s\t%s\n", offset, length, symbol, string);
		}
		else 
		{
			printf ("\n\t\t%s %s\n", symbol, string);
		}
		offset += length;
		lineno++;
	}
	return;
}


/*====================================================================*
 *   
 *   void zero (flag_t flags);
 *   
 *   read object description file and remove leading 0's from length
 *   specifications to remove color coding;
 *   
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void zero (flag_t flags) 

{
	extern signed c;
	while ((c = getc (stdin)) != EOF) 
	{
		if (isspace (c)) 
		{
			putc (c, stdout);
			continue;
		}
		if (c == '0') 
		{
			do 
			{
				c = getc (stdin);
			}
			while (c == '0');
			if (!isdigit (c)) 
			{
				putc ('0', stdout);
			}
		}
		do 
		{
			putc (c, stdout);
			c = getc (stdin);
		}
		while (nobreak (c));
		putc (c, stdout);
	}
	return;
}


/*====================================================================*
 *
 *   void function (char const * colors [], unsigned count, flag_t flags);
 *
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static void function (char const * colors [], unsigned count, flag_t flags) 

{
	if (_anyset (flags, (OFFSET_HTML | OFFSET_PAGE))) 
	{
		html (colors, count, flags);
	}
	else if (_anyset (flags, (OFFSET_TEXT))) 
	{
		tabs (flags);
	}
	else if (_anyset (flags, (OFFSET_EFSU))) 
	{
		efsu (flags);
	}
	else if (_anyset (flags, (OFFSET_ZERO))) 
	{
		zero (flags);
	}
	else 
	{
		text (flags);
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
	extern unsigned margin;
	extern unsigned column;
	static char const * optv [] = 
	{
		"bc:ehl:stz",
		PUTOPTV_S_FUNNEL,
		"print offset table",
		"b\tprint docbook format",
		"c n\talign descriptions to column (n) [" LITERAL (COLUMN) "]",
		"e\tprint efsu format",
		"h\tprint HTML table on stdout",
		"l n\tindent level is (n) [" LITERAL (MARGIN) "]",
		"s\tprint CSS2 stylesheet on stdout",
		"t\tprint text with TAB seperated columns",
		"z\tremove leading zeros",
		(char const *)(0)
	};
	char const * colors [] = 
	{
		"#FFFFFF",
		"#FFFF00",
		"#00FFFF",
		"#00FF00",
		"#FF00FF"
	};
	flag_t flags = (flag_t)(0);
	signed c;
	while ((c = getoptv (argc, argv, optv)) != -1) 
	{
		switch (c) 
		{
		case 'b':
			_setbits (flags, OFFSET_BOOK);
			break;
		case 'c':
			column = uintspec (optarg, 0, UCHAR_MAX);
			break;
		case 'e':
			_setbits (flags, OFFSET_EFSU);
			break;
		case 'h':
			_setbits (flags, OFFSET_HTML);
			break;
		case 'l':
			margin = (unsigned) (uintspec (optarg, 0, 16));
			break;
		case 's':
			stylesheet (margin);
			return (0);
		case 't':
			_setbits (flags, OFFSET_TEXT);
			break;
		case 'z':
			_setbits (flags, OFFSET_ZERO);
			break;
		default:
			break;
		}
	}
	argc -= optind;
	argv += optind;
	symbol = emalloc (SYMBOLSIZE);
	string = emalloc (STRINGSIZE);
	if (!argc) 
	{
		function (colors, sizeof (colors) / sizeof (const char *), flags);
	}
	while ((argc) && (* argv)) 
	{
		if (efreopen (* argv, "rb", stdin)) 
		{
			function (colors, sizeof (colors) / sizeof (const char *), flags);
		}
		argc--;
		argv++;
	}
	return (0);
}

