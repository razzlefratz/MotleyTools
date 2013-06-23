/*====================================================================*
 *
 *   number.h
 *
 *.  published 2003 by charles maier associates limited for internal use;
 *:  modified sun 07 sep 03 by user root on host zeus;
 *;  compiled for debian gnu/linux using gcc compiler;
 *
 *--------------------------------------------------------------------*/

#ifndef NUMBER_HEADER
#define NUMBER_HEADER
 
/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
 
/*====================================================================*
 *   numeric converson limits;
 *--------------------------------------------------------------------*/

#define RADIX_MIN 2
#define RADIX_MAX 36

#define BIN_RADIX 2
#define OCT_RADIX 8
#define DEC_RADIX 10
#define HEX_RADIX 16
 
/*====================================================================*
 *   numeric conversion strings;
 *--------------------------------------------------------------------*/

#define DIGITS_BIN "01" 
#define DIGITS_OCT "01234567" 
#define DIGITS_DEC "0123456789" 
#define DIGITS_HEX "0123456789ABCDEF" 
#define DIGITS_ALL "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ" 
 
#define BIN_OCTETS 8
#define DEC_OCTETS 3
#define OCT_OCTETS 3
#define HEX_OCTETS 2

/*====================================================================*
 *   numeric extenders;
 *--------------------------------------------------------------------*/

#define BIN_EXTENDER '-'
#define DEC_EXTENDER '.'
#define HEX_EXTENDER ':'
#define CHR_EXTENDER '.'
 
/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#define isodd(n)  (((n)&(1)) != 0)
#define iseven(n) (((n)&(1)) == 0)
 
/*====================================================================*
 *
 *--------------------------------------------------------------------*/
 
uint64_t basespec (char const * string, unsigned base, unsigned size);
uint64_t uintspec (char const * string, uint64_t minimum, uint64_t maximum);
uint64_t tonumber (char const * string, uint64_t minimum, uint64_t maximum, uint64_t nominal);
signed sintspec (char const *string, signed number);
signed totruth (char const *string, signed fail);
signed todigit (unsigned c);

/*====================================================================*
 *
 *--------------------------------------------------------------------*/
 
void printb (unsigned value, unsigned field, unsigned group, FILE *fp);
void printx (unsigned value, unsigned field, FILE *fp);
void printd (unsigned value, FILE *fp);
void printn (unsigned long value, unsigned field, FILE *fp);

/*====================================================================*
 *   ascii to integer convertion;
 *--------------------------------------------------------------------*/
 
unsigned long atoin (char const *string, char const *digits);

/*====================================================================*
 *   integer to ascii conversion;
 *--------------------------------------------------------------------*/
 
char * serial (char buffer [], size_t length, char c, unsigned number);
char *itosn (unsigned long number, char buffer [], size_t length, char const *digits);
char *itosm (unsigned long number, char buffer [], size_t length, char const *digits, size_t group, char comma);

/*====================================================================*
 *   end definitions;
 *--------------------------------------------------------------------*/

#endif
 

