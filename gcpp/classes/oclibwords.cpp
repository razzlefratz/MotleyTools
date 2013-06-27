/*====================================================================*
 *
 *   oclibwords.cpp - definition of oclibwords class.
 *
 *   symbol table containing standard C library function names;
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oCLIBWORDS_SOURCE
#define oCLIBWORDS_SOURCE

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#include "../classes/oclibwords.hpp"
#include "../../gcc/tools/types.h"

/*====================================================================*
 *
 *   oclibwords();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oclibwords::oclibwords () 

{
	static char const * table [] = 
	{
		"CHAR_BIT",
		"CHAR_MAX",
		"CHAR_MIN",
		"DBL_DIG",
		"DBL_EPSILON",
		"DBL_MANT_DIG",
		"DBL_MAX",
		"DBL_MAX_EXP",
		"DBL_MIN",
		"DBL_MIN_EXP",
		"EOF",
		"FILE",
		"FLT_DIG",
		"FLT_EPSILON",
		"FLT_MANT_DIG",
		"FLT_MAX",
		"FLT_MAX_EXP",
		"FLT_MIN",
		"FLT_MIN_EXP",
		"FLT_RADIX",
		"FLT_ROUNDS",
		"INT_MAX",
		"INT_MIN",
		"LONG_MAX",
		"LONG_MIN",
		"NULL",
		"SCHAR_MAX",
		"SCHAR_MIN",
		"SHRT_MAX",
		"SHRT_MIN",
		"UCHAR_MAX",
		"UINT_MAX",
		"ULONG_MAX",
		"USHRT_MAX",
		"_exit",
		"abort",
		"abs",
		"acos",
		"asin",
		"assert",
		"atan",
		"atan2",
		"atexit",
		"atof",
		"atoi",
		"atol",
		"bsearch",
		"calloc",
		"ceil",
		"clearerr",
		"clock",
		"close",
		"cos",
		"cosh",
		"ctime",
		"difftime",
		"div",
		"exit",
		"exp",
		"fabs",
		"fclose",
		"feof",
		"ferror",
		"fflush",
		"fgetc",
		"fgetpos",
		"fgets",
		"floor",
		"fmod",
		"fopen",
		"fprintf",
		"fputc",
		"fputs",
		"fread",
		"free",
		"freopen",
		"frexp",
		"fscanf",
		"fseek",
		"fsetpos",
		"ftell",
		"fwrite",
		"getc",
		"getchar",
		"getenv",
		"gets",
		"gmtime",
		"isalnum",
		"isalpha",
		"iscntrl",
		"isdigit",
		"isgraph",
		"islower",
		"isprint",
		"ispunct",
		"isspace",
		"isupper",
		"isxdigit",
		"labs",
		"ldexp",
		"ldiv",
		"localtime",
		"log",
		"log10",
		"longjmp",
		"lseek",
		"main",
		"malloc",
		"memchr",
		"memcpy",
		"memmove",
		"memset",
		"mktime",
		"modf",
		"msmcmp",
		"open",
		"perror",
		"pow",
		"printf",
		"putc",
		"putchar",
		"puts",
		"qsort",
		"raise",
		"rand",
		"realloc",
		"rewind",
		"scanf",
		"setbuf",
		"setjmp",
		"setvbuf",
		"signal",
		"sin",
		"sinh",
		"sprintf",
		"sqrt",
		"srand",
		"sscanf",
		"strcat",
		"strchr",
		"strcmp",
		"strcpy",
		"strcspn",
		"strerror",
		"strftime",
		"strlen",
		"strncat",
		"strncmp",
		"strncpy",
		"strpbrk",
		"strrchr",
		"strspn",
		"strstr",
		"strtod",
		"strtok",
		"strtol",
		"strtoul",
		"system",
		"tan",
		"tanh",
		"time",
		"tmpfile",
		"tmpnam",
		"va_arg",
		"va_end",
		"va_list",
		"va_start",
		"vfprintf",
		"vprintf",
		"vsprintf",
		(char const *)(0)
	};
	okeywords::mtitle = "clibwords";
	okeywords::mcount = SIZEOF (table) - 1;
	okeywords::mtable = table;
	okeywords::mcheck ();
	return;
}

/*====================================================================*
 *
 *   ~oclibwords();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oclibwords::~oclibwords () 

{
	return;
}

/*====================================================================*
 *   end definition;
 *--------------------------------------------------------------------*/

#endif

