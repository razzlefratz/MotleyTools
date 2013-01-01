/*====================================================================*
 *
 *   _stdlib.h - commonly used library functions
 *
 *   This include file contains the function declarations for
 *   commonly used library functions which either don't fit somewhere
 *   else, or, like toupper/tolower, can't be declared in the normal
 *   place for other reasons.
 *
 *.  Motley Tools by Charles Maier
 *:  modified sun 07 sep 03 by user root on host zeus;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef STDLIB_HEADER
#define STDLIB_HEADER

#include "_stddef.h"

/*====================================================================*
 *   search/sort functions;
 *--------------------------------------------------------------------*/

signed _bindex (void const *item, void * const list [], size_t size, int comp (void const *, void const *));
void *_bsearch (void const *item, void * const list [], size_t size, int comp (void const *, void const *));
void _qsort (void *list [], size_t size, int comp (void const *, void const *), void swap (void const *, void const *));

/*====================================================================*
 *   generic comparison macros;
 *--------------------------------------------------------------------*/

#define _max(a,b) ((a)>(b)?(a):(b))
#define _min(a,b) ((a)<(b)?(a):(b))
#define _cmp(a,b) ((a)>(b)?(int)(1):(a)<(b)?(int)(-1):(int)(0))

/*====================================================================*
 *   memory allocation and manipulation definitions;
 *--------------------------------------------------------------------*/

#include "_memory.h"

/*====================================================================*
 *   standard environmental variable functions;
 *--------------------------------------------------------------------*/

char *_getenv (char const *varname);
void _searchenv (char const *filename, char const *varname, char *pathname);

/*====================================================================*
 *   error message functions;
 *--------------------------------------------------------------------*/

int system (char const *command);
void perror (char const *message);
char *strerror (int);

/*====================================================================*
 *   process control functions;
 *--------------------------------------------------------------------*/

void exit (int status);
void _exit (int status);
void abort (void);
int atexit (void (*func)(void));

/*====================================================================*
 *   random number generation
 *--------------------------------------------------------------------*/

#define _RAND_MAX 0x7FFFFFFF

unsigned _rand (void);
void _srand (unsigned seed);

/*====================================================================*
 *   prototype standard numeric conversion functions;
 *--------------------------------------------------------------------*/

signed _atoi (char const *string);
signed long _atol (char const *string);
double _atof (char const *string);
double _strtod (const char *nptr, char **endptr);

/*====================================================================*
 *   end definition;
 *--------------------------------------------------------------------*/

#endif

