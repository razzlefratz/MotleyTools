/*====================================================================*
 *
 *   error.h - error functions definitions and declarations;
 *
 *.  Motley Tools by Charles Maier
 *:  compiled for debian gnu/linux environment using gcc 2.95 compiler;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef ERROR_HEADER
#define ERROR_HEADER

/*====================================================================*
 *   system header files; 
 *--------------------------------------------------------------------*/

#ifdef __GNUC__
#include <error.h>
#endif

/*====================================================================*
 *   functions;
 *--------------------------------------------------------------------*/

#ifndef _ERROR_H
#ifdef __GNUC__

__attribute__ ((format (printf, 3, 4))) 

#endif

void error (int status, errno_t number, char const *format, ...);

#ifdef __GNUC__

__attribute__ ((format (printf, 3, 4))) 

#endif

void event (int status, signo_t number, char const *format, ...);

#ifdef __GNUC__

__attribute__ ((format (printf, 5, 6))) 

#endif

void error_at_line (int status, errno_t number, char const *filename, unsigned lineno, char const *format, ...);

#endif

/*====================================================================*
 *   
 *--------------------------------------------------------------------*/

#endif

