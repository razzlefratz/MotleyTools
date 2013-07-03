/*====================================================================*
 *
 *   symbol.h - 
 *
 *   these are our favorite definitions and declarations; they are used
 *   throughout our software for clarity and consistency; learn to love
 *   them and make them your own;
 *
 *.  Motley Tools by Charles Maier
 *:  modified tue 16 sep 03 by user root on host zeus;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SYMBOL_HEADER
#define SYMBOL_HEADER

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <sys/types.h>
#include <time.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/types.h"

/*====================================================================*
 *   character and string constants;
 *--------------------------------------------------------------------*/

#ifndef NUL
#define NUL ((char)(0))
#endif

#ifndef NIL
#define NIL ("")
#endif

#define CSPACE (' ')
#define CUPPER ('=')
#define CLOWER ('-')
#define CCTRLR ('@')

/*====================================================================*
 *   wildcard pattern matching; 
 *--------------------------------------------------------------------*/

#define MATCH_C_MASK '?'
#define MATCH_C_WILD '*'

/*====================================================================*
 *   string validation macros;
 *--------------------------------------------------------------------*/

#ifndef valid
#define valid(s) (((s)!=(char *)(0))&&(*(s)=!(char)(0)))
#endif

#ifndef empty
#define empty(s) (((s)==(char *)(0))||(*(s)==(char)(0)))
#endif

/*====================================================================*
 *   minimal print routines; write directly to STDOUT or STDERROR
 *--------------------------------------------------------------------*/

#define _cwrite(d,c) write(d,(c),1)
#define _swrite(d,s) write(d,(s),sizeof(s)-1)
#define _ewrite(s) write(STDERR_FILENO,(s),sizeof(s)-1)

signed cread (signed fd);
signed cwrite (signed fd, signed c);

/*====================================================================*
 *   token parsing functions;
 *--------------------------------------------------------------------*/

#define TOKEN_SPACE ' '
#define TOKEN_ALPHA 'A'
#define TOKEN_DIGIT '0'

#ifndef __cplusplus
signed token (char buffer [], size_t length, unsigned * lineno, void * bp, signed get (void * bp), signed unget (signed c, void * bp));
signed value (void * bp, signed get (void * bp), signed unget (signed c, void * bp));
#endif

/*====================================================================*
 *   
 *--------------------------------------------------------------------*/

#ifndef __cplusplus
char const * codename (struct _code_ const list [], size_t size, code_t code, char const * name);
char const * typename (struct _type_ const list [], size_t size, type_t type, char const * name);
code_t namecode (struct _code_ const list [], size_t size, char const * name, code_t code);
type_t nametype (struct _type_ const list [], size_t size, char const * name, type_t type);
size_t typeload (struct _type_ list [], size_t size);
size_t codeload (struct _code_ list [], size_t size);
void codelist (struct _code_ const list [], size_t size, char const * group, char const * comma, FILE *);
void typelist (struct _type_ const list [], size_t size, char const * group, char const * comma, FILE *);
void typesave (struct _type_ const list [], size_t size, char const * name, flag_t);
void codesave (struct _code_ const list [], size_t size, char const * name, flag_t);
#endif

/*====================================================================*
 *   
 *--------------------------------------------------------------------*/

#ifndef __cplusplus
char const * synonym (struct _term_ const list [], size_t size, const char * term);
void synonyms (struct _term_ const list [], size_t size, const char * term, const char * type);
signed getfields (char const * fields [], signed limit, char buffer [], size_t length);
signed getargv (signed argc, char const * argv []);
#endif

/*====================================================================*
 *   
 *--------------------------------------------------------------------*/

#ifndef __cplusplus
signed equate (struct _code_ const list [], size_t size, const char * name, signed fail);
signed lookup (struct _code_ const list [], size_t size, const char * name);
void assist (struct _code_ const list [], size_t size, const char * name, const char * type, FILE *fp);
#endif

/*====================================================================*
 *   
 *--------------------------------------------------------------------*/

#endif

