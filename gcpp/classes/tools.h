/*====================================================================*
 *
 *   tools.h - a sorted array of delightful and charming definitions and 
 *   declarations for your programming pleasure;
 *
 *   these are our favorite definitions and declarations; they are used
 *   throughout our software for clarity and consistency; learn to love
 *   them and make them your own;
 *
 *.  published 2003 by charles maier associates limited for internal use;
 *:  modified tue 16 sep 03 by user root on host zeus;
 *;  compiled for debian gnu/linux using gcc compiler;
 *
 *--------------------------------------------------------------------*/

#ifndef TOOLS_HEADER
#define TOOLS_HEADER
 
/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <sys/types.h>
#include <time.h>
 
/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/types.h"
#include "../classes/sizes.h"
 
/*====================================================================*
 *   comparison and conversion constants;
 *--------------------------------------------------------------------*/

#ifndef NONE
#define NONE (signed)(0)
#endif

#ifndef VOID
#define VOID (unsigned)(-1)
#endif

#ifndef HUGE
#if 0

// already defined somewhere. drat! 
// some brian kernighan fan, no doubt. 
// #define HUGE ((unsigned short)(-1)) 
// #define HUGE (0x7FFF)
#define HUGE ((unsigned)(-1))
#endif
#endif

#ifndef MORE
#define MORE (signed)(1)
#endif

#ifndef LESS
#define LESS (signed)(-1)
#endif

#ifndef POS
#define POS (signed)(1)
#endif

#ifndef NEG
#define NEG (signed)(-1)
#endif

#ifndef EOF
#define EOF (signed)(-1)
#endif

#ifndef END
#define END (signed)(-1)
#endif

#ifndef ERR
#define ERR (signed)(-1)
#endif
 
/*====================================================================*
 *   character and string constants;
 *--------------------------------------------------------------------*/

#ifndef NUL
#define NUL ((char)(0))		       // empty character */
#endif

#ifndef NIL
#define NIL ("")		       // empty character string */
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
 *   symbolic names for some generic command delimiters; 
 *--------------------------------------------------------------------*/

#define ITEM_C_EXTENDER (':')
#define ITEM_S_EXTENDER (":")
#define LIST_C_EXTENDER (';')
#define LIST_S_EXTENDER (";")

#define TOOLS_B_NUMBER (1 << 0)
#define TOOLS_B_DEFINE (1 << 1)
#define TOOLS_B_DECLARE (1 << 2)
#define TOOLS_B_SWITCH (1 << 3)
#define TOOLS_B_SAMPLE (TOOLS_B_DEFINE|TOOLS_B_DECLARE|TOOLS_B_SWITCH)
 
/*====================================================================*
 *   lazy man's structure allocation;
 *--------------------------------------------------------------------*/

#define NEW(object) (object *)(emalloc(sizeof(object)))
#define BUF(length) (char *)(emalloc(sizeof(char)*(length+0)))
#define STR(length) (char *)(emalloc(sizeof(char)*(length+1)))
#define LST(object, length) (object*)(malloc(sizeof(object)*(length)))
 
/*====================================================================*
 *  define cmassoc standard file open loops;
 *--------------------------------------------------------------------*/

#if 0
#ifdef __cplusplus
#define _more()  getopt.optind() < argc && argv[getopt.optind()] != (char *)(0)
#define _open1() freopen(argv[getopt++], "r", stdin) != (FILE *)(0)
#define _open2() fopensave(argv[getopt++])
#else
#define _more()  (optind < argc) && (argv[optind] != (char *)(0))
#define _open1() freopen(argv[optind++], "r", stdin) != (FILE *)(0)
#define _open2() fopensave(argv[optind++])
#endif
#define _funnel(func) if(_more()) { while(_more()) { if(_open1()) { func; } } } else { func; }
#define _filter(func) if(_more()) { while(_more()) { if(_open2()) { func; } } } else { func; }
#endif
 
/*====================================================================*
 *   minimal print routines; write directly to STDOUT or STDERROR
 *--------------------------------------------------------------------*/

#define _cwrite(d,c) write(d,(c),1)
#define _swrite(d,s) write(d,(s),sizeof(s)-1)
#define _ewrite(s) write(STDERR_FILENO,(s),sizeof(s)-1)
 
signed cread (signed fd);
signed cwrite (signed fd, unsigned c);

/*====================================================================*
 *   function prototypes;
 *--------------------------------------------------------------------*/

