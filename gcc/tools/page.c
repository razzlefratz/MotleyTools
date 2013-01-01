/*====================================================================*
 *
 *   void setup_page(FILE *fp);
 *
 *   This function creates a page control block and associates it with
 *   a file pointer. Internal page controls are initialized to default
 *   values which may then be changed using macros defined in PAGE.H.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef PAGE_SOURCE
#define PAGE_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>

#include "../tools/tools.h"
#include "../tools/page.h"
#include "../date/date.h"

/*====================================================================*
 *   variables;
 *--------------------------------------------------------------------*/

struct _page_ page = 

{
	0,
	PAGE_TITLE,
	PAGE_ROWS,
	PAGE_COLS,
	PAGE_TABS,
	1,
	1,
	0,
	0
};


/*====================================================================*
 *
 *   void setup_page (PAGE * page);
 *
 *   This function creates a page control block and associates it with
 *   a file pointer. Internal page controls are initialized to default
 *   values which may then be changed using macros defined in PAGE.H.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

void setup_page (PAGE * page) 

{
	page->flags = 0;
	page->title = PAGE_TITLE;
	page->rows = PAGE_ROWS;
	page->cols = PAGE_COLS;
	page->tabs = PAGE_TABS;
	page->page = 1;
	page->line = 1;
	page->row = 0;
	page->col = 0;
	return;
}


/*====================================================================*
 *
 *   void reset_page(PAGE * page);
 *
 *   This function resets page, line and column counters in preparation
 *   for a new output listing. Other page characteristics are unchanged.
 * 
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

void reset_page (PAGE * page) 

{
	page->page = 1;
	page->line = 1;
	page->row = 0;
	page->col = 0;
	return;
}


/*====================================================================*
 *
 *   void header (struct _page_ * page);
 *
 *   print pagination header on stdout; the header does not affect
 *   current row or column counters; one blank line separates text
 *   from the header;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

static void header (struct _page_ * page) 

{
	char buffer [page->cols];
	time_t stamp = time ((time_t *)(0));
	signed length;
	signed offset;
	length = page->cols - DAYTIME_LEN - 2;
	length = snprintf (buffer, page->cols, "%-*.*s  ", length, length, page->title);
	for (offset = 0; offset < length; offset++) 
	{
		putc (buffer [offset], stdout);
	}
	length = strftime (buffer, sizeof (buffer), DAYTIME, localtime (&stamp));
	for (offset = 0; offset < length; offset++) 
	{
		putc (buffer [offset], stdout);
	}
	putc ('\n', stdout);
	putc ('\n', stdout);
	return;
}


/*====================================================================*
 *
 *   void footer (struct _page_ * page);
 * 
 *   print pagination footer on stdout; the footer does not affect
 *   current row or column counters; one blank line separates text
 *   from the footer;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

static void footer (struct _page_ * page) 

{
	char buffer [page->cols];
	signed length = snprintf (buffer, page->cols, "- %d -", page->page);
	signed offset = page->cols;
	if (length < offset) 
	{
		offset -= length;
		offset /= 2;
	}
	else 
	{
		length = offset;
		offset = 0;
	}
	putc ('\n', stdout);
	while (offset > 0) 
	{
		putc (' ', stdout);
		offset--;
	}
	while (length > 0) 
	{
		putc (buffer [offset++], stdout);
		length--;
	}
	putc ('\n', stdout);
	return;
}


/*====================================================================*
 *
 *   signed pageputc (signed c, struct _page_ * page); 
 *
 *   paginate one character to stdout; return the character value;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed pageputc (signed c, struct _page_ * page) 

{
	if (!page->row && !page->col) 
	{
		header (page);
		page->row = 1;
		page->col = 1;
	}
	if ((c == '\f') || (c == EOF)) 
	{
		while (page->row < page->rows) 
		{
			pageputc ('\n', page);
		}
		footer (page);
		page->page++;
		page->row = 0;
		page->col = 0;
	}
	else if (c == '\r') 
	{
		putc (c, stdout);
		page->col = 1;
	}
	else if (c == '\n') 
	{
		putc (c, stdout);
		page->line++;
		page->row++;
		page->col = 1;
	}
	else if (c == '\t') 
	{
		while (page->col % page->tabs) 
		{
			pageputc (' ', page);
		}
		pageputc (' ', page);
	}
	else if (iscntrl (c)) 
	{
		putc (' ', stdout);
		page->col++;
	}
	else 
	{
		putc (c, stdout);
		page->col++;
	}
	if (page->col > page->cols) 
	{
		pageputc ('\n', page);
	}
	if (page->row > page->rows) 
	{
		pageputc ('\f', page);
	}
	return (c);
}


#endif

