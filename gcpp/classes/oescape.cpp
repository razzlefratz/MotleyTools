/*====================================================================*
 *
 *   oescape.cpp - implementation of the oescape class.
 *
 *   escape character translation table; each entry represents a character
 *   and contains either it's own character value or that of another where
 *   the other is the intended one; for example, '\b' means a backspace so
 *   the location for 'b' contains 8 which is the code for backspace;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oESCAPE_SOURCE
#define oESCAPE_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <climits>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/oescape.hpp"

#ifndef isoctal
#define isoctal(c) (((c) >= '0') && ((c) <= '7'))
#endif

/*====================================================================*
 *   program variables;
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
 *  [Ä] [Å] [Ç] [É] [Ñ] [Ö] [Ü] [á] [à] [â] [ä] [ã] [å] [ç] [é] [è]
 *  [ê] [ë] [í] [ì] [î] [ï] [ñ] [ó] [ò] [ô] [ö] [õ] [ú] [ù] [û] [ü]
 *  [†] [°] [¢] [£] [§] [•] [¶] [ß] [®] [©] [™] [´] [¨] [≠] [Æ] [Ø]
 *  [∞] [±] [≤] [≥] [¥] [µ] [∂] [∑] [∏] [π] [∫] [ª] [º] [Ω] [æ] [ø]
 *  [¿] [¡] [¬] [√] [ƒ] [≈] [∆] [«] [»] […] [ ] [À] [Ã] [Õ] [Œ] [œ]
 *  [–] [—] [“] [”] [‘] [’] [÷] [◊] [ÿ] [Ÿ] [⁄] [€] [‹] [›] [ﬁ] [ﬂ]
 *  [‡] [·] [‚] [„] [‰] [Â] [Ê] [Á] [Ë] [È] [Í] [Î] [Ï] [Ì] [Ó] [Ô]
 *  [] [Ò] [Ú] [Û] [Ù] [ı] [ˆ] [˜] [¯] [˘] [˙] [˚] [¸] [˝] [˛] [ˇ]
 *
 *--------------------------------------------------------------------*/

unsigned char oescape::mtable [UCHAR_MAX +  1] =

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
	34,
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
	7,
	8,
	99,
	127,
	27,
	12,
	103,
	104,
	105,
	106,
	107,
	108,
	109,
	10,
	111,
	112,
	39,
	13,
	32,
	9,
	117,
	11,
	119,
	120,
	121,
	122,
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
 *   unsigned oescape::define (signed c, unsigned e);
 *
 *   define the unescape value for character c;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

unsigned oescape::define (signed c, signed e)

{
	return (oescape::mtable [c & UCHAR_MAX] = e & UCHAR_MAX);
}

/*====================================================================*
 *
 *   unsigned oescape::unescaped (signed c) const;
 *
 *   return the equivalent an ascii character of an escape character
 *   or itself, if no equivalent is defined;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

unsigned oescape::unescape (signed c)

{
	return (oescape::mtable [(unsigned) (c) & UCHAR_MAX]);
}

/*====================================================================*
 *
 *   char * unescape (char *string) const;
 *
 *   scan a string for character escape sequences of the form '\ddd',
 *   '\c' and '^c'; replace each with an ASCII character value; return
 *   the string argument as the function value;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char * oescape::unescape (register char * string)

{
	register char * sp = string;
	register char * cp = string;
	if (string) for (sp = cp = string; (* sp = * cp++); ++ sp)
	{
		if (* sp == '\\')
		{
			if (isoctal (* cp))
			{
				unsigned digits = 3;
				while ((digits--) && isoctal (* cp))
				{
					* sp *= 8;
					* sp += * cp++ - '0';
				}
				continue;
			}
			if ((* cp == 'x') || (* cp == 'X'))
			{
				cp++;
				* sp = 0;
				if (oascii::isxdigit (* cp))
				{
					* sp = (* sp << 4) +  oascii::todigit (* cp++);
				}
				if (oascii::isxdigit (* cp))
				{
					* sp = (* sp << 4) +  oascii::todigit (* cp++);
				}
				continue;
			}

#if oESCAPE_NOTABLE

			switch (* cp)
			{
			case 'a':
				* sp = '\a';
				break;
			case 'b':
				* sp = '\b';
				break;
			case 'f':
				* sp = '\f';
				break;
			case 'n':
				* sp = '\n';
				break;
			case 'r':
				* sp = '\r';
				break;
			case 't':
				* sp = '\t';
				break;
			case 'v':
				* sp = '\v';
				break;
			case '?':
				* sp = '\?';
				break;
			case '\'':
				* sp = '\'';
				break;
			case '\"':
				* sp = '\"';
				break;
			case '\\':
				* sp = '\\';
				break;
			default: 
				* sp = * cp;
				break;
			}
			cp++;

#else

			* sp = oescape::unescape (* cp++);

#endif

			continue;
		}

#if oESCAPE_ISO_646_1983

		if (* sp == '?')
		{
			if (* cp == '?')
			{
				switch (* ++ cp)
				{
				case '=':
					* sp = '#';
					break;
				case '(':
					* sp = '[';
					break;
				case '/':
					* sp = '\\';
					break;
				case ')':
					* sp = ']';
					break;
				case '\'':
					* sp = '^';
					break;
				case '<':
					* sp = '{';
					break;
				case '!':
					* sp = '|';
					break;
				case '>':
					* sp = '}';
					break;
				case '-':
					* sp = '~';
					break;
				default: 
					* ++ sp = '?';
					* ++ sp = * cp;
					break;
				}
				cp++;
			}
			continue;
		}

#endif

		if (* sp == '^')
		{
			* sp = oascii::tocntrl (* cp++);
			continue;
		}
	}
	return (string);
}

/*====================================================================*
 *
 *   oescape ();
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oescape::oescape ()

{
	return;
}

/*====================================================================*
 *
 *   ~oescape ();
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oescape::~ oescape ()

{
	return;
}

/*====================================================================*
 *   end implementation;
 *--------------------------------------------------------------------*/

#endif



