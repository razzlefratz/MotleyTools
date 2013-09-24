/*====================================================================*
 *
 *   ofunctions.cpp - definition of ofunctions class.
 *
 *   symbol table containing standard C library function names;
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oFUNCTIONS_SOURCE
#define oFUNCTIONS_SOURCE

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#include "../classes/ofunctions.hpp"

/*====================================================================*
 *
 *   ofunctions();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ofunctions::ofunctions ()

{
	static char const * table [] = 
	{
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
		(char const *) (0)
	};
	okeywords::mtitle = "functions";
	okeywords::mcount = sizeof (table) / sizeof (char const *) - 1;
	okeywords::mtable = table;
	okeywords::mcheck ();
	return;
}

/*====================================================================*
 *
 *   ~ofunctions();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ofunctions::~ ofunctions ()

{
	return;
}

/*====================================================================*
 *   end definition;
 *--------------------------------------------------------------------*/

#endif



