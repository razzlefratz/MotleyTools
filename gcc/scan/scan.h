/*====================================================================*
 *
 *   scan.h -  text content definitions and declarations;
 *
 *   declare SCAN structure and functions that use it; the SCAN structure
 *   supports scanning of strings for tokens and fields; functions defined
 *   in text.c use and maintain the structure; these functions can perform
 *   virtually any scanning task required when used in combination; 
 *
 *.  Motley Tools by Charles Maier
 *:  modified fri 19 sep 03 by user root on host zeus;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SCAN_HEADER
#define SCAN_HEADER

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <stddef.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/types.h"

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#define TOKEN_EMPTY 'E'
#define TOKEN_SPACE ' '
#define TOKEN_ALPHA 'A'
#define TOKEN_DIGIT '0'
#define TOKEN_IDENT 'I'
#if 0
#define TOKEN_QUOTE 'Q'
#define TOKEN_CNOTE 'C'  
#define TOKEN_TRASH 'T'
#define TOKEN_BOUND 'B'
#define TOKEN_BREAK 'X'
#define TOKEN_CHUNK 'K'
#endif
#define TOKEN_WIDTH 255

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#define SCAN_LOWER "abcdefghijklmnopqrstuvwxyz"
#define SCAN_UPPER "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define SCAN_ALPHA SCAN_LOWER SCAN_UPPER
#define SCAN_DIGIT "0123456789"
#define SCAN_IDENT SCAN_ALPHA SCAN_DIGIT "_-."

// #define SHOWTOKEN(content) showtoken (content);

#define SHOWTOKEN(content) 

/*====================================================================*
 *   define data structures;
 *--------------------------------------------------------------------*/

typedef struct _scan_ 

{
	char const * start;
	char const * first;
	char const * final;
	char const * limit;
	char const * index;
	signed class;
	signed width;
	signed block;
	char * token;
}

SCAN;

/*====================================================================*
 *   declare function prototypes; 
 *--------------------------------------------------------------------*/

void scaninput (SCAN * content, char const buffer [], signed length);
void scanwrite (SCAN * content, signed fd);
void scanprint (SCAN * content, signed fd);
void scanstart (SCAN * content);
void scanreset (SCAN * content);
void scanlimit (SCAN * content);
char * tokentext (SCAN * content);
void showtoken (SCAN * content);
void copytoken (SCAN * content, char buffer [], signed length);
void copyquote (SCAN * content, char buffer [], signed length);
unsigned tokentype (SCAN * content);
size_t tokensize (SCAN * content);
void scanalpha (SCAN * content);
void scanalnum (SCAN * content);
void scanblank (SCAN * content);
void scanchunk (SCAN * content);
void scancntrl (SCAN * content);
void scandigit (SCAN * content);
void scanflush (SCAN * content);
void scanident (SCAN * content);
void scanspace (SCAN * content);
void scanbreak (SCAN * content, char const *charset);
void scanright (SCAN * content, char const *charset);
void scanwhile (SCAN * content, char const *charset);
void scanuntil (SCAN * content, char const *charset);
void scanquote (SCAN * content, char const *charset);
void scangroup (SCAN * content, char const *charset);
void scanblock (SCAN * content, char const *charset);
void scanbreakmatch (SCAN * content);
void scanwhilematch (SCAN * content);
void scanuntilmatch (SCAN * content);
void scanquotematch (SCAN * content);
void scanblockmatch (SCAN * content);
void scantoken (SCAN * content);
void nexttoken (SCAN * content);
void nextbreak (SCAN * content);
bool isready (SCAN * content);
bool isclass (SCAN * content, char const *charset);
bool istoken (SCAN * content, char const *literal);
bool isbreak (SCAN * content, char const *charset);
bool ismatch (SCAN * content);
bool haveclass (SCAN * content, char const *charset);
bool havebreak (SCAN * content, char const *charset);
bool havetoken (SCAN * content, char const *literal);
unsigned tovalue (SCAN * content);

/*====================================================================*
 *   end definitions and declarations;
 *--------------------------------------------------------------------*/

#endif

