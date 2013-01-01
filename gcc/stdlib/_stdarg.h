/*====================================================================*
 *
 *   stdarg.h - variable argument macros and function prototypes
 *
 *.  Motley Tools by Charles Maier
 *:  modified sun 07 sep 03 by user root on host zeus;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef STDARG_HEADER
#define STDARG_HEADER

/*====================================================================*
 * variable argument macros (standard);
 *--------------------------------------------------------------------*/

typedef char *va_list;

#define _INTSIZE_T_SPEC(n) ((sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1))
#define va_start(argp, var) argp = (va_list)(&var) + _INTSIZE_T_SPEC(var)
#define va_arg(argp, type) (*(type *)((argp += _INTSIZE_T_SPEC(type)) - _INTSIZE_T_SPEC(type)))
#define va_end(argp) argp = (va_list)(0)

/*====================================================================*
 * end definitions;
 *--------------------------------------------------------------------*/

#endif

