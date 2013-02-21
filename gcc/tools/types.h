/*====================================================================*
 *
 *   types.h - generic data type definitions and declarations; 
 *
 *   these are our favorite definitions and declarations; they are used
 *   throughout our software for clarity and consistency; learn to love
 *   them and make them your own;
 *
 *.  Motley Tools by Charles Maier
 *:  modified tue 16 sep 03 by user root on host zeus;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef TYPES_HEADER
#define TYPES_HEADER

/*====================================================================*
 *   POSIX data types; (new or proposed)
 *--------------------------------------------------------------------*/

typedef signed errno_t;
typedef signed signo_t;
typedef unsigned char byte;
typedef unsigned word;

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
#ifdef __GNUC__
#define __packed __attribute__ ((packed))
#else
#define __packed
#endif
#endif

#if defined (WIN32)
	#define SIZE_T_SPEC "%I64d"
	#define ADDR_T_SPEC "%04X"
	#define OFF_T_SPEC "%I64d"
#elif defined (__APPLE__) 
	#define SIZE_T_SPEC "%zu"
	#define ADDR_T_SPEC "%04Xzu"
	#define OFF_T_SPEC "%lld"
#elif defined (__OpenBSD__)
	#define SIZE_T_SPEC "%zu"
	#define ADDR_T_SPEC "%04Xzu"
	#define OFF_T_SPEC "%ld"
#elif defined (__linux__)
	#define SIZE_T_SPEC "%zu"
	#define ADDR_T_SPEC "%04Xzu"
	#define OFF_T_SPEC "%ld"
#else
#error "Unknown Environment!"
#endif

#if defined (WIN32)
#define __func__ __FUNCTION__
#endif

/*====================================================================*
 *   macros;
 *--------------------------------------------------------------------*/

#define MONIKER(x) #x
#define LITERAL(x) MONIKER(x)
#define SIZEOF(list) (sizeof(list)/sizeof(list[0]))

/*====================================================================*
 *   custom data types;
 *--------------------------------------------------------------------*/

typedef signed file_t;
typedef signed sock_t;
typedef signed code_t;
typedef signed bool_t;
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

