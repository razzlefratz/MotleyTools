/*====================================================================*
 *
 *   extern unsigned char ct_ascii[];
 *
 *   this table contains the ascii codes for ebcdic characters stored by
 *   ebcdic value; use an ebcdic code as the index to find an ascii code;
 *   for example:
 *
 *   #define _toascii(c) (ct_ascii[(unsigned)(c)])
 *
 *   this implementation only converts to 7 bit ascii codes because some
 *   ebcdic codes had no ascii equivalent;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include <limits.h>

unsigned char ct_ascii [UCHAR_MAX+1] = 

{
	0,
	1,
	2,
	3,
	0,
	9,
	0,
	127,
	0,
	0,
	0,
	11,
	12,
	13,
	14,
	15,
	16,
	17,
	18,
	19,
	0,
	0,
	8,
	0,
	24,
	25,
	0,
	0,
	28,
	29,
	30,
	31,
	0,
	0,
	0,
	0,
	0,
	10,
	23,
	27,
	0,
	0,
	0,
	0,
	0,
	5,
	6,
	7,
	0,
	0,
	22,
	0,
	0,
	0,
	0,
	4,
	0,
	0,
	0,
	0,
	20,
	21,
	0,
	26,
	32,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	46,
	60,
	40,
	43,
	124,
	38,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	33,
	36,
	42,
	41,
	59,
	94,
	45,
	47,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	24,
	44,
	37,
	95,
	62,
	63,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	96,
	58,
	35,
	64,
	39,
	61,
	34,
	0,
	97,
	98,
	99,
	100,
	101,
	102,
	103,
	104,
	105,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	106,
	107,
	108,
	109,
	110,
	111,
	112,
	113,
	114,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	126,
	115,
	116,
	117,
	118,
	119,
	120,
	121,
	122,
	0,
	0,
	0,
	91,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	93,
	0,
	0,
	123,
	65,
	66,
	67,
	68,
	69,
	70,
	71,
	72,
	73,
	0,
	0,
	0,
	0,
	0,
	0,
	125,
	74,
	75,
	76,
	77,
	78,
	79,
	80,
	81,
	82,
	0,
	0,
	0,
	0,
	0,
	0,
	92,
	0,
	83,
	84,
	85,
	86,
	87,
	88,
	89,
	90,
	0,
	0,
	0,
	0,
	0,
	0,
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
	0,
	0,
	0,
	0,
	0,
	0
};

