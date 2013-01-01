/*====================================================================*
 *
 *   regex.h - regular expression constants, macros, structures and functions;
 *
 *.  Motley Tools by Charles Maier
 *:  modified sun 07 sep 03 by user root on host zeus;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef REGEXP_HEADER
#define REGEXP_HEADER

/*====================================================================*
 *   custome header files;                          
 *--------------------------------------------------------------------*/

#include "../tools/tools.h"
#include "../tools/types.h"
#include "../tools/flags.h"

/*====================================================================*
 *   define character set specification constants;
 *--------------------------------------------------------------------*/

#define REGEX_TRACE 0

#define REGEX_LABEL_EXTENSIONS
#define REGEX_POSIX_EXTENSIONS
#define REGEX_COUNT_MAX 0x7FFF

#define REGEX_C_KLEENE_STAR ('*')  /* Kleene star (reflexive transitive closure) */
#define REGEX_C_KLEENE_PLUS ('+')  /* Kleene plus (transitive closure) */
#define REGEX_C_KLEENE_ONCE ('?')  

#define REGEX_C_SRT   ('[') /* begin character set */
#define REGEX_C_END   (']') /* close character set */
#define REGEX_C_RNG   ('-')
#define REGEX_C_ESC  ('\\') /* escape character */
#define REGEX_C_NOT   ('!')
#define REGEX_C_ANY   ('.')
#define REGEX_C_BOL   ('^')
#define REGEX_C_EOL   ('$')

#define REGEX_S_WORD  (".+")
#define REGEX_S_SPAN  (".*")

/*====================================================================*
 *   variables;
 *--------------------------------------------------------------------*/

typedef struct _regexp_ 

{
	struct _regexp_ *next;
	size_t minimum;
	size_t maximum;
	bool exclude;
	char *charset;
}

regexp;

/*====================================================================*
 *   functions;
 *--------------------------------------------------------------------*/

bool regexcomp (char const * charset, char character, bool exclude);
regexp *regexmake (char const * literal);
regexp *regexfree (regexp * pattern);
char const *regexscan (const regexp * pattern, char const * literal);
char const *regexspan (const regexp * pattern, char const * literal);
char const *regexmin (const regexp * pattern, char const * literal);
char const *regexmax (const regexp * pattern, char const * literal);
void regexshow (const regexp * pattern);
void regexhelp (void);

/*====================================================================*
 *   
 *--------------------------------------------------------------------*/

#endif

