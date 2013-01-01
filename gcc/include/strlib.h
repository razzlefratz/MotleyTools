/*====================================================================*
 *
 *   strlib.h - 
 *
 *.  Motley Tools by Charles Maier
 *:  compiled for debian gnu/linux environment using gcc 2.95 compiler;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef STRLIB_HEADER
#define STRLIB_HEADER

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <stdlib.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/types.h"

/*====================================================================*
 *   
 *--------------------------------------------------------------------*/

#ifndef empty
#define empty(s) (((s)==(char *)(0))||(*(s)==(char)(0)))
#endif

#ifndef valid
#define valid(s) (((s)!=(char *)(0))&&(*(s)!=(char)(0)))
#endif

#ifndef isempty
#define isempty(s) (((s)==(char *)(0))||(*(s)==(char)(0)))
#endif

#ifndef notempty
#define notempty(s) (((s)!=(char *)(0))&&(*(s)!=(char)(0)))
#endif

/*====================================================================*
 *   
 *--------------------------------------------------------------------*/

char const ** stov (char const *string, unsigned c);
size_t strfbits (char buffer [], size_t length, char const *operands [], char const *operator, flag_t flagword);
size_t strfcsv (char buffer [], size_t length, char const *fields [], char const *comma, char const *quote);
size_t strsplit (char const *vector [], size_t length, char string [], unsigned c);
size_t strargv (size_t argc, char const *argv [], char buffer [], unsigned c);
char *strlwr (char *string);
char *strcut (char *string, unsigned c);

/*====================================================================*
 *   string vector functions;
 *--------------------------------------------------------------------*/

void svorder (char const *name, char const *list [], size_t size, int (*comp)(char const *, char const *));
size_t svindex (char const *name, char const *list [], size_t size, int (*comp)(char const *, char const *));
size_t svfirst (char const *name, char const *list [], size_t size, int (*comp)(char const *, char const *));

/*====================================================================*
 *   end definitions and declarations;
 *--------------------------------------------------------------------*/

#endif

