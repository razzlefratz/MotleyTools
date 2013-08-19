/*====================================================================*
 *
 *   clang.h - c language parsing definitions and declarations;
 *
 *
 *.  Motley Tools by Charles Maier
 *:  modified mon 01 nov 04 by user root on host zephir;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef CLANG_HEADER
#define CLANH_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/tools.h"
#include "../tools/types.h"
#include "../clang/cword.h"
#include "../clang/coper.h"
#include "../list/list.h"

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#define CLANG_HT '\t'
#define CLANG_CR '\r'
#define CLANG_LF '\n'
#define CLANG_SP ' '

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

/*
 * enable parsing and formtting features; these symbols are either 
 * defined or undefined; their value is not significant; 
 */

#define CPARSE_PREAMBLE 1
#define CPARSE_EXTENDBAR 1
#define CPARSE_PADMARGIN 1
#define CPARSE_ONELINECOMMENT 1

/*
 * bitmaps for struct _text_ flagwords; flagwords are set by user 
 * in function main();
 */

#define CFLAG_STATUS (1 << 0)
#define CFLAG_HEADER (1 << 1)
#define CFLAG_FOOTER (1 << 2)
#define CFLAG_SINGLE (1 << 3)
#define CFLAG_DOUBLE (1 << 4)
#define CFLAG_TRIPLE (1 << 5)

#define CFLAG_PREAMBLE (1 << 10)
#define CFLAG_RELEASED (1 << 11)
#define CFLAG_PACKAGED (1 << 12)
#define CFLAG_LICENSED (1 << 13)

/*
 * buffer lengths and comment bar width; comment bar width is now
 * set to prevent line wrap when using the vi editor in 80 column 
 * mode with line numbers enabled;
 */

#define CSOURCE 4096
#define COUTPUT 8192
#define CBARWIDTH 68

/*
 * multi-character token classes detected by cgettoken();
 */

#define CTOKEN_COMMENT 'C'
#define CTOKEN_COMPILER 'P'
#define CTOKEN_RESERVED 'R'
#define CTOKEN_VARIABLE 'V'
#define CTOKEN_CONSTANT '0'
#define CTOKEN_OPERATOR 'O'

#define CINFO_RELEASED ('.')
#define CINFO_PACKAGED (':')
#define CINFO_LICENSED (';')

/*====================================================================*
 *   csource (input) functions;
 *--------------------------------------------------------------------*/

#if 0

int cgettoken (TEXT *csource);
int cgetmacro (TEXT *csource);
int cgetblock (TEXT *csource);
int cgetbrack (TEXT *csource);
int cgetparen (TEXT *csource);
int cgetquote (TEXT *csource);
int cgetapost (TEXT *csource);
int cgetspace (void);
int cgetblank (void);

#endif

/*====================================================================*
 *   coutput (output) functions;
 *--------------------------------------------------------------------*/

#if 0

void cputstate (TEXT *csource, char const *title, int level, int token);
void cputerror (TEXT *csource, char const *title);
void cputtoken (TEXT *coutput, TEXT *csource);
void cputbreak (TEXT *coutput, FILE *file, size_t margin);
void cputspace (TEXT *coutput);

#endif

/*====================================================================*
 *   insert preprocessor directives;
 *--------------------------------------------------------------------*/

flag_t cheader (char const *title, char const *class, flag_t flags);
flag_t cfooter (char const *title, char const *class, flag_t flags);

/*====================================================================*
 *   insert comment text and format;
 *--------------------------------------------------------------------*/

int ccollect (LIST * files, char const * paths []);
int cinclude (LIST * files, char const * paths []);

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif

