/*====================================================================*
 *
 *   tabs.h - definitions for tab column set/clear functions (tabdef.c);
 *
 *.  Motley Tools by Charles Maier
 *:  modified sun 07 sep 03 by user root on host zeus;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef TABS_HEADER
#define TABS_HEADER

/*====================================================================*
 *   system header files
 *--------------------------------------------------------------------*/

#include <stddef.h>

/*====================================================================*
 *  custom header files
 *--------------------------------------------------------------------*/

#include "../tools/tools.h"
#include "../tools/types.h"

/*====================================================================*
 *   declare constants;
 *--------------------------------------------------------------------*/

#define TABS_L_RULER 0x100
#define TABS_O_SPACE 8

/*====================================================================*
 *   prototype tabstop functions;
 *--------------------------------------------------------------------*/

void putruler(size_t length);
void tabrule(size_t length);
char * tabspec(char const * string);
bool tabset(size_t column, int offset);
bool tabcol(size_t column);
size_t tabend(size_t column);

/*====================================================================*
 *   end definitions;
 *--------------------------------------------------------------------*/

#endif



