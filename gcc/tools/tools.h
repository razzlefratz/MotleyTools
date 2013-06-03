/*====================================================================*
 *
 *   tools.h - 
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

#ifndef TOOLS_HEADER
#define TOOLS_HEADER

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <stdio.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/types.h"

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

/*
 *   already defined somewhere. drat! 
 *   some brian kernighan fan, no doubt. 
 *   #define HUGE ((unsigned short)(-1)) 
 *   #define HUGE (0x7FFF)
 */

#define HUGE (unsigned)(~0)
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
#define END (unsigned)(~0)
#endif

#ifndef ERR
#define ERR (unsigned)(~0)
#endif

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
#define TOOLS_B_MARKUP (1 << 4)
#define TOOLS_B_NORMAL (TOOLS_B_DEFINE|TOOLS_B_DECLARE|TOOLS_B_SWITCH|TOOLS_B_MARKUP)

/*====================================================================*
 *   minimal print routines; write directly to STDOUT or STDERROR
 *--------------------------------------------------------------------*/

#define _cwrite(d,c) write(d,(c),1)
#define _swrite(d,s) write(d,(s),sizeof(s)-1)
#define _ewrite(s) write(STDERR_FILENO,(s),sizeof(s)-1)

signed cread (signed fd);
signed cwrite (signed fd, signed c);

// size_t statement (int fd, char buffer [], size_t length, size_t * lineno);

int cgetc (int fd);

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

signed fgetline (char * buffer, size_t length, FILE * fp);
signed fgetlongline (char * buffer, size_t length, unsigned preserve, FILE * fp);
signed fputline (char const * buffer, size_t length, FILE * fp);
void fputn (unsigned value, unsigned short radix, size_t width, FILE * ofp);
size_t fgetv (char * list [], size_t size, char * buffer, size_t length, FILE * fp);
void fputv (char const * list [], size_t size, FILE * fp);
int fprintv (FILE *fp, char const *list [], size_t size);
void signf (char const * string, int c, size_t width);
size_t cgets (char buffer [], size_t length);
char * argv2str (char * argv []);
void center (char const buffer [], unsigned length, unsigned margin);

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

char const * termspec (char const * term, char const * type, const struct _term_ list [], size_t size);
void nodef (char const * term, char const * type, const struct _term_ list [], size_t size);

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

char *unixencode (char const *string, char *buffer, size_t length);
char *ietfencode (char const *string, char *buffer, size_t length);
char *unixdecode (char *string);
char *ietfdecode (char *string);

/*====================================================================*
 *   string based character i/o functions;
 *--------------------------------------------------------------------*/

signed sgetc (char **bp);
signed sputc (int c, char **bp);
signed sungetc (int c, char **bp);

/*====================================================================*
 *   end definitions;
 *--------------------------------------------------------------------*/

#endif

