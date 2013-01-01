/*====================================================================*
 *
 *   sv_textp - text formatter commands
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include <stdio.h>

#define TP_O_BR                           0
#define TP_O_CE                           1
#define TP_O_EJ                           2
#define TP_O_EL                           3
#define TP_O_FU                           4
#define TP_O_IN                           5
#define TP_O_LC                           6
#define TP_O_LE                           7
#define TP_O_LI                           8
#define TP_O_LM                           9
#define TP_O_NC                          10
#define TP_O_PA                          11
#define TP_O_RI                          12
#define TP_O_RM                          13
#define TP_O_SP                          14
#define TP_O_TI                          15
#define TP_O_UC                          16
#define TP_O_NULL                        17

char const *sv_tp [] = 

{
	"br",
	"ce",
	"ej",
	"el",
	"fu",
	"in",
	"lc",
	"le",
	"li",
	"lm",
	"nc",
	"pa",
	"ri",
	"rm",
	"sp",
	"ti",
	"uc",
	NULL
};

