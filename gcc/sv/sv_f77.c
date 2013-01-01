/*====================================================================*
 * 
 *   sv_f77[] - 
 * 
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 * 
 *--------------------------------------------------------------------*/

#include <stddef.h>

#define F77_O_ACCEPT                      0
#define F77_O_ACCESS                      1
#define F77_O_ASSERT                      2
#define F77_O_ASSIGN                      3
#define F77_O_ASSOCIATEVARIABLE           4
#define F77_O_AUTOMATIC                   5
#define F77_O_BACKSPACE                   6
#define F77_O_BLANK                       7
#define F77_O_BLOCKDATA                   8
#define F77_O_BLOCKSIZE                   9
#define F77_O_BUFFERCOUNT                10
#define F77_O_CALL                       11
#define F77_O_CARRIAGECONTROL            12
#define F77_O_CASE                       13
#define F77_O_CHARACTER                  14
#define F77_O_CLOSE                      15
#define F77_O_COMMON                     16
#define F77_O_COMPLEX                    17
#define F77_O_CONTINUE                   18
#define F77_O_CONVERT                    19
#define F77_O_CYCLE                      20
#define F77_O_DATA                       21
#define F77_O_DECODE                     22
#define F77_O_DEFAULTFILE                23
#define F77_O_DELETE                     24
#define F77_O_DIMENSION                  25
#define F77_O_DIRECT                     26
#define F77_O_DISPOSE                    27
#define F77_O_DO                         28
#define F77_O_DOWHILE                    29
#define F77_O_DOUBLE                     30
#define F77_O_ELSE                       31
#define F77_O_ELSEIF                     32
#define F77_O_ENCODE                     33
#define F77_O_END                        34
#define F77_O_ENDDO                      35
#define F77_O_ENDIF                      36
#define F77_O_ENDMAP                     37
#define F77_O_ENDSELECT                  38
#define F77_O_ENDSTRUCTURE               39
#define F77_O_ENDUNION                   40
#define F77_O_ENDFILE                    41
#define F77_O_ENTRY                      42
#define F77_O_EQUVALENCE                 43
#define F77_O_ERR                        44
#define F77_O_EXIST                      45
#define F77_O_EXIT                       46
#define F77_O_EXTENDSIZE                 47
#define F77_O_EXTERNAL                   48
#define F77_O_FILE                       49
#define F77_O_FORM                       50
#define F77_O_FORMAT                     51
#define F77_O_FORMATTED                  52
#define F77_O_FUNCTION                   53
#define F77_O_GOTO                       54
#define F77_O_IF                         55
#define F77_O_IMPLICIT                   56
#define F77_O_IMPLICITNONE               57
#define F77_O_INCLUDE                    58
#define F77_O_INITIALSIZE                59
#define F77_O_INQUIRE                    60
#define F77_O_INTEGER                    61
#define F77_O_INTRINSIC                  62
#define F77_O_IOSTAT                     63
#define F77_O_KEY                        64
#define F77_O_KEYED                      65
#define F77_O_LOGICAL                    66
#define F77_O_MAP                        67
#define F77_O_MAXREC                     68
#define F77_O_NAME                       69
#define F77_O_NAMED                      70
#define F77_O_NAMELIST                   71
#define F77_O_NEXTREC                    72
#define F77_O_NOSPANBLOCKS               73
#define F77_O_NUMBER                     74
#define F77_O_OPEN                       75
#define F77_O_OPENED                     76
#define F77_O_OPTIONS                    77
#define F77_O_ORGANIZATION               78
#define F77_O_PARAMETER                  79
#define F77_O_PAUSE                      80
#define F77_O_POINTER                    81
#define F77_O_PRINT                      82
#define F77_O_PROGRAM                    83
#define F77_O_READ                       84
#define F77_O_READONLY                   85
#define F77_O_REAL                       86
#define F77_O_RECL                       87
#define F77_O_RECORD                     88
#define F77_O_RECORDSIZE                 89
#define F77_O_RECORDTYPE                 90
#define F77_O_RETURN                     91
#define F77_O_REWIND                     92
#define F77_O_REWRITE                    93
#define F77_O_SAVE                       94
#define F77_O_SEQUENTIAL                 95
#define F77_O_SHARED                     96
#define F77_O_STATIC                     97
#define F77_O_STATUS                     98
#define F77_O_STOP                       99
#define F77_O_STRUCTURE                 100
#define F77_O_SUBROUTINE                101
#define F77_O_TYPE                      102
#define F77_O_UNFORMATTED               103
#define F77_O_UNION                     104
#define F77_O_UNIT                      105
#define F77_O_UNLOCK                    106
#define F77_O_USEROPEN                  107
#define F77_O_VOLATILE                  108
#define F77_O_WRITE                     109
#define F77_O_NULL                      110
#define F77_N_ITEM                      110

char const *sv_f77 [] = 

{
	"ACCEPT",
	"ACCESS",
	"ASSERT",
	"ASSIGN",
	"ASSOCIATEVARIABLE",
	"AUTOMATIC",
	"BACKSPACE",
	"BLANK",
	"BLOCK DATA",
	"BLOCKSIZE",
	"BUFFERCOUNT",
	"CALL ",
	"CARRIAGE CONTROL",
	"CASE",
	"CHARACTER",
	"CLOSE",
	"COMMON",
	"COMPLEX",
	"CONTINUE",
	"CONVERT",
	"CYCLE",
	"DATA",
	"DECODE",
	"DEFAULTFILE",
	"DELETE",
	"DIMENSION",
	"DIRECT",
	"DISPOSE",
	"DO",
	"DO WHILE",
	"DOUBLE",
	"ELSE",
	"ELSE IF",
	"ENCODE",
	"END",
	"END DO",
	"END IF",
	"END MAP",
	"END SELECT",
	"END STRUCTURE",
	"END UNION",
	"ENDFILE",
	"ENTRY",
	"EQUVALENCE",
	"ERR",
	"EXIST",
	"EXIT",
	"EXTENDSIZE",
	"EXTERNAL",
	"FILE",
	"FORM",
	"FORMAT",
	"FORMATTED",
	"FUNCTION",
	"GOTO",
	"IF",
	"IMPLICIT",
	"IMPLICIT NONE",
	"INCLUDE",
	"INITIALSIZE",
	"INQUIRE",
	"INTEGER",
	"INTRINSIC",
	"IOSTAT",
	"KEY",
	"KEYED",
	"LOGICAL",
	"MAP",
	"MAXREC",
	"NAME",
	"NAMED",
	"NAMELIST",
	"NEXTREC",
	"NOSPANBLOCKS",
	"NUMBER",
	"OPEN",
	"OPENED",
	"OPTIONS",
	"ORGANIZATION",
	"PARAMETER",
	"PAUSE",
	"POINTER",
	"PRINT",
	"PROGRAM",
	"READ",
	"READONLY",
	"REAL",
	"RECL",
	"RECORD",
	"RECORDSIZE",
	"RECORDTYPE",
	"RETURN",
	"REWIND",
	"REWRITE",
	"SAVE",
	"SEQUENTIAL",
	"SHARED",
	"STATIC",
	"STATUS",
	"STOP",
	"STRUCTURE",
	"SUBROUTINE",
	"TYPE",
	"UNFORMATTED",
	"UNION",
	"UNIT",
	"UNLOCK",
	"USEROPEN",
	"VOLATILE",
	"WRITE",
	NULL
};

