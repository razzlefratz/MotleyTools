/*====================================================================*
 *
 *   sign signf(char const *sp, int c, size_t width);
 *
 *   write ofp; produce a matrix of specified width that represents the
 *   contents of the string argument; use character c to populate the
 *   matrix; the width is expressed in characteRs;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <limits.h>

#include "../tools/tools.h"

#define BACK_CHR    0
#define FILL_CHR    1
#define FONT_ROW    9
#define FONT_COL    6

/*====================================================================*
 *
 *            @   @@ @@  @ @    @   @@  @  @     @@      @   @
 *            @   @@ @@  @ @   @@@@ @@  @ @ @    @@     @     @
 *            @    @  @ @@@@@ @ @      @  @ @     @    @       @
 *            @   @  @   @ @   @@@    @    @     @     @       @
 *            @         @@@@@   @ @  @    @ @ @        @       @
 *                       @ @  @@@@  @  @@ @  @          @     @
 *            @          @ @    @   @  @@  @@ @          @   @
 *
 *
 *
 *      @                               @  @@@    @    @@@   @@@
 *    @ @ @   @                         @ @   @  @@   @   @ @   @
 *     @@@    @                        @  @  @@   @       @     @
 *    @@@@@ @@@@@       @@@@@         @   @ @ @   @      @    @@
 *     @@@    @                      @    @@  @   @     @       @
 *    @ @ @   @    @@          @@   @     @   @   @    @    @   @
 *      @          @@          @@   @      @@@   @@@  @@@@@  @@@
 *                  @
 *                 @
 *
 *       @  @@@@@   @@@ @@@@@  @@@   @@@                  @
 *      @@  @      @        @ @   @ @   @  @@            @
 *     @ @  @@@@  @        @  @   @ @   @  @@    @@     @   @@@@@
 *    @  @      @ @@@@    @    @@@   @@@@        @@    @
 *    @@@@@     @ @   @  @    @   @     @  @@           @   @@@@@
 *       @  @   @ @   @ @     @   @    @   @@    @@      @
 *       @   @@@   @@@  @      @@@  @@@          @@       @
 *                                                @
 *                                               @
 *
 *    @      @@@   @@@    @   @@@@   @@@  @@@@  @@@@@ @@@@@  @@@
 *     @    @   @ @   @  @ @  @   @ @   @ @   @ @     @     @   @
 *      @       @ @ @@@ @   @ @   @ @     @   @ @     @     @
 *       @     @  @ @ @ @@@@@ @@@@  @     @   @ @@@@  @@@@  @
 *      @     @   @ @@@ @   @ @   @ @     @   @ @     @     @ @@@
 *     @      @   @     @   @ @   @ @   @ @   @ @     @     @   @
 *    @            @@@@ @   @ @@@@   @@@  @@@@  @@@@@ @      @@@@
 *            @
 *
 *
 *    @   @  @@@    @@@ @   @ @     @   @ @   @  @@@  @@@@   @@@
 *    @   @   @      @  @  @  @     @@ @@ @@  @ @   @ @   @ @   @
 *    @   @   @      @  @ @   @     @ @ @ @ @ @ @   @ @   @ @   @
 *    @@@@@   @      @  @@    @     @ @ @ @  @@ @   @ @@@@  @   @
 *    @   @   @      @  @ @   @     @   @ @   @ @   @ @     @ @ @
 *    @   @   @   @  @  @  @  @     @   @ @   @ @   @ @     @  @@
 *    @   @  @@@   @@   @   @ @@@@@ @   @ @   @  @@@  @      @@ @
 *
 *
 *
 *    @@@@   @@@  @@@@@ @   @ @   @ @   @ @   @ @   @ @@@@@  @@@
 *    @   @ @   @   @   @   @ @   @ @   @ @   @ @   @     @  @
 *    @   @ @       @   @   @ @   @ @   @  @ @   @ @     @   @
 *    @@@@   @@@    @   @   @  @ @  @ @ @   @     @     @    @
 *    @ @       @   @   @   @  @ @  @ @ @  @ @    @    @     @
 *    @  @  @   @   @   @   @   @   @ @ @ @   @   @   @      @
 *    @   @  @@@    @    @@@    @    @ @  @   @   @   @@@@@  @@@
 *
 *
 *
 *    @      @@@    @          @@         @               @
 *    @        @   @@@         @@         @               @
 *     @       @  @ @ @        @     @@@  @@@@   @@@   @@@@  @@@
 *      @      @    @           @       @ @   @ @   @ @   @ @   @
 *       @     @    @                @@@@ @   @ @     @   @ @@@@@
 *        @    @    @               @   @ @   @ @     @   @ @
 *        @  @@@    @                @@@@ @@@@   @@@@  @@@@  @@@@
 *                      @@@@@
 *
 *
 *      @@        @       @       @ @      @@
 *     @          @                 @       @
 *    @@@@   @@@@ @@@@   @@      @@ @  @    @   @@@@  @@@@   @@@
 *     @    @   @ @   @   @       @ @ @     @   @ @ @ @   @ @   @
 *     @    @   @ @   @   @       @ @@ @    @   @ @ @ @   @ @   @
 *     @    @   @ @   @   @       @ @   @   @   @ @ @ @   @ @   @
 *     @     @@@@ @   @  @@@  @   @ @   @  @@@  @ @ @ @   @  @@@
 *              @              @@@
 *           @@@
 *
 *                             @
 *                             @
 *    @@@@   @@@@ @ @@   @@@@ @@@@  @   @ @   @ @   @ @   @ @   @
 *    @   @ @   @  @  @ @      @    @   @ @   @ @ @ @  @ @  @   @
 *    @   @ @   @  @     @@@   @    @   @ @   @ @ @ @   @   @   @
 *    @   @ @   @  @        @  @    @   @  @ @  @ @ @  @ @  @   @
 *    @@@@   @@@@  @    @@@@    @@   @@@@   @    @ @  @   @  @@@@
 *    @         @                                               @
 *    @         @                                            @@@
 *
 *             @@   @   @@     @
 *            @     @     @   @@@@@
 *    @@@@@   @     @     @      @
 *       @   @             @
 *      @     @     @     @
 *     @      @     @     @
 *    @@@@@    @@   @   @@
 *
 *--------------------------------------------------------------------*/

