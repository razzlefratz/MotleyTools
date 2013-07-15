/*====================================================================*
 *
 *   catalog.c - 
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
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../tools/format.h"
#include "../tools/markup.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../tools/emalloc.c"
#include "../tools/uintspec.c"
#include "../tools/todigit.c"
#include "../tools/indent.c"
#include "../tools/error.c"
#endif

#ifndef MAKEFILE
#include "../files/vfopen.c"
#include "../files/makepath.c"
#include "../files/splitpath.c"
#include "../files/mergepath.c"
#include "../files/filepart.c"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define CATALOG_COLUMN 5
#define CATALOG_STYLESHEET "catalog.css"
#define CATALOG_INDEX (1 << 0)
#define CATALOG_TOPIC (1 << 1)
#define CATALOG_GLYPH (1 << 2)
#define CATALOG_DELETE (1 << 3)

/*====================================================================*
 *   program variables;
 *--------------------------------------------------------------------*/

typedef struct page 

{ 
	struct page * prev; 
	struct page * home; 
	struct page * next; 
	char const * file; 
	char const * path; 
	char const * name; 
} 

page; 

/*====================================================================*
 *
 *   void pagelink (unsigned level, struct page * page, char const * link);
 *
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

void pagelink (unsigned level, struct page * page, char const * link) 

{ 
	indent (level, "[<a href='%s' title=' %s '>%s</a>]", page->path, page->name, link); 
	return; 
} 

/*====================================================================*
 *
 *   signed header (signed margin, struct page * page);
 *
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static signed header (signed margin, struct page * page, char const * stylesheet) 

{ 
	indent (margin, "<?xml version='%s' encoding='%s'?>", XML_VERSION, XML_CHARSET); 
	indent (margin, "<!doctype html public '%s' '%s'>", W3C_STD, W3C_DTD); 
	indent (margin++, "<html xmlns='%s' lang='%s'>", XML_NAMESPACE, XML_LANGUAGE); 
	indent (margin++, "<head>"); 
	indent (margin++, "<title>"); 
	indent (margin, "%s", page->name); 
	indent (margin--, "</title>"); 
	indent (margin, "<meta http-equiv='content-type' content='%s'/>", HTML_CONTENT); 
	indent (margin, "<meta name='generator' content='%s'/>", HTML_PROGRAM); 
	indent (margin, "<meta name='author' content='%s'/>", HTML_AUTHOR); 
	indent (margin, "<meta name='robots' content='%s'/>", HTML_ROBOTS); 
	indent (margin, "<link href='%s' rel='stylesheet' type='%s'/>", stylesheet, CSS_CONTENT); 
	indent (margin--, "</head>"); 
	indent (margin++, "<body>"); 
	indent (margin++, "<div class='%s'>", STYLE_TOPLINK); 
	pagelink (margin, page->prev, HTML_PREV); 
	pagelink (margin, page->home, HTML_HOME); 
	pagelink (margin, page->next, HTML_NEXT); 
	indent (margin--, "</div>"); 
	return (margin); 
} 

/*====================================================================*
 *
 *   signed footer (signed margin, struct page * page);
 *
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static signed footer (signed margin, struct page * page) 

{ 
	indent (margin++, "<div class='%s'>", STYLE_BOTLINK); 
	pagelink (margin, page->prev, HTML_PREV); 
	pagelink (margin, page->home, HTML_HOME); 
	pagelink (margin, page->next, HTML_NEXT); 
	indent (margin--, "</div>"); 
	indent (margin--, "</body>"); 
	indent (margin--, "</html>"); 
	return (margin); 
} 

/*====================================================================*
 *
 *   void htmlindex (struct page * page, char const * stylesheet, unsigned group, flag_t flags);
 *
 *   traverse a page list and write an index page on stdout;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

void htmlindex (struct page * page, char const * stylesheet, unsigned group, flag_t flags) 

{ 
	unsigned margin = 0; 
	unsigned count = 0; 
	unsigned index = 0; 
	if (!group) 
	{ 
		return; 
	} 
	if (_anyset (flags, CATALOG_INDEX)) 
	{ 
		margin = header (margin, page, stylesheet); 
		indent (margin++, "<h1>"); 
		indent (margin, "%s", page->name); 
		indent (margin--, "</h1>"); 
	} 
	indent (margin++, "<table>"); 
	indent (margin++, "<tr valign='top'>"); 
	for (page = page->next; page != page->home; page = page->next) 
	{ 
		count++; 
	} 
	count = (count + group - 1)/ group; 
	indent (margin++, "<td>"); 
	indent (margin++, "<ol start='1'>"); 
	for (page = page->next; page != page->home; page = page->next) 
	{ 
		if ((index) && (index % count == 0)) 
		{ 
			indent (margin--, "</ol>"); 
			indent (margin--, "</td>"); 
			indent (margin++, "<td>"); 
			indent (margin++, "<ol start='%d'>", index + 1); 
		} 
		indent (margin++, "<li class='index'>"); 
		indent (margin, "<a href='%s'>%s</a>", page->path, page->name); 
		indent (margin--, "</li>"); 
		index++; 
	} 
	indent (margin--, "</ol>"); 
	indent (margin--, "</td>"); 
	indent (margin--, "</tr>"); 
	indent (margin--, "</table>"); 
	if (_anyset (flags, CATALOG_INDEX)) 
	{ 
		margin = footer (margin, page); 
	} 
	return; 
} 

/*====================================================================*
 *
 *   void htmltopic (struct page * page, char const * stylesheet, flag_t flags);
 *
 *   traverse a page list and write a page to stdout; a page contains
 *   the original input file enclosed in an html <pre>...</pre> block
 *   with upper and lower navigation links; 
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

void htmltopic (struct page * page, char const * stylesheet, flag_t flags) 

{ 
	unsigned margin = 0; 
	signed c = getc (stdin); 
	margin = header (margin, page, stylesheet); 
	indent (0, "<pre>"); 
	while (c != EOF) 
	{ 
		if ((c == '\n') || (c == '\r')) 
		{ 
			while ((c == '\n') || (c == '\r')) 
			{ 
				c = getc (stdin); 
			} 
			putc ('\n', stdout); 
		} 
		while ((c != '\n') && (c != '\r') && (c != EOF)) 
		{ 
			if (_anyset (flags, CATALOG_GLYPH)) 
			{ 
				if (c == '&') 
				{ 
					fputs ("&amp;", stdout); 
					c = getc (stdin); 
					continue; 
				} 
				if (c == '<') 
				{ 
					fputs ("&lt;", stdout); 
					c = getc (stdin); 
					continue; 
				} 
				if (c == '>') 
				{ 
					fputs ("&gt;", stdout); 
					c = getc (stdin); 
					continue; 
				} 
				if (c == '\"') 
				{ 
					fputs ("&quot;", stdout); 
					c = getc (stdin); 
					continue; 
				} 

#if 0

/*
 * IE does not support this glyph notation;
 */

				if (c == '\'') 
				{ 
					fputs ("&apos;", stdout); 
					c = getc (stdin); 
					continue; 
				} 

