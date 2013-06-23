/*====================================================================*
 *
 *   ochrupr.cpp - definition of ochrupr class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oCHRUPR_SOURCE
#define oCHRUPR_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <climits>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/ochrupr.hpp"

/*====================================================================*
 *   class variables;
 *--------------------------------------------------------------------*
 *
 *  NUL SOH STX ETX EOT ENQ ACK BEL BS  HT  LF  VT  FF  CR  SO  SI
 *  DLE DC1 DC2 DC3 DC4 NAK SYN ETB CAN EM  SUB ESC FS  GS  RS  US
 *  [ ] [!] ["] [#] [$] [%] [&] ['] [(] [)] [*] [+] [,] [-] [.] [/]
 *  [0] [1] [2] [3] [4] [5] [6] [7] [8] [9] [:] [;] [<] [=] [>] [?]
 *  [@] [A] [B] [C] [D] [E] [F] [G] [H] [I] [J] [K] [L] [M] [N] [O]
 *  [P] [Q] [R] [S] [T] [U] [V] [W] [X] [Y] [Z] [[] [\] []] [^] [_]
 *  [ ] [a] [b] [c] [d] [e] [f] [g] [h] [i] [j] [k] [l] [m] [n] [o]
 *  [p] [q] [r] [s] [t] [u] [v] [w] [x] [y] [z] [{] [|] [}] [~] DEL
 *  [�] [�] [�] [�] [�] [�] [�] [�] [�] [�] [�] [�] [�] [�] [�] [�]
 *  [�] [�] [�] [�] [�] [�] [�] [�] [�] [�] [�] [�] [�] [�] [�] [�]
 *  [�] [�] [�] [�] [�] [�] [�] [�] [�] [�] [�] [�] [�] [�] [�] [�]
 *  [�] [�] [�] [�] [�] [�] [�] [�] [�] [�] [�] [�] [�] [�] [�] [�]
 *  [�] [�] [�] [�] [�] [�] [�] [�] [�] [�] [�] [�] [�] [�] [�] [�]
 *  [�] [�] [�] [�] [�] [�] [�] [�] [�] [�] [�] [�] [�] [�] [�] [�]
 *  [�] [�] [�] [�] [�] [�] [�] [�] [�] [�] [�] [�] [�] [�] [�] [�]
 *  [�] [�] [�] [�] [�] [�] [�] [�] [�] [�] [�] [�] [�] [�] [�] [�]
 *
 *--------------------------------------------------------------------*/

const unsigned char ochrupr::table [UCHAR_MAX + 1] = 

{
	0,
	1,
	2,
	3,
	4,
	5,
	6,
	7,
	8,
	9,
	32,
	11,
	12,
	13,
	14,
	15,
	16,
	17,
	18,
	19,
	20,
	21,
	22,
	23,
	24,
	25,
	26,
	27,
	28,
	29,
	30,
	31,
	32,
	33,
	34,
	35,
	36,
	37,
	38,
	39,
	40,
	41,
	42,
	43,
	44,
	45,
	46,
	47,
	48,
	49,
	50,
	51,
	52,
	53,
	54,
	55,
	56,
	57,
	58,
	59,
	60,
	61,
	62,
	63,
	64,
	65,
	66,
	67,
	68,
	67,
	70,
	71,
	72,
	73,
	74,
	75,
	76,
	77,
	78,
	79,
	80,
	81,
	82,
	83,
	84,
	85,
	86,
	87,
	88,
	89,
	90,
	91,
	92,
	93,
	94,
	95,
	96,
	65,
	66,
	67,
	68,
	69,
	70,
	71,
	72,
	73,
	74,
	75,
	76,
	77,
	78,
	79,
	80,
	81,
	82,
	83,
	84,
	85,
	86,
	87,
	88,
	89,
	90,
	123,
	124,
	125,
	126,
	127,
	128,
	129,
	130,
	131,
	132,
	133,
	134,
	135,
	136,
	137,
	138,
	139,
	140,
	141,
	142,
	143,
	144,
	145,
	146,
	147,
	148,
	149,
	150,
	151,
	152,
	153,
	154,
	155,
	156,
	157,
	158,
	159,
	160,
	161,
	162,
	163,
	164,
	165,
	166,
	167,
	168,
	169,
	170,
	171,
	172,
	173,
	174,
	175,
	176,
	177,
	178,
	179,
	180,
	181,
	182,
	183,
	184,
	185,
	186,
	187,
	188,
	189,
	190,
	191,
	192,
	193,
	194,
	195,
	196,
	197,
	198,
	199,
	200,
	201,
	202,
	203,
	204,
	205,
	206,
	207,
	208,
	209,
	210,
	211,
	212,
	213,
	214,
	215,
	216,
	217,
	218,
	219,
	220,
	221,
	222,
	223,
	224,
	225,
	226,
	227,
	228,
	229,
	230,
	231,
	232,
	233,
	234,
	235,
	236,
	237,
	238,
	239,
	240,
	241,
	242,
	243,
	244,
	245,
	246,
	247,
	248,
	249,
	250,
	251,
	252,
	253,
	254,
	255
};

/*====================================================================*
 *
 *   ochrupr();
 *
 *   set base translation table to uppercase character table;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ochrupr::ochrupr () 

{
	ochrtbl::mtable = ochrupr::table;
	return;
}

/*====================================================================*
 *
 *   ~ochrupr();
 *
 *   nothing to do;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ochrupr::~ochrupr () 

{
	return;
}

/*====================================================================*
 *   end definition;
 *--------------------------------------------------------------------*/

#endif

