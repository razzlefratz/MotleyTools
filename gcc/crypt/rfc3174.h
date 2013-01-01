/*====================================================================*
 *
 *  crypt.h
 *
 *  Description:
 *      This is the header file for code which implements the Secure
 *      Hashing Algorithm 1 as defined in FIPS PUB 180-1 published
 *      April 17, 1995.
 *
 *      Many of the variable names in this code, especially the
 *      single character names, were used because those were the names
 *      used in the publication.
 *
 *      Please read the file crypt.c for more information.
 *
 *--------------------------------------------------------------------*/

#ifndef RFC3174_HEADER
#define RFC3174_HEADER

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#include <stdint.h>

/*
 * If you do not have the ISO standard stdint.h header file, then you
 * must typdef the following:
 *    name              meaning
 *  uint32_t         unsigned 32 bit integer
 *  uint8_t          unsigned 8 bit integer (i.e., unsigned char)
 *  int_least16_t    integer of >= 16 bits
 *
 */

/*====================================================================*
 *   constants;
 *--------------------------------------------------------------------*/

#ifndef SHA_ENUM 
#define SHA_ENUM 

enum 

{
	shaSuccess = 0,
	shaNull,
	shaInputTooLong,
	shaStateError
};


#endif

#define SHA1HashSize 20
#define SHA1_MSG_MAX 64

/*====================================================================*
 *   variables;
 *--------------------------------------------------------------------*/

/*
 *  This structure will hold context information for the SHA-1
 *  hashing operation
 */

typedef struct SHA1Context 

{

/*
 * Message Digest  
 * Message length in bits      
 * Index into message block array   
 * 512-bit message blocks      
 * Is the message digest corrupted? 
 * Is the digest computed?         
 */

	uint32_t Intermediate_Hash [SHA1HashSize/4];
	uint32_t Length_Low;
	uint32_t Length_High;
	int_least16_t Message_Block_Index;
	uint8_t Message_Block [SHA1_MSG_MAX];
	int Corrupted;
	int Computed;
}

SHA1Context;

/*====================================================================*
 *  Function Prototypes
 *--------------------------------------------------------------------*/

int SHA1Reset (SHA1Context *);
int SHA1Input (SHA1Context *, const uint8_t * message, unsigned int);
int SHA1Result (SHA1Context *, uint8_t Message_Digest [SHA1HashSize]);

/*====================================================================*
 *  
 *--------------------------------------------------------------------*/

#endif

