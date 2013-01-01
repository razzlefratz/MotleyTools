/*====================================================================*
 *
 *   types.h - custom data type definitions and declarations;
 *
 *.  Motley Tools by Charles Maier
 *:  compiled for debian gnu/linux environment using gcc 2.95 compiler;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef TYPES_HEADER
#define TYPES_HEADER

/*====================================================================*
 *   define C++ style true and false for use in standard C programs;
 *--------------------------------------------------------------------*/

#ifndef __cplusplus

typedef enum 

{
	false,
	true
}

bool;

#endif

/*====================================================================*
 *   define flagword (bitmap) variable type for clarity;
 *--------------------------------------------------------------------*/

typedef signed file_t;
typedef signed code_t;
typedef unsigned bool_t;
typedef unsigned flag_t;
typedef struct _code_ 

{
	char const *name;
	code_t code;
}

code;
typedef struct _flag_ 

{
	char const *name;
	flag_t flag;
}

flag;
typedef struct _term_ 

{
	char const *name;
	char *text;
}

term;

/*====================================================================*
 *   new POSIX datatypes;
 *--------------------------------------------------------------------*/

typedef signed signo_t;
typedef signed errno_t;

/*====================================================================*
 *   end definitions and declarations;
 *--------------------------------------------------------------------*/

#endif

