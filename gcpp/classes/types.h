/*====================================================================*
 *
 *   types.h - generic data type definitions and declarations; 
 *
 *   these are our favorite definitions and declarations; they are used
 *   throughout our software for clarity and consistency; learn to love
 *   them and make them your own;
 *
 *.  published 2003 by charles maier associates limited for internal use;
 *:  modified tue 16 sep 03 by user root on host zeus;
 *;  compiled for debian gnu/linux using gcc compiler;
 *
 *--------------------------------------------------------------------*/

#ifndef TYPES_HEADER
#define TYPES_HEADER
 
/*====================================================================*
 *   macros;
 *--------------------------------------------------------------------*/

#define _OPTSTR(x) #x
#define LITERAL(x) _OPTSTR(x)

#define SIZEOF(list) (sizeof(list)/sizeof(list[0]))

/*====================================================================*
 *   POSIX data types; (new or proposed)
 *--------------------------------------------------------------------*/
 
typedef signed errno_t;
typedef signed signo_t;
typedef unsigned char byte;
typedef unsigned long long huge_t;

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

#ifndef __packed
#define __packed __attribute__ ((packed))
#endif
 
/*====================================================================*
 *   custom data types;
 *--------------------------------------------------------------------*/
 
typedef signed file_t;
typedef signed sock_t;
typedef signed code_t;
typedef unsigned type_t;
typedef unsigned char byte_t;
typedef unsigned flag_t;
typedef struct _file_ 

{
	file_t file;
	char const * name;
}

file;
typedef struct _code_ 

{
	code_t code;
	char const * name;
}

code;
typedef struct _type_ 

{
	type_t type;
	char const * name;
}

type;
typedef struct _flag_ 

{
	flag_t flag;
	char const * name;
}

flag;
typedef struct _term_ 

{
	char const * term;
	char const * text;
}

term;

/*====================================================================*
 *   end definitions and declarations;
 *--------------------------------------------------------------------*/

#endif
 

