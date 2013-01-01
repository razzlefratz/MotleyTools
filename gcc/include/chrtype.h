/*====================================================================*
 *
 *   chrtype.h - character type declarations and definitions;
 *
 *.  Motley Tools by Charles Maier
 *:  modified sun 07 sep 03 by user root on host zeus;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef CHRTYPE_HEADER
#define CHRTYPE_HEADER

/*====================================================================*
 *   define standard character conversion function prototypes;
 *--------------------------------------------------------------------*/

signed ctoascii (signed c);
signed ctoupper (signed c);
signed ctolower (signed c);
signed ctocntrl (signed c);
signed ctoprint (signed c);

/*====================================================================*
 *   define standard character conversion function macros;
 *--------------------------------------------------------------------*/

#define _ctoupper(c) (unsigned int)((islower(c))?((unsigned int)(c)-('a'-'A')):(unsigned int)(c))
#define _ctolower(c) (unsigned int)((isupper(c))?((unsigned int)(c)+('a'-'A')):(unsigned int)(c))

#define _ctoascii(c) (unsigned int)((unsigned int)(c)&(0x007F))
#define _ctocntrl(c) (unsigned int)((unsigned int)(c)&(0x001F))
#define _ctoprint(c) (unsigned int)((unsigned int)(c)|(0x0040))

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

extern const unsigned chrtype [];

/*====================================================================*
 *   define bit masks for character typing;
 *--------------------------------------------------------------------*/

#define CTYPE_B_NTYPE  0x00  /* no type or unknown type */
#define CTYPE_B_CNTRL  0x01  /* control */
#define CTYPE_B_SPACE  0x02  /* space */
#define CTYPE_B_UPPER  0x04  /* upper case letter */
#define CTYPE_B_LOWER  0x08  /* lower case letter */
#define CTYPE_B_ALPHA (CTYPE_B_UPPER|CTYPE_B_LOWER)
#define CTYPE_B_DIGIT  0x10  /* digit */
#define CTYPE_B_ALNUM (CTYPE_B_ALPHA|CTYPE_B_DIGIT)
#define CTYPE_B_HEX    0x20  /* hexidecimal */
#define CTYPE_B_PUNCT  0x40  /* punctuation */
#define CTYPE_B_GRAPH (CTYPE_B_ALNUM|CTYPE_B_PUNCT)

/*====================================================================*
 *   define standard character typing macros;
 *--------------------------------------------------------------------*/

#define cisascii(c) ((unsigned int)(c)<=(0x0080))
#define cisupper(c) ((chrtype[(unsigned int)(c)] & (CTYPE_B_UPPER))!=0)
#define cislower(c) ((chrtype[(unsigned int)(c)] & (CTYPE_B_LOWER))!=0)
#define cisalpha(c) ((chrtype[(unsigned int)(c)] & (CTYPE_B_ALPHA))!=0)
#define cisdigit(c) ((chrtype[(unsigned int)(c)] & (CTYPE_B_DIGIT))!=0)
#define cisalnum(c) ((chrtype[(unsigned int)(c)] & (CTYPE_B_ALNUM))!=0)
#define cisxdigit(c)((chrtype[(unsigned int)(c)] & (CTYPE_B_HEX))!=0)
#define cisspace(c) ((chrtype[(unsigned int)(c)] & (CTYPE_B_SPACE))!=0)
#define cispunct(c) ((chrtype[(unsigned int)(c)] & (CTYPE_B_PUNCT))!=0)
#define cisgraph(c) ((chrtype[(unsigned int)(c)] & (CTYPE_B_GRAPH))!=0)
#define cisprint(c) ((chrtype[(unsigned int)(c)] & (CTYPE_B_CNTRL))==0)
#define ciscntrl(c) ((chrtype[(unsigned int)(c)] & (CTYPE_B_CNTRL))!=0)

/*====================================================================*
 *   end definitions;
 *--------------------------------------------------------------------*/

#endif

