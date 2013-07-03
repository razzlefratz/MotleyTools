/*====================================================================*
 *
 *   tidy.h - 
 *
 *.  Motley Tools by Charles Maier
 *:  modified tue 16 sep 03 by user root on host zeus;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef TIDY_HEADER
#define TIDY_HEADER

/*====================================================================*
 *  constant declaration; 
 *--------------------------------------------------------------------*/

#define TIDY_S_MARGIN ""
#define TIDY_S_OFFSET "\t"
#define TIDY_S_FINISH ""
#define TIDY_S_RECORD "\n"

#define TIDY_B_RECORD (1 << 0)
#define TIDY_B_INDENT (1 << 1)
#define TIDY_B_INSERT (1 << 2)

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#ifndef isblank
// #if ! defined (__GNUC__) && ! defined (__APPLE__)
#define isblank(c) (((char)(c) == ' ') || ((char)(c) == '\t'))
// #endif
#endif

#ifndef nobreak
#define nobreak(c) ((char)(c) != '\r') && ((char)(c) != '\n') && ((int)(c) != EOF)
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
 *  function declarations; 
 *--------------------------------------------------------------------*/

signed content (signed c);
signed escaped (signed c);
signed fortran (signed c);
signed comment (signed c);
signed mention (signed c);
signed advance (signed c);
signed nothing (signed c);
signed literal (signed c);
signed context (signed c, signed e);
signed control (signed c, signed e);
signed discard (signed c, signed e);
signed collect (signed c, signed e);
signed divider (signed c, unsigned width);
void newline (signed align);
void endline (signed space);
signed nocomment (signed c);
signed nocontext (signed c, signed e);
signed nocontent (signed c, signed e);
signed noliteral (signed e);
signed noescaped (signed c);
signed consume (signed e);
signed connect (signed c);
signed span (signed c);
signed keep (signed c);
signed find (signed c);

/*====================================================================*
 *   end definitions;
 *--------------------------------------------------------------------*/

#endif


