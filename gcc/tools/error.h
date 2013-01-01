/*====================================================================*
 *
 *   error.h - linux definitions and declarations;
 *
 *   this file is an alterantive to the GNU header file of the same
 *   name; in addition to standard GNU error function declarations,
 *   some additional functions are declared; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 2005 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef ERROR_HEADER
#define ERROR_HEADER

/*====================================================================*
 *   system header files; 
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <errno.h>

/*====================================================================*
 *   custom header files; 
 *--------------------------------------------------------------------*/

#include "../tools/types.h"

/*====================================================================*
 *   POSIX error codes for systems that do not have them;
 *--------------------------------------------------------------------*/

#ifndef ECANCELED
#define ECANCELED 0
#endif

#ifndef ENOTSUP
#define ENOTSUP 0
#endif

/*====================================================================*
 *   
 *--------------------------------------------------------------------*/

#if defined (WIN32)
#define __func__ __FUNCTION__
#endif

#define TRACE error (0, 0, "%s (%d)", __FILE__, __LINE__);

/*====================================================================*
 *   define common error message strings; 
 *--------------------------------------------------------------------*/

#define ERROR_NOTROOT "Program needs root priviledges"
#define ERROR_TOOMANY "Too many command line arguments"

/*====================================================================*
 *   declare GNU error() and error_at_line() functions;  
 *--------------------------------------------------------------------*/

#ifdef __GNUC__

__attribute__ ((format (printf, 3, 4))) 

#endif

void error (int status, errno_t number, char const *format, ...);

#ifdef __GNUC__

__attribute__ ((format (printf, 5, 6))) 

#endif

void error_on_line (int status, errno_t number, char const *filename, unsigned lineno, char const *format, ...);

/*====================================================================*
 *   declare custom alternative error() function;  
 *--------------------------------------------------------------------*/

#ifdef __GNUC__

__attribute__ ((format (printf, 1, 2))) 

#endif

void alert (char const *format, ...);

#ifdef __GNUC__

__attribute__ ((format (printf, 3, 4))) 

#endif

void event (int status, signo_t number, char const *format, ...);

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
 *   memory allocation functions (also declared in memory.h);
 *--------------------------------------------------------------------*/

void * emalloc (size_t nbytes);
void * erealloc (void *address, size_t nbytes);

/*====================================================================*
 *   file open functions (also declared in files.h);
 *--------------------------------------------------------------------*/

FILE * efopen (char const *pathname, char const *openmode);
FILE * efreopen (char const *pathname, char const *openmode, FILE * fp);

/*====================================================================*
 *   end definitions and declarations;
 *--------------------------------------------------------------------*/

#endif

