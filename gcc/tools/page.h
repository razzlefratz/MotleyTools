/*====================================================================*
 *
 *   page.h - 
 *
 *.  Motley Tools by Charles Maier
 *:  modified sun 21 sep 03 by user root on host zeus;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef PAGE_HEADER
#define PAGE_HEADER

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <stdio.h>

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#define PAGE_TITLE "Standard Input"
#define PAGE_ROWS 60
#define PAGE_COLS 78
#define PAGE_TABS 8

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

typedef struct _page_

{
	unsigned flags;
	char const * title;
	unsigned rows;
	unsigned cols;
	unsigned tabs;
	unsigned page;
	unsigned line;
	unsigned row;
	unsigned col;
}

PAGE;

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

void setup_page(PAGE * page);
void reset_page(PAGE * page);
int pageputc(int c, PAGE * page);
char const * pageputs(char const * string, PAGE * page);

/*====================================================================*
 *   end definitions and declarations;
 *--------------------------------------------------------------------*/

#endif



