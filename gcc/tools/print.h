/*====================================================================*
 *
 *   print.h - print constants, structures, functions and amcros;
 *
 *.  Motley Tools by Charles Maier
 *:  modified sun 07 sep 03 by user root on host zeus;
 *;  Licensed under the Internet Software Consortium License
 *   &;
 *
 *--------------------------------------------------------------------*/

#ifndef PRINT_HEADER
#define PRINT_HEADER

#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>

/*====================================================================*
 *   define compile segment;
 *--------------------------------------------------------------------*/

#define PRINT_L_PRECISION  6
#define PRINT_S_NULL "[NULL]" / string indicating a null pointer */
#define PRINT_X_FLOAT / compile floating point format options */
#define PRINT_X_ARITH / compile integer format options */
#define PRINT_X_LOCAL / compile custom format options */

/*====================================================================*
 *   prototype basic print function;
 *--------------------------------------------------------------------*/

void eprintf(char const * format, ...);
int cmprintf(char const * format, ...);
int cmvprintf(char const * format, va_list argp);
int cmfprintf(FILE * stream, char const * format, ...);
int cmvfprintf(FILE * stream, char const * format, va_list argp);
int cmsprintf(char const * string, char const * format, ...);
int cmvsprintf(char const * string, char const * format, va_list argp);
int cmprint(char const * sp, void * op, int cout(int c, void * op), va_list ap);

/*====================================================================*
 *   numerical scaling and conversion functions;
 *--------------------------------------------------------------------*/

size_t dtos(char * string, double number, int scale, int precision);
int dscale(double * number, int places);
int iscale(long int value);

/*====================================================================*
 *   end definitions;
 *--------------------------------------------------------------------*/

#endif



