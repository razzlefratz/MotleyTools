/*====================================================================*
 *
 *   strlib.h - custom string constants, structures, functions and macros;
 *
 *.  published 2003 by charles maier associates limited for internal use;
 *:  modified sun 07 sep 03 by user root on host zeus;
 *;  compiled for debian gnu/linux using gcc compiler;
 *
 *--------------------------------------------------------------------*/

#ifndef STRLIB_HEADER
#define STRLIB_HEADER

#include <unistd.h>
 
/*====================================================================*
 *  custom header files; 
 *--------------------------------------------------------------------*/

#include "../classes/types.h"
 
/*====================================================================*
 *   declare custom string function prototypes;
 *--------------------------------------------------------------------*/
 
char *strlwr (char *string);
char *strupr (char *string);
char *stresc (char *string);
char *struesc (char *string);
char *strpcat (char *target, char const *source);
char *strpcpy (char *target, char const *source);
char *strnpcat (char *target, char const *source, size_t size);
char *strnpcpy (char *target, char const *source, size_t size);
char *strcpyn (char buffer [], size_t length, char const *source, size_t count);
char *strcatn (char buffer [], size_t length, char const *source, size_t count);
size_t strrcpy (char buffer [], size_t length, char const *string);
int stricmp (char const *string1, char const *string2);
int strucmp (char const *string1, char const *string2);
int strlcmp (char const *string1, char const *string2);
int strdcmp (char const *string1, char const *string2);
int strxcmp (char const *string1, char const *string2, const unsigned char table []);
int strvercmp (char const *string1, char const *string2, unsigned c);
int strpkgcmp (char const *string1, char const *string2, unsigned c);
bool strwcmp (char const *string, char const *pattern, char const *charset);
bool ischarset (char const *string, char const *charset);
size_t strselect (char *string, char const *charset);
size_t strremove (char *string, char const *charset);
char *strcut (char *string, const unsigned c);
char *strrcut (char *string, const unsigned c);
char *strvis (char *string, char const c);
char *strend (char const *string);
char const *strpfx (char const *string, char const *prefix);
char const *strsfx (char const *string, char const *suffix);
char *strtrim (char buffer []);
char *strmin (char buffer [], char const *punct, char const *space, char const *trash);
char *strmap (char buffer [], char const *charset1, char const *charset2);
char *strcap (char buffer [], char const *charset);
char *strcrlf (char buffer [], char const *source, const int mode);
size_t strnchr (char const *string, char const *charset);
unsigned long strint (char const *string, char const *digits);
signed strcomp (char const *string1, char const *string2, unsigned char (* compare)(unsigned c));
char *strconv (char *string, unsigned char (* convert)(unsigned c));

/*====================================================================*
 *   declare custom string function prototypes;
 *--------------------------------------------------------------------*/

#define  __strlen(sp) (strchr((sp),(char)(0))-(sp))
#define  _strend(sp) (strchr((sp),(char)(0)))
#define _strtrim(sp) (strmin((sp),(char *)(0)," ",(char *)(0)))

#define  _strpcat(bp,sp)    (strchr(strcat((bp),(sp)),(char)(0)))
#define _strnpcat(bp,sp,n) (strchr(strncat((bp),(sp),(n)),(char)(0)))
#define  _strpcpy(bp,sp)    (strchr(strcpy((bp),(sp)),(char)(0)))
#define _strnpcpy(bp,sp,n) (strchr(strncpy((bp),(sp),(n)),(char)(0)))
 
/*====================================================================*
 *
 *--------------------------------------------------------------------*/
 
size_t svindex (char const *string, char const *vector [], size_t length, int (*comp)(char const *, char const *));
size_t svfirst (char const *string, char const *vector [], size_t length, int (*comp)(char const *, char const *));
size_t svfinal (char const *string, char const *vector [], size_t length, int (*comp)(char const *, char const *));
void svorder (char const *string, char const *vector [], size_t length, int (*comp)(char const *, char const *));
size_t strvsplit (char *vector [], char buffer []);
size_t strargv (size_t argc, char const *argv [], char buffer [], unsigned c);
char const **stov (char const *string, unsigned c);
size_t strsplit (char const *vector [], size_t length, char buffer [], unsigned c);
size_t strmerge (char buffer [], size_t length, char const *vector [], unsigned c);
size_t strpart (char const *vector [], char buffer [], unsigned c);
size_t strjoin (char const *vector [], char buffer [], unsigned c);

/*====================================================================*
 *
 *--------------------------------------------------------------------*/
 
char *strfield (char buffer [], char const *string, char const *charset);
size_t strfcsv (char buffer [], size_t length, char const *operands [], char const *comma, char const *quote);
size_t strfbits (char buffer [], size_t length, char const *operands [], char const *comma, flag_t flagword);
size_t strfascii (char buffer [], size_t length, unsigned c);
size_t strfcntrl (char buffer [], size_t length, unsigned c);
size_t strfglyph (char buffer [], size_t length, unsigned c);
size_t strfunix (char buffer [], size_t length, unsigned c);
size_t strfietf (char buffer [], size_t length, unsigned c);

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#if 0
#ifndef empty
#define empty(s) (((s)==(char *)(0))||(*(s)==(char)(0)))
#endif
#ifndef valid
#define valid(s) (((s!==(char *)(0))&&(*(s)=!(char)(0)))
#endif
#endif
 
/*====================================================================*
 *   end definition;
 *--------------------------------------------------------------------*/

#endif
 

