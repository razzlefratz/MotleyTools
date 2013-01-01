/*====================================================================*
 *
 *   sv_cword[] -
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SV_CWORD_SOURCE
#define SV_CWORD_SOURCE

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#ifndef CWORD_O_NULL
#define CWORD_O_AUTO                      0
#define CWORD_O_BOOL                      1
#define CWORD_O_BREAK                     2
#define CWORD_O_CASE                      3
#define CWORD_O_CHAR                      4
#define CWORD_O_CONST                     5
#define CWORD_O_CONTINUE                  6
#define CWORD_O_DEFAULT                   7
#define CWORD_O_DO                        8
#define CWORD_O_DOUBLE                    9
#define CWORD_O_ELSE                     10
#define CWORD_O_ENTRY                    11
#define CWORD_O_ENUM                     12
#define CWORD_O_EXTERN                   13
#define CWORD_O_FLOAT                    14
#define CWORD_O_FOR                      15
#define CWORD_O_GOTO                     16
#define CWORD_O_IF                       17
#define CWORD_O_INT                      18
#define CWORD_O_LONG                     19
#define CWORD_O_REGISTER                 20
#define CWORD_O_RETURN                   21
#define CWORD_O_SHORT                    22
#define CWORD_O_SIGNED                   23
#define CWORD_O_SIZE_T_SPEC                   24
#define CWORD_O_STATIC                   25
#define CWORD_O_STRUCT                   26
#define CWORD_O_SWITCH                   27
#define CWORD_O_TYPEDEF                  28
#define CWORD_O_UNION                    29
#define CWORD_O_UNSIGNED                 30
#define CWORD_O_VOID                     31
#define CWORD_O_VOLATILE                 32
#define CWORD_O_WHILE                    33
#define CWORD_O_NULL                     34
#endif

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

char const * sv_cword [] = 

{
	"auto",
	"bool",
	"break",
	"case",
	"char",
	"const",
	"continue",
	"default",
	"do",
	"double",
	"else",
	"entry",
	"enum",
	"extern",
	"float",
	"for",
	"goto",
	"if",
	"int",
	"long",
	"register",
	"return",
	"short",
	"signed",
	"sizeof",
	"static",
	"struct",
	"switch",
	"typedef",
	"union",
	"unsigned",
	"void",
	"volatile",
	"while",
	(char const *)(0)
};


/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif

