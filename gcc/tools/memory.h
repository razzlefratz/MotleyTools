/*====================================================================*
 *
 *   memory.h
 *
 *.  Motley Tools by Charles Maier
 *:  Published 2001-2009 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef MEMORY_HEADER
#define MEMORY_HEADER

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/types.h"

/*====================================================================*
 *   lazy man's structure allocation;
 *--------------------------------------------------------------------*/

#define NEW(object) (object *)(emalloc(sizeof(object)))
#define BUF(object) (byte *)(emalloc(sizeof(object)))
#define MEM(length) (unsigned char *)(emalloc(sizeof(char)*(length+0)))
#define STR(length) (char *)(emalloc(sizeof(char)*(length+1)))
#define LST(object, length) (object*)(emalloc(sizeof(object)*(length)))

/*====================================================================*
 *  
 *--------------------------------------------------------------------*/

#ifndef offset
#define offset(struct, member) (signed)(&struct.member)-(signed)(&struct)
#endif

/*====================================================================*
 *  header strings for memory dump functions;
 *--------------------------------------------------------------------*/

#define REGDUMP_HEADER "REGISTER CONTENTS 31----24 23----16 15----08 07----00\n"
#define HEXDUMP_HEADER "-------- 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F ----------------\n"

/*====================================================================*
 *  
 *--------------------------------------------------------------------*/

#define IPv4_LEN 4
#define IPv6_LEN 16

/*====================================================================*
 *   variables;
 *--------------------------------------------------------------------*/

typedef struct field 

{
	signed type;
	void * base;
	size_t size;
}

FIELD;

/*====================================================================*
 *   memory allocation functions (also declared in error.h);
 *--------------------------------------------------------------------*/

void *emalloc (size_t extent);
void *erealloc (void * memory, size_t extent);

/*====================================================================*
 *   memory increment/decrement functions;
 *--------------------------------------------------------------------*/

void reverse (void * memory, size_t extent);
void memwrap (void * memory, size_t extent, ssize_t offset);
void memswap (void *, void *, size_t extent);
void memcopy (void *, void const *, size_t extent);
void memfold (void *, void const *, size_t extent);
signed strincr (void * memory, size_t extent, byte min, byte max);
signed strdecr (void * memory, size_t extent, byte min, byte max);
signed memincr (void * memory, size_t extent);
signed memdecr (void * memory, size_t extent);

/*====================================================================*
 *   memory validation functions;
 *--------------------------------------------------------------------*/

uint16_t checksum16 (void const * memory, size_t extent, uint16_t checksum);
uint32_t checksum32 (void const * memory, size_t extent, uint32_t checksum);
uint16_t fdchecksum16 (int fd, size_t extent, uint16_t checksum);
uint32_t fdchecksum32 (int fd, size_t extent, uint32_t checksum);

/*====================================================================*
 *   memory encode functions;
 *--------------------------------------------------------------------*/

size_t decencode (void * memory, size_t extent, char const * string);
size_t hexencode (void * memory, size_t extent, char const * string);
size_t binencode (void * memory, size_t extent, char const * string);
size_t numencode (void * memory, size_t extent, char const * string, unsigned radix, unsigned comma);
size_t memencode (void * memory, size_t extent, char const * type, char const * data);

/*====================================================================*
 *   memory decode functions;
 *--------------------------------------------------------------------*/

size_t enhex (char buffer [], size_t length, void const * memory, size_t extent);
size_t dehex (char const buffer [], size_t length, void * memory, size_t extent);
size_t decdecode (void const * memory, size_t extent, char buffer [], size_t length);
size_t hexdecode (void const * memory, size_t extent, char buffer [], size_t length);
size_t bindecode (void const * memory, size_t extent, char buffer [], size_t length);
char * decstring (char buffer [], size_t length, const byte memory [], size_t extent);
char * hexstring (char buffer [], size_t length, const byte memory [], size_t extent);
char * binstring (char buffer [], size_t length, const byte memory [], size_t extent);
char * hexoffset (char buffer [], size_t length, off_t offset);

/*====================================================================*
 *   memory input functions;
 *--------------------------------------------------------------------*/

size_t hexread (signed fd, void * memory, size_t extent);
size_t hexload (void * memory, size_t extent, FILE * fp);
void hexwrite (signed fd, void const * memory, size_t extent, size_t column);
size_t gather (void * memory, size_t extent, struct field const *, unsigned fields);
size_t scatter (void const * memory, size_t extent, struct field const *, unsigned fields);

/*====================================================================*
 *   memory print functions;
 *--------------------------------------------------------------------*/

void hexout (void const * memory, size_t extent, char c, char e, FILE * fp);
void binout (void const * memory, size_t extent, char c, char e, FILE * fp);
void decout (void const * memory, size_t extent, char c, char e, FILE * fp);
void chrout (void const * memory, size_t extent, char c, char e, FILE * fp);
void bindump (void const * memory, size_t offset, size_t extent, FILE * fp);
void hexdump (void const * memory, size_t offset, size_t extent, FILE * fp);
void hexview (void const * memory, size_t offset, size_t extent, FILE * fp);
void regview (void const * memory, size_t offset, size_t extent, FILE * fp);
void hexsave (void const * memory, size_t extent, size_t column, FILE * fp);
void hexpeek (void const * memory, size_t origin, size_t offset, size_t extent, size_t window, FILE * fp);

/*====================================================================*
 *   network address functions; 
 *--------------------------------------------------------------------*/

size_t dataspec (char const * string, void * memory, size_t extent);
size_t bytespec (char const * string, void * memory, size_t extent);
size_t ipv4spec (char const * string, byte memory []);
size_t ipv6spec (char const * string, byte memory []);

/*====================================================================*
 *   
 *--------------------------------------------------------------------*/

signed fdputc (signed fd, signed c);
signed fdgetc (signed fd);

/*====================================================================*
 *   end definitions;
 *--------------------------------------------------------------------*/

#endif

