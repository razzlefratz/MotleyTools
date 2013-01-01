/*====================================================================*
 *
 *   unget.h - 
 *
 *.  Motley Tools by Charles Maier
 *:  modified tue 16 sep 03 by user root on host zeus;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef UNGET_HEADER
#define UNGET_HEADER

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <stdio.h>

/*====================================================================*
 *   
 *--------------------------------------------------------------------*/

int getch (FILE * ifp);
int ungetch (int c, FILE * ifp);
char *getst (char *string, size_t length, FILE * ifp);
int ungetst (char *string, FILE * ifp);

/*====================================================================*
 *   end definitions;
 *--------------------------------------------------------------------*/

#endif

