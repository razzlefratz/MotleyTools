/*====================================================================*
 *
 *   _ctype.h - character type declarations and definitions;
 *
 *.  Motley Tools by Charles Maier
 *:  modified sun 07 sep 03 by user root on host zeus;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef _CTYPE_HEADER
#define _CTYPE_HEADER

/*====================================================================*
 *   define standard character conversion function prototypes;
 *--------------------------------------------------------------------*/

signed _toascii (signed c);
signed _toupper (signed c);
signed _tolower (signed c);
signed _tocntrl (signed c);
signed _toprint (signed c);

/*====================================================================*
 *   define standard character conversion function macros;
 *--------------------------------------------------------------------*/

#define __toupper(c) (unsigned int)((islower(c))?((unsigned int)(c)-('a'-'A')):(unsigned int)(c))
#define __tolower(c) (unsigned int)((isupper(c))?((unsigned int)(c)+('a'-'A')):(unsigned int)(c))

#define __toascii(c) (unsigned int)((unsigned int)(c)&(0x007F))
#define __tocntrl(c) (unsigned int)((unsigned int)(c)&(0x001F))
#define __toprint(c) (unsigned int)((unsigned int)(c)|(0x0040))

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

extern const unsigned _ctype [];

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

#define _isascii(c) ((unsigned int)(c)<=(0x0080))
#define _isupper(c) ((_ctype[(unsigned int)(c)] & (CTYPE_B_UPPER))!=0)
#define _islower(c) ((_ctype[(unsigned int)(c)] & (CTYPE_B_LOWER))!=0)
#define _isalpha(c) ((_ctype[(unsigned int)(c)] & (CTYPE_B_ALPHA))!=0)
#define _isdigit(c) ((_ctype[(unsigned int)(c)] & (CTYPE_B_DIGIT))!=0)
#define _isalnum(c) ((_ctype[(unsigned int)(c)] & (CTYPE_B_ALNUM))!=0)
#define _isxdigit(c)((_ctype[(unsigned int)(c)] & (CTYPE_B_HEX))!=0)
#define _isspace(c) ((_ctype[(unsigned int)(c)] & (CTYPE_B_SPACE))!=0)
#define _ispunct(c) ((_ctype[(unsigned int)(c)] & (CTYPE_B_PUNCT))!=0)
#define _isgraph(c) ((_ctype[(unsigned int)(c)] & (CTYPE_B_GRAPH))!=0)
#define _isprint(c) ((_ctype[(unsigned int)(c)] & (CTYPE_B_CNTRL))==0)
#define _iscntrl(c) ((_ctype[(unsigned int)(c)] & (CTYPE_B_CNTRL))!=0)

/*====================================================================*
 *   end definitions;
 *--------------------------------------------------------------------*/

#endif

