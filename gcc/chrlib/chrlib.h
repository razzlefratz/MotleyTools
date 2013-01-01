/*====================================================================*
 *
 *   chrlib.h - character table driven definitions and declarations;
 *
 *.  Motley Tools by Charles Maier
 *:  modified sun 07 sep 03 by user root on host zeus;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef CHRLIB_HEADER
#define CHRLIB_HEADER

/*====================================================================*
 *   system include files; 
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <stddef.h>

/*====================================================================*
 *   custom include files; 
 *--------------------------------------------------------------------*/

#include "../tools/types.h"
#include "../tools/chars.h"

/*====================================================================*
 *   custom program features; 
 *--------------------------------------------------------------------*/

#define CHRLIB_ISO_646_1983
#define CHRLIB_EXTENSIONS
#define GLYPH_MAX 12
#define DIGIT_MAX 36
#define CHRLIB_WORDSET "_[:alnum:]$"

/*====================================================================*
 *   table driven character name tables and functions;
 *--------------------------------------------------------------------*/

char * strascii (char *buffer, char const * string);

#define _chrascii(c) (sv_ascii[(unsigned)(c)&(SCHAR_MAX)])

/*====================================================================*
 *   table driven character conversion functions;
 *--------------------------------------------------------------------*/

char chresc (unsigned c);
char chruesc (unsigned c);
void chrtable (const unsigned char table [], FILE *);
void chrtbl (const unsigned char table [], FILE *);
void chrescmap (const unsigned char table [], char escape);
void chruescmap (const unsigned char table [], char escape);

/*====================================================================*
 *   table driven character conversion functions;
 *--------------------------------------------------------------------*/

unsigned char chrupr (unsigned c);
unsigned char chrlwr (unsigned c);
char *strupr (char * string);
char *strlwr (char * string);
signed struprcmp (char const * string1, char const * string2);
signed strlwrcmp (char const * string1, char const * string2);

/*====================================================================*
 *   table driven character conversion functions;
 *--------------------------------------------------------------------*/

char *chrtohex (char * string, unsigned c);
char *chrtoconst (char * string, unsigned c);
char *chrtoietf (char * string, unsigned c);
char *chrtoiso (char * string, unsigned c);
char *chrtohtml (char * string, unsigned c);
char *chrtooctal (char * string, unsigned c);
char *chrtounix (char * string, unsigned c);
char *chrtoesc (char * string, unsigned c);
char *chrtocntrl (char * string, unsigned c);
char *chrtoglyph (char * string, unsigned c);

/*====================================================================*
 *   declare character set expansion function prototypes;
 *--------------------------------------------------------------------*/

void chrset (char ctable []);
void chrdef (char ctable [], char const * charset);
void chrsub (char ctable [], char const * charset, char const * replace);

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

char const * charset (char const * string, signed c, char buffer [], size_t length);
size_t chrindex (char const * string, signed c);
size_t chrcount (char const * string, signed c);
size_t cursor (signed c);

/*====================================================================*
 *   end definitions;
 *--------------------------------------------------------------------*/

#endif

