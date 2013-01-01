/*====================================================================*
 *
 *   _stddef.h - standard library definitions and declarations;
 *
 *.  Motley Tools by Charles Maier
 *:  modified sun 07 sep 03 by user root on host zeus;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include <stddef.h>

#define STDDEF_HEADER
#ifndef STDDEF_HEADER

/*====================================================================*
 *   posix macro definitions
 *--------------------------------------------------------------------*/

#define NULL ((void *)(0))

#define offsetof(type, member)

/*====================================================================*
 *   posix type declarations
 *--------------------------------------------------------------------*/

typedef signed long ptrdiff_t;
typedef unsigned long size_t;
typedef unsigned int wchar_t;

/*====================================================================*
 *   end definitions and declarations;
 *--------------------------------------------------------------------*/

#endif

