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

#define __FUNC__ __FUNCTION__
#if defined (WIN32)
#define __func__ __FUNCTION__
#endif

/*====================================================================*
 *   
 *--------------------------------------------------------------------*/

#if __TRACE__
#define EVENT(format, args...) fprintf (stderr, "%s: Event %s (%d): " format "\n", __FILE__, __FUNC__, __LINE__, ##args);
#define ENTER(format, args...) fprintf (stderr, "%s: Enter %s (%d): " format "\n", __FILE__, __FUNC__, __LINE__, ##args);
#define LEAVE(format, args...) fprintf (stderr, "%s: Leave %s (%d): " format "\n", __FILE__, __FUNC__, __LINE__, ##args);
#else
#define EVENT(format, args...)
#define ENTER(format, args...)
#define LEAVE(format, args...)
#endif

/*====================================================================*
 *   define common error message strings; 
 *--------------------------------------------------------------------*/

#define ERROR_NOTROOT "Program needs root priviledges"
#define ERROR_TOOMANY "Too many command line arguments"

/*====================================================================*
 *   declare GNU error() and error_at_line() functions;  
 *--------------------------------------------------------------------*/

#ifdef __GNUC__

__attribute__ ((format(printf, 3, 4))) 

#endif

signed error(int status, errno_t number, char const * format, ...);

#ifdef __GNUC__

__attribute__ ((format(printf, 3, 4))) 

#endif

signed debug(int status, char const * string, char const * format, ...);

#ifdef __GNUC__

__attribute__ ((format(printf, 5, 6))) 

#endif

signed error_on_line(int status, errno_t number, char const * filename, unsigned lineno, char const * format, ...);

/*====================================================================*
 *   declare custom alternative error () function;  
 *--------------------------------------------------------------------*/

#ifdef __GNUC__

__attribute__ ((format(printf, 1, 2))) 

#endif

signed alert(char const * format, ...);

#ifdef __GNUC__

__attribute__ ((format(printf, 3, 4))) 

#endif

signed event(int status, signo_t number, char const * format, ...);

/*====================================================================*
 *   error message functions;
 *--------------------------------------------------------------------*/

#ifdef __GNUC__

__attribute__ ((format(printf, 1, 2))) 

#endif

void eprintf(char const * format, ...);

#ifdef __GNUC__

__attribute__ ((format(printf, 1, 2))) 

#endif

void eperror(char const * format, ...);

/*====================================================================*
 *   memory allocation functions (also declared in memory.h);
 *--------------------------------------------------------------------*/

void * emalloc(size_t nbytes);
void * erealloc(void * address, size_t nbytes);

/*====================================================================*
 *   file open functions (also declared in files.h);
 *--------------------------------------------------------------------*/

FILE * efopen(char const * pathname, char const * openmode);
FILE * efreopen(char const * pathname, char const * openmode, FILE * fp);

/*====================================================================*
 *   end definitions and declarations;
 *--------------------------------------------------------------------*/

#endif



