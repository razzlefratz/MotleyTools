/*====================================================================* 
 *   
 *   sv_sv_python[] - 
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *   
 *--------------------------------------------------------------------*/

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#ifndef SV_PYTHON
#define SV_PYTHON_O_NONE                      0
#define SV_PYTHON_O_AND                       1
#define SV_PYTHON_O_AS                        2
#define SV_PYTHON_O_ASSERT                    3
#define SV_PYTHON_O_BREAK                     4
#define SV_PYTHON_O_CLASS                     5
#define SV_PYTHON_O_CONTINUE                  6
#define SV_PYTHON_O_DEF                       7
#define SV_PYTHON_O_DEL                       8
#define SV_PYTHON_O_ELIF                      9
#define SV_PYTHON_O_ELSE                     10
#define SV_PYTHON_O_EXCEPT                   11
#define SV_PYTHON_O_EXEC                     12
#define SV_PYTHON_O_FINALLY                  13
#define SV_PYTHON_O_FOR                      14
#define SV_PYTHON_O_FROM                     15
#define SV_PYTHON_O_GLOBAL                   16
#define SV_PYTHON_O_IF                       17
#define SV_PYTHON_O_IMPORT                   18
#define SV_PYTHON_O_IN                       19
#define SV_PYTHON_O_IS                       20
#define SV_PYTHON_O_LAMBDA                   21
#define SV_PYTHON_O_NOT                      22
#define SV_PYTHON_O_OR                       23
#define SV_PYTHON_O_PASS                     24
#define SV_PYTHON_O_PRINT                    25
#define SV_PYTHON_O_RAISE                    26
#define SV_PYTHON_O_RETURN                   27
#define SV_PYTHON_O_TRY                      28
#define SV_PYTHON_O_WHILE                    29
#define SV_PYTHON_O_YIELD                    30
#define SV_PYTHON  31
#endif

/*====================================================================*
 *   program variables;
 *--------------------------------------------------------------------*/

char const *sv_python [SV_PYTHON+1] = 

{
	"None",
	"and",
	"as",
	"assert",
	"break",
	"class",
	"continue",
	"def",
	"del",
	"elif",
	"else",
	"except",
	"exec",
	"finally",
	"for",
	"from",
	"global",
	"if",
	"import",
	"in",
	"is",
	"lambda",
	"not",
	"or",
	"pass",
	"print",
	"raise",
	"return",
	"try",
	"while",
	"yield",
	(char const *)(0)
};

