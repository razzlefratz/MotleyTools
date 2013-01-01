/*====================================================================*
 *
 *   sv_vb6[] -
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include <stddef.h>

#define VB6_O_ABS                         0
#define VB6_O_ACCESS                      1
#define VB6_O_ALIAS                       2
#define VB6_O_AND                         3
#define VB6_O_ANY                         4
#define VB6_O_AS                          5
#define VB6_O_ATTRIBUTE                   6
#define VB6_O_BINARY                      7
#define VB6_O_BOOLEAN                     8
#define VB6_O_BYREF                       9
#define VB6_O_BYVAL                      10
#define VB6_O_BYTE                       11
#define VB6_O_CALL                       12
#define VB6_O_CASE                       13
#define VB6_O_CLOSE                      14
#define VB6_O_COMPARE                    15
#define VB6_O_CONST                      16
#define VB6_O_DATE                       17
#define VB6_O_DECLARE                    18
#define VB6_O_DIM                        19
#define VB6_O_DO                         20
#define VB6_O_DOUBLE                     21
#define VB6_O_EOF                        22
#define VB6_O_EACH                       23
#define VB6_O_ELSE                       24
#define VB6_O_ELSEIF                     25
#define VB6_O_END                        26
#define VB6_O_ENUM                       27
#define VB6_O_ERROR                      28
#define VB6_O_EVENTS                     29
#define VB6_O_EXIT                       30
#define VB6_O_EXPLICIT                   31
#define VB6_O_FALSE                      32
#define VB6_O_FIX                        33
#define VB6_O_FOR                        34
#define VB6_O_FUNCTION                   35
#define VB6_O_GET                        36
#define VB6_O_GOTO                       37
#define VB6_O_IF                         38
#define VB6_O_IMP                        39
#define VB6_O_INPUT                      40
#define VB6_O_INSTR                      41
#define VB6_O_INSTRREV                   42
#define VB6_O_INT                        43
#define VB6_O_INTEGER                    44
#define VB6_O_IS                         45
#define VB6_O_JOIN                       46
#define VB6_O_LBOUND                     47
#define VB6_O_LOF                        48
#define VB6_O_LEFT                       49
#define VB6_O_LEN                        50
#define VB6_O_LET                        51
#define VB6_O_LIB                        52
#define VB6_O_LONG                       53
#define VB6_O_LOOP                       54
#define VB6_O_ME                         55
#define VB6_O_MID                        56
#define VB6_O_MOD                        57
#define VB6_O_NEXT                       58
#define VB6_O_NOT                        59
#define VB6_O_NOTHING                    60
#define VB6_O_NULL                       61
#define VB6_O_OBJECT                     62
#define VB6_O_ON                         63
#define VB6_O_OPEN                       64
#define VB6_O_OPTION                     65
#define VB6_O_OPTIONAL                   66
#define VB6_O_OR                         67
#define VB6_O_OUTPUT                     68
#define VB6_O_PRESERVE                   69
#define VB6_O_PRINT                      70
#define VB6_O_PRIVATE                    71
#define VB6_O_PROPERTY                   72
#define VB6_O_PUBLIC                     73
#define VB6_O_PUT                        74
#define VB6_O_QUIT                       75
#define VB6_O_RAISEEVENT                 76
#define VB6_O_REDIM                      77
#define VB6_O_READ                       78
#define VB6_O_REM                        79
#define VB6_O_REPLACE                    80
#define VB6_O_RESUME                     81
#define VB6_O_RETURN                     82
#define VB6_O_RIGHT                      83
#define VB6_O_SELECT                     84
#define VB6_O_SET                        85
#define VB6_O_SGN                        86
#define VB6_O_SINGLE                     87
#define VB6_O_SPLIT                      88
#define VB6_O_STEP                       89
#define VB6_O_STOP                       90
#define VB6_O_STRING                     91
#define VB6_O_SUB                        92
#define VB6_O_THEN                       93
#define VB6_O_TO                         94
#define VB6_O_TRIM                       95
#define VB6_O_TRUE                       96
#define VB6_O_TYPE                       97
#define VB6_O_UBOUND                     98
#define VB6_O_UNTIL                      99
#define VB6_O_VARIANT                   100
#define VB6_O_WHILE                     101
#define VB6_O_WITH                      102
#define VB6_O_WRITE                     103
#define VB6_O_XOR                       104

char const *sv_vb6 [] = 

{
	"Abs",
	"Access",
	"Alias",
	"And",
	"Any",
	"As",
	"Attribute",
	"Binary",
	"Boolean",
	"ByRef",
	"ByVal",
	"Byte",
	"Call",
	"Case",
	"Close",
	"Compare",
	"Const",
	"Date",
	"Declare",
	"Dim",
	"Do",
	"Double",
	"EOF",
	"Each",
	"Else",
	"ElseIf",
	"End",
	"Enum",
	"Error",
	"Events",
	"Exit",
	"Explicit",
	"False",
	"Fix",
	"For",
	"Function",
	"Get",
	"GoTo",
	"If",
	"Imp",
	"Input",
	"Instr",
	"InstrRev",
	"Int",
	"Integer",
	"Is",
	"Join",
	"LBound",
	"LOF",
	"Left",
	"Len",
	"Let",
	"Lib",
	"Long",
	"Loop",
	"Me",
	"Mid",
	"Mod",
	"Next",
	"Not",
	"Nothing",
	"Null",
	"Object",
	"On",
	"Open",
	"Option",
	"Optional",
	"Or",
	"Output",
	"Preserve",
	"Print",
	"Private",
	"Property",
	"Public",
	"Put",
	"Quit",
	"RaiseEvent",
	"ReDim",
	"Read",
	"Rem",
	"Replace",
	"Resume",
	"Return",
	"Right",
	"Select",
	"Set",
	"Sgn",
	"Single",
	"Split",
	"Step",
	"Stop",
	"String",
	"Sub",
	"Then",
	"To",
	"Trim",
	"True",
	"Type",
	"UBound",
	"Until",
	"Variant",
	"While",
	"With",
	"Write",
	"Xor",
	NULL
};

