/*====================================================================*
 * 
 *   sv_clib[] - 
 * 
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 * 
 *--------------------------------------------------------------------*/

#include <stddef.h>

#define CLIB_O_CHAR_BIT                   0
#define CLIB_O_CHAR_MAX                   1
#define CLIB_O_CHAR_MIN                   2
#define CLIB_O_DBL_DIG                    3
#define CLIB_O_DBL_EPSILON                4
#define CLIB_O_DBL_MANT_DIG               5
#define CLIB_O_DBL_MAX                    6
#define CLIB_O_DBL_MAX_EXP                7
#define CLIB_O_DBL_MIN                    8
#define CLIB_O_DBL_MIN_EXP                9
#define CLIB_O_EOF                       10
#define CLIB_O_FILE                      11
#define CLIB_O_FLT_DIG                   12
#define CLIB_O_FLT_EPSILON               13
#define CLIB_O_FLT_MANT_DIG              14
#define CLIB_O_FLT_MAX                   15
#define CLIB_O_FLT_MAX_EXP               16
#define CLIB_O_FLT_MIN                   17
#define CLIB_O_FLT_MIN_EXP               18
#define CLIB_O_FLT_RADIX                 19
#define CLIB_O_FLT_ROUNDS                20
#define CLIB_O_INT_MAX                   21
#define CLIB_O_INT_MIN                   22
#define CLIB_O_LONG_MAX                  23
#define CLIB_O_LONG_MIN                  24
#define CLIB_O_NULL_PTR                  25
#define CLIB_O_SCHAR_MAX                 26
#define CLIB_O_SCHAR_MIN                 27
#define CLIB_O_SHRT_MAX                  28
#define CLIB_O_SHRT_MIN                  29
#define CLIB_O_UCHAR_MAX                 30
#define CLIB_O_UINT_MAX                  31
#define CLIB_O_ULONG_MAX                 32
#define CLIB_O_USHRT_MAX                 33
#define CLIB_O__EXIT                     34
#define CLIB_O_ABORT                     35
#define CLIB_O_ABS                       36
#define CLIB_O_ACOS                      37
#define CLIB_O_ASIN                      38
#define CLIB_O_ASSERT                    39
#define CLIB_O_ATAN                      40
#define CLIB_O_ATAN2                     41
#define CLIB_O_ATEXIT                    42
#define CLIB_O_ATOF                      43
#define CLIB_O_ATOI                      44
#define CLIB_O_ATOL                      45
#define CLIB_O_BSEARCH                   46
#define CLIB_O_CALLOC                    47
#define CLIB_O_CEIL                      48
#define CLIB_O_CLEARERR                  49
#define CLIB_O_CLOCK                     50
#define CLIB_O_CLOSE                     51
#define CLIB_O_COS                       52
#define CLIB_O_COSH                      53
#define CLIB_O_CTIME                     54
#define CLIB_O_DIFFTIME                  55
#define CLIB_O_DIV                       56
#define CLIB_O_EXIT                      57
#define CLIB_O_EXP                       58
#define CLIB_O_FABS                      59
#define CLIB_O_FCLOSE                    60
#define CLIB_O_FEOF                      61
#define CLIB_O_FERROR                    62
#define CLIB_O_FFLUSH                    63
#define CLIB_O_FGETC                     64
#define CLIB_O_FGETPOS                   65
#define CLIB_O_FGETS                     66
#define CLIB_O_FLOOR                     67
#define CLIB_O_FMOD                      68
#define CLIB_O_FOPEN                     69
#define CLIB_O_FPRINTF                   70
#define CLIB_O_FPUTC                     71
#define CLIB_O_FPUTS                     72
#define CLIB_O_FREAD                     73
#define CLIB_O_FREE                      74
#define CLIB_O_FREOPEN                   75
#define CLIB_O_FREXP                     76
#define CLIB_O_FSCANF                    77
#define CLIB_O_FSEEK                     78
#define CLIB_O_FSETPOS                   79
#define CLIB_O_FTELL                     80
#define CLIB_O_FWRITE                    81
#define CLIB_O_GETC                      82
#define CLIB_O_GETCHAR                   83
#define CLIB_O_GETENV                    84
#define CLIB_O_GETS                      85
#define CLIB_O_GMTIME                    86
#define CLIB_O_IAALNUM                   87
#define CLIB_O_ISCNTRL                   88
#define CLIB_O_ISALPHA                   89
#define CLIB_O_ISDIGIT                   90
#define CLIB_O_ISGRAPH                   91
#define CLIB_O_ISLOWER                   92
#define CLIB_O_ISPRINT                   93
#define CLIB_O_ISPUNCT                   94
#define CLIB_O_ISSPACE                   95
#define CLIB_O_ISUPPER                   96
#define CLIB_O_ISXDIGIT                  97
#define CLIB_O_LABS                      98
#define CLIB_O_LDEXP                     99
#define CLIB_O_LDIV                     100
#define CLIB_O_LOCALTIME                101
#define CLIB_O_LOG                      102
#define CLIB_O_LOG10                    103
#define CLIB_O_LONGJMP                  104
#define CLIB_O_LSEEK                    105
#define CLIB_O_MALLOC                   106
#define CLIB_O_MEMCHR                   107
#define CLIB_O_MEMCPY                   108
#define CLIB_O_MEMMOVE                  109
#define CLIB_O_MEMSET                   110
#define CLIB_O_MKTIME                   111
#define CLIB_O_MODF                     112
#define CLIB_O_MSMCMP                   113
#define CLIB_O_OPEN                     114
#define CLIB_O_PERROR                   115
#define CLIB_O_POW                      116
#define CLIB_O_PRINTF                   117
#define CLIB_O_PUTC                     118
#define CLIB_O_PUTCHAR                  119
#define CLIB_O_PUTS                     120
#define CLIB_O_QSORT                    121
#define CLIB_O_RAISE                    122
#define CLIB_O_RAND                     123
#define CLIB_O_REALLOC                  124
#define CLIB_O_REWIND                   125
#define CLIB_O_SCANF                    126
#define CLIB_O_SETBUF                   127
#define CLIB_O_SETJMP                   128
#define CLIB_O_SETVBUF                  129
#define CLIB_O_SIGNAL                   130
#define CLIB_O_SIN                      131
#define CLIB_O_SINH                     132
#define CLIB_O_SPRINTF                  133
#define CLIB_O_SQRT                     134
#define CLIB_O_SRAND                    135
#define CLIB_O_SSCANF                   136
#define CLIB_O_STRCAT                   137
#define CLIB_O_STRCHR                   138
#define CLIB_O_STRCMP                   139
#define CLIB_O_STRCPY                   140
#define CLIB_O_STRCSPN                  141
#define CLIB_O_STRERROR                 142
#define CLIB_O_STRFTIME                 143
#define CLIB_O_STRLEN                   144
#define CLIB_O_STRNCAT                  145
#define CLIB_O_STRNCMP                  146
#define CLIB_O_STRNCPY                  147
#define CLIB_O_STRPBRK                  148
#define CLIB_O_STRRCHR                  149
#define CLIB_O_STRSPN                   150
#define CLIB_O_STRSTR                   151
#define CLIB_O_STRTOD                   152
#define CLIB_O_STRTOK                   153
#define CLIB_O_STRTOL                   154
#define CLIB_O_STRTOUL                  155
#define CLIB_O_SYSTEM                   156
#define CLIB_O_TAN                      157
#define CLIB_O_TANH                     158
#define CLIB_O_TIME                     159
#define CLIB_O_TMPFILE                  160
#define CLIB_O_TMPNAM                   161
#define CLIB_O_VA_ARG                   162
#define CLIB_O_VA_END                   163
#define CLIB_O_VA_LIST                  164
#define CLIB_O_VA_START                 165
#define CLIB_O_VFPRINTF                 166
#define CLIB_O_VPRINTF                  167
#define CLIB_O_VSPRINTF                 168
#define CLIB_O_169                      169
#define CLIB_O_NULL                     170

char const *sv_clib [] = 

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
	"iaalnum",
	"is cntrl",
	"isalpha",
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
	"",
	NULL
};

