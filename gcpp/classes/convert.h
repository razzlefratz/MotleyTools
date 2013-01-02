/*====================================================================*
 *
 *   convert.h
 *
 *.  published 2003 by charles maier associates limited for internal use;
 *:  modified sun 07 sep 03 by user root on host zeus;
 *;  compiled for debian gnu/linux using gcc compiler;
 *
 *--------------------------------------------------------------------*/

#ifndef CONVERT_HEADER
#define CONVERT_HEADER
 
/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
 
/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/tools.h"
 
/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#define DIGITS_BIN "01" 
#define DIGITS_OCT "01234567" 
#define DIGITS_DEC "0123456789" 
#define DIGITS_HEX "0123456789ABCDEF" 
#define DIGITS_RADIX "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ" 

#define BIN_EXTENDER ' '
#define DEC_EXTENDER '.'
#define HEX_EXTENDER ':'
 
/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#define BYTE_MAX 0xFF
#define NIBBLE_MAX 0x0F
#define RADIX_MIN 2
#define RADIX_MAX 36
 
/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#define isodd(n)  (((n)&(1)) != 0)
#define iseven(n) (((n)&(1)) == 0)
 
/*====================================================================*
 *
 *--------------------------------------------------------------------*/
 
char const *symbol (signed number, struct _code_ list [], size_t size);
signed equate (char const *string, struct _code_ list [], size_t size, signed fail);
unsigned number (char const *string, unsigned minimum, unsigned maximum, unsigned nominal);
signed truth (char const *string, signed fail);
int ivalue (void *bp, int get (void *bp), int unget (int c, void *bp));

/*====================================================================*
 *
 *--------------------------------------------------------------------*/
 
signed decencode (uint8_t memory [], size_t length, char const *string);
signed hexencode (uint8_t memory [], size_t length, char const *string);
size_t decdecode (const uint8_t memory [], size_t length, char buffer [], size_t chars);
size_t hexdecode (const uint8_t memory [], size_t length, char buffer [], size_t chars);
void hexdump (const uint8_t memory [], size_t length, FILE *fp);
size_t hexin (uint8_t memory [], size_t length, FILE *fp);
void hexout (const uint8_t memory [], size_t length, unsigned c, FILE *fp);
void binout (const uint8_t memory [], size_t length, unsigned c, FILE *fp);

/*====================================================================*
 *
 *--------------------------------------------------------------------*/
 
char *unixencode (char const *string, char *buffer, size_t length);
char *ietfencode (char const *string, char *buffer, size_t length);
char *unixdecode (char *string);
char *ietfdecode (char *string);

/*====================================================================*
 *
 *--------------------------------------------------------------------*/
 
void printb (unsigned value, unsigned short field, unsigned short group);
void printx (unsigned value, unsigned short field);
void printd (signed value);
void printn (unsigned long value, unsigned short field);

/*====================================================================*
 *   ascii to integer convertion;
 *--------------------------------------------------------------------*/
 
unsigned long atoin (char const *string, char const *digits);

/*====================================================================*
 *   integer to ascii conversion;
 *--------------------------------------------------------------------*/
 
char *serial (char buffer [], size_t length, unsigned char c, unsigned number);
char *itosn (unsigned long number, char buffer [], size_t length, char const *digits);
char *itosm (unsigned long number, char buffer [], size_t length, char const *digits, size_t group, char comma);

/*====================================================================*
 *   end definitions;
 *--------------------------------------------------------------------*/

#endif
 