#endif

			} 
			putc (c, stdout); 
			c = getc (stdin); 
		} 
		if (c == '\r') 
		{ 
			c = getc (stdin); 
			if (c != '\n') 
			{ 
				ungetc (c, stdin); 
			} 
		} 
		putc ('\n', stdout); 
		c = getc (stdin); 
	} 
	indent (0, "</pre>"); 
	margin = footer (margin, page); 
	return; 
} 

/*====================================================================*
 *
 *   void function (struct page * page, char const * stylesheet, unsigned group, flag_t flags);
 *
 *   traverse a page list and produce a set of linked html pages plus 
 *   an index;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

void function (struct page * page, char const * stylesheet, unsigned group, flag_t flags) 

{ 
	htmlindex (page, stylesheet, group, flags); 
	for (page = page->next; page != page->home; page = page->next) 
	{ 
		if (!freopen (page->file, "rb", stdin)) 
		{ 
			error (0, errno, "Can't open %s for input", page->file); 
			continue; 
		} 
		if (!freopen (page->path, "wb", stdout)) 
		{ 
			error (0, errno, "Can't open %s for output", page->path); 
			continue; 
		} 
		htmltopic (page, stylesheet, flags); 
		if (_anyset (flags, CATALOG_DELETE)) 
		{ 
			if (remove (page->file)) 
			{ 
				error (0, errno, "Can't delete %s", page->file); 
			} 
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
		"c:dgin:p:s:", 
		PUTOPTV_S_FILTER, 
		"produce a set of linked html pages with index page", 
		"c n\tindex column count is n [" LITERAL (CATALOG_COLUMN) "]", 
		"d\tdelete source files after conversion", 
		"g\treplace selected punctuation with IETF/HTML/ISO glyphs", 
		"i\tproduce an index page", 
		"n s\tindex page name is s [" HTML_NAME "]", 
		"p f\tindex page path is f [" HTML_PATH "]", 
		"s f\tstylesheet path is f [" CATALOG_STYLESHEET "]", 
		(char *) (0)
	}; 
	unsigned column = CATALOG_COLUMN; 
	char filename [FILENAME_MAX]; 
	char const * stylesheet = CATALOG_STYLESHEET; 
	struct page * page = NEW (struct page); 
	struct page * temp; 
	flag_t flags = (flag_t) (0); 
	signed c; 
	page->prev = page; 
	page->home = page; 
	page->next = page; 
	page->file = HTML_PATH; 
	page->path = HTML_PATH; 
	page->name = HTML_NAME; 
	while ((c = getoptv (argc, argv, optv)) != - 1) 
	{ 
		switch (c) 
		{ 
		case 'c': 
			column = uintspec (optarg, 1, 12); 
			break; 
		case 'd': 
			_setbits (flags, CATALOG_DELETE); 
			break; 
		case 'g': 
			_setbits (flags, CATALOG_GLYPH); 
			break; 
		case 'i': 
			_setbits (flags, CATALOG_INDEX); 
			break; 
		case 'n': 
			page->name = optarg; 
			break; 
		case 'p': 
			page->path = optarg; 
			break; 
		case 's': 
			stylesheet = optarg; 
			break; 
		default: 
			break; 
		} 
	} 
	argc -= optind; 
	argv += optind; 
	if (!argc) 
	{ 
		function (page, stylesheet, column, flags); 
		free (page); 
		return (0); 
	} 
	while ((argc) && (* argv)) 
	{ 
		temp = NEW (struct page); 
		temp->prev = page->prev; 
		temp->prev->next = temp; 
		temp->next = page; 
		temp->home = page; 
		page->prev = temp; 
		temp->name = filepart (* argv); 
		temp->file = filepart (* argv); 
		strcpy (filename, temp->file); 
		strcat (filename, ".html"); 
		temp->path = strdup (filename); 
		argc--; 
		argv++; 
	} 
	function (page, stylesheet, column, flags); 
	while (page->next != page->home) 
	{ 
		temp = page->next; 
		page->next = temp->next; 
		temp->next->prev = page; 
		temp->prev = (struct page *)(0); 
		temp->next = (struct page *)(0); 
		free ((char *)(temp->path)); 
		free (temp); 
	} 
	free (page); 
	return (0); 
} 

