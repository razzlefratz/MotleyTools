/*====================================================================*
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

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#ifndef isblank
#define isblank(c) (((c) == ' ') || ((c) == '\t'))
#endif

#ifndef isquote
#define isquote(c) (((char)(c) == '\'') || ((char)(c) == '\"'))
#endif

#ifndef isoctal
#define isoctal(c) (((char)(c) >= '0') && ((char)(c) <= '7'))
#endif

#ifndef isvalid
#define isvalid(c) (((int)(c) != EOF) && ((char)(c) != (char)(0)))
#endif

#ifndef isbreak
#define isbreak(c) (((int)(c) == EOF) || ((char)(c) == (char)(0)) || ((char)(c) == '\n'))
#endif

#ifndef nobreak
#define nobreak(c) (((int)(c) != EOF) && ((char)(c) != (char)(0)) && ((char)(c) != '\n'))
#endif

#ifndef nomatch
#define nomatch(c,o) (((int)(c) != EOF) && ((char)(c) != (char)(0)) && ((char)(c) != (char)(o)))
#endif

#ifdef NEEDED
#ifndef islatin
#define islatin(c) (((c) == ' ') || ((c) == '\t') || ((c) == '\r') || ((c) == '\n') || (((unsigned)(c) > 32) && ((unsigned)(c) < 127)) || (((unsigned)(c) > 159) && ((unsigned)(c) < 256)))
#endif
#endif

/*====================================================================*
 *   end definitions;
 *--------------------------------------------------------------------*/

#endif