#define _lost(string) fprintf(stderr,"don't understand \"%s\" \n", string)
#define _quit(action,value,state) fprintf(stderr,"%s '%s' %s \n", action, value, state)
#define _cant(action,object) fprintf(stderr,"can't %s '%s' \n", action, object)
#define _dont(action,object) fprintf(stderr,"don't %s '%s' \n", action, object)
#define _wont(action,object) fprintf(stderr,"won't %s '%s' \n", action, object)
#define _what(object) fprintf(stderr,"what %s ?\n", object)
#define _stop(reason) fprintf(stderr,"%s \n", reason)
 
/*====================================================================*
 *   busy widget print routines;
 *--------------------------------------------------------------------*/

#define _busy(cnt) { write(STDERR_FILENO,"\\|/-"[++cnt%4],1); write(STDERR_FILENO,"\r",1); }
 
/*====================================================================*
 *   file open functions;
 *--------------------------------------------------------------------*/
 
FILE *efopen (char const *pathname, char const *openmode);
FILE *efreopen (char const *pathname, char const *openmode, FILE * fp);

/*====================================================================*
 *   memory allocation functions;
 *--------------------------------------------------------------------*/
 
void *emalloc (size_t nbytes);
void *erealloc (void *address, size_t nbytes);

/*====================================================================*
 *   
 *--------------------------------------------------------------------*/

#if 0
#ifdef __GNUC__

__attribute__ ((format (printf, 1, 2)))

#endif
 
void alert (char const *format, ...);

#ifdef __GNUC__

__attribute__ ((format (printf, 1, 2)))

#endif
 
void event (char const *format, ...);

#ifdef __GNUC__

__attribute__ ((format (printf, 1, 2)))

#endif
 
void usage (char const *format, ...);

#endif
 
/*====================================================================*
 *   error message functions;
 *--------------------------------------------------------------------*/

#ifdef __GNUC__

__attribute__ ((format (printf, 1, 2)))

#endif
 
void eprintf (char const *format, ...);

#ifdef __GNUC__

__attribute__ ((format (printf, 1, 2)))

#endif
 
void eperror (char const *format, ...);

/*====================================================================*
 *
 *--------------------------------------------------------------------*/
 
signed fgetline (char *buffer, size_t length, FILE * fp);
signed fgetlongline (char *buffer, size_t length, unsigned preserve, FILE * fp);
signed fputline (char const *buffer, size_t length, FILE * fp);
void fputn (unsigned value, unsigned short radix, size_t width, FILE * ofp);
size_t fgetv (char *list [], size_t size, char *buffer, size_t length, FILE * fp);
void fputv (char const *list [], size_t size, FILE * fp);
int fprintv (char const *list [], size_t size, FILE * fp);
void signf (char const *string, int c, size_t width);
unsigned uintspec (char const *value, unsigned minimum, unsigned maximum);
unsigned number (char const *value, unsigned minimum, unsigned maximum, unsigned nominal);
signed sintspec (char const *string, signed number);
time_t timespec (char const *string);
time_t waitspec (char const *string);
time_t datespec (char const *string);
mode_t modespec (char const *string);

/*====================================================================*
 *   token parsing functions;
 *--------------------------------------------------------------------*/

#define TOKEN_SPACE ' '
#define TOKEN_ALPHA 'A'
#define TOKEN_DIGIT '0'
 
signed getclass (char buffer [], size_t length, unsigned *lineno, void *bp, signed get (void *bp), signed unget (signed c, void *bp));
signed getvalue (void *bp, signed get (void *bp), signed unget (signed c, void *bp));
signed cursor (signed c);

/*====================================================================*
 *  file name functions;
 *--------------------------------------------------------------------*/
 
bool plain (char const *filename);
bool match (char const *filename, char const *wildcard);

/*====================================================================*
 *   
 *--------------------------------------------------------------------*/
 
// char const *codename (const struct _code_ list [], size_t size, code_t code, char const * name); 
// char const *typename (const struct _type_ list [], size_t size, type_t type, char const * name); 
code_t namecode (const struct _code_ list [], size_t size, char const *name, code_t code);
type_t nametype (const struct _type_ list [], size_t size, char const *name, type_t type);
void typesave (struct _type_ list [], size_t size, char const * name, flag_t flags);
void codesave (struct _code_ list [], size_t size, char const * name, flag_t flags);
size_t typeload (struct _type_ list [], size_t size);
size_t codeload (struct _code_ list [], size_t size);

/*====================================================================*
 *   end definitions;
 *--------------------------------------------------------------------*/

#endif
 

