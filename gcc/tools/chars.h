/*====================================================================*:wq
 *
 *   chars.h - character selection and matcing macros; 
 *
 *.  Motley Tools by Charles Maier
 *:  modified sun 07 sep 03 by user root on host zeus;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef CHARS_HEADER
#define CHARS_HEADER

#include <ctype.h>

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#ifndef isblank
#define isblank(c) (((char)(c) == ' ') || ((char)(c) == '\t'))
#endif

#ifndef nobreak
#define nobreak(c) ((char)(c) != '\0') && ((char)(c) != '\r') && ((char)(c) != '\n') && ((int)(c) != EOF)
#endif

#ifndef nocomma
#define nocomma(c) (((char)(c) != ',') && ((char)(c) != ';') && ((char)(c) != ':'))
#endif

#ifndef nomatch
#define nomatch(c,o) ((char)(c) != (char)(o)) && ((int)(c) != EOF)
#endif

#ifndef isquote
#define isquote(c) ((char)(c) == '\'') || ((char)(c) == '\"')
#endif

#ifndef isslash
#define isslash(c) ((char)(c) == '/') || ((char)(c) == '\\')
#endif

#ifndef isident
#define isident(c) (isalnum (c) || ((char)(c) == '_'))
#endif

#ifndef iscomma
#define iscomma(c) (((char)(c) == ',') || ((char)(c) == ';') || ((char)(c) == ':'))
#endif

#ifndef isoctal
#define isoctal(c) ((char)(c) >= '0') && ((char)(c) <= '7')
#endif

/*====================================================================*
 *   end definitions;
 *--------------------------------------------------------------------*/

#endif



