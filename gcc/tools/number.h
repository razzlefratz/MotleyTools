/*====================================================================*
 *
 *   number.h
 *
 *.  Motley Tools by Charles Maier
 *:  modified sun 07 sep 03 by user root on host zeus;
 *;  Licensed under the Internet Software Consortium License
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

#define RADIX_BIN 2
#define RADIX_OCT 8
#define RADIX_DEC 10
#define RADIX_HEX 16
#define RADIX_MIN 2
#define RADIX_MAX 36

#define OCTETS_BIN 8
#define OCTETS_OCT 3 
#define OCTETS_DEC 3
#define OCTETS_HEX 2

/*====================================================================*
 *   numeric conversion strings;
 *--------------------------------------------------------------------*/

#define DIGITS_BIN "01" 
#define DIGITS_OCT "01234567" 
#define DIGITS_DEC "0123456789" 
#define DIGITS_HEX "0123456789ABCDEF" 
#define DIGITS_B36 "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ" 

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

#define isodd(n)  (((n) & 1) != 0)
#define iseven(n) (((n) & 1) == 0)

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

unsigned long basespec(char const * string, unsigned base, unsigned size);
unsigned long long uintspec(char const * string, unsigned long long minimum, unsigned long long maximum);
signed long long tonumber(char const * string, signed long long minimum, signed long long maximum, signed long long nominal);
signed long long sintspec(char const * string, signed long long number);
signed totruth(char const * string);
signed todigit(unsigned c);

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

void printb(unsigned value, unsigned field, unsigned group, FILE * fp);
void printx(unsigned value, unsigned field, FILE * fp);
void printd(unsigned value, FILE * fp);
void printn(unsigned long value, unsigned field, FILE * fp);

/*====================================================================*
 *   ascii to integer convertion;
 *--------------------------------------------------------------------*/

unsigned long atoin(char const * string, char const * digits);

/*====================================================================*
 *   integer to ascii conversion;
 *--------------------------------------------------------------------*/

char * serial(char buffer[], size_t length, char c, unsigned number);
char * itosn(char buffer[], size_t length, unsigned long number, char const * digits);
char * itosm(char buffer[], size_t length, unsigned long number, char const * digits, unsigned group, char comma);

/*====================================================================*
 *   end definitions;
 *--------------------------------------------------------------------*/

#endif



