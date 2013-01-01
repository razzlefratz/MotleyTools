/*====================================================================*
 *
 *   sv_ps[] -
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include <stddef.h>

#define PS_O_ABS                          0
#define PS_O_ADD                          1
#define PS_O_ALOAD                        2
#define PS_O_ANCHORSEARCH                 3
#define PS_O_AND                          4
#define PS_O_ARC                          5
#define PS_O_ARCTO                        6
#define PS_O_ARRAY                        7
#define PS_O_ASHOW                        8
#define PS_O_ASTORE                       9
#define PS_O_ATAN                        10
#define PS_O_AWIDTHSHOW                  11
#define PS_O_BANDDEVICE                  12
#define PS_O_BEGIN                       13
#define PS_O_BIND                        14
#define PS_O_BITSHIFT                    15
#define PS_O_BYTESAVAILABLE              16
#define PS_O_CACHESTATUS                 17
#define PS_O_CEILING                     18
#define PS_O_CHARPATH                    19
#define PS_O_CLEAR                       20
#define PS_O_CLEARTOMARK                 21
#define PS_O_CLIP                        22
#define PS_O_CLIPPATH                    23
#define PS_O_CLOSEFILE                   24
#define PS_O_CLOSEPATH                   25
#define PS_O_CONCAT                      26
#define PS_O_CONCATMATRIX                27
#define PS_O_COPY                        28
#define PS_O_COPYPAGE                    29
#define PS_O_COS                         30
#define PS_O_COUNT                       31
#define PS_O_COUNTDICTSTACK              32
#define PS_O_COUNTEXECSTACK              33
#define PS_O_COUNTTOMARK                 34
#define PS_O_CURRENTDASH                 35
#define PS_O_CURRENTDICT                 36
#define PS_O_CURRENTFILE                 37
#define PS_O_CURRENTFLAT                 38
#define PS_O_CURRENTFONT                 39
#define PS_O_CURRENTGRAY                 40
#define PS_O_CURRENTHSBCOLOR             41
#define PS_O_CURRENTLINECAP              42
#define PS_O_CURRENTLINEJOIN             43
#define PS_O_CURRENTLINEWIDTH            44
#define PS_O_CURRENTMATRIX               45
#define PS_O_CURRENTMITERLIMIT           46
#define PS_O_CURRENTPOINT                47
#define PS_O_CURRENTRGBCOLOR             48
#define PS_O_CURRENTSCREEN               49
#define PS_O_CURRENTTRANSFER             50
#define PS_O_CURVETO                     51
#define PS_O_CVI                         52
#define PS_O_CVLIT                       53
#define PS_O_CVN                         54
#define PS_O_CVR                         55
#define PS_O_CVRS                        56
#define PS_O_CVS                         57
#define PS_O_CVX                         58
#define PS_O_DEF                         59
#define PS_O_DEFAULTMATRIX               60
#define PS_O_DEFINEFONT                  61
#define PS_O_DICT                        62
#define PS_O_DICTFULL                    63
#define PS_O_DICTSTACK                   64
#define PS_O_DICTSTACKOVERFLOW           65
#define PS_O_DICTSTACKUNDERFLOW          66
#define PS_O_DIV                         67
#define PS_O_DTRANSFORM                  68
#define PS_O_DUP                         69
#define PS_O_ECHO                        70
#define PS_O_END                         71
#define PS_O_EOCLIP                      72
#define PS_O_EOFILL                      73
#define PS_O_EQ                          74
#define PS_O_ERASEPAGE                   75
#define PS_O_ERRORDICT                   76
#define PS_O_EXCH                        77
#define PS_O_EXEC                        78
#define PS_O_EXECSTACK                   79
#define PS_O_EXECSTACKOVERFLOW           80
#define PS_O_EXECUTEONLY                 81
#define PS_O_EXIT                        82
#define PS_O_EXP                         83
#define PS_O_FALSE                       84
#define PS_O_FILE                        85
#define PS_O_FILL                        86
#define PS_O_FINDFONT                    87
#define PS_O_FLATTENPATH                 88
#define PS_O_FLOOR                       89
#define PS_O_FLUSH                       90
#define PS_O_FLUSHFILE                   91
#define PS_O_FONTDIRECTORY               92
#define PS_O_FOR                         93
#define PS_O_FORALL                      94
#define PS_O_FRAMEDEVICE                 95
#define PS_O_GE                          96
#define PS_O_GET                         97
#define PS_O_GETINTERVAL                 98
#define PS_O_GRESTORE                    99
#define PS_O_GRESTOREALL                100
#define PS_O_GSAVE                      101
#define PS_O_HANDLEERROR                102
#define PS_O_INDENTMATRIX               103
#define PS_O_IDIV                       104
#define PS_O_IDTRANSFORM                105
#define PS_O_IF                         106
#define PS_O_IFELSE                     107
#define PS_O_IMAGE                      108
#define PS_O_IMAGEMASK                  109
#define PS_O_INDEX                      110
#define PS_O_INITCLIP                   111
#define PS_O_INITGRAPHICS               112
#define PS_O_INITMATRIX                 113
#define PS_O_INTERRUPT                  114
#define PS_O_INVALIDACCESS              115
#define PS_O_INVALIDEXIT                116
#define PS_O_INVALIDFILEACCESS          117
#define PS_O_INVALIDFONT                118
#define PS_O_INVALIDRESTORE             119
#define PS_O_INVERTMATRIX               120
#define PS_O_IOERROR                    121
#define PS_O_ITRANSFORM                 122
#define PS_O_KNOWN                      123
#define PS_O_KSHOW                      124
#define PS_O_LE                         125
#define PS_O_LENGTH                     126
#define PS_O_LIMITCHECK                 127
#define PS_O_LOAD                       128
#define PS_O_LOG                        129
#define PS_O_LOOP                       130
#define PS_O_MAKEFONT                   131
#define PS_O_MARK                       132
#define PS_O_MATRIX                     133
#define PS_O_MAXLENGTH                  134
#define PS_O_MOD                        135
#define PS_O_MOVETO                     136
#define PS_O_MUL                        137
#define PS_O_NE                         138
#define PS_O_NEG                        139
#define PS_O_NEWPATH                    140
#define PS_O_NOACCESS                   141
#define PS_O_NOCURRENTPOINT             142
#define PS_O_NOT                        143
#define PS_O_NULL                       144
#define PS_O_NULLDEVICE                 145
#define PS_O_OR                         146
#define PS_O_PATHBBOX                   147
#define PS_O_PATHFORALL                 148
#define PS_O_POP                        149
#define PS_O_PRINT                      150
#define PS_O_PROMPT                     151
#define PS_O_PSTACK                     152
#define PS_O_PUT                        153
#define PS_O_PUTINTERVAL                154
#define PS_O_QUIT                       155
#define PS_O_RAND                       156
#define PS_O_RANGECHECK                 157
#define PS_O_RCHECK                     158
#define PS_O_RCURVETO                   159
#define PS_O_READ                       160
#define PS_O_READHEXSTRING              161
#define PS_O_READLINE                   162
#define PS_O_READONLY                   163
#define PS_O_READSTRING                 164
#define PS_O_RENDERBANDS                165
#define PS_O_REPEAT                     166
#define PS_O_RESETFILE                  167
#define PS_O_RESTORE                    168
#define PS_O_REVERSEPATH                169
#define PS_O_RLINETO                    170
#define PS_O_RMOVETO                    171
#define PS_O_ROLL                       172
#define PS_O_ROTATE                     173
#define PS_O_ROUND                      174
#define PS_O_RRAND                      175
#define PS_O_RUN                        176
#define PS_O_SAVE                       177
#define PS_O_SCALE                      178
#define PS_O_SCALEFONT                  179
#define PS_O_SEARCH                     180
#define PS_O_SETCACHEDEVICE             181
#define PS_O_SETCACHELIMIT              182
#define PS_O_SETCHARWIDTH               183
#define PS_O_SETDASH                    184
#define PS_O_SETFLAT                    185
#define PS_O_SETFONT                    186
#define PS_O_SETGRAY                    187
#define PS_O_SETRSBCOLOR                188
#define PS_O_SETLINECAP                 189
#define PS_O_SETLINEJOIN                190
#define PS_O_SETLINEWIDTH               191
#define PS_O_SETMATRIX                  192
#define PS_O_SETMITERLIMIT              193
#define PS_O_SETRGBCOLOR                194
#define PS_O_SETSCREEN                  195
#define PS_O_SETTRANSFER                196
#define PS_O_SHOW                       197
#define PS_O_SHOWPAGE                   198
#define PS_O_SIN                        199
#define PS_O_SQRT                       200
#define PS_O_SRAND                      201
#define PS_O_STACK                      202
#define PS_O_STACKOVERFLOW              203
#define PS_O_STACKUNDERFLOW             204
#define PS_O_STANDARDENCODING           205
#define PS_O_START                      206
#define PS_O_STATUS                     207
#define PS_O_STOP                       208
#define PS_O_STOPPED                    209
#define PS_O_STORE                      210
#define PS_O_STRING                     211
#define PS_O_STRINGWIDTH                212
#define PS_O_STROKE                     213
#define PS_O_STROKEPATH                 214
#define PS_O_SYNTAXERROR                215
#define PS_O_SYSTEMDICT                 216
#define PS_O_TIMEOUT                    217
#define PS_O_TOKEN                      218
#define PS_O_TRANSFORM                  219
#define PS_O_TRANSLATE                  220
#define PS_O_TRUE                       221
#define PS_O_TRUNCATE                   222
#define PS_O_TYPE                       223
#define PS_O_TYPECHECK                  224
#define PS_O_UNDEFINED                  225
#define PS_O_UNDEFINEDFILENAME          226
#define PS_O_UNDEFINEDRESULT            227
#define PS_O_UMATCHEDMARK               228
#define PS_O_UNREGISTERED               229
#define PS_O_USERDICT                   230
#define PS_O_USERTIME                   231
#define PS_O_VERSION                    232
#define PS_O_VMERROR                    233
#define PS_O_VMSTATUS                   234
#define PS_O_WCHECCK                    235
#define PS_O_WHERE                      236
#define PS_O_WIDTHSHOW                  237
#define PS_O_WRITE                      238
#define PS_O_WRITEHEXSTRING             239
#define PS_O_WRITESTRING                240
#define PS_O_XCHECK                     241
#define PS_O_XOR                        242

char const *sv_ps [] = 

{
	"abs",
	"add",
	"aload",
	"anchorsearch",
	"and",
	"arc",
	"arcto",
	"array",
	"ashow",
	"astore",
	"atan",
	"awidthshow",
	"banddevice",
	"begin",
	"bind",
	"bitshift",
	"bytesavailable",
	"cachestatus",
	"ceiling",
	"charpath",
	"clear",
	"cleartomark",
	"clip",
	"clippath",
	"closefile",
	"closepath",
	"concat",
	"concatmatrix",
	"copy",
	"copypage",
	"cos",
	"count",
	"countdictstack",
	"countexecstack",
	"counttomark",
	"currentdash",
	"currentdict",
	"currentfile",
	"currentflat",
	"currentfont",
	"currentgray",
	"currenthsbcolor",
	"currentlinecap",
	"currentlinejoin",
	"currentlinewidth",
	"currentmatrix",
	"currentmiterlimit",
	"currentpoint",
	"currentrgbcolor",
	"currentscreen",
	"currenttransfer",
	"curveto",
	"cvi",
	"cvlit",
	"cvn",
	"cvr",
	"cvrs",
	"cvs",
	"cvx",
	"def",
	"defaultmatrix",
	"definefont",
	"dict",
	"dictfull",
	"dictstack",
	"dictstackoverflow",
	"dictstackunderflow",
	"div",
	"dtransform",
	"dup",
	"echo",
	"end",
	"eoclip",
	"eofill",
	"eq",
	"erasepage",
	"errordict",
	"exch",
	"exec",
	"execstack",
	"execstackoverflow",
	"executeonly",
	"exit",
	"exp",
	"false",
	"file",
	"fill",
	"findfont",
	"flattenpath",
	"floor",
	"flush",
	"flushfile",
	"FontDirectory",
	"for",
	"forall",
	"framedevice",
	"ge",
	"get",
	"getinterval",
	"grestore",
	"grestoreall",
	"gsave",
	"handleerror",
	"indentmatrix",
	"idiv",
	"idtransform",
	"if",
	"ifelse",
	"image",
	"imagemask",
	"index",
	"initclip",
	"initgraphics",
	"initmatrix",
	"interrupt",
	"invalidaccess",
	"invalidexit",
	"invalidfileaccess",
	"invalidfont",
	"invalidrestore",
	"invertmatrix",
	"ioerror",
	"itransform",
	"known",
	"kshow",
	"le",
	"length",
	"limitcheck",
	"load",
	"log",
	"loop",
	"makefont",
	"mark",
	"matrix",
	"maxlength",
	"mod",
	"moveto",
	"mul",
	"ne",
	"neg",
	"newpath",
	"noaccess",
	"nocurrentpoint",
	"not",
	"null",
	"nulldevice",
	"or",
	"pathbbox",
	"pathforall",
	"pop",
	"print",
	"prompt",
	"pstack",
	"put",
	"putinterval",
	"quit",
	"rand",
	"rangecheck",
	"rcheck",
	"rcurveto",
	"read",
	"readhexstring",
	"readline",
	"readonly",
	"readstring",
	"renderbands",
	"repeat",
	"resetfile",
	"restore",
	"reversepath",
	"rlineto",
	"rmoveto",
	"roll",
	"rotate",
	"round",
	"rrand",
	"run",
	"save",
	"scale",
	"scalefont",
	"search",
	"setcachedevice",
	"setcachelimit",
	"setcharwidth",
	"setdash",
	"setflat",
	"setfont",
	"setgray",
	"setrsbcolor",
	"setlinecap",
	"setlinejoin",
	"setlinewidth",
	"setmatrix",
	"setmiterlimit",
	"setrgbcolor",
	"setscreen",
	"settransfer",
	"show",
	"showpage",
	"sin",
	"sqrt",
	"srand",
	"stack",
	"stackoverflow",
	"stackunderflow",
	"StandardEncoding",
	"start",
	"status",
	"stop",
	"stopped",
	"store",
	"string",
	"stringwidth",
	"stroke",
	"strokepath",
	"syntaxerror",
	"systemdict",
	"timeout",
	"token",
	"transform",
	"translate",
	"true",
	"truncate",
	"type",
	"typecheck",
	"undefined",
	"undefinedfilename",
	"undefinedresult",
	"umatchedmark",
	"unregistered",
	"userdict",
	"usertime",
	"version",
	"VMerror",
	"vmstatus",
	"wchecck",
	"where",
	"widthshow",
	"write",
	"writehexstring",
	"writestring",
	"xcheck",
	"xor",
	NULL
};