/*====================================================================*
 *
 *   this array contains the default background and fill character for
 *   generating the character matrix;
 *
 *--------------------------------------------------------------------*/

static unsigned char FILL [2] = 

{
	' ',
	'@'
};


/*====================================================================*
 *
 *   this matrix contains offsets for all patterns of background and
 *   fill characters in a single matrix row; 0 indicates a background;
 *   1 indicates a fill;
 *
 *--------------------------------------------------------------------*/

static unsigned char LINE [64][6] = 

{
	{
		0,
		0,
		0,
		0,
		0,
		0
	},
	{
		0,
		0,
		0,
		0,
		0,
		1
	},
	{
		0,
		0,
		0,
		0,
		1,
		0
	},
	{
		0,
		0,
		0,
		0,
		1,
		1
	},
	{
		0,
		0,
		0,
		1,
		0,
		0
	},
	{
		0,
		0,
		0,
		1,
		0,
		1
	},
	{
		0,
		0,
		0,
		1,
		1,
		0
	},
	{
		0,
		0,
		0,
		1,
		1,
		1
	},
	{
		0,
		0,
		1,
		0,
		0,
		0
	},
	{
		0,
		0,
		1,
		0,
		0,
		1
	},
	{
		0,
		0,
		1,
		0,
		1,
		0
	},
	{
		0,
		0,
		1,
		0,
		1,
		1
	},
	{
		0,
		0,
		1,
		1,
		0,
		0
	},
	{
		0,
		0,
		1,
		1,
		0,
		1
	},
	{
		0,
		0,
		1,
		1,
		1,
		0
	},
	{
		0,
		0,
		1,
		1,
		1,
		1
	},
	{
		0,
		1,
		0,
		0,
		0,
		0
	},
	{
		0,
		1,
		0,
		0,
		0,
		1
	},
	{
		0,
		1,
		0,
		0,
		1,
		0
	},
	{
		0,
		1,
		0,
		0,
		1,
		1
	},
	{
		0,
		1,
		0,
		1,
		0,
		0
	},
	{
		0,
		1,
		0,
		1,
		0,
		1
	},
	{
		0,
		1,
		0,
		1,
		1,
		0
	},
	{
		0,
		1,
		0,
		1,
		1,
		1
	},
	{
		0,
		1,
		1,
		0,
		0,
		0
	},
	{
		0,
		1,
		1,
		0,
		0,
		1
	},
	{
		0,
		1,
		1,
		0,
		1,
		0
	},
	{
		0,
		1,
		1,
		0,
		1,
		1
	},
	{
		0,
		1,
		1,
		1,
		0,
		0
	},
	{
		0,
		1,
		1,
		1,
		0,
		1
	},
	{
		0,
		1,
		1,
		1,
		1,
		0
	},
	{
		0,
		1,
		1,
		1,
		1,
		1
	},
	{
		1,
		0,
		0,
		0,
		0,
		0
	},
	{
		1,
		0,
		0,
		0,
		0,
		1
	},
	{
		1,
		0,
		0,
		0,
		1,
		0
	},
	{
		1,
		0,
		0,
		0,
		1,
		1
	},
	{
		1,
		0,
		0,
		1,
		0,
		0
	},
	{
		1,
		0,
		0,
		1,
		0,
		1
	},
	{
		1,
		0,
		0,
		1,
		1,
		0
	},
	{
		1,
		0,
		0,
		1,
		1,
		1
	},
	{
		1,
		0,
		1,
		0,
		0,
		0
	},
	{
		1,
		0,
		1,
		0,
		0,
		1
	},
	{
		1,
		0,
		1,
		0,
		1,
		0
	},
	{
		1,
		0,
		1,
		0,
		1,
		1
	},
	{
		1,
		0,
		1,
		1,
		0,
		0
	},
	{
		1,
		0,
		1,
		1,
		0,
		1
	},
	{
		1,
		0,
		1,
		1,
		1,
		0
	},
	{
		1,
		0,
		1,
		1,
		1,
		1
	},
	{
		1,
		1,
		0,
		0,
		0,
		0
	},
	{
		1,
		1,
		0,
		0,
		0,
		1
	},
	{
		1,
		1,
		0,
		0,
		1,
		0
	},
	{
		1,
		1,
		0,
		0,
		1,
		1
	},
	{
		1,
		1,
		0,
		1,
		0,
		0
	},
	{
		1,
		1,
		0,
		1,
		0,
		1
	},
	{
		1,
		1,
		0,
		1,
		1,
		0
	},
	{
		1,
		1,
		0,
		1,
		1,
		1
	},
	{
		1,
		1,
		1,
		0,
		0,
		0
	},
	{
		1,
		1,
		1,
		0,
		0,
		1
	},
	{
		1,
		1,
		1,
		0,
		1,
		0
	},
	{
		1,
		1,
		1,
		0,
		1,
		1
	},
	{
		1,
		1,
		1,
		1,
		0,
		0
	},
	{
		1,
		1,
		1,
		1,
		0,
		1
	},
	{
		1,
		1,
		1,
		1,
		1,
		0
	},
	{
		1,
		1,
		1,
		1,
		1,
		1
	}
};


