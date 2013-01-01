/*====================================================================*
 *
 *   tools.h - 
 *
 *.  Motley Tools by Charles Maier
 *:  compiled for debian gnu/linux environment using gcc 2.95 compiler;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef TOOLS_HEADER
#define TOOLS_HEADER

/*====================================================================*
 *   system header files;     
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <time.h>

/*====================================================================*
 *   custom header files;     
 *--------------------------------------------------------------------*/

#include "../tools/types.h"

/*====================================================================*
 *   define common constants; 
 *--------------------------------------------------------------------*/

#ifndef NONE
#define NONE (unsigned)(0)
#endif

#ifndef NIL
#define NIL ""
#endif

#ifndef ERR
#define ERR (signed)(-1)
#endif

/*====================================================================*
 *   lin-line functions;
 *--------------------------------------------------------------------*/

#define NEW(object) (object *)(malloc(sizeof(object)))
#define BUF(length) (char *)(malloc(sizeof(char)*(length+0)))
#define STR(length) (char *)(malloc(sizeof(char)*(length+1)))
#define LST(object, length) (object*)(malloc(sizeof(object)*(length)))

#define sdebug(s) write(1,(s),strlen(s)); write(1,"\n",1);
#define swrite(s) write(1,(s),strlen(s)) 
#define cwrite(c) write(1,(&c),1) 

#define STATE(flags, flag) ((flags)&(flag)?"enabled":"disabled")

/*====================================================================*
 *   
 *--------------------------------------------------------------------*/

void *emalloc (size_t bytes);
void *xmalloc (size_t bytes);

/*====================================================================*
 *   
 *--------------------------------------------------------------------*/

bool numeric (char const *string);
unsigned uintspec (char const *string, unsigned minimum, unsigned maximum);
time_t timespec (char const *string, char const *notime);
time_t waitspec (char const *string);

#ifndef nobreak
#define nobreak(c)   (((int)(c) != EOF) && ((char)(c) != (char)(0)) && ((char)(c) != '\n'))
#endif

size_t statement (file_t fd, char buffer [], size_t length, size_t *lineno);

/*====================================================================*
 *   end definitions and declarations;
 *--------------------------------------------------------------------*/

#endif