/*====================================================================*
 *
 *   this matrix defines each character font by row; each row points
 *   to one of the 64 patterns in the _ccol[][] matrix;
 *
 *--------------------------------------------------------------------*/

static unsigned char FONT [128][10] = 

{

/* 000 nul */

	{
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0
	},

/* 001 soh */

	{
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0
	},

/* 002 stx */

	{
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0
	},

/* 003 ext */

	{
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0
	},

/* 004 eot */

	{
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0
	},

/* 005 enq */

	{
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0
	},

/* 006 ack */

	{
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0
	},

/* 007 bel */

	{
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0
	},

/* 010 bs  */

	{
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0
	},

/* 011 ht  */

	{
		20,
		20,
		28,
		20,
		7,
		2,
		2,
		2,
		0
	},

/* 012 lf  */

	{
		16,
		16,
		16,
		28,
		7,
		4,
		6,
		4,
		0
	},

/* 013 vt  */

	{
		20,
		20,
		20,
		8,
		7,
		2,
		2,
		2,
		0
	},

/* 014 ff  */

	{
		28,
		16,
		24,
		16,
		7,
		4,
		6,
		4,
		0
	},

/* 015 cr  */

	{
		12,
		16,
		16,
		12,
		6,
		5,
		6,
		5,
		0
	},

/* 016 so  */

	{
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0
	},

/* 017 si  */

	{
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0
	},

/* 020 dle */

	{
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0
	},

/* 021 dc1 */

	{
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0
	},

/* 022 dc2 */

	{
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0
	},

/* 023 dc3 */

	{
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0
	},

/* 024 dc4 */

	{
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0
	},

/* 025 nak */

	{
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0
	},

/* 026 syn */

	{
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0
	},

/* 027 etb */

	{
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0
	},

/* 030 can */

	{
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0
	},

/* 031 em  */

	{
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0
	},

/* 032 sub */

	{
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0
	},

/* 033 esc */

	{
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0
	},

/* 034 fs  */

	{
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0
	},

/* 035 gs  */

	{
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0
	},

/* 036 rs  */

	{
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0
	},

/* 037 us  */

	{
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0
	},

/* 040 sp  */

	{
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0
	},

/* 041 [!] */

	{
		4,
		14,
		14,
		4,
		4,
		0,
		4,
		0,
		0
	},

/* 042 ["] */

	{
		27,
		27,
		9,
		18,
		0,
		0,
		0,
		0,
		0
	},

/* 043 [#] */

	{
		10,
		10,
		31,
		10,
		31,
		10,
		10,
		0,
		0
	},

/* 044 [$] */

	{
		4,
		15,
		20,
		14,
		5,
		30,
		4,
		0,
		0
	},

/* 045 [%] */

	{
		25,
		25,
		2,
		4,
		8,
		19,
		19,
		0,
		0
	},

/* 046 [&] */

	{
		8,
		20,
		20,
		8,
		21,
		18,
		13,
		0,
		0
	},

/* 047 ['] */

	{
		12,
		12,
		4,
		8,
		0,
		0,
		0,
		0,
		0
	},

/* 050 [(] */

	{
		2,
		4,
		8,
		8,
		8,
		4,
		2,
		0,
		0
	},

/* 051 [)] */

	{
		8,
		4,
		2,
		2,
		2,
		4,
		8,
		0,
		0
	},

/* 052 [*] */

	{
		4,
		21,
		14,
		31,
		14,
		21,
		4,
		0,
		0
	},

/* 053 [+] */

	{
		0,
		4,
		4,
		31,
		4,
		4,
		0,
		0,
		0
	},

/* 054 [,] */

	{
		0,
		0,
		0,
		0,
		0,
		12,
		12,
		4,
		8
	},

/* 055 [-] */

	{
		0,
		0,
		0,
		31,
		0,
		0,
		0,
		0,
		0
	},

/* 056 [.] */

	{
		0,
		0,
		0,
		0,
		0,
		12,
		12,
		0,
		0
	},

/* 057 [/] */

	{
		1,
		1,
		2,
		4,
		8,
		16,
		16,
		0,
		0
	},

/* 058 [0] */

	{
		14,
		17,
		19,
		21,
		25,
		17,
		14,
		0,
		0
	},

/* 060 [1] */

	{
		4,
		12,
		4,
		4,
		4,
		4,
		14,
		0,
		0
	},

/* 061 [2] */

	{
		14,
		17,
		1,
		2,
		4,
		8,
		31,
		0,
		0
	},

/* 062 [3] */

	{
		14,
		17,
		1,
		6,
		1,
		17,
		14,
		0,
		0
	},

/* 063 [4] */

	{
		2,
		6,
		10,
		18,
		31,
		2,
		2,
		0,
		0
	},

/* 064 [5] */

	{
		31,
		16,
		30,
		1,
		1,
		17,
		14,
		0,
		0
	},

/* 065 [6] */

	{
		7,
		8,
		16,
		30,
		17,
		17,
		14,
		0,
		0
	},

/* 066 [7] */

	{
		31,
		1,
		2,
		4,
		8,
		16,
		16,
		0,
		0
	},

/* 070 [8] */

	{
		14,
		17,
		17,
		14,
		17,
		17,
		14,
		0,
		0
	},

/* 071 [9] */

	{
		14,
		17,
		17,
		15,
		1,
		2,
		28,
		0,
		0
	},

/* 072 [:] */

	{
		0,
		12,
		12,
		0,
		12,
		12,
		0,
		0,
		0
	},

/* 073 [;] */

	{
		0,
		0,
		12,
		12,
		0,
		12,
		12,
		4,
		8
	},

/* 074 [<] */

	{
		1,
		2,
		4,
		8,
		4,
		2,
		1,
		0,
		0
	},

/* 075 [=] */

	{
		0,
		0,
		31,
		0,
		31,
		0,
		0,
		0,
		0
	},

/* 076 [>] */

	{
		16,
		8,
		4,
		2,
		4,
		8,
		16,
		0,
		0
	},

/* 077 [?] */

	{
		14,
		17,
		1,
		2,
		4,
		4,
		0,
		4,
		0
	},

/* 100 [@] */

	{
		14,
		17,
		23,
		21,
		23,
		16,
		15,
		0,
		0
	},

/* 101 [A] */

	{
		4,
		10,
		17,
		31,
		17,
		17,
		17,
		0,
		0
	},

/* 102 [B] */

	{
		30,
		17,
		17,
		30,
		17,
		17,
		30,
		0,
		0
	},

/* 103 [C] */

	{
		14,
		17,
		16,
		16,
		16,
		17,
		14,
		0,
		0
	},

/* 104 [D] */

	{
		30,
		17,
		17,
		17,
		17,
		17,
		30,
		0,
		0
	},

/* 105 [E] */

	{
		31,
		16,
		16,
		30,
		16,
		16,
		31,
		0,
		0
	},

/* 106 [F] */

	{
		31,
		16,
		16,
		30,
		16,
		16,
		16,
		0,
		0
	},

/* 107 [G] */

	{
		14,
		17,
		16,
		16,
		23,
		17,
		15,
		0,
		0
	},

/* 110 [H] */

	{
		17,
		17,
		17,
		31,
		17,
		17,
		17,
		0,
		0
	},

/* 111 [I] */

	{
		14,
		4,
		4,
		4,
		4,
		4,
		14,
		0,
		0
	},

/* 112 [J] */

	{
		7,
		2,
		2,
		2,
		2,
		18,
		12,
		0,
		0
	},

/* 113 [K] */

	{
		17,
		18,
		20,
		24,
		20,
		18,
		17,
		0,
		0
	},

/* 114 [L] */

	{
		16,
		16,
		16,
		16,
		16,
		16,
		31,
		0,
		0
	},

/* 115 [M] */

	{
		17,
		27,
		21,
		21,
		17,
		17,
		17,
		0,
		0
	},

/* 116 [N] */

	{
		17,
		25,
		21,
		19,
		17,
		17,
		17,
		0,
		0
	},

/* 117 [O] */

	{
		14,
		17,
		17,
		17,
		17,
		17,
		14,
		0,
		0
	},

/* 120 [P] */

	{
		30,
		17,
		17,
		30,
		16,
		16,
		16,
		0,
		0
	},

/* 121 [Q] */

	{
		14,
		17,
		17,
		17,
		21,
		19,
		13,
		0,
		0
	},

/* 122 [R] */

	{
		30,
		17,
		17,
		30,
		20,
		18,
		17,
		0,
		0
	},

/* 123 [S] */

	{
		14,
		17,
		16,
		14,
		1,
		17,
		14,
		0,
		0
	},

/* 124 [T] */

	{
		31,
		4,
		4,
		4,
		4,
		4,
		4,
		0,
		0
	},

/* 125 [U] */

	{
		17,
		17,
		17,
		17,
		17,
		17,
		14,
		0,
		0
	},

/* 126 [V] */

	{
		17,
		17,
		17,
		10,
		10,
		4,
		4,
		0,
		0
	},

/* 127 [W] */

	{
		17,
		17,
		17,
		21,
		21,
		21,
		10,
		0,
		0
	},

/* 130 [X] */

	{
		17,
		17,
		10,
		4,
		10,
		17,
		17,
		0,
		0
	},

/* 131 [Y] */

	{
		17,
		17,
		10,
		4,
		4,
		4,
		4,
		0,
		0
	},

/* 132 [Z] */

	{
		31,
		1,
		2,
		4,
		8,
		16,
		31,
		0,
		0
	},

/* 133 [[] */

	{
		14,
		8,
		8,
		8,
		8,
		8,
		14,
		0,
		0
	},

/* 134 [] */

	{
		16,
		16,
		8,
		4,
		2,
		1,
		1,
		0,
		0
	},

/* 135 []] */

	{
		14,
		2,
		2,
		2,
		2,
		2,
		14,
		0,
		0
	},

/* 136 [^] */

	{
		4,
		14,
		21,
		4,
		4,
		4,
		4,
		0,
		0
	},

/* 137 [_] */

	{
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		31,
		0
	},

/* 140 [`] */

	{
		12,
		12,
		8,
		4,
		0,
		0,
		0,
		0,
		0
	},

/* 141 [a] */

	{
		0,
		0,
		14,
		1,
		15,
		17,
		15,
		0,
		0
	},

/* 142 [b] */

	{
		16,
		16,
		30,
		17,
		17,
		17,
		30,
		0,
		0
	},

/* 143 [c] */

	{
		0,
		0,
		14,
		17,
		16,
		16,
		15,
		0,
		0
	},

/* 144 [d] */

	{
		1,
		1,
		15,
		17,
		17,
		17,
		15,
		0,
		0
	},

/* 145 [e] */

	{
		0,
		0,
		14,
		17,
		31,
		16,
		15,
		0,
		0
	},

/* 146 [f] */

	{
		6,
		8,
		30,
		8,
		8,
		8,
		8,
		0,
		0
	},

/* 147 [g] */

	{
		0,
		0,
		15,
		17,
		17,
		17,
		15,
		1,
		14
	},

/* 150 [h] */

	{
		16,
		16,
		30,
		17,
		17,
		17,
		17,
		0,
		0
	},

/* 151 [i] */

	{
		4,
		0,
		12,
		4,
		4,
		4,
		14,
		0,
		0
	},

/* 152 [j] */

	{
		1,
		0,
		3,
		1,
		1,
		1,
		17,
		14,
		0
	},

/* 153 [k] */

	{
		16,
		16,
		18,
		20,
		26,
		17,
		17,
		0,
		0
	},

/* 154 [l] */

	{
		12,
		4,
		4,
		4,
		4,
		4,
		14,
		0,
		0
	},

/* 155 [m] */

	{
		0,
		0,
		30,
		21,
		21,
		21,
		21,
		0,
		0
	},

/* 156 [n] */

	{
		0,
		0,
		30,
		17,
		17,
		17,
		17,
		0,
		0
	},

/* 157 [o] */

	{
		0,
		0,
		14,
		17,
		17,
		17,
		14,
		0,
		0
	},

/* 160 [p] */

	{
		0,
		0,
		30,
		17,
		17,
		17,
		30,
		16,
		16
	},

/* 161 [q] */

	{
		0,
		0,
		15,
		17,
		17,
		17,
		15,
		1,
		1
	},

/* 162 [r] */

	{
		0,
		0,
		22,
		9,
		8,
		8,
		8,
		0,
		0
	},

/* 163 [s] */

	{
		0,
		0,
		15,
		16,
		14,
		1,
		30,
		0,
		0
	},

/* 164 [t] */

	{
		8,
		8,
		30,
		8,
		8,
		8,
		6,
		0,
		0
	},

/* 165 [u] */

	{
		0,
		0,
		17,
		17,
		17,
		17,
		15,
		0,
		0
	},

/* 166 [v] */

	{
		0,
		0,
		17,
		17,
		17,
		10,
		4,
		0,
		0
	},

/* 167 [w] */

	{
		0,
		0,
		17,
		21,
		21,
		21,
		10,
		0,
		0
	},

/* 170 [x] */

	{
		0,
		0,
		17,
		10,
		4,
		10,
		17,
		0,
		0
	},

/* 171 [y] */

	{
		0,
		0,
		17,
		17,
		17,
		17,
		15,
		1,
		14
	},

/* 172 [z] */

	{
		0,
		0,
		31,
		2,
		4,
		8,
		31,
		0,
		0
	},

/* 173 [{] */

	{
		3,
		4,
		4,
		8,
		4,
		4,
		3,
		0,
		0
	},

/* 174 [|] */

	{
		4,
		4,
		4,
		0,
		4,
		4,
		4,
		0,
		0
	},

/* 175 [}] */

	{
		24,
		4,
		4,
		2,
		4,
		4,
		24,
		0,
		0
	},

/* 176 [~] */

	{
		8,
		31,
		2,
		0,
		0,
		0,
		0,
		0,
		0
	},

/* 177 del */

	{
		24,
		20,
		20,
		24,
		4,
		4,
		4,
		7,
		0
	},
};


/*====================================================================*
 *
 *   char const *signf(char const *string, int c, size_t width);
 *
 *   This function outputs a banner, in 6 X 10 character matrix format,
 *   to the output stream associated with a file pointer. The banner is
 *   formed with the specified fill character. A pointer to the string
 *   is returned;
 *
 *   the character set includes the lower 128  ASCII characters, including
 *   control characters, which appear as blanks. Lower case letters and
 *   and punctuation characters have true descenders.
 *
 *   A sample character string matrix, illustrated below, was generated
 *   by the following:  "fputm("abcABC123@$%",'@',fp);"
 *
 *       @             @   @@@@   @@@    @    @@@   @@@   @@@    @   @@  @
 *       @            @ @  @   @ @   @  @@   @   @ @   @ @   @  @@@@ @@  @
 *  @@@  @@@@   @@@  @   @ @   @ @       @       @     @ @ @@@ @ @      @
 *     @ @   @ @   @ @@@@@ @@@@  @       @      @    @@  @ @ @  @@@    @
 *  @@@@ @   @ @     @   @ @   @ @       @     @       @ @ @@@   @ @  @
 * @   @ @   @ @     @   @ @   @ @   @   @    @    @   @ @     @@@@  @  @@
 *  @@@@ @@@@   @@@@ @   @ @@@@   @@@   @@@  @@@@@  @@@   @@@@   @   @  @@
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

void signf (char const *string, int c, size_t limit) 

{
	char const *sp;
	size_t width;
	size_t col;
	size_t row;
	FILL [FILL_CHR] = (unsigned char)((isprint (c))? (c):('@'));
	for (width = row = 0; row < FONT_ROW; width = 0, row++) 
	{
		for (sp = string; *sp != (char)(0); sp++) 
		{
			if (*sp == '\\') 
			{
				sp++;
			}
			if (*sp == (char) (0)) 
			{
				break;
			}
			for (col = 0; (col < FONT_COL) && (width < limit); width++, col++) 
			{
				putc (FILL [LINE [FONT [(unsigned char)(*sp)&(SCHAR_MAX)][row]][col]], stdout);
			}
		}
		putc ('\n', stdout);
	}
	return;
}

